/**
 * @file excelhelper.h
 * @brief 程序执行帮助类，主要包含一个execl输出文件辅助函数；使用单例模式；
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2020-12-29 23:03:10
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
 *    <td> 2020-12-29 23:03:10 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 添加文档 </td>
 * </tr>
 * </table>
 */
#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QObject>
/**
 * @brief 程序执行帮助类，主要包含一个execl输出文件辅助函数；使用单例模式；
 */
class ExcelHelper : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief Construct a new Excel Helper object
     * @param  parent           父节点
     */
    explicit ExcelHelper(QObject *parent = 0);
    static ExcelHelper *_instance; ///< 全局唯一静态指针

public:
    /**
     * @brief 创建单例，使用懒汉模式进行创建
     * @return ExcelHelper* 
     */
    static ExcelHelper *Instance()
    {
        if (!_instance)
        {
            _instance = new ExcelHelper;
        }
        return _instance;
    }
    /**
     * @brief  讲相关配置转换为execl表格存储
     * @param  fileName         存储文件名称
     * @param  sheetName        表格名称
     * @param  title            表格标题
     * @param  columnNames      列名称
     * @param  columnWidths     列宽度
     * @param  columnCount      列数量
     * @param  content          列的上下文
     */
    void ToExcel(QString fileName, QString sheetName,
                 QString title, QString columnNames[],
                 int columnWidths[], int columnCount, QStringList content);
};

#endif // EXCELHELPER_H
