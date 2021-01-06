/**
 * @file streamvideowidget.h
 * @brief StreamVideoWidget类头文件；主要是接收网络流
 * @details       接收Videodecodethrea的Image信号槽函数 \n
 *  QT Version    5.11.3
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-04-22 15:58:52
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
 *    <td> 2019-04-22 15:58:52 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成类的基本内容 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 21:34:39 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef STREAMVIDEOWIDGET_H
#define STREAMVIDEOWIDGET_H

#include "videodecodethread.h"

#include <QWidget>
#include <QMainWindow>
#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QtDebug>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QSharedPointer>
#include <QPaintEvent>
#include <QPainter>

/**
 * @brief 视频直播流时的显示类，主要用户综合模式和监看模式下的，视频实时显示
 * @details StreamVideoWidget 和VideoDecodeThread 相互配合使用，一个VideoDecodeThread只能 \n
 * 对应一个VideoDecodeThread 但是，一个VideoDecodeThread可以对应多个StreamVideoWidget
 */
class StreamVideoWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Stream Video Widget object
     * @param  parent           父指针
     */
    explicit StreamVideoWidget(QWidget *parent = nullptr);
    /**
     * @brief 直接用解码线程初始化构造函数
     * @param  new_decode       解码线程智能指针
     */
    StreamVideoWidget(QSharedPointer<VideoDecodeThread> new_decode);
    /**
     * @brief Destroy the Stream Video Widget object
     */
    ~StreamVideoWidget() = default;
    /**
     * @brief Set the decode thread object
     * @param  new_decode       解码线程
     */
    void set_decode_thread(QSharedPointer<VideoDecodeThread> new_decode);
    /**
     * @brief  获取解码线程
     * @return QSharedPointer<VideoDecodeThread> 
     */
    inline QSharedPointer<VideoDecodeThread> decode_thread() { return decode_thread_; }
    /**
     * @brief 是否正在播放
     * @return true 是
     * @return false 否
     */
    inline bool is_play() { return is_play_; }
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

protected:
    /**
     * @brief 重载事件绘制函数，主要用来更新界面
     * @param  event         动作事件
     */
    void paintEvent(QPaintEvent *event);
    QImage display_image; ///< 当前显示的图像
private slots:
    /**
     * @brief  帧图像处理函数
     * @param  show_img       收到的图像
     */
    void slot_get_frame(QImage show_img);

private:
    QSharedPointer<VideoDecodeThread> decode_thread_ = nullptr; ///< 解码线程指针
    bool is_play_ = false;                                      ///< 记录状态是否有画面播放
};

#endif // STREAMVIDEOWIDGET_H
