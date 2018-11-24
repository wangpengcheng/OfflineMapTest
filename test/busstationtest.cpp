#include "busstationtest.h"
#include <QtQuick/private/qquickimage_p.h>
BusStationTest::BusStationTest()
{
    bus_station_test_=NULL;
    bus_station_test_=new BusStation();
}
BusStationTest::~BusStationTest()
{
    if(bus_station_test_!=NULL)
    {
         delete[] bus_station_test_;
    }
}
void BusStationTest::ConstructFunctionTest()
{
    QGeoCoordinate coordinate(30.5565134000,103.9940400000);
    QUrl img_path("qrc:/img/bus_station.png");
    BusStation station0;//construct0;
    BusStation station1(coordinate);//construct1;
    BusStation station2(coordinate,"2");//construct2
    BusStation station3(coordinate,"3","station3");//construct3;
    BusStation station4(coordinate,"4","station4",img_path);//construct4
    QQuickImage *test_image;
    test_image=station4.bus_station_iocn();
    tool.TestNoteTool("ConstructFunctionTest",0);
    qDebug()<<"This img_path is "<<img_path.toString();
    if(station0.bus_station_id()==""
       &&station0.bus_station_iocn()!=NULL
       &&station0.coordinate()!=coordinate)
    {
        qDebug()<<"This construct0 function is OK";
    }else {
        qDebug()<<"This construct0 function is error";
    }
    if(station1.coordinate()==coordinate)
    {
        qDebug()<<"This construct1 function is OK";
    }else {
        qDebug()<<"This construct1 function is error";
    }
    if(station2.bus_station_id()=="2")
    {
        qDebug()<<"This construct2 function is OK";
    }else {
        qDebug()<<"This construct2 function is error";
    }
    if(station3.bus_station_name()=="station3")
    {
        qDebug()<<"This construct3 function is OK";
    }else {
        qDebug()<<"This construct3 function is error";
    }

    if(station4.bus_station_name()=="station4")
    {
        qDebug()<<"This construct4 function is OK";
    }else {
        qDebug()<<"This construct4 function is error";
    }
    tool.TestNoteTool("ConstructFunctionTest",1);
   // delete station0;//station1,station2,station3,station4;

}
void BusStationTest::SetBusStationIdTest()
{
    tool.TestNoteTool("SetBusStationIdTest",0);
    bus_station_test_->SetBusStationId("station1");
    if(bus_station_test_->bus_station_id()=="station1")
    {
        qDebug()<<"This SetBusStationId() function is OK";
    }else {
        qDebug()<<"This SetBusStationId() function is error";
    }
    tool.TestNoteTool("SetBusStationIdTest",1);
}
void BusStationTest::SetBusStationNameTest()//设置站点名称测试
{
    tool.TestNoteTool("SetBusStationNameTest",0);
    bus_station_test_->SetBusStationName("station1");
    if(bus_station_test_->bus_station_name()=="station1")
    {
        qDebug()<<"This SetBusStationNameTest() function is OK";
    }else {
        qDebug()<<"This SetBusStationNameTest() function is error";
    }
    tool.TestNoteTool("SetBusStationNameTest",1);

}
void BusStationTest::SetBusStationIocnTest()
{
    tool.TestNoteTool("SetBusStationIocnTest",0);
    QQuickImage *test_image=new QQuickImage();
    test_image->setSource(QUrl("qrc:/img/6.png"));
    test_image->setHeight(100);
    test_image->setWidth(100);
    bus_station_test_->SetBusStationIocn(test_image);
    if(bus_station_test_->bus_station_iocn()->source()==QUrl("qrc:/img/6.png"))
    {
        qDebug()<<"This SetBusStationIocnTest() function is OK";
    }else {
        qDebug()<<"This SetBusStationIocnTest() function is error";
    }
    tool.TestNoteTool("SetBusStationIocnTest",1);
}
void BusStationTest::SetBusStationInformationTest()
{
    tool.TestNoteTool("SetBusStationInformationTest",0);
    //TO-DO
    tool.TestNoteTool("SetBusStationInformationTest",2);
}
void BusStationTest::SetIocnScaleTest()
{
    tool.TestNoteTool("SetIocnScaleTest",0);
    bus_station_test_->SetIocnScale(0.5);
    /*
    if(bus_station_test_->bus_station_iocn()->size()==QSize(25,25))
    {
        qDebug()<<"This SetIocnScaleTest() function is OK";
    }else {
        qDebug()<<"This SetIocnScaleTest() function is error";
        qDebug()<<"The Height is"<<bus_station_test_->bus_station_iocn()->size();
    }
    tool.TestNoteTool("SetBusStationIdTest",1);
    */
}
void BusStationTest::ShowTest(QDeclarativeGeoMap *qMap)
{
    /*Must use next code in main function
     *
    QQmlApplicationEngine engine;
    load qml file
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //qt 获取qml第一个对象：
    QObject *pRoot=engine.rootObjects().first();
    //找到map节点
    QDeclarativeGeoMap *qMap=pRoot->findChild<QDeclarativeGeoMap *>("maptest1");
    */
     tool.TestNoteTool("ShowTest",0);
    if(qMap!=NULL)
    {
        qMap->addMapItem(bus_station_test_);
    }else {
        qDebug()<<"Please give the right inputs";
    }
    tool.TestNoteTool("ShowTest",1);
}
void BusStationTest::MainTest()
{
    tool.TestNoteTool("MainTest",0);
    ConstructFunctionTest();
    SetBusStationIdTest();
    SetBusStationNameTest();
    SetBusStationIocnTest();
    SetIocnScaleTest();
    tool.TestNoteTool("MainTest",1);
}
