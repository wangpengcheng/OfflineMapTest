/**
 * @file frminputbox.h
 * @brief frmInputBox 弹出框实现类
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:12:52
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
 *    <td> 2020-12-29 23:12:52 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释  </td>
 * </tr>
 * </table>
 */
#ifndef FRMINPUTBOX_H
#define FRMINPUTBOX_H

#include <QDialog>

namespace Ui
{
    class frmInputBox;
}
/**
 * @brief  输入弹出框，主要在 myHelper类中进行使用
 */
class frmInputBox : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new frm Input Box object
     * @param  parent           父类指针
     */
    explicit frmInputBox(QWidget *parent = 0);
    ~frmInputBox();
    /**
     * @brief 设置弹出提示消息
     * @param  title            消息内容
     */
    void SetMessage(QString title);
    /**
     * @brief Get the Value object
     * @return QString 输入的字符串
     */
    QString GetValue() const
    {
        return value;
    }

protected:
    /**
     * @brief QDialog 鼠标移动事件
     * @details 和 mousePressEvent 、mouseReleaseEvent 结合用于实现拖动效果
     * @param  e       事件指针
     */
    void mouseMoveEvent(QMouseEvent *e);
    /**
     * @brief QDialog 鼠标点击事件
     * @param  e       事件指针
     */
    void mousePressEvent(QMouseEvent *e);
    /**
     * @brief QDialog 鼠标释放事件
     * @param  e       事件指针
     */
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    /**
     * @brief 确认点击槽函数，点击确认后关闭窗口
     */
    void on_btnOk_clicked();

private:
    /**
     * @brief  设置窗口样式，初始化无边框窗体
     */
    void InitStyle();
    Ui::frmInputBox *ui; ///< UI界面指针
    QPoint mousePoint;   ///< 鼠标拖动自定义标题栏时的坐标
    bool mousePressed;   ///< 鼠标是否按下
    QString value;       ///< 输入的值
};

#endif // FRMINPUTBOX_H
