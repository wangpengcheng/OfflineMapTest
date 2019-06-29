#ifndef PLAYER_H
#define PLAYER_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          player.h
** @brief         初始的播放控制类，已经弃用
** @details       曾经的播放控制类，现在已经弃用
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:36:22
** @example
**
** 示例代码
**
*****************************************************************************/

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
#include "VideoControl/recordselectdialog.h"
QT_END_NAMESPACE

class PlaylistModel;
class HistogramWidget;

class Player : public QWidget
{
    Q_OBJECT

public:
    //基本构造函数
    Player(QWidget* parent=nullptr);
    ~Player();

    bool isPlayerAvailable() const;

    void addToPlaylist(const QList<QUrl> &urls);
    void setCustomAudioRole(const QString &role);
    //获取显示
    inline QVideoWidget* videoWidget(){return m_videoWidget;}
    inline QMediaPlayer* GetPlyer(){return m_player;}

signals:
    void fullScreenChanged(bool fullScreen);
    void SendQGeoCoordinate(QGeoCoordinate);

private slots:
    void open();
    void durationChanged(qint64 duration);//最后信号更改
    void positionChanged(qint64 progress);//
    void metaDataChanged();

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

    void showColorDialog();
    void InitQGeoCoordinates(int record_id);//从数据库获取坐标信息
    void SendCoordinatesToBus(int index); //抛出信号的函数
    void GetMainShowMessage(MainSendMessage new_message);//接收查询结果信息
    //void UpdatePlayInfo();
private:
    void clearHistogram();
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);
    QMediaPlayer *m_player = nullptr;//播放器
    QMediaPlaylist *m_playlist = nullptr;//播放列表
    QVideoWidget *m_videoWidget = nullptr;//显示列表
    QLabel *m_coverLabel = nullptr;//转换列表
    QSlider *m_slider = nullptr; //进度条
    QLabel *m_labelDuration = nullptr;//
    QPushButton *m_fullScreenButton = nullptr;//全屏按钮
    QPushButton *m_colorButton = nullptr;//色彩按钮
    QDialog *m_colorDialog = nullptr;//色彩选框
    QLabel *m_statusLabel = nullptr;//状态标签
    QStatusBar *m_statusBar = nullptr;//状态条

    QLabel *m_labelHistogram = nullptr;//频率条
    HistogramWidget *m_videoHistogram = nullptr;//视频
    HistogramWidget *m_audioHistogram = nullptr;//音频
    QVideoProbe *m_videoProbe = nullptr;//视频属性
    QAudioProbe *m_audioProbe = nullptr;//音频属性

    PlaylistModel *m_playlistModel = nullptr;
    QAbstractItemView *m_playlistView = nullptr;
    QString m_trackInfo;
    QString m_statusInfo;
    qint64 m_duration;
    QList<QGeoCoordinate> bus_coordinates_list_;//公交的历史坐标点信息
    RecordSelectDialog* sql_choose_dialog_;//sql选择框


};

#endif // PLAYER_H
