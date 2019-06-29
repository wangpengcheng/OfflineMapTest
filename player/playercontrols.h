#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          playercontrols.h
** @brief         控制播放类文件
** @details       player类中的重要控制播放文件类，已经弃用
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:37:48
** @example
**
** 示例代码
**
*****************************************************************************/

#include <QMediaPlayer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControls(QWidget *parent = nullptr);

    QMediaPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
    qreal playbackRate() const;

public slots:
    void setState(QMediaPlayer::State state);
    void setVolume(int volume);
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
    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
    bool m_playerMuted = false;
    QAbstractButton *m_playButton = nullptr;//播放按钮
    QAbstractButton *m_stopButton = nullptr;//停止按钮
    QAbstractButton *m_nextButton = nullptr;//播放下一个
    QAbstractButton *m_previousButton = nullptr;//播放前一个
    QAbstractButton *m_muteButton = nullptr;//声音按钮
    QAbstractSlider *m_volumeSlider = nullptr;//声音滑块
    QComboBox *m_rateBox = nullptr;//播放速度
};

#endif // PLAYERCONTROLS_H
