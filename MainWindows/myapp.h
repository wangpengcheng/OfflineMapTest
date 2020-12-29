/**
 * @file myapp.h
 * @brief myApp 实现头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:10:40
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
 *    <td> 2020-12-30 00:10:40 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef MYAPP_H
#define MYAPP_H

class QString;
/**
 * @brief 主要是应用启动时的各种配置参数
 */
class myApp
{
public:
    static QString AppPath;               ///< 应用程序路径
    static int DeskWidth;                 ///< 桌面可用宽度
    static int DeskHeight;                ///< 桌面可用高度
    static QString AppTitle;              ///< 界面标题
    static QString NVRType;               ///< 硬盘录像机厂家
    static QString IPCType;               ///< 网络摄像机厂家
    static QString AppStyle;              ///< 界面样式
    static int VideoDelayTime;            ///< 视频加载响应延时时间
    static bool UseVideoOffLineCheck;     ///< 视频断线检测
    static int VideoOffLineCheckInterval; ///< 视频断线检测间隔
    static int RtspType;                  ///< 码流类型
    static bool AutoRun;                  ///< 开机自动运行
    static bool AutoPoll;                 ///< 自动轮询
    static int PollType;                  ///< 轮询画面数
    static int PollInterval;              ///< 轮询间隔
    static int PollSleep;                 ///< 轮询延时
    static QString RtspAddr12;            ///< 12个通道对应rtsp地址
    static QString VideoType;             ///< 当前画面展示类型
    static QString LastConfig;            ///< 软件最后配置信息
    /**
     * @brief 读取配置文件
     */
    static void ReadConfig();
    /**
     * @brief 写入配置文件
     */
    static void WriteConfig();
};

#endif // MYAPP_H
