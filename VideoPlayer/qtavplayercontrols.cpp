#include "qtavplayercontrols.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>

QtAVPlayerControls::QtAVPlayerControls(QWidget *parent)
    : QWidget(parent)
{
    m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked, this, &QtAVPlayerControls::playClicked);

    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setEnabled(false);

    connect(m_stopButton, &QAbstractButton::clicked, this, &QtAVPlayerControls::stop);

    m_nextButton = new QToolButton(this);
    m_nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    connect(m_nextButton, &QAbstractButton::clicked, this, &QtAVPlayerControls::next);

    m_previousButton = new QToolButton(this);
    m_previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    connect(m_previousButton, &QAbstractButton::clicked, this, &QtAVPlayerControls::previous);

    m_muteButton = new QToolButton(this);
    m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    connect(m_muteButton, &QAbstractButton::clicked, this, &QtAVPlayerControls::muteClicked);

    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);

    connect(m_volumeSlider, &QSlider::valueChanged, this, &QtAVPlayerControls::onVolumeSliderValueChanged);

    m_rateBox = new QComboBox(this);
    m_rateBox->addItem("0.5x", QVariant(0.5));
    m_rateBox->addItem("1.0x", QVariant(1.0));
    m_rateBox->addItem("2.0x", QVariant(2.0));
    m_rateBox->setCurrentIndex(1);

    connect(m_rateBox, QOverload<int>::of(&QComboBox::activated), this, &QtAVPlayerControls::updateRate);

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_previousButton);
    layout->addWidget(m_playButton);
    layout->addWidget(m_nextButton);
    layout->addWidget(m_muteButton);
    layout->addWidget(m_volumeSlider);
    layout->addWidget(m_rateBox);
    setLayout(layout);
}
QtAV::AVPlayer::State QtAVPlayerControls::state() const
{
    return m_playerState;
}

void QtAVPlayerControls::setState(QtAV::AVPlayer::State state)
{
    if (state != m_playerState)
    {
        m_playerState = state;
        switch (state)
        {
        case QtAV::AVPlayer::State::StoppedState:
            m_stopButton->setEnabled(false);
            m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QtAV::AVPlayer::State::PlayingState:
            m_stopButton->setEnabled(true);
            m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QtAV::AVPlayer::State::PausedState:
            m_stopButton->setEnabled(true);
            m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

int QtAVPlayerControls::volume() const
{
    qreal linearVolume = QAudio::convertVolume(m_volumeSlider->value() / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
}

void QtAVPlayerControls::setVolume(qreal volume)
{

    qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100),
                                                    QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    m_volumeSlider->setValue(qRound(logarithmicVolume * 100));
}

bool QtAVPlayerControls::isMuted() const
{
    return m_playerMuted;
}

void QtAVPlayerControls::setMuted(bool muted)
{
    if (muted != m_playerMuted)
    {
        m_playerMuted = muted;

        m_muteButton->setIcon(style()->standardIcon(muted
                                                        ? QStyle::SP_MediaVolumeMuted
                                                        : QStyle::SP_MediaVolume));
    }
}

void QtAVPlayerControls::playClicked()
{
    qDebug() << m_playerState;
    switch (m_playerState)
    {
    case QtAV::AVPlayer::State::StoppedState:
    case QtAV::AVPlayer::State::PausedState:
        qDebug() << "send start";
        emit play();
        break;
    case QtAV::AVPlayer::State::PlayingState:
        emit pause();
        qDebug() << "send pause";
        break;
    }
}

void QtAVPlayerControls::muteClicked()
{
    emit changeMuting(!m_playerMuted);
}

qreal QtAVPlayerControls::playbackRate() const
{
    return m_rateBox->itemData(m_rateBox->currentIndex()).toDouble();
}

void QtAVPlayerControls::setPlaybackRate(float rate)
{
    for (int i = 0; i < m_rateBox->count(); ++i)
    {
        if (qFuzzyCompare(rate, float(m_rateBox->itemData(i).toDouble())))
        {
            m_rateBox->setCurrentIndex(i);
            return;
        }
    }

    m_rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
    m_rateBox->setCurrentIndex(m_rateBox->count() - 1);
}

void QtAVPlayerControls::updateRate()
{
    emit changeRate(playbackRate());
}

void QtAVPlayerControls::onVolumeSliderValueChanged()
{
    emit changeVolume(volume());
}
