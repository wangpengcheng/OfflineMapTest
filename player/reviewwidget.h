/**
 * @file reviewwidget.h
 * @brief 视频回放相关类接口
 * @details 视频回放相关类接口
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 01:39:24
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
 *    <td> 2020-12-29 01:39:24 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档内容 </td>
 * </tr>
 * </table>
 */
#ifndef REVIEWWIDGET_H
#define REVIEWWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QStatusBar;
class QVideoProbe;
class VideoWidget;
class QAudioProbe;
class VideoWidget;
#include <QGeoCoordinate>
#include <QVideoWidget>
#include <QQuickView>
#include <QLabel>
#include "VideoControl/recordselectdialog.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "VideoControl/qtavvideowidget.h"
#include "VideoControl/videoshowwidget.h"
#include "QtAV/AVPlayer.h"
#include <QtLocation/private/qdeclarativegeomap_p.h>

/**
 * @brief 设置添加地图控制,当开启此声明时，回放也可以进行地图控制和缩放
 */
#define ADD_MAP_CONTROL
QT_END_NAMESPACE

namespace Ui
{
    class ReviewWidget;
}
/**
 * @brief 地图回放UI类，主要是对地图和视频回放组件的封装
 */
class ReviewWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Review Widget object
     * @param  parent           父类指针
     */
    explicit ReviewWidget(QWidget *parent = nullptr);
    ~ReviewWidget();
    /**
     * @brief Get the Plyer object
     * @return QtAV::AVPlayer* QtAV指导对象
     */
    inline QtAV::AVPlayer *GetPlyer() { return m_player; }
    /**
     * @brief 设置显示界面对象，主要是为了在回放时，也可以进行多屏分割和控制
     * @return VideoShowWidget<QLabel>* 
     */
    inline VideoShowWidget<QLabel> *video_choose_widget() { return video_choose_widgets; }
    /**
     * @brief  视频播放对象列表
     * @return QList<QSharedPointer<QtAV::AVPlayer>> 
     */
    inline QList<QSharedPointer<QtAV::AVPlayer>> player_list() { return m_player_list_; }
#ifdef ADD_MAP_CONTROL
    /**
     * @brief  获取回放地图指针
     * @return std::shared_ptr<QDeclarativeGeoMap> 回放时的地图指针
     */
    inline std::shared_ptr<QDeclarativeGeoMap> re_view_control_map() { return re_view_control_map_; }
#endif
    /**
     * @brief 初始化相关变量
     * @todo 完善基本功能
     */
    void Init();
    /**
     * @brief 连接视频反馈
     */
    void SetPlayConnect();
    /**
     * @brief 断开视频反馈
     */
    void CancelPlayConnect();
    /**
     * @brief 添加播放列表
     * @param  message          播放列表消息框
     */
    void addToPlaylist(const MainSendMessage &message);
    /**
     * @brief 是否播放器存在 
     * @return true 存在
     * @return false 不存在
     */
    bool isPlayerAvailable() const;

signals:
    /**
     * @brief 信号函数--是否全屏
     * @param  fullScreen       是否全屏
     */
    void fullScreenChanged(bool fullScreen);
    /**
     * @brief 发送位置信息
     */
    void SendQGeoCoordinate(QGeoCoordinate);
    /**
     * @brief 发送当前选中的QLabel关键信息
     * @param  label_id         label对应的编号
     */
    void SendLabelId(QString label_id);
    /**
     * @brief 发送视频连接改变信息,主要是点击时的连接操作
     * @param  av_player_index  播放器编号
     * @param  show_widget_index 显示label编号索引
     */
    void SendConnect(int av_player_index, int show_widget_index);

protected:
    /**
     * @brief 鼠标点击事件判断 
     * @param  obj             对象指针
     * @param  event           响应事件
     * @return true            设置成功
     * @return false           设置失败
     */
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    /**
     * @brief 槽函数--播放
     */
    void play();
    /**
     * @brief 槽函数--暂停
     */
    void pause();
    /**
     * @brief 槽函数--停止
     */
    void stop();
    /**
     * @brief 更改播放速度
     * @param  speed            播放速度值
     */
    void setSpeed(qreal speed);
    /**
     * @brief 开启查询窗口,主要是打开查询界面，开启查询历史记录功能
     */
    void open();
    /**
     * @brief 最后时间更改
     * @param  duration         更改时间戳
     */
    void durationChanged(qint64 duration);
    /**
     * @brief 位置坐标更改
     * @param  progress         位置更改
     */
    void positionChanged(qint64 progress);
    /**
     * @brief  基础元数据更改
     */
    void metaDataChanged();
    /**
     * @brief 上一个按钮点击事件
     */
    void previousClicked();
    /**
     * @brief 进度条点击事件，主要是进行播放控制
     * @param  seconds          播放秒数
     */
    void seek(int seconds);
    /**
     * @brief 进度条跳跃更改事件
     * @param  index           选项
     */
    void jump(const QModelIndex &index);
    /**
     * @brief 播放列表位置更改事件
     */
    void playlistPositionChanged(int);
    /**
     * @brief 媒体更改，主要是对所有播放视频一起更改
     * @param  status           设置的新的播放状态
     */
    void statusChanged(QtAV::MediaStatus status);
    /**
     * @brief 播放状态更改，主要是对所有播放视频一起更改
     * @param  state            My Param doc
     */
    void stateChanged(QtAV::AVPlayer::State state);
    /**
     * @brief 缓冲处理区间，主要是读取进度条
     * @param  progress         处理值
     */
    void bufferingProgress(int progress);
    /**
     * @brief 视频存在播放修改，当布局更改是，某些窗口被隐藏，此时不必再进行图像渲染
     * @param  available        是否存在
     */
    void videoAvailableChanged(bool available);
    /**
     * @brief 显示错误信息
     */
    void displayErrorMessage();
    /**
     * @brief 从数据库中，获取信息列表
     * @param  record_id        历史记录Id
     */
    void InitQGeoCoordinates(int record_id);
    /**
     * @brief  设置坐标信号函数
     * @param  index          位置列表的索引值
     */
    void SendCoordinatesToBus(int index);
    /**
     * @brief 接收查询结果信息
     * @param  new_message      新的消息
     */
    void GetMainShowMessage(MainSendMessage new_message);
    /**
     * @brief 初始化选择标签框
     */
    void InitChooseShowWidgets();
private slots:
    /**
     * @brief 左侧树节点，双击响应事件，主要是；绑定对应的函数
     * @param  index            对应的索引
     */
    void on_treeMain_doubleClicked(const QModelIndex &index);

private:
    Ui::ReviewWidget *ui;
    /**
     * @brief Set the Track Info object
     * @param  info             提示信息
     */
    void setTrackInfo(const QString &info);
    /**
     * @brief Set the Status Info object
     * @param  info             提示信息
     */
    void setStatusInfo(const QString &info);
    /**
     * @brief 
     * @param  status           My Param doc
     */
    void handleCursor(QtAV::MediaStatus status);
    /**
     * @brief  更新速度信息
     * @param  currentInfo      My Param doc
     */
    void updateDurationInfo(qint64 currentInfo);
    QtAV::AVPlayer *m_player = nullptr;                                 ///< 播放器，多视频同时播放时主要是第一个
    QList<QSharedPointer<QtAV::AVPlayer>> m_player_list_;               ///< 播放器列表
    VideoShowWidget<QLabel> *video_choose_widgets = nullptr;            ///< QLable的多显示界面
#ifdef ADD_MAP_CONTROL
    QWidget *re_map_control_widget_ = nullptr;                          ///< 回放地图控制界面类
    QVBoxLayout *re_map_vbox_layout_ = nullptr;                         ///< 地图布局指针
    QQuickView *re_map_control_view_ = nullptr;                         ///< 地图显示界面
    std::shared_ptr<QDeclarativeGeoMap> re_view_control_map_ = nullptr; ///< 控制地图类
#endif
    QLabel *tempLab = nullptr;                                          ///< 记录鼠标当前的QLabel
    QString m_trackInfo;                                                ///< 临时站点信息
    QString m_statusInfo;                                               ///< 当前状态信息
    qint64 m_duration;                                                  ///< 当前转换率
    QList<QGeoCoordinate> bus_coordinates_list_;                        ///< 公交的历史坐标点信息
    RecordSelectDialog *sql_choose_dialog_;                             ///< sql选择框
};

#endif // REVIEWWIDGET_H
