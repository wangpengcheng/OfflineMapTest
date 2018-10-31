#ifndef TOOL_TEST_H
#define TOOL_TEST_H
#include "tool.h"
#include <qdebug.h>
class tool_test
{
public:
    tool_test();
    tool_test(const Tool temp);
    void WPS84Test();
    Tool m_tool;//tool成员对象
};

#endif // TOOL_TEST_H
