#ifndef REVIEWWIDGET_H
#define REVIEWWIDGET_H

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

namespace Ui {
class ReviewWidget;
}

class ReviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReviewWidget(QWidget *parent = nullptr);
    ~ReviewWidget();
    bool isPlayerAvailable() const;
    //将url添加到列表中
    void addToPlaylist(const QList<QString> &urls);
    inline QtAV::AVPlayer*  GetPlyer(){return m_player;}
    QtAVVideoWidget* videoWidget(){return m_videoWidget;}
    void Init();
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
    Ui::ReviewWidget *ui;
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QtAV::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    QtAV::AVPlayer *m_player = nullptr;//播放器
    QtAVVideoWidget *m_videoWidget = nullptr;//播放显示界面
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
    QList<QGeoCoordinate> bus_coordinates_list_;//公交的历史坐标点信息
    RecordSelectDialog* sql_choose_dialog_;//sql选择框
};

#endif // REVIEWWIDGET_H
