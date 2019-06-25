#include "tool.h"

#ifndef QT_QTPOSITIONING_MODULE_H
#include <QtPositioning>
#endif

#ifndef  QLOCATION_H
#include <QLocation>
#endif

#ifndef QGEOCOORDINATE_H
#include <QGeoCoordinate>
#endif

#ifndef QMATH_H
#include <QtMath>
#endif
#ifndef QDEBUG_H
#include <QDebug>
#endif

#include <QProcess>

Tool::Tool(QObject *parent):QObject(parent)
{

}

/*
 * 将经纬度映射到瓦片坐标体系，
 * 即将设置经纬度坐标偏差将wps84坐标设置为GGJ02坐标体系中国
 * 模块开始
 * mondel start
 */
/*定义基本常量*/
const long long  pi =3.1415926535897932384626;//定义pi=3.14
const long long  earth_radius =6378245.0;//定义地球半径
const long long  ee=0.00669342162296594323;//
const double NF_pi = 0.01745329251994329; // 弧度 PI/180

//将纬度lat转换为常用度数
double Tool::TransfromLatToDouble(const double x,
                                  const double y)
{
    double temp_result=0;
    temp_result += -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * qSqrt(qAbs(x));
    temp_result += (20.0 *  qSin(6.0 * x * pi) + 20.0 * qSin(2.0 * x * pi)) * 2.0 / 3.0;
    temp_result += (20.0 * qSin(y * pi) + 40.0 * qSin(y / 3.0 * pi)) * 2.0 / 3.0;
    temp_result += (160.0 * qSin(y / 12.0 * pi) + 320 * qSin(y * pi / 30.0)) * 2.0 / 3.0;
    return temp_result;
}

//将经度转化为常用度数
double Tool::TransfromLonToDouble(const double x,
                                  const double y)
{
    double temp_result;
    temp_result = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * qSqrt(qAbs(x));
    temp_result += (20.0 * qSin(6.0 * x * pi) + 20.0 * qSin(2.0 * x * pi)) * 2.0 / 3.0;
    temp_result += (20.0 * qSin(x * pi) + 40.0 * qSin(x / 3.0 * pi)) * 2.0 / 3.0;
    temp_result += (150.0 * qSin(x / 12.0 * pi) + 300.0 * qSin(x / 30.0 * pi)) * 2.0 / 3.0;
    return temp_result;
}

//对GPS坐标做处理，Wps84转Gcj-02
QGeoCoordinate Tool::WPS84ToGCJ02(const double lat,
                                  const double lon)
{

    double dLat,dLon,radLat,magic,sqrtMagic,mgLat, mgLon;
    dLat = TransfromLatToDouble(lon - 105.0, lat - 35.0);
    dLon = TransfromLonToDouble(lon - 105.0, lat - 35.0);
    radLat = lat/(180.0) * pi;
    magic = qSin(radLat);
    magic = 1 - ee*magic* magic;
    sqrtMagic = qSqrt(magic);
    dLat = (dLat*180.0)/((earth_radius*(1 - ee))/(magic*sqrtMagic)*pi);
    dLon = (dLon * 180.0) / (earth_radius / sqrtMagic * qCos(radLat) * pi);
    mgLat = lat + dLat;
    mgLon = lon + dLon;
    QGeoCoordinate result(mgLat, mgLon);
    return  result;
}
    /**
    * 将度转化为弧度
    * @param {degree} Number 度
    * @returns {Number} 弧度
    */
   double DegreeToRad(const double degree){
       return pi * degree/180;
   }

   /**
    * 将弧度转化为度
    * @param {radian} Number 弧度
    * @returns {Number} 度
    */
   double RadToDegree(const double rad){
       return (180 * rad) / pi;
   }

    /*将v值限定在a,b之间，纬度使用 */
   double GetRange(double v,
                   const double a,
                   const double b)
   {
           if(a !=NULL){
               v = qMax(v, a);
           }
           if(b != NULL){
               v = qMin(v, b);
           }
           return v;
       }

     /* 将v值限定在a,b之间，经度使用*/
     double GetLoop(double v,
                    const double a,
                    const double b)
     {
           while(v>b){
               v-=b-a;
           }
           while(v<a){
               v+=b-a;
           }
           return v;
     }
     /**
          * 计算两点之间的距离,两点坐标必须为经纬度
          * @param {point1} Point 点对象
          * @param {point2} Point 点对象
          * @returns {Number} 两点之间距离，单位为米
          */
double Tool::GetDistance(QGeoCoordinate point1,QGeoCoordinate point2)//高德地图坐标计算公式，针对高德地图坐标
{
             //判断类型
             if(!point1.isValid()||!point2.isValid())
             {
                 qDebug()<<"points are not full valid ,Please check input again!!!";
                 return 0;
             }
             double x1,x2,y1,y2,temp_result;
             x1 = NF_pi*point1.longitude();
             y1 = NF_pi*point1.latitude();
             x2 = NF_pi*point2.longitude();
             y2 = NF_pi*point2.latitude();
             double sinx1 = qSin(x1);
             double siny1 = qSin(y1);
             double cosx1 = qCos(x1);
             double cosy1 = qCos(y1);
             double sinx2 = qSin(x2);
             double siny2 = qSin(y2);
             double cosx2 = qCos(x2);
             double cosy2 = qCos(y2);
             double v1[3];
             v1[0] = cosy1 * cosx1 - cosy2 * cosx2;
             v1[1] = cosy1 * sinx1 - cosy2 * sinx2;
             v1[2] = siny1 - siny2;
             double dist = qSqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
             temp_result =qAsin(dist / 2) * 12742001.5798544;
             return  temp_result;
         }

/*
 * 地图经纬度坐标转换
 * 模块结束
 *mondel end;
 */

/*测试工具模块开始*/
/*测试提示*/
void Tool::TestNoteTool(const QString TestName,
                         const int i)
{
    if(i==0)
    {
        qDebug()<<QString("----------This %1 test Start----------").arg(TestName);
    }else if (i==1) {
        qDebug()<<QString("----------This %1 test End  ----------").arg(TestName);
    }else {
        qDebug()<<"Please input the right option";
    }

}

QString Tool::CreatFile(QString director_name,//文件夹名字
                    QString file_name,//文件名称
                    QString file_type//文件后缀
                    )
{
    QString file_full_path;//定义最终结果
    QString filePath=QDir::currentPath()+"/"+director_name;
    //QDateTime current_date_time =QDateTime::currentDateTime();
    //QString fileName=current_date_time.toString("yyyy-MM-dd-hh-mm-ss-zzz")+".txt";
    QString fileName=file_name+"."+file_type;
    file_full_path=filePath+"/"+fileName;
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"this path is not exite"<<endl;
        tempDir.mkpath(filePath);
    }
    QFile temp_file(file_full_path);
    //判断文件是否存在
    if(temp_file.exists())
    {
       qDebug()<<"FIle is aleadt exits";
        return file_full_path;
     }else{
            //存在打开，不存在创建
        if(!temp_file.open(QIODevice::ReadWrite)){
            qDebug()<<"creat file fail ";
            return "error";
        }else{
            //提示成功
            qDebug()<<"creat file success";
        }
            //写入内容,这里需要转码，否则报错。
//            QByteArray str = fileName.toUtf8();
//            //写入QByteArray格式字符串
//            temp_file.write(str);

    }
        //关闭文件
        temp_file.close();
        return file_full_path;
}
//网络请求线程异步失败；将其改为模板类，运行指定函数。
/*
input：request url string, post data QJSonObject
recturn back return QJsonObject
*/
QJsonObject Tool::NetWorkGet(QString url,//传输的地址
                             QJsonObject send_data//请求的数据
                            )
{
    QJsonObject result;
    QNetworkAccessManager save_manage;
    QNetworkRequest network_request;
    //定义阻塞线程，将异步变为同步
    QEventLoop eventLoop;
    network_request.setUrl(QUrl(url));

    network_request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QByteArray send_data_array=QJsonDocument(send_data).toJson();
//    qDebug()<<send_data_array;
    /*发送get网络请求*/
    connect(&save_manage, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    //获取返回结果
    QNetworkReply* reply=save_manage.post(network_request,send_data_array);
    //阻塞结束
    eventLoop.exec();
   // connect(&save_manage,&QNetworkAccessManager::finished,this,[=](QNetworkReply *reply){
    //处理收到的结果
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.isValid()){
            qDebug() << "status code=" << statusCode.toInt();
        }
        QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        if(reason.isValid()){
            qDebug() << "reason=" << reason.toString();
        }
        QNetworkReply::NetworkError err = reply->error();
        if(err != QNetworkReply::NoError) {
            qDebug() << "Failed: " << reply->errorString();
        }else {
            QByteArray read_all=reply->readAll();
            qDebug()<<read_all;
            // 获取返回内容
            result = QJsonDocument::fromJson(read_all).object();
            if(result.isEmpty()){
                qDebug()<<"recive error";
                qDebug()<<QString::fromLocal8Bit(read_all);
            }else {
                qDebug()<<result.isEmpty();
                qDebug()<<result.value("result").toInt();
            }
        }
        return  result;
}

void Tool::RunWindowsCommand(QString command){
    QProcess* cmd_process=new QProcess();
    QString program = "cmd";
    QStringList arguments;

    arguments <<"/r"<<command;
    cmd_process->start(program,arguments);
    if (cmd_process->waitForStarted())
    {
        cmd_process->waitForFinished();
        qDebug() << QString::fromLocal8Bit(cmd_process->readAllStandardOutput());
        qDebug() << "ok------";
    }else{
        qDebug() << "Failed to start";
    }
    //销毁
    DELETE_QOBJECT(cmd_process);
}
