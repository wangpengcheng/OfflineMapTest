#include "bustest.h"
#ifndef BUS_H
#include "MapItems/bus.h"
#endif
BusTest::BusTest(QObject *parent):QObject(parent)
{
    bus_test_=nullptr;
    bus_test_=new Bus(Tool::WPS84ToGCJ02(30.5563134000,103.9938400000));//江安
    //bus_test_=new Bus(Tool::WPS84ToGCJ02(30.631091622,104.081949595));//望江
}
BusTest::~BusTest()
{
    if(bus_test_!=nullptr)
    {
        delete[] bus_test_;
        bus_test_=nullptr;
    }
}
void BusTest::ShowTest(QDeclarativeGeoMap *qMap)
{
    Tool::TestNoteTool("ShowTest",0);
    if(bus_test_==nullptr)
    {
        bus_test_=new Bus(Tool::WPS84ToGCJ02(30.5563134000,103.9938400000));//江安
        //bus_test_=new Bus(Tool::WPS84ToGCJ02(30.631091622,104.081949595));
    };
    bus_test_->SetMap(qMap);
    qDebug()<<bus_test_->bus_quick_item()->parentItem();
    auto *parent1=bus_test_->bus_quick_item()->quickMap();
    qDebug()<<parent1->fromCoordinate(parent1->center());
    Tool::TestNoteTool("ShowTest",1);
}
void BusTest::MoveTest()
{
    Tool::TestNoteTool("MoveTest",0);
    if(bus_test_->bus_quick_item()->parentItem())
    {
       bus_test_->bus_quick_item()->setCoordinate(Tool::WPS84ToGCJ02(30.5563134000,103.9938400000));
    }
    Tool::TestNoteTool("MoveTest",1);
}
void BusTest::UpdataPositionTest()
{
    Tool::TestNoteTool("UpdataPositionTest",0);
    bus_test_->UpdataPosition();
    Tool::TestNoteTool("UpdataPositionTest",1);
}
void BusTest::UpdataPositionBySocketTest()
{
    Tool::TestNoteTool("UpdataPositionBySocketTest",0);
    bus_test_->UpdateCoordinatesBySocket();
    Tool::TestNoteTool("UpdataPositionBySocketTest",1);
}
void BusTest::LuShuTest()
{
    //准备数据
    QList<QGeoCoordinate> temp_points;
    AddCoordinateToList(temp_points);
    Tool::TestNoteTool("LuShuTest",0);
    bus_test_->set_is_cricle(false);
    bus_test_->set_bus_path_coordinates(temp_points);
    bus_test_->ChangePath();
    bus_test_->LuShu();
    Tool::TestNoteTool("LuShuTest",1);
}
void BusTest::ChangePathTest()
{
    Tool::TestNoteTool("ChangePathTest",0);
    QList<QGeoCoordinate> temp_points1;
    this->AddCoordinateToList(temp_points1);
    this->bus_test_->set_bus_path_coordinates(temp_points1);
    qDebug()<<temp_points1;
    qDebug()<<this->bus_test_->bus_path_coordinates().size();
    this->bus_test_->ChangePath();
    Tool::TestNoteTool("ChangePathTest",1);

}
//数据存储测试

void BusTest::SaveCoordinateToSqlTest()
{
    Tool::TestNoteTool("SaveCoordinateToSqlTest",0);
    QGeoCoordinate temp_point(30.5563134000,103.9938400000);
    bus_test_->SaveCoordinateToSql(temp_point,5);
    Tool::TestNoteTool("SaveCoordinateToSqlTest",1);
}
void BusTest::SaveCoordinateToSqlWithLuShuTest()
{
    Tool::TestNoteTool("SaveCoordinateToSqlWithLuShuTest",0);
    //打开路书
    LuShuTest();
    //通过设置定时器来存储视频
    //设置定时器；
    QTimer *timer=new QTimer(this);
    static unsigned int i=0;
    this->connect(timer,&QTimer::timeout,this,[&](){
        qDebug()<<"is stop:"<<bus_test_->is_stop();
        i++;
        qDebug()<<i;
        if(!bus_test_->is_stop()){//车辆没有停止就持续记录
            bus_test_->SaveCoordinateToSql(bus_test_->bus_quick_item()->coordinate(),5);
            //qDebug()<<bus_test_->bus_quick_item()->coordinate();
        }else{
            timer->stop();
            timer->destroyed();
        }
    });
    timer->start(1000);
    Tool::TestNoteTool("SaveCoordinateToSqlWithLuShuTest",1);
}

void BusTest::MainTest()
{
    Tool::TestNoteTool("MainTest",0);
    Tool::TestNoteTool("MainTest",1);

}
void BusTest::AddCoordinateToList(QList<QGeoCoordinate> &temp)
{
    temp.append(Tool::WPS84ToGCJ02(30.5563134000,103.9938400000));//体育学院站
    temp.append(Tool::WPS84ToGCJ02(30.5571043000,103.9934402500));
    temp.append(Tool::WPS84ToGCJ02(30.5573103000,103.9932192500));
    temp.append(Tool::WPS84ToGCJ02(30.5584908100,103.9922940300));//艺术学院站
    temp.append(Tool::WPS84ToGCJ02(30.5586408100,103.9922160300));
    temp.append(Tool::WPS84ToGCJ02(30.5588028100,103.9921570300));
    temp.append(Tool::WPS84ToGCJ02(30.5590498100,103.9921060300));//
    temp.append(Tool::WPS84ToGCJ02(30.5598418100,103.9922780300));
    temp.append(Tool::WPS84ToGCJ02(30.5609897200,103.9926928200));//
    temp.append(Tool::WPS84ToGCJ02(30.5613687200,103.9929398200));
    temp.append(Tool::WPS84ToGCJ02(30.5616037200,103.9931808200));
    temp.append(Tool::WPS84ToGCJ02(30.5618997200,103.9935998200));
    temp.append(Tool::WPS84ToGCJ02(30.5620887200,103.9940178200));//土木实验室
    temp.append(Tool::WPS84ToGCJ02(30.5622367200,103.9944358200));
    temp.append(Tool::WPS84ToGCJ02(30.5622917200,103.9950048200));
    temp.append(Tool::WPS84ToGCJ02(30.5623057200,103.9958828200));//制造实验室
    temp.append(Tool::WPS84ToGCJ02(30.5624307200,103.9966978200));
    temp.append(Tool::WPS84ToGCJ02(30.5627307200,103.9977438200));//
    temp.append(Tool::WPS84ToGCJ02(30.5628877200,103.9982558200));
    temp.append(Tool::WPS84ToGCJ02(30.5629197200,103.9985078200));
    temp.append(Tool::WPS84ToGCJ02(30.5628927200,103.9986898200));
    temp.append(Tool::WPS84ToGCJ02(30.5628807200,103.9988478200));
    temp.append(Tool::WPS84ToGCJ02(30.5628077200,103.9990678200));
    temp.append(Tool::WPS84ToGCJ02(30.5626867200,103.9992878200));
    temp.append(Tool::WPS84ToGCJ02(30.5625027200,103.9995348200));
    temp.append(Tool::WPS84ToGCJ02(30.5622527200,103.9998078200));
    temp.append(Tool::WPS84ToGCJ02(30.5616847200,104.0002318200));
    temp.append(Tool::WPS84ToGCJ02(30.5615377200,104.0003298200));//
    temp.append(Tool::WPS84ToGCJ02(30.5611987200,104.0006108200));
    temp.append(Tool::WPS84ToGCJ02(30.5610907200,104.0008778200));//计算机学院
    temp.append(Tool::WPS84ToGCJ02(30.5606957200,104.0017388200));
    temp.append(Tool::WPS84ToGCJ02(30.5604837200,104.0021948200));
    temp.append(Tool::WPS84ToGCJ02(30.5602867200,104.0023988200));//
    temp.append(Tool::WPS84ToGCJ02(30.5601718900,104.0025398400));
    temp.append(Tool::WPS84ToGCJ02(30.5594968900,104.0031678400));//一号运动场
    temp.append(Tool::WPS84ToGCJ02(30.5590118900,104.0036178400));
    temp.append(Tool::WPS84ToGCJ02(30.5583098900,104.0042138400));//东南门
}
