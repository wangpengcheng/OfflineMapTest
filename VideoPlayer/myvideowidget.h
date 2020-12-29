/**
 * @file myvideowidget.h
 * @brief MyVideoWidget类的头文件
 * @details 将Qt播放列表重新封装一次，便于后期的使用和布局，将其封装为类似HTML video的易于使用的类
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-04-03 19:09:57
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
 *    <td> 2019-04-03 19:09:57 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完成类的基本功能 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 21:17:09 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 * @example myvideowidget.h
 * 显示基本信息和内容
 * 
 * @code{.cpp}
 *    QString video_path=QString("C:/Users/lin/Videos/Captures/minieyeone.mp4");
 *    MyVideoWidget test(QUrl::fromLocalFile(video_path));
 *    test.resize(400,300);
 *    test.show();
 *    test.VideoPlay();
 * @endcode
 */
#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>
#include <QVBoxLayout>
#include <QVideoEncoderSettingsControl>
/**
 * @brief 将Qt播放列表重新封装一次，便于后期的使用和布局，将其封装为类似HTML video的易于使用的类
 */
class MyVideoWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new My Video Widget object
     * @param  parent           父节点数据指针
     */
    explicit MyVideoWidget(QWidget *parent = nullptr);
    /**
     * @brief Construct a new My Video Widget object
     * @param  video_file_path  视频文件位置
     */
    MyVideoWidget(QUrl video_file_path);
    /**
     * @brief Destroy the My Video Widget object
     */
    ~MyVideoWidget();
    //基本存取函数
    inline QMediaPlayer *media_player() { return media_player_; }
    inline void set_media_player(QMediaPlayer *media_player) { media_player_ = media_player; }
    inline QVideoWidget *video_widget() { return video_widget_; }
    inline void set_video_widget(QVideoWidget *video_widget) { video_widget_ = video_widget; }
    inline QMediaPlaylist *play_list() { return play_list_; }
    inline void set_play_list(QMediaPlaylist *play_list) { play_list_ = play_list; }
    inline QUrl play_file_path() { return play_file_path_; }
    inline void set_play_file_path(QUrl new_path) { play_file_path_ = new_path; }
    /**
     * @brief 初始化相关函数
     */
    void Init();
    /**
     * @brief 播放函数
     */
    void VideoPlay();
    /**
     * @brief 暂停
     */
    void VideoPause();
    /**
     * @brief 播放停止
     */
    void VideoStop();

private:
    QMediaPlayer *media_player_ = nullptr; ///< 对应的视频媒体管理器，主要是管理播放列表
    QVideoWidget *video_widget_ = nullptr; ///< 对应的video显示Widget
    QMediaPlaylist *play_list_ = nullptr;  ///< 媒体列表类，主要是抽象播放列表，相关操作
    QVBoxLayout *video_layout_ = nullptr;  ///< 显示界面的外围水平封装类
    QUrl play_file_path_;                  ///< 视频文件位置，主要是回放的时候进行使用
};

#endif // MYVIDEOWIDGET_H
