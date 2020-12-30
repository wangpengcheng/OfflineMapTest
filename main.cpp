#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtPlugin>
#include <QDebug>
#include <QDir>
#include <QWidget>
#include <QDesktopWidget>
#include <QDialog>
#include <QStandardPaths>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickWindow>
#include <QFontDatabase>
#include <QSharedPointer>
#include <QTimer>
#include <QTimeLine>
//使用location 注册类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include <QtLocation/private/qdeclarativecirclemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapquickitem_p.h>
#include <QtLocation/private/qdeclarativepolylinemapitem_p.h>
#include <QtLocation/private/qdeclarativegeomapitemgroup_p.h>
#include <QGeoPath>
//引入tool类
#include <QtQuick/private/qquickimage_p.h>
#include <QtQuick/private/qquickwindow_p.h>
#include <QtQuick/private/qquickitem_p.h>
#include "MapItems/tool.h"
//video
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//键盘监听
#include <QKeyEvent>
#include "test/screencontroltest.h"


//使用函数
#include "MapItems/busline.h"
#include "MapItems/busstation.h"
#include "MapItems/bus.h"
#include "MapItems/mapcontrlconnect.h"
#include "MainWindows/mainshowdialog.h"

#include "VideoPlayer/videodecodethread.h"
#include "VideoPlayer/streamvideowidget.h"
#include "VideoPlayer/myvideowidget.h"
#include "MainWindows/recordselectdialog.h"
#include "VideoPlayer/qtavvideowidget.h"
//主函数
#include "MainWindows/myhelper.h"
#include "MainWindows/frmmain.h"
#include "MainWindows/myapp.h"
#include "MainWindows/myreviewwidget.h"
#include "MainWindows/reviewwidget.h"
#include "QtAVWidgets/QtAVWidgets.h"


int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication app(argc, argv);
    QString path_string=QDir::tempPath();

    //添加字体
    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));
    //开启地图插件 use Plugin
    Q_IMPORT_PLUGIN(GeoServiceProviderFactory);
    app.setApplicationName("VM");         //设置应用程序名称
    app.setApplicationVersion("V201812"); //设置应用程序版本
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);//允许使用qquickwidget
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
    if(!mem.create(1)){
        myHelper::ShowMessageBoxError(QStringLiteral("程序已运行,软件将自动关闭!"));
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
    return app.exec();
}
