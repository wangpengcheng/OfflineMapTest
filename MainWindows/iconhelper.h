/**
 * @file iconhelper.h
 * @brief IconHelper 类头文件
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-30 00:13:55
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
 *    <td> 2020-12-30 00:13:55 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档注释内容 </td>
 * </tr>
 * </table>
 */
#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
/**
 * @brief 应用ICON辅助类，主要用于加载应用图标
 */
class IconHelper : public QObject
{
private:
    /**
     * @brief 构造函数，方便实现饿汉单例
     * @param  parent           parent
     */
    explicit IconHelper(QObject *parent = 0);
    QFont iconFont;               ///< 图标数据
    static IconHelper *_instance; ///< 实例化的对象指针

public:
    /**
     * @brief 获取实例对象
     * @return IconHelper* 
     */
    static IconHelper *Instance()
    {
        static QMutex mutex;
        if (!_instance)
        {
            QMutexLocker locker(&mutex);
            if (!_instance)
            {
                _instance = new IconHelper;
            }
        }
        return _instance;
    }
    /**
     * @brief 从QLabel中设置icon
     * @param  lab              lab 标签
     * @param  c                字符
     * @param  size             大小
     */
    void SetIcon(QLabel *lab, QChar c, int size = 10);
    /**
     * @brief Set the Icon object
     * @param  btn              button数据指针
     * @param  c                字符
     * @param  size             大小
     */
    void SetIcon(QPushButton *btn, QChar c, int size = 10);
};

#endif // ICONHELPER_H
