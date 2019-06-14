#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>
#include <QStandardPaths>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickWindow>
#include <QFontDatabase>
#include <QSharedPointer>
#include <QTimer>
#include <QTimeLine>
//使用location 注册类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#include <QtLocation/private/qdeclarativepolylinemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapitemgroup_p.h>
#include <QGeoPath>//geoPath
//引入tool类
#include <QtQuick/private/qquickimage_p.h>
#include <QtQuick/private/qquickwindow_p.h>
#include <QtQuick/private/qquickitem_p.h>
#include "src/tool.h"
//video
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//键盘监听
#include <QKeyEvent>
#include "test/screencontroltest.h"

//#define MyTest 1
#ifdef MyTest
#include "test/buslinetest.h"
#include "test/bustest.h"
#include "test/tool_test.h"
#include "test/videodecodetheadtest.h"
#endif

//使用函数
#include "src/busline.h"
#include "src/busstation.h"
#include "src/bus.h"
#include "src/mapcontrlconnect.h"
#include "src/mainshowdialog.h"
#include "VideoControl/videodecodethread.h"
#include "VideoControl/streamvideowidget.h"
//主函数
#include "VideoControl/myhelper.h"
#include "VideoControl/frmmain.h"
#include "VideoControl/myapp.h"
//use tool
Tool tool;
#include <QLabel>
//设置内部函数
void AddCoordinateToList(QList<QGeoCoordinate> &temp);
void VideoTest();//test video
void ShowBusLine(QDeclarativeGeoMap *qMap);//显示公交线路
void MoveTest(QDeclarativeGeoMap *qMap);//公交移动测试
int VideoControlTest(QApplication app);
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QString path_string=QDir::tempPath();
//方便开启测试模式
#ifndef MyTest
    //添加字体
    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));
    //VideoTest();

    //use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    app.setApplicationName("VM");         //设置应用程序名称
    app.setApplicationVersion("V201412"); //设置应用程序版本
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);//允许使用
    myHelper::SetUTF8Code();            //设置程序编码为UTF-8
    myHelper::SetChinese();             //设置程序为中文字库

    //赋值当前应用程序路径和桌面宽度高度
    myApp::AppPath = QApplication::applicationDirPath() + "/";
    myApp::DeskWidth = qApp->desktop()->availableGeometry().width();
    myApp::DeskHeight = qApp->desktop()->availableGeometry().height();

    //程序加载时先加载所有配置信息
    myApp::ReadConfig();

    //加载和应用样式
    myHelper::SetStyle(myApp::AppStyle);

    //创建共享内存,判断是否已经运行程序
    QSharedMemory mem("VM");
    if(!mem.create(1)){
        myHelper::ShowMessageBoxError(QStringLiteral("程序已运行,软件将自动关闭!"));
    }

    //判断当前数据库文件是否存在(如果数据库打开失败则终止应用程序)
    if (!myHelper::FileIsExist(myApp::AppPath + "VM.db")) {
        myHelper::ShowMessageBoxError(QStringLiteral("数据库文件不存在,程序将自动关闭!"));
        return 1;
    }

    QSqlDatabase DbConn;
    DbConn = QSqlDatabase::addDatabase("QSQLITE");
    DbConn.setDatabaseName(myApp::AppPath + "VM.db");

    //创建数据库连接并打开(如果数据库打开失败则终止应用程序)
    if (!DbConn.open()) {
        myHelper::ShowMessageBoxError(QStringLiteral("打开数据库失败,程序将自动关闭！"));
        return 1;
    }
    frmMain w;
    w.show();
    //w.setGeometry(qApp->desktop()->availableGeometry());
    qDebug()<<"init file";



#endif

#ifdef MyTest
    tool_test test;
    test.CreatFileTest();
    VideoDecodeTheadTest decode_test;
    decode_test.MainTest();
#endif
    return app.exec();


}

void AddCoordinateToList(QList<QGeoCoordinate> &temp)
{
    temp.append(tool.WPS84ToGCJ02(30.5563134000,103.9938400000));//体育学院站
    temp.append(tool.WPS84ToGCJ02(30.5571043000,103.9934402500));
    temp.append(tool.WPS84ToGCJ02(30.5573103000,103.9932192500));
    temp.append(tool.WPS84ToGCJ02(30.5584908100,103.9922940300));//艺术学院站
    temp.append(tool.WPS84ToGCJ02(30.5586408100,103.9922160300));
    temp.append(tool.WPS84ToGCJ02(30.5588028100,103.9921570300));
    temp.append(tool.WPS84ToGCJ02(30.5590498100,103.9921060300));//
    temp.append(tool.WPS84ToGCJ02(30.5598418100,103.9922780300));
    temp.append(tool.WPS84ToGCJ02(30.5609897200,103.9926928200));//
    temp.append(tool.WPS84ToGCJ02(30.5613687200,103.9929398200));
    temp.append(tool.WPS84ToGCJ02(30.5616037200,103.9931808200));
    temp.append(tool.WPS84ToGCJ02(30.5618997200,103.9935998200));
    temp.append(tool.WPS84ToGCJ02(30.5620887200,103.9940178200));//土木实验室
    temp.append(tool.WPS84ToGCJ02(30.5622367200,103.9944358200));
    temp.append(tool.WPS84ToGCJ02(30.5622917200,103.9950048200));
    temp.append(tool.WPS84ToGCJ02(30.5623057200,103.9958828200));//制造实验室
    temp.append(tool.WPS84ToGCJ02(30.5624307200,103.9966978200));
    temp.append(tool.WPS84ToGCJ02(30.5627307200,103.9977438200));//
    temp.append(tool.WPS84ToGCJ02(30.5628877200,103.9982558200));
    temp.append(tool.WPS84ToGCJ02(30.5629197200,103.9985078200));
    temp.append(tool.WPS84ToGCJ02(30.5628927200,103.9986898200));
    temp.append(tool.WPS84ToGCJ02(30.5628807200,103.9988478200));
    temp.append(tool.WPS84ToGCJ02(30.5628077200,103.9990678200));
    temp.append(tool.WPS84ToGCJ02(30.5626867200,103.9992878200));
    temp.append(tool.WPS84ToGCJ02(30.5625027200,103.9995348200));
    temp.append(tool.WPS84ToGCJ02(30.5622527200,103.9998078200));
    temp.append(tool.WPS84ToGCJ02(30.5616847200,104.0002318200));
    temp.append(tool.WPS84ToGCJ02(30.5615377200,104.0003298200));//
    temp.append(tool.WPS84ToGCJ02(30.5611987200,104.0006108200));
    temp.append(tool.WPS84ToGCJ02(30.5610907200,104.0008778200));//计算机学院
    temp.append(tool.WPS84ToGCJ02(30.5606957200,104.0017388200));
    temp.append(tool.WPS84ToGCJ02(30.5604837200,104.0021948200));
    temp.append(tool.WPS84ToGCJ02(30.5602867200,104.0023988200));//
    temp.append(tool.WPS84ToGCJ02(30.5601718900,104.0025398400));
    temp.append(tool.WPS84ToGCJ02(30.5594968900,104.0031678400));//一号运动场
    temp.append(tool.WPS84ToGCJ02(30.5590118900,104.0036178400));
    temp.append(tool.WPS84ToGCJ02(30.5583098900,104.0042138400));//东南门
}
void ShowBusLine(QDeclarativeGeoMap *qMap)
{

    QList<QGeoCoordinate> coordinate_list,coordinate_list2;
    AddCoordinateToList(coordinate_list);//添加关键路径点
    //定义GeoPath路径
    QGeoPath bus_path;
    bus_path.setPath(coordinate_list);
    bus_path.setWidth(0.5);
    //创建线段对象
    QDeclarativePolylineMapItem *BusLine1=new QDeclarativePolylineMapItem();
//    BusLine->setPath(coordinate_list);
    BusLine1->setPath(bus_path);
    BusLine1->line()->setColor("red");
   // BusLine->line()->setWidth(3.5);

    //测试QDeclarativeGeoMapItemGroup
    QDeclarativeGeoMapItemGroup *test=new QDeclarativeGeoMapItemGroup();
    //QQuickWindow *qWindow=engine.findChild<QQuickWindow *>("main");
   // qDebug()<<qWindow->width();
        if(qMap!=0){
            //添加线路
            //qMap->addMapItem(BusLine);
            int station_array[]={0,3,12,16,29,34,36};
            for(int i=0;i<7;++i)//添加站点
            {
                BusStation *temp_station=new BusStation();
                temp_station->setCoordinate(coordinate_list.value(station_array[i]));
               // qMap->addMapItem(temp_station);
                temp_station->setParentItem(test);
                coordinate_list2.append(coordinate_list.value(station_array[i]));
            }

           }else {
               qDebug("Can not get this Object");
           }
       // BusLine->setParentItem(test);
       // qDebug()<<BusLine->parentItem();
        //test();
        BusLine *bus_line_test=new BusLine(coordinate_list,coordinate_list2);
        //qMap->addMapItemGroup(test);
        qMap->addMapItemGroup(bus_line_test);
}
void VideoTest()
{
    tool.TestNoteTool("video test ",0);
    for(int i=0;i<10;++i){
    QVideoWidget *vw = new QVideoWidget();
    QMediaPlayer *player=new QMediaPlayer();
    QMediaPlaylist *playlist=new QMediaPlaylist();

    QString video_path=QString("C:/Users/lin/Videos/Captures/minieyeone.mp4");

//    QFile file(video_path);

//        if(!file.open(QIODevice::ReadOnly)){

//            qDebug() << "Could not open file";
//        }else{
//            player->setMedia(QUrl::fromLocalFile(video_path));
//            playlist->addMedia(QUrl("http://example.com/movie1.mp4"));

//            vw->show();
//            player->play();
//        }
       // playlist->addMedia(QUrl("file:///D:/minieyeone.mp4"));
        playlist->addMedia(QUrl::fromLocalFile(video_path));
       // playlist->addMedia(QUrl::fromLocalFile(video_path));
        playlist->setCurrentIndex(1);
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        player->setPlaylist(playlist);
        player->setVideoOutput(vw);
        vw->resize(400,400);
        vw->setGeometry(QRect(400*(i%4),20+400*(i/4),400,400));
        vw->show();
        player->play();
    }
    tool.TestNoteTool("video test ",1);
}
void MoveTest(QDeclarativeGeoMap *qMap)
{
    BusStation *bus_station_test=new BusStation();
    bus_station_test->setCoordinate(tool.WPS84ToGCJ02(30.5595483655,103.9976232481));
    qMap->addMapItem(bus_station_test);
    //QQuickImage temp_image=new QQuickImage("qrc:/img/car_up.png");
    bus_station_test->SetBusStationIocn(QUrl("qrc:/img/car_up.png"));
   // QTimeLine timeline=new QTimeLine(1000);
    // Construct a 1-second timeline with a frame range of 0 - 100
   bus_station_test->setCoordinate(tool.WPS84ToGCJ02(30.5697483655,103.9976232481));

}
