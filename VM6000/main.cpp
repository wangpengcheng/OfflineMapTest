#include <QApplication>
#include "myhelper.h"
#include "frmmain.h"
#include "myapp.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("VM");         //设置应用程序名称
    a.setApplicationVersion("V201412"); //设置应用程序版本
    myHelper::SetUTF8Code();            //设置程序编码为UTF-8
    myHelper::SetChinese();             //设置程序为中文字库

    //赋值当前应用程序路径和桌面宽度高度
    myApp::AppPath = QApplication::applicationDirPath() + "/";
    myApp::DeskWidth = qApp->desktop()->availableGeometry().width();
    myApp::DeskHeight = qApp->desktop()->availableGeometry().height();

    //程序加载时先加载所有配置信息
    myApp::ReadConfig();

    //加载和应用样式
    myHelper::SetStyle(myApp::AppStyle);

    //创建共享内存,判断是否已经运行程序
    QSharedMemory mem("VM");
    if (!mem.create(1)) {
        myHelper::ShowMessageBoxError(QStringLiteral("程序已运行,软件将自动关闭!"));
        return 1;
    }

    //判断当前数据库文件是否存在(如果数据库打开失败则终止应用程序)
    if (!myHelper::FileIsExist(myApp::AppPath + "VM.db")) {
        myHelper::ShowMessageBoxError(QStringLiteral("数据库文件不存在,程序将自动关闭!"));
        return 1;
    }

    QSqlDatabase DbConn;
    DbConn = QSqlDatabase::addDatabase("QSQLITE");
    DbConn.setDatabaseName(myApp::AppPath + "VM.db");

    //创建数据库连接并打开(如果数据库打开失败则终止应用程序)
    if (!DbConn.open()) {
        myHelper::ShowMessageBoxError(QStringLiteral("打开数据库失败,程序将自动关闭！"));
        return 1;
    }

    frmMain w;
    w.show();
    w.setGeometry(qApp->desktop()->availableGeometry());

    return a.exec();
}
