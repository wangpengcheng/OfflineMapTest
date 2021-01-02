/**
 * @file switchbutton.h
 * @brief 自定义开关按钮控件头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:31:51
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
 *    <td> 2020-12-29 23:31:51 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档信息 </td>
 * </tr>
 * </table>
 */
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

/**
 * @brief 自定义开关按钮控件类
 * @details 用来控制配置文件的开关设置 \n
 * 主要用于在应用设置中，更改主要的样式
 */
class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Switch Button object
     * @param  parent           parent
     */
    explicit SwitchButton(QWidget *parent = 0);

    /**
     * @brief 获取当前选中状态
     * @return true  被选中
     * @return false 没有被选中
     */
    bool GetCheck() const
    {
        return isCheck;
    }
    /**
     * @brief 设置当前选中状态
     * @param  isCheck        是否选中
     */
    void SetCheck(bool isCheck);

private:
    bool isCheck;     ///< 是否选中
    QString styleOn;  ///< 开启样式
    QString styleOff; ///< 关闭样式

private slots:
    /**
     * @brief 样式改变的槽函数
     */
    void ChangeOnOff();
};
#endif // SWITCHBUTTON_H
