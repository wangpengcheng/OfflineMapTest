#ifndef REVIEWWIDGET_H
#define REVIEWWIDGET_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          REVIEWWIDGET_H
** @brief         主要实现回放类的布局和设计
** @details       主要实现回放类的布局和相关设计
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-28 周五  15:39:57
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "QtAV/AVPlayer.h"
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
#include "VideoControl/recordselectdialog.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "VideoControl/qtavvideowidget.h"
QT_END_NAMESPACE

class PlaylistModel;
class HistogramWidget;

class ReviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReviewWidget(QWidget *parent = nullptr);
    ~ReviewWidget();
    //是否可见
    bool isPlayerAvailable() const;
    //将url添加到列表中
    void addToPlaylist(const QList<QString> &urls);
    //设置传统音频角色
    //void setCustomAudioRole(const QString &role);
//    //获取显示窗口
//    inline QVideoWidget* videoWidget(){return m_videoWidget;}
//    //获取播放控制
//    inline QMediaPlayer* GetPlyer(){return m_player;}
    inline QtAV::AVPlayer*  GetPlyer(){return m_player;}
    QtAVVideoWidget* videoWidget(){return m_videoWidget;}

signals:
    void fullScreenChanged(bool fullScreen);
    void SendQGeoCoordinate(QGeoCoordinate);
public slots:
    void play();
    void pause();
    void stop();
    //开启函数
    void open();
    //时间更改
    void durationChanged(qint64 duration);//最后信号更改
    //位置更改
    void positionChanged(qint64 progress);//
    //基础数据更改
    void metaDataChanged();

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QtAV::MediaStatus status);
    void stateChanged(QtAV::AVPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

    void InitQGeoCoordinates(int record_id);//从数据库获取坐标信息
    void SendCoordinatesToBus(int index); //抛出信号的函数
    void GetMainShowMessage(MainSendMessage new_message);//接收查询结果信息
    //void UpdatePlayInfo();
private:
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QtAV::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    QtAV::AVPlayer *m_player = nullptr;//播放器
    //QMediaPlaylist *m_playlist = nullptr;//播放列表

    //QVideoWidget *m_videoWidget = nullptr;//显示列表
    QtAVVideoWidget *m_videoWidget = nullptr;
    QLabel *m_coverLabel = nullptr;//转换列表
    QSlider *m_slider = nullptr; //进度条
    QLabel *m_labelDuration = nullptr;//
    QLabel *m_statusLabel = nullptr;//状态标签
    QStatusBar *m_statusBar = nullptr;//状态条

    //PlaylistModel *m_playlistModel = nullptr;
    QAbstractItemView *m_playlistView = nullptr;
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
    QList<QGeoCoordinate> bus_coordinates_list_;//公交的历史坐标点信息
    RecordSelectDialog* sql_choose_dialog_;//sql选择框
};

#endif // REVIEWWIDGET_H
