/**
 * @file frmmessagebox.h
 * @brief frmMessageBox UI实现类
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:36:05
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
 *    <td> 2020-12-30 00:36:05 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档内容 </td>
 * </tr>
 * </table>
 */
#ifndef FRMMESSAGEBOX_H
#define FRMMESSAGEBOX_H

#include <QDialog>

namespace Ui
{
    class frmMessageBox;
}
/**
 * @brief 消息弹窗提示类；主要提示应用错误和警告信息 \n
 * 与 frmInputBox 相似，不做过多叙述
 * 详情 @see frmInputBox
 * 
 */
class frmMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmMessageBox(QWidget *parent = 0);
    ~frmMessageBox();

    void SetMessage(QString msg, int type);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmMessageBox *ui;

    QPoint mousePoint; ///< 鼠标拖动自定义标题栏时的坐标
    bool mousePressed; ///< 鼠标是否按下
    void InitStyle();  ///< 初始化无边框窗体
};

#endif // FRMMESSAGEBOX_H
