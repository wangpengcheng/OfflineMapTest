#include "reviewwidget.h"
#include "ui_reviewwidget.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QVideoProbe>
#include <QVideoWidget>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>
#include <QQuickView>
#include <player/videowidget.h>
#include "player/qtavplayercontrols.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "VideoControl/myhelper.h"
#include "videowidget.h"
#include "src/tool.h"

ReviewWidget::ReviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReviewWidget)
{
    ui->setupUi(this);

    //连接UI控件的信号和槽
    connect(ui->m_slider, &QSlider::sliderMoved, this, &ReviewWidget::seek);
    connect(ui->m_slider,&QSlider::valueChanged,this,&ReviewWidget::SendCoordinatesToBus);//更新函数坐标位置
    connect(ui->openButton, &QPushButton::clicked, this, &ReviewWidget::open);

    connect(ui->controls, &QtAVPlayerControls::play,this, &ReviewWidget::play);//播放
    connect(ui->controls, &QtAVPlayerControls::pause, this, &ReviewWidget::pause);//暂停
    connect(ui->controls, &QtAVPlayerControls::stop, this, &ReviewWidget::stop);//停止
    connect(ui->controls, &QtAVPlayerControls::previous, this, &ReviewWidget::previousClicked);//前一个
    connect(ui->controls, &QtAVPlayerControls::changeRate, this, &ReviewWidget::setSpeed);//设置播放速度
    //connect(ui->controls, &QtAVPlayerControls::stop, m_videoWidget, QOverload<>::of(&QVideoWidget::update));//设置更新
    metaDataChanged();
    InitChooseShowWidgets();
#ifdef ADD_MAP_CONTROL
    re_map_vbox_layout_=new QVBoxLayout(ui->re_map_control_widget);
    ui->re_map_control_widget->setLayout(re_map_vbox_layout_);
    re_map_vbox_layout_->setMargin(1);

    //初始化地图
    re_map_control_view_=new QQuickView();
    re_map_control_view_->setSource(QUrl("qrc:/qml/MapControlModel.qml"));
    re_map_control_view_->setResizeMode(QQuickView::SizeRootObjectToView);
    re_map_control_widget_=QWidget::createWindowContainer(re_map_control_view_);
    re_map_vbox_layout_->addWidget(re_map_control_widget_);
    //获取地图
    re_view_control_map_=std::shared_ptr<QDeclarativeGeoMap>(re_map_control_view_->rootObject()->findChild<QDeclarativeGeoMap *>("control_show_map"));
#endif
}

ReviewWidget::~ReviewWidget()
{
    delete ui;
}
bool ReviewWidget::isPlayerAvailable() const
{
    //return m_player->isAvailable();
    return m_player->isLoaded();
}
void ReviewWidget::setSpeed(qreal speed)
{

    for(int i=0;i<m_player_list_.size();++i){
        m_player_list_.at(i)->setSpeed(speed);
    }
}
void ReviewWidget::open()
{
    sql_choose_dialog_=new RecordSelectDialog(this);
    connect(sql_choose_dialog_,&RecordSelectDialog::SendShowMessage,this,&ReviewWidget::GetMainShowMessage);
    sql_choose_dialog_->show();
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void ReviewWidget::addToPlaylist(const MainSendMessage &message)
{
    QList<QString> urls=message.video_paths;
    ui->treeMain->clear();
    //清除列表
    m_player_list_.clear();
    QTreeWidgetItem *itemNVR = new QTreeWidgetItem
            (ui->treeMain, QStringList(QStringLiteral("视频列表 ")+message.start_datetime));
    itemNVR->setIcon(0, QIcon(":/image/nvr.png"));
    if(!urls.isEmpty()){

        for(int i=0;i<urls.size();++i){
            if(!urls.at(i).isEmpty()){
                //获取文件名称
                QString video_name=urls.at(i).split("/").last();
                //创建节点
                QString item_name=QStringLiteral("视频%1 %2").arg(QString::number(i)).arg(QString("[" + video_name + "]"));
                qDebug()<<item_name;
                //将文件添加到上面
                QTreeWidgetItem *temp_item=new QTreeWidgetItem(itemNVR,QStringList(item_name));
                //初始化播放器
                QSharedPointer<QtAV::AVPlayer> temp_player(new QtAV::AVPlayer(this));
                temp_player->setFile(urls.at(i));
                //将播放器插入
                m_player_list_.append(temp_player);

            }else{
                qDebug()<<"url is empty ";
            };

            CancelPlayConnect();//断开连接
            m_player=m_player_list_.at(0).get();//指向新地址
            SetPlayConnect();//重新建立连接
        }

        ui->treeMain->expandAll();//展开所有

    }else{
        qDebug()<<" This input file url is empty";
    }
}
void ReviewWidget::CancelPlayConnect(){
    disconnect(m_player, &QtAV::AVPlayer::durationChanged, this, &ReviewWidget::durationChanged);//最终位置更改
    disconnect(m_player, &QtAV::AVPlayer::positionChanged, this, &ReviewWidget::positionChanged);//位置更改
    disconnect(m_player, &QtAV::AVPlayer::stateChanged, this, &ReviewWidget::stateChanged);//状态更改
    disconnect(m_player, SIGNAL(stateChanged(QtAV::AVPlayer::State)), ui->controls, SLOT(setState(QtAV::AVPlayer::State)));//转变函数
}
void ReviewWidget::SetPlayConnect(){

    ui->controls->setState(m_player->state());
    ui->controls->setVolume(m_player->audio()->volume());
    //初始化进度条范围
    ui->m_slider->setRange(0, m_player->duration() / 1000);
    //连接信号和槽
    connect(m_player, &QtAV::AVPlayer::durationChanged, this, &ReviewWidget::durationChanged);//最终位置更改
    connect(m_player, &QtAV::AVPlayer::positionChanged, this, &ReviewWidget::positionChanged);//位置更改
    connect(m_player, &QtAV::AVPlayer::stateChanged, this, &ReviewWidget::stateChanged);//状态更改
    connect(m_player, SIGNAL(stateChanged(QtAV::AVPlayer::State)), ui->controls, SLOT(setState(QtAV::AVPlayer::State)));//转变函数
}
bool ReviewWidget::eventFilter(QObject *obj, QEvent *event)
{
    //将鼠标点击事件转为静态指针
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress&&
        MouseEvent->buttons() == Qt::LeftButton) {
        tempLab = qobject_cast<QLabel *>(obj);
        emit(SendLabelId(tempLab->objectName()));
    }
    return false;
}
//持续时间更改
void ReviewWidget::durationChanged(qint64 duration)
{
    //m_duration = duration / 1000;
    m_duration = duration/1000;//更改系数，使得更加完整
    ui->m_slider->setMaximum(m_duration);
}
//位置更改
void ReviewWidget::positionChanged(qint64 progress)
{
    if (!ui->m_slider->isSliderDown())
        ui->m_slider->setValue(progress / 1000);
    //更新数字信息
    updateDurationInfo(progress / 1000);
    //更新位置发射
    //SendCoordinatesToBus(progress/1000);
}
//元数据更改
void ReviewWidget::metaDataChanged()
{
//    if (m_player->isMetaDataAvailable()) {
//        setTrackInfo(QString("%1 - %2")
//                .arg(m_player->metaData(QMediaMetaData::AlbumArtist).toString())
//                .arg(m_player->metaData(QMediaMetaData::Title).toString()));

//        if (m_coverLabel) {
//            QUrl url = m_player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

//            m_coverLabel->setPixmap(!url.isEmpty()
//                    ? QPixmap(url.toString())
//                    : QPixmap());
//        }
//    }
}

void ReviewWidget::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if (m_player->position() <= 5000)
    {
        //m_playlist->previous();
    }else{
        m_player->setPosition(0);
    }
}

void ReviewWidget::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        //m_playlist->setCurrentIndex(index.row());
        m_player->play();
    }
}

void ReviewWidget::playlistPositionChanged(int currentItem)
{
    //m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
}

void ReviewWidget::seek(int seconds)
{
    qint64 real_position=seconds * 1000;
    if(!m_player_list_.isEmpty()){
        for(int i=0;i<m_player_list_.size();++i){
            if(real_position<=m_player_list_.at(i)->duration())
            {
                m_player_list_.at(i)->seek(real_position);
            }else{
                qDebug()<<" This silder Position is over player "<<i<<"'s duration ";
            }
        }
    }
}

void ReviewWidget::statusChanged(QtAV::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
    case QtAV::MediaStatus::UnknownMediaStatus:
    case QtAV::MediaStatus::NoMedia:
    case QtAV::MediaStatus::LoadedMedia:
        setStatusInfo(QString());
        break;
    case QtAV::MediaStatus::LoadingMedia:
        setStatusInfo(tr("Loading..."));
        break;
    case QtAV::MediaStatus::BufferingMedia:
    case QtAV::MediaStatus::BufferedMedia:
        setStatusInfo(tr("Buffering %1%").arg(m_player->bufferMode()));
        break;
    case QtAV::MediaStatus::StalledMedia:
        setStatusInfo(tr("Stalled %1%").arg(m_player->bufferMode()));
        break;
    case QtAV::MediaStatus::EndOfMedia:
        QApplication::alert(this);
        break;
    case QtAV::MediaStatus::InvalidMedia:
        displayErrorMessage();
        break;
    }
}

void ReviewWidget::stateChanged(QtAV::AVPlayer::State state)
{
    qDebug()<<"------ state changed ------";
}

void ReviewWidget::handleCursor(QtAV::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QtAV::MediaStatus::LoadingMedia ||
        status == QtAV::MediaStatus::BufferingMedia ||
        status == QtAV::MediaStatus::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}

void ReviewWidget::bufferingProgress(int progress)
{
    if (m_player->mediaStatus() == QMediaPlayer::StalledMedia)
        setStatusInfo(tr("Stalled %1%").arg(progress));
    else
        setStatusInfo(tr("Buffering %1%").arg(progress));
}

void ReviewWidget::videoAvailableChanged(bool available)
{

}
//设置相关信息
void ReviewWidget::setTrackInfo(const QString &info)
{
//    m_trackInfo = info;

//    if (m_statusBar) {
//        m_statusBar->showMessage(m_trackInfo);
//        m_statusLabel->setText(m_statusInfo);
//    } else {
//        if (!m_statusInfo.isEmpty())
//            setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
//        else
//            setWindowTitle(m_trackInfo);
//    }
}
//
void ReviewWidget::setStatusInfo(const QString &info)
{
    m_statusInfo = info;

//    if (m_statusBar) {
//        m_statusBar->showMessage(m_trackInfo);
//        m_statusLabel->setText(m_statusInfo);
//    } else {
//        if (!m_statusInfo.isEmpty())
//            setWindowTitle(QString("%1 | %2").arg(m_trackInfo).arg(m_statusInfo));
//        else
//            setWindowTitle(m_trackInfo);
//    }
}
//显示错误信息
void ReviewWidget::displayErrorMessage()
{
    //setStatusInfo(m_player->error());
}
//更新时间信息
void ReviewWidget::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || m_duration) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
            m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    //设置更新时间
    ui->m_labelDuration->setText(tStr);

}


void ReviewWidget::InitQGeoCoordinates(int record_id)
{
    Tool::TestNoteTool("InitQGeoCoordinates",0);
    QJsonObject temp_data;
    temp_data.insert("record_id",record_id);
    QString request_url="http://localhost/re_get_gps.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    QJsonArray result_array=test.value("result").toArray();
    //便利初始化坐标数组
    bus_coordinates_list_.clear();//清除原有的数据
    int array_size=result_array.size();
    for(int i=0;i<array_size;++i){
        QJsonObject temp=result_array.at(i).toObject();//取得第i组数据
        double latitude=temp.value("latitude").toString().toDouble();
        double longitude=temp.value("longitude").toString().toDouble();
        bus_coordinates_list_.append(QGeoCoordinate(latitude,longitude));
    }
    Tool::TestNoteTool("InitQGeoCoordinates",1);
}
void ReviewWidget::SendCoordinatesToBus(int index)
{
    int coordinates_size=bus_coordinates_list_.size();
    //注意这里要检查m_slider的值，应为停止播放的时候可能值为0
    //直接写入函数，发射信号
    int position_index=0;
    if(ui->m_slider->maximum()>0){
        position_index=index*(coordinates_size/ui->m_slider->maximum());
    }else{
        qDebug()<<"this video max slider is 0";
        return;
    }
    qDebug()<<"send positon index:"<<position_index;
    //发射信号更新位置
    if(position_index<coordinates_size){
        emit(SendQGeoCoordinate(bus_coordinates_list_.at(position_index)));
    }else{
        qDebug()<<"this over";
    }
}
void ReviewWidget::GetMainShowMessage(MainSendMessage new_message)
{
    //重新初始化记录
    InitQGeoCoordinates(new_message.record_id);
    addToPlaylist(new_message);
}
void ReviewWidget::play()
{

    for(int i=0;i<m_player_list_.size();++i){
        m_player_list_.at(i)->play();
        m_player_list_.at(i)->setState(QtAV::AVPlayer::PlayingState);
    }
}
void ReviewWidget::pause()
{
    for(int i=0;i<m_player_list_.size();++i){
        m_player_list_.at(i)->pause();
    }
}
void ReviewWidget::stop()
{
    for(int i=0;i<m_player_list_.size();++i){
        m_player_list_.at(i)->stop();
    }

}
void ReviewWidget::InitChooseShowWidgets()
{
    video_choose_widgets=new VideoShowWidget<QLabel>(this);
    auto temp_labs=video_choose_widgets->video_widgets();
    for(int i=0;i<temp_labs.size();++i){
        temp_labs.at(i)->setObjectName(QString("%1").arg(i + 1));
        temp_labs.at(i)->installEventFilter(this);
        temp_labs.at(i)->setFocusPolicy(Qt::StrongFocus);
        temp_labs.at(i)->setAlignment(Qt::AlignCenter);
        //二选一可以选择显示文字,也可以选择显示背景图片
        temp_labs.at(i)->setLineWidth(2);
        temp_labs.at(i)->setText(QString(QStringLiteral("通道 %1")).arg(i + 1));
    }
    ui->verticalLayout_2->addWidget(video_choose_widgets);


}

void ReviewWidget::on_treeMain_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"double check";
    if (ui->treeMain->currentItem()->parent() == nullptr) {
        myHelper::ShowMessageBoxError("This tree is empty;Please click OPen button to select data");
        return;
    }
    //当前还没有选择通道
    if (tempLab == nullptr) {
        myHelper::ShowMessageBoxError("current Label is empty;Please click OPen label");
        return;
    }
    QString temp=ui->treeMain->currentIndex().data().toString();
    qDebug()<<temp;
    int player_index=temp.split("[")[0].right(2).toInt();
    int show_index=tempLab->objectName().toInt()-1;
    qDebug()<<player_index<<"show index"<<show_index;
    emit SendConnect(player_index,show_index);

}
