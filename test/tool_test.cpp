#include "test/tool_test.h"
#include <qdebug.h>
#include <QGeoCoordinate>

tool_test::tool_test():m_tool()
{

}

//测试wps84ToGejTest()
void tool_test::WPS84Test(){
   double lat_test=Tool::TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   double lon_test=Tool::TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   QGeoCoordinate coordinate=Tool::WPS84ToGCJ02(30.5594483655,103.9976232481);
   qDebug()<<"--------This test start--------";
   qDebug()<<"This test lat is <<"<<lat_test;
   qDebug()<<"This test lon is <<"<<lon_test;
   qDebug()<<"This test coordinate is <<"<<coordinate.toString();
   qDebug("This test coordinate's Latitude is %0.8f",coordinate.latitude());
   qDebug("This test coordinate's Lotitude is %0.8f",coordinate.longitude());
   qDebug()<<"--------This test end--------";

}
void tool_test::TestNoteToolTest()
{
    Tool::TestNoteTool("TestToolTest Function",0);
    Tool::TestNoteTool("TestToolTest Function",1);
}
void tool_test::GetDistanceTest()
{
    Tool::TestNoteTool("GetDistanceTest",0);
    double test_1=Tool::GetDistance(QGeoCoordinate(39.923423,116.368904),
                                     QGeoCoordinate(39.922501,116.387271));
    qDebug()<<QString::number(test_1,'f',10);
     Tool::TestNoteTool("GetDistanceTest",1);

}
void tool_test::CreatFileTest(){
    Tool::TestNoteTool("Tool CreateFile Test",0);
    QString file_name="test";
    QString file_type="mp4";
    QString director_name="video";
    QString result=Tool::CreatFile(director_name,file_name,file_type);
    qDebug()<<"this file full path is"<<result;
    Tool::TestNoteTool("Tool CreateFile Test",1);
}
void tool_test::NetWorkGetTest(){
    Tool::TestNoteTool("NetWorkGetTest",0);
    QJsonObject temp_data;
    temp_data.insert("record_id",5);
    QString request_url="http://localhost/re_get_gps.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    qDebug()<<result_array.at(10);
    qDebug()<<result_array.size();
    Tool::TestNoteTool("NetWorkGetTest",1);
}
