/**
 * @file frmnvr.h
 * @brief  frmNVR 实现头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:31:26
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
 *    <td> 2020-12-30 00:31:26 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释 </td>
 * </tr>
 * </table>
 */
#ifndef FRMNVR_H
#define FRMNVR_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmNVR;
}
/**
 * @brief NVR管理类，主要内容与 frmIPC 相同，不做过多叙述
 * 
 * 详见: @see frmIPC
 */
class frmNVR : public QDialog
{
    Q_OBJECT

public:
    explicit frmNVR(QWidget *parent = 0);
    ~frmNVR();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();
    void on_btnExcel_clicked();
    void on_tableMain_pressed(const QModelIndex &index);

private:
    Ui::frmNVR *ui;///< ui界面指针
    QSqlQueryModel *queryModule;///< sql查询模式

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
    void LoadNVRInfo();
     /**
     * @brief  检查是否已经存在此记录
     * @param  NVRID            相机编号
     * @return true             存在
     * @return false            不存在
     */
    bool IsExistNVRID(QString NVRID);
     /**
     * @brief  检查是否已经存在此记录
     * @param  NVRIP            相机编号
     * @return true             存在
     * @return false            不存在
     */
    bool IsExistNVRIP(QString NVRIP);

};

#endif // FRMNVR_H
