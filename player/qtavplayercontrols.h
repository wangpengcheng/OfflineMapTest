#ifndef QTAVPLAYERCONTROLS_H
#define QTAVPLAYERCONTROLS_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          qtavplaycontrols.h
** @brief         QtAVPlayerControls 类主要与ReviewWidget相结合，控制播放
** @details       有通过相关信号和槽，实现进度条控制等功能
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:44:14
** @example
**
** 示例代码
**
*****************************************************************************/
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
    void setState(QtAV::AVPlayer::State state);                 //当前播放状态
    void setVolume(qreal volume);                               //播放音量
    void setMuted(bool muted);                                  //是否静音
    void setPlaybackRate(float rate);                           //初始化播放速度选框

signals:
    void play();                                                //播放
    void pause();                                               //暂停
    void stop();                                                //停止
    void next();                                                //ToDo 播放下一个
    void previous();                                            //ToDo 播放上一个
    void changeVolume(int volume);                              //设置音量
    void changeMuting(bool muting);
    void changeRate(qreal rate);

private slots:
    void playClicked();                                         //播放按钮点击事件
    void muteClicked();                                         //静音按钮
    void updateRate();                                          //更新播放速度显示
    void onVolumeSliderValueChanged();                          //音量控制函数

private:
    QtAV::AVPlayer::State m_playerState = QtAV::AVPlayer::State::StoppedState; //记录播放器的状态，改成多播放器后没什么用，只用来记录第一个的状态
    bool m_playerMuted = false;
    QAbstractButton *m_playButton = nullptr;                    //播放按钮
    QAbstractButton *m_stopButton = nullptr;                    //停止按钮
    QAbstractButton *m_nextButton = nullptr;                    //播放下一个
    QAbstractButton *m_previousButton = nullptr;                //播放前一个
    QAbstractButton *m_muteButton = nullptr;                    //声音按钮
    QAbstractSlider *m_volumeSlider = nullptr;                  //声音滑块
    QComboBox *m_rateBox = nullptr;                             //播放速度模块
};
#endif // QTAVPLAYERCONTROLS_H
