/**
 * @file frmpollconfig.h
 * @brief frmPollConfig 类实现头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:18:15
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
 *    <td> 2020-12-30 00:18:15 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef FRMPOLLCONFIG_H
#define FRMPOLLCONFIG_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmPollConfig;
}
/**
 * @brief NVCR 配置类，主要用于管理NVCR,IPC等的配置管理界面
 */
class frmPollConfig : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new frm Poll Config object
     * @param  parent           parent
     */
    explicit frmPollConfig(QWidget *parent = 0);
    /**
     * @brief Destroy the frm Poll Config object
     */
    ~frmPollConfig();

private slots:
    /**
     * @brief 添加一条数据
     */
    void on_btnAddOne_clicked();
    /**
     * @brief 添加所有数据
     */
    void on_btnAddAll_clicked();
    /**
     * @brief 移除一条数据
     */
    void on_btnRemoveOne_clicked();
    /**
     * @brief 移除所有数据
     */
    void on_btnRemoveAll_clicked();
    /**
     * @brief 表格点击响应
     */
    void on_btnExcel_clicked();
    /**
     * @brief 树节点双击，表示选中
     * @param  index         节点索引
     */
    void on_treeMain_doubleClicked(const QModelIndex &index);
    /**
     * @brief 表节点双击
     * @param  index         节点索引
     */
    void on_tableMain_doubleClicked(const QModelIndex &index);

private:
    Ui::frmPollConfig *ui;       ///< 图形数据指针
    QSqlQueryModel *queryModule; ///< sql查询模式
    /**
     * @brief 初始化无边框窗体
     */
    void InitStyle();
    /**
     * @brief 初始化窗体数据
     */
    void InitForm();
    /**
     * @brief 加载NVR及IPC数据
     */
    void LoadNVRIPC();
    /**
     * @brief 加载轮询数据
     */
    void LoadPollInfo();
    /**
     * @brief 获取NVRIP 对应的NVRID
     * @param  NVRIP           
     * @return QString id字符串
     */
    QString GetNVRID(QString NVRIP);
    /**
     * @brief 检查PCID是否存在
     * @param IPCID
     * @return 存在/存在
     */
    bool IsExistIPCID(QString IPCID);
    /**
     * @brief  在VM.db中查询摄像头的相关数据,主要根据NVRID查询
     * @param  NVRID            NVRID
     * @param  IPCID            IPCID-摄像头编号 
     * @param  IPCName          摄像头名称
     * @param  IPCRtspAddrMain  摄像头主码流地址
     * @param  IPCRtspAddrSub   摄像头子码流地址
     */
    void GetIPCInfo(QString NVRID, QStringList &IPCID, QStringList &IPCName,
                    QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub);
    /**
     * @brief  在VM.db中查询所有已近启用的摄像头的相关数据
     * @param  IPCID            摄像头编号 
     * @param  IPCName          摄像头名称
     * @param  NVRID            NVR编号
     * @param  NVRName          NVR名称
     * @param  IPCRtspAddrMain  主码流地址
     * @param  IPCRtspAddrSub   子码流地址
     */
    void GetIPCInfo(QStringList &IPCID, QStringList &IPCName,
                    QStringList &NVRID, QStringList &NVRName,
                    QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub);
    /**
     * @brief  在VM.db中查询摄像头的相关数据,主要根据IPCID和NVRID查询
     * @param  NVRID            NVRID
     * @param  IPCID            IPCID-摄像头编号 
     * @param  IPCName          摄像头名称
     * @param  IPCRtspAddrMain  摄像头主码流地址
     * @param  IPCRtspAddrSub   摄像头子码流地址
     */
    void GetIPCInfo(QString NVRID, QString IPCID, QString &IPCName,
                    QString &IPCRtspAddrMain, QString &IPCRtspAddrSub);
    /**
     * @brief  向数据库中写入信息
     * @param  IPCID            摄像头编号 
     * @param  IPCName          摄像头名称
     * @param  NVRID            NVR编号
     * @param  NVRName          NVR名称
     * @param  IPCRtspAddrMain  主码流地址
     * @param  IPCRtspAddrSub   子码流地址
     */
    void AddPollInfo(QString IPCID, QString IPCName,
                     QString NVRID, QString NVRName,
                     QString IPCRtspAddrMain, QString IPCRtspAddrSub);
};

#endif // FRMPOLLCONFIG_H
