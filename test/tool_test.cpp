#include "test/tool_test.h"
#include <qdebug.h>
#include <QGeoCoordinate>

tool_test::tool_test():m_tool()
{

}

//测试wps84ToGejTest()
void tool_test::WPS84Test(){
   double lat_test=m_tool.TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   double lon_test=m_tool.TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   QGeoCoordinate coordinate=m_tool.WPS84ToGCJ02(30.5594483655,103.9976232481);
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
    m_tool.TestNoteTool("TestToolTest Function",0);
    m_tool.TestNoteTool("TestToolTest Function",1);
}
