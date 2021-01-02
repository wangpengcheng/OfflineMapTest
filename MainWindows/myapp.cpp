#include "myapp.h"
#include "myhelper.h"

QString myApp::AppPath = QStringLiteral("");
int myApp::DeskWidth = 1024;
int myApp::DeskHeight = 768;

QString myApp::AppTitle = QStringLiteral("视频监管平台");
QString myApp::NVRType = QStringLiteral("深广;宝学;敏达;泰杰;汇迪;银江;海康;大华;宇视;皓维;银海");
QString myApp::IPCType = QStringLiteral("泰杰;敏达;银江;海康;大华;宇视");
QString myApp::AppStyle = ":/image/silvery.css";

int myApp::VideoDelayTime = 300;
bool myApp::UseVideoOffLineCheck = true;
int myApp::VideoOffLineCheckInterval = 30;
int myApp::RtspType = 1;

bool myApp::AutoRun = false;
bool myApp::AutoPoll = false;
int myApp::PollType = 1;
int myApp::PollInterval = 30;
int myApp::PollSleep = 0;

//默认16个通道全部显示
QString myApp::VideoType = "12";
//16个通道对应rtsp地址,方便自启动后自动加载
QString myApp::RtspAddr12 = "|||||||||||||||";
//最后配置信息,画面数
QString myApp::LastConfig = "1";

//读取配置文件
void myApp::ReadConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    //如果配置文件不存在,则以初始值继续运行
    if (!myHelper::FileIsExist(fileName))
    {
        //对应中文转成正确的编码
        myApp::AppTitle = myApp::AppTitle.toLatin1();
        myApp::NVRType = myApp::NVRType.toLatin1();
        myApp::IPCType = myApp::IPCType.toLatin1();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    myApp::AppTitle = set->value("AppTitle").toString();
    myApp::NVRType = set->value("NVRType").toString();
    myApp::IPCType = set->value("IPCType").toString();
    myApp::AppStyle = set->value("AppStyle").toString();
    myApp::VideoDelayTime = set->value("VideoDelayTime").toInt();
    myApp::UseVideoOffLineCheck = set->value("UseVideoOffLineCheck").toBool();
    myApp::VideoOffLineCheckInterval = set->value("VideoOffLineCheckInterval").toInt();
    myApp::RtspType = set->value("RtspType").toInt();
    myApp::AutoRun = set->value("AutoRun").toBool();
    myApp::AutoPoll = set->value("AutoPoll").toBool();
    myApp::PollType = set->value("PollType").toInt();
    myApp::PollInterval = set->value("PollInterval").toInt();
    myApp::PollSleep = set->value("PollSleep").toInt();
    myApp::VideoType = set->value("VideoType").toString();
    myApp::RtspAddr12 = set->value("RtspAddr16").toString();
    myApp::LastConfig = set->value("LastConfig").toString();
    set->endGroup();
}

//写入配置文件
void myApp::WriteConfig()
{
    QString fileName = myApp::AppPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    set->setValue("AppTitle", myApp::AppTitle);
    set->setValue("NVRType", myApp::NVRType);
    set->setValue("IPCType", myApp::IPCType);
    set->setValue("AppStyle", myApp::AppStyle);
    set->setValue("VideoDelayTime", myApp::VideoDelayTime);
    set->setValue("UseVideoOffLineCheck", myApp::UseVideoOffLineCheck);
    set->setValue("VideoOffLineCheckInterval", myApp::VideoOffLineCheckInterval);
    set->setValue("RtspType", myApp::RtspType);
    set->setValue("AutoRun", myApp::AutoRun);
    set->setValue("AutoPoll", myApp::AutoPoll);
    set->setValue("PollType", myApp::PollType);
    set->setValue("PollInterval", myApp::PollInterval);
    set->setValue("PollSleep", myApp::PollSleep);
    set->setValue("VideoType", myApp::VideoType);
    set->setValue("RtspAddr12", myApp::RtspAddr12);
    set->setValue("LastConfig", myApp::LastConfig);
    set->endGroup();
}
