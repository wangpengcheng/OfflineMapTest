/**
 * 
 * @file qtavplayercontrols.h
 * @brief QtAVPlayerControls 类主要与ReviewWidget相结合，控制播放
 * @details QtAVPlayerControls 类主要与ReviewWidget相结合，控制播放 \n 
 * 有通过相关信号和槽，实现进度条控制等功能
 * \n  QT Version    5.11.1-5.12.3
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-06-29 18:44:14
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2019-06-29 18:44:14 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完善类的基本内容 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 01:26:47 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#ifndef QTAVPLAYERCONTROLS_H
#define QTAVPLAYERCONTROLS_H

#include "QtAV/AVPlayer.h"

#include <QWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE
/**
 * @brief QtAVPlayerControls 类主要与ReviewWidget相结合，控制播放
 */
class QtAVPlayerControls : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief QtAVPlayerControls 基本构造函数
     * @param  parent        父类指针
     */
    explicit QtAVPlayerControls(QWidget *parent = nullptr);
    /**
     * @brief 记录当前的播放状态 
     * @return QtAV::AVPlayer::State 播放状态常数
     */
    QtAV::AVPlayer::State state() const;
    /**
     * @brief 播放音量
     * @return int 播放的音量值
     */
    int volume() const;
    /**
     * @brief 是否静音
     * @return true     静音
     * @return false    不静音
     */
    bool isMuted() const;
    /**
     * @brief  播放速度选框值
     * @return qreal 播放速度
     */
    qreal playbackRate() const;

public slots:
    /**
     * @brief 设置当前播放状态
     * @param  state            播放状态
     */
    void setState(QtAV::AVPlayer::State state);
    /**
     * @brief 设置播放音量
     * @param  volume          播放音量
     */
    void setVolume(qreal volume);
    /**
     * @brief 设置是否静音
     * @param  muted      是否静音
     */
    void setMuted(bool muted);
    /**
     * @brief 设置播放速度
     * @param  rate      播放速度
     */
    void setPlaybackRate(float rate);

signals:
    /**
     * @brief 播放
     */
    void play();
    /**
     * @brief 暂停
     */
    void pause();
    /**
     * @brief 停止
     */
    void stop();
    /**
     * @brief 播放下一个
     * @todo  实现功能 
     */
    void next();
    /**
     * @brief 播放上一个
     * @todo  实现功能 
     */
    void previous();
    /**
     * @brief 设置音量
     * @param  volume       音量
     */
    void changeVolume(int volume);
    /**
     * @brief 设置是否静音
     * @param  muting          是否静音
     */
    void changeMuting(bool muting);
    /**
     * @brief 更改播放速度
     * @param  rate            播放速度
     */
    void changeRate(qreal rate);

private slots:
    /**
     * @brief 播放按钮点击事件
     */
    void playClicked();
    /**
     * @brief 静音按钮
     */
    void muteClicked();
    /**
     * @brief 更新播放速度显示
     */
    void updateRate();
    /**
     * @brief 音量控制函数
     */
    void onVolumeSliderValueChanged();

private:
    QtAV::AVPlayer::State m_playerState = QtAV::AVPlayer::State::StoppedState; ///< 记录播放器的状态，改成多播放器后没什么用，只用来记录第一个的状态
    bool m_playerMuted = false;                                                ///< 是否静音
    QAbstractButton *m_playButton = nullptr;                                   ///< 播放按钮
    QAbstractButton *m_stopButton = nullptr;                                   ///< 停止按钮
    QAbstractButton *m_nextButton = nullptr;                                   ///< 播放下一个
    QAbstractButton *m_previousButton = nullptr;                               ///< 播放前一个
    QAbstractButton *m_muteButton = nullptr;                                   ///< 声音按钮
    QAbstractSlider *m_volumeSlider = nullptr;                                 ///< 声音滑块
    QComboBox *m_rateBox = nullptr;                                            ///< 播放速度模块
};
#endif // QTAVPLAYERCONTROLS_H
