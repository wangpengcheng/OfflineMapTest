/**
 * @file frmipc.h
 * @brief frmIPC 信息提示框类
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:20:27
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
 *    <td> 2020-12-29 23:20:27 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加注释文档 </td>
 * </tr>
 * </table>
 */
#ifndef FRMIPC_H
#define FRMIPC_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmIPC;
}
/**
 * @brief 主界面的IPC管理按钮点击后的显示界面 \n
 * 主要用来进行IPC的管理和删除修改
 */
class frmIPC : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new frmIPC object
     * @param  parent           父类指针
     */
    explicit frmIPC(QWidget *parent = 0);
    /**
     * @brief Destroy the frm I P C object
     */
    ~frmIPC();
private slots:
    /**
     * @brief 界面添加按钮响应
     * @details 主要用来添加新的流媒体地址
     */
    void on_btnAdd_clicked();
    /**
     * @brief 删除按钮响应 
     * @details 主要用来删除流媒体地址
     */
    void on_btnDelete_clicked();
    /**
     * @brief 更新按钮响应 
     * @details 主要用来更新流媒体地址列表
     */
    void on_btnUpdate_clicked();
    /**
     * @brief 保存按钮响应
     * @details 主要用来保存流媒体地址列表
     */
    void on_btnExcel_clicked();
    /**
     * @brief 表格框点击响应，主要是发送消息给侧边栏；进行信息显示
     * @param  index            对应的索引
     */
    void on_tableMain_pressed(const QModelIndex &index);
    /**
     * @brief 激活NVRID 
     * @param  arg1             My Param doc
     */
    void on_cboxNVRID_activated(const QString &arg1);
    /**
     * @brief  当IPC编号更改时的响应事件，主要用来校验地址和更新表格
     * @param  arg1             My Param doc
     */
    void on_txtIPCRtspAddrMain_textChanged(const QString &arg1);
    /**
     * @brief  激活后的显示变化
     * @param  arg1            新的标题显示名称
     */
    void on_cboxIPCID_activated(const QString &arg1);

private:
    /**
     * @brief  设置窗口样式，初始化无边框窗体
     */
    void InitStyle();
    /**
     * @brief 初始化窗体数据
     */
    void InitForm();
    /**
     * @brief 载入VM.db 中存储的网络摄像机数据
     */
    void LoadIPCInfo();
    /**
     * @brief 关联绑定NVR编号到右侧下拉框
     */
    void BindNVRID();
    /**
     * @brief  检查是否已经存在此记录
     * @param  NVRID            相机编号
     * @param  IPCID            Url编号
     * @return true             存在
     * @return false            不存在
     */
    bool IsExistIPCID(QString NVRID, QString IPCID);
    /**
     * @brief 获取NVR名称
     * @param  NVRID           
     * @return QString 名称字符串
     */
    QString GetNVRName(QString NVRID);
    Ui::frmIPC *ui;              ///< ui界面指针
    QSqlQueryModel *queryModule; ///< sql查询模式
};

#endif // FRMIPC_H
