#ifndef QTAVPLAYERCONTROLS_H
#define QTAVPLAYERCONTROLS_H

#include <QWidget>
#include <QMediaPlayer>
#include "QtAV/AVPlayer.h"
QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class QtAVPlayerControls: public QWidget
{
    Q_OBJECT

public:
    explicit QtAVPlayerControls(QWidget *parent = nullptr);
    //记录当前的播放状态
    QtAV::AVPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
    qreal playbackRate() const;

public slots:
    void setState(QtAV::AVPlayer::State state);
    void setVolume(qreal volume);
    void setMuted(bool muted);
    void setPlaybackRate(float rate);

signals:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void changeVolume(int volume);
    void changeMuting(bool muting);
    void changeRate(qreal rate);

private slots:
    void playClicked();
    void muteClicked();
    void updateRate();
    void onVolumeSliderValueChanged();

private:
    QtAV::AVPlayer::State m_playerState = QtAV::AVPlayer::State::StoppedState;
    bool m_playerMuted = false;
    QAbstractButton *m_playButton = nullptr;//播放按钮
    QAbstractButton *m_stopButton = nullptr;//停止按钮
    QAbstractButton *m_nextButton = nullptr;//播放下一个
    QAbstractButton *m_previousButton = nullptr;//播放前一个
    QAbstractButton *m_muteButton = nullptr;//声音按钮
    QAbstractSlider *m_volumeSlider = nullptr;//声音滑块
    QComboBox *m_rateBox = nullptr;//播放速度模块
};
#endif // QTAVPLAYERCONTROLS_H
