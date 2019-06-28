#include "qtavtest.h"

using namespace QtAV;
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>

QtAVTest::QtAVTest(QWidget *parent) : QWidget(parent)
{
    m_unit = 1000;
    setWindowTitle(QString::fromLatin1("QtAV simple player example"));
        m_player = new AVPlayer(this);
        QVBoxLayout *vl = new QVBoxLayout();
        setLayout(vl);
        m_vo = new VideoOutput(this);
        if (!m_vo->widget()) {
            QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
            return;
        }
        m_player->setRenderer(m_vo);
        vl->addWidget(m_vo->widget());
        m_slider = new QSlider();
        m_slider->setOrientation(Qt::Horizontal);
        connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
        connect(m_slider, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
        connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
        connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
        connect(m_player, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));

        vl->addWidget(m_slider);
        QHBoxLayout *hb = new QHBoxLayout();
        vl->addLayout(hb);
        m_openBtn = new QPushButton(tr("Open"));
        m_playBtn = new QPushButton(tr("Play/Pause"));
        m_stopBtn = new QPushButton(tr("Stop"));
        hb->addWidget(m_openBtn);
        hb->addWidget(m_playBtn);
        hb->addWidget(m_stopBtn);
        connect(m_openBtn, SIGNAL(clicked()), SLOT(openMedia()));
        connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
        connect(m_stopBtn, SIGNAL(clicked()), m_player, SLOT(stop()));
}

void QtAVTest::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, tr("Open a video"));
    qDebug()<<"---------------:"<<file;
    if (file.isEmpty())
        return;
    m_player->play(file);
}

void QtAVTest::seekBySlider(int value)
{
    if (!m_player->isPlaying())
        return;
    m_player->seek(qint64(value*m_unit));
}

void QtAVTest::seekBySlider()
{
    seekBySlider(m_slider->value());
}

void QtAVTest::playPause()
{
    if (!m_player->isPlaying()) {
        m_player->play();
        return;
    }
    m_player->pause(!m_player->isPaused());
}

void QtAVTest::updateSlider(qint64 value)
{
    m_slider->setRange(0, int(m_player->duration()/m_unit));
    m_slider->setValue(int(value/m_unit));
}

void QtAVTest::updateSlider()
{
    updateSlider(m_player->position());
}

void QtAVTest::updateSliderUnit()
{
    m_unit = m_player->notifyInterval();
    updateSlider();
}
