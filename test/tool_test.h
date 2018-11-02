#ifndef TOOL_TEST_H
#define TOOL_TEST_H
/*
 * 工具测试用例代码；测试Tool工具类
 * 王鹏程 2018-11-2 17:23
 * QQ 673018936
 * 使用方法：
 * #include "test/tool_test.h" //head
 * tool_test temp_test; //main function
 * 测试用例：
 * temp_test.WPS84Test();//wps84Test tool
 */

#include "tool.h"
class tool_test
{
public:
    tool_test();
    void WPS84Test();
    Tool m_tool;//tool指针成员对象
};

#endif // TOOL_TEST_H
