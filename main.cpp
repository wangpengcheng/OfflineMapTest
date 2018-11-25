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
//使用location 注册类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#include <QtLocation/private/qdeclarativepolylinemapitem_p.h>
#include <QGeoPath>//geoPath
//引入tool类
#include <QtQuick/private/qquickimage_p.h>
#include "src/tool.h"

#include "src/busstation.h"
//video
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//键盘监听
#include <QKeyEvent>

#include "test/screencontroltest.h"

//use tool
Tool tool;
//设置内部函数
void AddCoordinateToList(QList<QGeoCoordinate> &temp);
void VideoTest();//test video
void ShowBusLine(QQmlApplicationEngine &engine);//显示公交线路
int main(int argc, char *argv[])
{

    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    QString path_string=QDir::tempPath();
    qDebug()<<path_string;
   // VideoTest();
    //use Plugin
    ScreenControlTest screen_control_test;
    screen_control_test.initTest();
 //   Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    //add qucik
 //   QQmlApplicationEngine engine;
    //load qml file
 //   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
 //   ShowBusLine(engine);
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
void ShowBusLine(QQmlApplicationEngine &engine)
{

    QList<QGeoCoordinate> coordinate_list;
    AddCoordinateToList(coordinate_list);//添加关键路径点
    //定义GeoPath路径
    QGeoPath bus_path;
    //创建线段对象
    QDeclarativePolylineMapItem *BusLine=new QDeclarativePolylineMapItem();
    BusLine->setPath(coordinate_list);
    BusLine->line()->setColor("red");
    BusLine->line()->setWidth(3.5);

    //qt 获取qml第一个对象：
    QObject *pRoot=engine.rootObjects().first();
    //找到map节点
    QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");
    //QQuickWindow *qWindow=engine.findChild<QQuickWindow *>("main");
   // qDebug()<<qWindow->width();
        if(qMap!=0){
            //添加线路
            qMap->addMapItem(BusLine);
            int station_array[]={0,3,12,16,29,34,36};
            for(int i=0;i<7;++i)//添加站点
            {
                BusStation *temp_station=new BusStation();
                temp_station->setCoordinate(coordinate_list.value(station_array[i]));
                qMap->addMapItem(temp_station);
            }

           }else {
               qDebug("Can not get this Object");
           }
}
void VideoTest()
{
    tool.TestNoteTool("video test ",0);
    for(int i=0;i<12;++i){
    QVideoWidget *vw = new QVideoWidget();
    QMediaPlayer *player=new QMediaPlayer();
    QMediaPlaylist *playlist=new QMediaPlaylist();

    QString video_path=QString("C:/Users/lin/Videos/Captures/%1.mp4").arg(i%3);

//    QFile file(video_path);

//        if(!file.open(QIODevice::ReadOnly)){

//            qDebug() << "Could not open file";
//        }else{
//            player->setMedia(QUrl::fromLocalFile(video_path));
//            playlist->addMedia(QUrl("http://example.com/movie1.mp4"));

//            vw->show();
//            player->play();
//        }
        playlist->addMedia(QUrl("file:///C:/Users/lin/Videos/Captures/2.mp4"));
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
