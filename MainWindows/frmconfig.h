/**
 * @file frmconfig.h
 * @brief 系统配置界面类，主要是配置系统参数
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:08:22
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
 *    <td> 2020-12-29 23:08:22 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QDialog>

namespace Ui
{
    class frmConfig;
}
/**
 * @brief 统配置界面类，主要是配置系统参数
 * @details 主界面系统设置按钮弹出界面
 */
class frmConfig : public QDialog
{
    Q_OBJECT

public:
    explicit frmConfig(QWidget *parent = 0);
    ~frmConfig();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_btnOk_clicked();
    void on_btnClearNVR_clicked();
    void on_btnClearIPC_clicked();
    void on_btnClearPoll_clicked();
    void on_btnClearAll_clicked();

private:
    Ui::frmConfig *ui;

    QPoint mousePoint;  //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;  //鼠标是否按下
    void InitStyle();   //初始化无边框窗体
    void InitForm();    //初始化窗体数据

};

#endif // FRMCONFIG_H
