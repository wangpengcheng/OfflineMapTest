#include "recordselectdialogtest.h"
#include "src/tool.h"

RecordSelectDialogTest::RecordSelectDialogTest(QObject *parent) : QObject(parent)
{

}

void RecordSelectDialogTest::InitCarsTest()
{
    Tool::TestNoteTool("InitCarsTest",0);
    this->test_record_dialog_.InitCarList();
    Tool::TestNoteTool("InitCarsTest",1);
}
