/**
 * @file qtavvideowidget.h
 * @brief qtavvideowidget 类的头文件 
 * @details 主要实现播放类的封装成widget \n
 * QT Version    5.11.1-5.12.3
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-06-27 10:50:46
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
 *    <td> 2019-06-27 10:50:46 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 21:24:03 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#ifndef QTAVVIDEOWIDGET_H
#define QTAVVIDEOWIDGET_H

#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QWidget>
#include <QHBoxLayout>
#include <QtAV/QtAV.h>
#include "QtAVWidgets/QtAVWidgets.h"

/**
 * @brief QtAV显示视频Widget相关文件
 */
class QtAVVideoWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Qt A V Video Widget object
     * @param  parent           父指针
     */
    explicit QtAVVideoWidget(QWidget *parent = nullptr);
    /**
     * @brief Construct a new Qt A V Video Widget object
     * @param  new_player       QtAVPlayer的数据指针
     * @param  new_vid          vid类型
     */
    QtAVVideoWidget(QSharedPointer<QtAV::AVPlayer> new_player, QString new_vid = "gl");
    /**
     * @brief 拷贝构造函数
     */
    QtAVVideoWidget(const QtAVVideoWidget &);
    /**
     * @brief Destroy the QtAVVideo Widget object
     */
    ~QtAVVideoWidget();
    //基本的存取函数
    inline QSharedPointer<QtAV::AVPlayer> av_player() { return av_player_; }
    //inline void set_av_player(QSharedPointer<QtAV::AVPlayer*> new_player){av_player_=new_player;}
    inline QtAV::VideoRenderer *video_render() { return video_render_; }
    //inline void set_video_render(QtAV::VideoRenderer* new_render){video_render_=new_render;}
    /**
     * @brief  是否正在播放
     * @return true  正在播放
     * @return false 没有
     */
    inline bool is_play() { return is_play_; }
    /**
     * @brief 更改渲染器函数
     * @param  new_render       新的渲染播放器
     */
    void ChangeVideoRender(QtAV::VideoRenderer *new_render);
    /**
     * @brief 更改播放器函数
     * @param  new_player   更改播放器函数
     */
    void ChangeAVPlayer(QSharedPointer<QtAV::AVPlayer> new_player);

    /**
     * @brief 初始化函数
     */
    void Init();
    /**
     * @brief 播放视频
     */
    void VideoPlay();
    /**
     * @brief 暂停视频
     */
    void VideoPause();

private:
    QSharedPointer<QtAV::AVPlayer> av_player_;    ///< 指向播放器的指针
    QtAV::VideoRenderer *video_render_ = nullptr; ///< 渲染器
    QHBoxLayout *video_layer_out_ = nullptr;      ///< 视频显示布局
    QString vid = "wg";                           ///< 显示的渲染方式,默认使用wg渲染；注意如果要与OpenGL或者QML一起使用，必须选择wg模式。
    bool is_play_ = false;                        ///< 记录是否正在播放状态
};

#endif // QTAVVIDEOWIDGET_H
