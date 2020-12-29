#include "buslinetest.h"


BusLineTest::BusLineTest()
{
    bus_line_=nullptr;
    bus_line_=new BusLine();
}
BusLineTest::~BusLineTest()
{
    if(bus_line_!=nullptr)
    {
        delete [] bus_line_;
        bus_line_=nullptr;
    }
}
void BusLineTest::ConstructFunctionTest()
{
    Tool::TestNoteTool("ConstructFunctionTest",0);
    //准备数据
    QList<QGeoCoordinate> temp_coordinates,temp_station_coordinates;
    AddCoordinateToList(temp_coordinates);
    //准备站点数据
    int station_array[]={0,3,12,16,29,34,36};
    for(int i=0;i<7;++i)//添加站点
    {
        temp_station_coordinates.append(temp_coordinates.at(station_array[i]));
    }
    //构造函数
    BusLine bus_line;//构造函数1
    BusLine bus_line1(temp_coordinates,temp_station_coordinates);//构造函数二
    if(bus_line.bus_line_name()=="")
    {
        qDebug()<<"the construct function0 is ok";
    }else {
        qDebug()<<"the construct function0 is eorr";
    }
    if(bus_line1.bus_station_list().size()==temp_station_coordinates.size()&&
       bus_line1.bus_poly_line()->pathLength()==temp_coordinates.size())
    {
        qDebug()<<"the construct function1 is ok";
        qDebug()<<bus_line1.bus_station_list().size();
    }else {
        qDebug()<<"the construct function1 is eorr";
    }
    Tool::TestNoteTool("ConstructFunctionTest",1);
    bus_line_=new BusLine(temp_coordinates,temp_station_coordinates);
}
void BusLineTest::ShowTest(QDeclarativeGeoMap *qMap)
{
    Tool::TestNoteTool("ShowTest",0);
    //判断是否为空
    if(bus_line_->bus_poly_line()->size().isEmpty())
    {
        //准备数据
        QList<QGeoCoordinate> temp_coordinates,temp_station_coordinates;
        AddCoordinateToList(temp_coordinates);
        //准备站点数据
        int station_array[]={0,3,12,16,29,34,36};
        for(int i=0;i<7;++i)//添加站点
        {
            temp_station_coordinates.append(temp_coordinates.at(station_array[i]));
        }
        bus_line_=new BusLine(temp_coordinates,temp_station_coordinates);
    }else {
        qDebug()<<"Please check input data;key points size is 0";
    }
   if(qMap!=nullptr&&
     bus_line_->bus_poly_line()->size().isEmpty())
   {
      qMap->addMapItemGroup(bus_line_);
   }else {
       qDebug()<<"Please give the right inputs";
   }
   Tool::TestNoteTool("ShowTest",1);
}
void BusLineTest::AddCoordinateToList(QList<QGeoCoordinate> &temp)
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
void BusLineTest::MainTest()
{
    Tool::TestNoteTool("BusLineMainTest",0);
    ConstructFunctionTest();
    Tool::TestNoteTool("BusLineMainTest",1);
}
