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

#include <QtLocation/private/qdeclarativegeomap_p.h>
#include "VideoControl/recordselectdialog.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "VideoControl/qtavvideowidget.h"
#include "VideoControl/videoshowwidget.h"
#include "QtAV/AVPlayer.h"

#define ADD_MAP_CONTROL //设置添加地图控制
QT_END_NAMESPACE

namespace Ui {
class ReviewWidget;
}

class ReviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReviewWidget(QWidget *parent = nullptr);
    ~ReviewWidget();
    //将url添加到列表中

    inline QtAV::AVPlayer*  GetPlyer(){return m_player;}
    inline VideoShowWidget<QLabel>* video_choose_widget(){return video_choose_widgets;}
    inline QList<QSharedPointer<QtAV::AVPlayer>> player_list(){return m_player_list_;}
#ifdef ADD_MAP_CONTROL
    inline std::shared_ptr<QDeclarativeGeoMap> re_view_control_map(){return re_view_control_map_;}
#endif
    void Init();                                                                // ToDo 初始化相关变量
    void SetPlayConnect();                                                      //连接视频反馈
    void CancelPlayConnect();                                                   //断开视频反馈
    void addToPlaylist(const MainSendMessage &message);                         //添加播放列表
    bool isPlayerAvailable() const;                                             //是否播放器存在

signals:
    void fullScreenChanged(bool fullScreen);                                    //是否全屏
    void SendQGeoCoordinate(QGeoCoordinate);                                    //发送位置信息
    void SendLabelId(QString label_id);                                         //发送当前选中的QLabel关键信息
    void SendConnect(int av_player_index,int show_widget_index);                //发送视频连接改变信息
protected:
    bool eventFilter(QObject *obj, QEvent *event);                              //鼠标点击事件判断
public slots:
    void play();                                                                //播放
    void pause();                                                               //暂停
    void stop();                                                                //停止
    void setSpeed(qreal speed);                                                 //更改播放速度函数
    void open();                                                                //开启查询窗口
    void durationChanged(qint64 duration);                                      //最后时间更改
    void positionChanged(qint64 progress);                                      //位置更改
    void metaDataChanged();                                                     //基础数据更改

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QtAV::MediaStatus status);
    void stateChanged(QtAV::AVPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

    void InitQGeoCoordinates(int record_id);                                    //从数据库获取坐标信息
    void SendCoordinatesToBus(int index);                                       //抛出信号的函数
    void GetMainShowMessage(MainSendMessage new_message);                       //接收查询结果信息
    //void UpdatePlayInfo();
    void InitChooseShowWidgets();
private slots:
    void on_treeMain_doubleClicked(const QModelIndex &index);

private:
    Ui::ReviewWidget *ui;
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QtAV::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    QtAV::AVPlayer *m_player = nullptr;                                         //播放器，多视频同时播放时主要是第一个
    QList<QSharedPointer<QtAV::AVPlayer>> m_player_list_;                       //播放器列表
    VideoShowWidget<QLabel>* video_choose_widgets=nullptr;                      //QLable的多显示界面
#ifdef ADD_MAP_CONTROL
    QWidget* re_map_control_widget_=nullptr;
    QVBoxLayout* re_map_vbox_layout_=nullptr;                                   //地图布局指针
    QQuickView* re_map_control_view_=nullptr;                                   //地图显示界面
    std::shared_ptr<QDeclarativeGeoMap> re_view_control_map_=nullptr;           //控制地图类
#endif
    QLabel* tempLab=nullptr;                                                    //记录鼠标当前的QLabel
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
    QList<QGeoCoordinate> bus_coordinates_list_;                                //公交的历史坐标点信息
    RecordSelectDialog* sql_choose_dialog_;                                     //sql选择框
};

#endif // REVIEWWIDGET_H
