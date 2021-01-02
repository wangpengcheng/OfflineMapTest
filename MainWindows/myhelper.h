/**
 * @file myhelper.h
 * @brief myHelper 类实现头文件
 * @todo 将实现和接口进行分离，实现写入myHelper.cpp文件中
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:49:36
 * @copyright Copyright (c) 2020  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 23:49:36 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef MYHELPER_H
#define MYHELPER_H

#include <QtCore>
#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#endif
#include <QtNetwork>
#include <QtSql>
#include "frmmessagebox.h"
#include "frminputbox.h"

/* 说明:
 * 功能:窗体显示/编码设置/开机启动/文件选择与复制/对话框等
 * 作者:刘典武  QQ:517216493
 * 时间:2013-12-30  检查:2014-1-10
 */

/**
 * @brief 全局辅助操作类,均为静态函数
 * @details 主要实现:
 * - 窗体显示
 * - 编码设置
 * - 开机启动
 * - 文件选择与复制
 * - 对话框等
 */
class myHelper : public QObject
{

public:
    /**
     * @brief 设置为开机启动 
     * @param  IsAutoRun        是否开机启动
     * @param  AppName          应用名称
     * @param  AppPath          应用路径
     * @bug win10 存在兼容问题，不能正常使用
     */
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
    {
        QSettings *reg = new QSettings(
            QStringLiteral("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
            QSettings::NativeFormat);

        if (IsAutoRun)
        {
            reg->setValue(AppName, AppPath);
        }
        else
        {
            reg->setValue(AppName, "");
        }
    }

    /**
     * @brief 设置编码为UTF8,防止中文乱码
     */
    static void SetUTF8Code()
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    /**
     * @brief 设置为中文字符
     */
    static void SetChinese()
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/image/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    /**
     * @brief 设置指定样式
     * @param  qssFile          样式表路径
     */
    static void SetStyle(const QString &qssFile)
    {
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly))
        {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            QString PaletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(QColor(PaletteColor)));
            file.close();
        }
    }

    /**
     * @brief 判断是否是IP地址 
     * @param  IP               ip地址字符串
     * @return true             是
     * @return false            否
     */
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }

    /**
     * @brief  显示输入提示框
     * @param  info             提示框信息
     * @param  ok               提示框选择结果
     * @return QString          返回输入消息
     */
    static QString ShowInputBox(QString info, bool &ok)
    {
        frmInputBox input;
        input.SetMessage(info);
        ok = input.exec();
        return input.GetValue();
    }

    /**
     * @brief  消息提示框，无选项
     * @param  info             提示信息
     */
    static void ShowMessageBoxInfo(QString info)
    {
        frmMessageBox msg;
        msg.SetMessage(info, 0);
        msg.exec();
    }

    /**
     * @brief 错误警告框 仅确定按钮
     * @param  info            警告信息
     */
    static void ShowMessageBoxError(QString info)
    {
        frmMessageBox msg;
        msg.SetMessage(info, 2);
        msg.exec();
    }

    /**
     * @brief 显示询问框,确定和取消按钮 
     * @param  info             消息
     * @return int              执行结果
     */
    static int ShowMessageBoxQuesion(QString info)
    {
        frmMessageBox msg;
        msg.SetMessage(info, 1);
        return msg.exec();
    }

    /**
     * @brief 16进制字符串转字节数组
     * @param  str              16进制字符串
     * @return QByteArray       二进制字符串
     */
    static QByteArray HexStrToByteArray(QString str)
    {
        QByteArray senddata;
        int hexdata, lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len / 2);
        char lstr, hstr;
        for (int i = 0; i < len;)
        {
            hstr = str[i].toLatin1();
            if (hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if (i >= len)
            {
                break;
            }
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if ((hexdata == 16) || (lowhexdata == 16))
            {
                break;
            }
            else
            {
                hexdata = hexdata * 16 + lowhexdata;
            }
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }
    /**
     * @brief 将转字符换为16进制
     * @param  ch               字符
     * @return char             转换后的字符
     */
    static char ConvertHexChar(char ch)
    {
        if ((ch >= '0') && (ch <= '9'))
        {
            return ch - 0x30;
        }
        else if ((ch >= 'A') && (ch <= 'F'))
        {
            return ch - 'A' + 10;
        }
        else if ((ch >= 'a') && (ch <= 'f'))
        {
            return ch - 'a' + 10;
        }
        else
        {
            return (-1);
        }
    }

    /**
     * @brief 字节数组转16进制字符串
     * @param  data             二进制数组
     * @return QString          字符串
     */
    static QString ByteArrayToHexStr(QByteArray data)
    {
        QString temp = "";
        QString hex = data.toHex();
        for (int i = 0; i < hex.length(); i = i + 2)
        {
            temp += hex.mid(i, 2) + " ";
        }
        return temp.trimmed().toUpper();
    }

    /**
     * @brief 16进制字符串转10进制
     * @param  strHex           16进制字符串
     * @return int              10进制数
     */
    static int StrHexToDecimal(QString strHex)
    {
        bool ok;
        return strHex.toInt(&ok, 16);
    }

    /**
     * @brief 10进制字符串转10进制
     * @param  strDecimal           10进制字符串
     * @return int              10进制数
     */
    static int StrDecimalToDecimal(QString strDecimal)
    {
        bool ok;
        return strDecimal.toInt(&ok, 10);
    }

    /**
     * @brief 2进制字符串转10进制
     * @param  strBin           2进制字符串
     * @return int              10进制数
     */
    static int StrBinToDecimal(QString strBin)
    {
        bool ok;
        return strBin.toInt(&ok, 2);
    }

    /**
     * @brief 16进制字符串转2进制字符串
     * @param  strHex           16进制字符串
     * @return QString          最终结果字符串
     */
    static QString StrHexToStrBin(QString strHex)
    {
        uchar decimal = StrHexToDecimal(strHex);
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len < 8)
        {
            for (int i = 0; i < 8 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    /**
     * @brief 10进制转2进制字符串一个字节 
     * @param  decimal         10进制值 
     * @return QString         转换为字符串
     */
    static QString DecimalToStrBin1(int decimal)
    {
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len <= 8)
        {
            for (int i = 0; i < 8 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    /**
     * @brief 10进制转2进制字符串两个字节
     * @param  decimal          My Param doc
     * @return QString          转换为字符串
     */
    static QString DecimalToStrBin2(int decimal)
    {
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len <= 16)
        {
            for (int i = 0; i < 16 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    /**
     * @brief 10进制转16进制字符串,补零.
     * @param  decimal         原始数据
     * @return QString          输出字符串
     */
    static QString DecimalToStrHex(int decimal)
    {
        QString temp = QString::number(decimal, 16);
        if (temp.length() == 1)
        {
            temp = "0" + temp;
        }
        return temp;
    }

    /**
     * @brief 响应休眠函数
     * @param  sec        休眠时间
     */
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while (QTime::currentTime() < dieTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    /**
     * @brief 设置系统日期时间
     * @param  year           年
     * @param  month          月
     * @param  day            日
     * @param  hour           时
     * @param  min            分
     * @param  sec            秒
     */
    static void SetSystemDateTime(int year, int month, int day, int hour, int min, int sec)
    {
        QProcess p(0);

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();
    }

    /**
     * @brief 窗体居中显示
     * @param  frm              窗口指针
     * @param  deskWidth        桌面宽度
     * @param  deskHeigth       桌面高度
     */
    static void FormInCenter(QWidget *frm, int deskWidth, int deskHeigth)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeigth / 2 - frmY / 2);
        frm->move(movePoint);
    }

    /**
     * @brief 获取选择的文件，简单弹窗
     * @param  filter           文件后缀
     * @return QString          选择的文件地址
     */
    static QString GetFileName(QString filter)
    {
        return QFileDialog::getOpenFileName(0, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }
    /**
     * @brief 获取选择的文件路径集合，简单弹窗，多选框
     * @param  filter           文件后缀
     * @return QString          选择的文件地址列表
     */
    static QStringList GetFileNames(QString filter)
    {
        return QFileDialog::getOpenFileNames(0, "选择文件", QCoreApplication::applicationDirPath(), filter);
    }

    /**
     * @brief 选择的目录
     * @return QString  目录名称
     */
    static QString GetFolderName()
    {
        return QFileDialog::getExistingDirectory();
        ;
    }

    /**
     * @brief 获取文件名,含拓展名
     * @param  strFilePath      路径
     * @return QString          名称
     */
    static QString GetFileNameWithExtension(QString strFilePath)
    {
        QFileInfo fileInfo(strFilePath);
        return fileInfo.fileName();
    }

    /**
     * @brief 获取选择文件夹中的文件
     * @param  filter           筛选类型列表
     * @return QStringList      最终列表
     */
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if (!strFolder.length() == 0)
        {
            QDir myFolder(strFolder);
            if (myFolder.exists())
            {
                fileList = myFolder.entryList(filter);
            }
        }
        return fileList;
    }

    /**
     * @brief 文件夹是否存在
     * @param  strFolder        文件夹名称
     * @return true             存在
     * @return false            不存在
     */
    static bool FolderIsExist(QString strFolder)
    {
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    /**
     * @brief 文件是否存在
     * @param  strFile          文件名称
     * @return true     存在
     * @return false    不存在
     */
    static bool FileIsExist(QString strFile)
    {
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    /**
     * @brief 复制文件
     * @param  sourceFile       源文件
     * @param  targetFile       目标文件
     * @return true             复制成功
     * @return false            复制失败
     */
    static bool CopyFile(QString sourceFile, QString targetFile)
    {
        if (FileIsExist(targetFile))
        {
            if (ShowMessageBoxQuesion("文件已经存在,是否替换?") == 1)
            {
                return false;
            }
        }
        return QFile::copy(sourceFile, targetFile);
    }

    /**
     * @brief 异或加密算法，主要用来混淆
     * @param  str              原始字符串
     * @param  key              秘钥值
     * @return QString          最终字符串
     */
    static QString getXorEncryptDecrypt(QString str, char key)
    {
        QByteArray data = str.toLatin1();
        int size = data.size();
        for (int i = 0; i < size; i++)
        {
            data[i] = data[i] ^ key;
        }
        return QLatin1String(data);
    }

    /**
     * @brief 检查摄像机是否在线
     * @param  rtspAddr         摄像机地址
     * @return true             在线
     * @return false            不在线
     */
    static bool IPCEnable(QString rtspAddr)
    {
        QStringList temp = rtspAddr.split("/");
        QString ip = temp[2].split(":")[0];
        QString port = temp[2].split(":")[1];
        qDebug() << "point " << port.toInt();
        QTcpSocket tcpClient;
        tcpClient.abort();
        tcpClient.connectToHost(ip, port.toInt());
        //100毫秒没有连接上则判断该摄像机不在线
        bool ok = tcpClient.waitForConnected(100);
        return ok;
    }
};

#endif // MYHELPER_H
