#ifndef TOOL_TEST_H
#define TOOL_TEST_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version     5.11.1
** This file is part of the OfflineMapTest project.
** @file          tool_test.h
** @brief         tool_test class
** @details       tool_test class to test this tool class
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2018-11-2 周五  17:23:01
** @example
**
** #include "test/tool_test.h" //head
** //main function start
** tool_test temp_test; //init class
** temp_test.WPS84Test();//wps84Test tool
** //main function end
**
** QT Version    5.11.1
*****************************************************************************/

#include "src/tool.h"
class tool_test
{
public:
    tool_test();
    void WPS84Test();
    void TestNoteToolTest();
    void GetDistanceTest();
    void CreatFileTest();
    Tool m_tool;//tool指针成员对象
};

#endif // TOOL_TEST_H
