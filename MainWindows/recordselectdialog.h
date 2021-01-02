/**
 * @file recordselectdialog.h
 * @brief 回访记录查询的操作窗口
 * @details 定义历史数据查询弹窗UI相关功能 \n
 * 通过这个窗口执行查询操作，实现回放的控制,主要功能是查询相关的数据并传递给Player进行回放控制。
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2019-06-24 19:16:27
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
 *    <td> 2019-06-24 19:16:27 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td> 完善类的基本功能 </td>
 * </tr>
 * <tr>
 *    <td> 2020-12-29 23:35:51 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#ifndef RECORDSELECTDIALOG_H
#define RECORDSELECTDIALOG_H

#include <QDialog>
/**
 * @brief 数据库基本映射类，主要包含数量和索引
 */
struct ShowChoose
{
    int show_video_number;          ///< 显示视频数量，必须是2的倍数
    QVector<int> show_videos_index; ///< 显示视频的下标索引。
};
/**
 * @brief 请求消息发送结构体，为主要的数据消息传送接口字段
 */
struct MainSendMessage
{
    int record_id;              ///< record_id 号
    QString start_datetime;     ///< 记录开始时间
    QList<QString> video_paths; ///< 视频路径列表
    //ShowChoose vidoe_show_paramer;///< 相关的显示输出参数
};
namespace Ui
{
    class RecordSelectDialog;
}
/**
 * @brief 消息选择框UI类
 */
class RecordSelectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Record Select Dialog object
     * @param  parent          parent
     */
    explicit RecordSelectDialog(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Record Select Dialog object
     */
    ~RecordSelectDialog();
    inline MainSendMessage send_message() { return this->send_message_; }
    /**
     * @brief 初始化车辆选择列表 \n
     * 主要是查询现存的车辆列表
     */
    void InitCarList();
    /**
     * @brief 初始化日期列表，查询车辆有记录的历史段,主要是天
     * @param  car_id       车辆编号
     */
    void UpDateList(int car_id);
    /**
     * @brief 更新日期选框
     */
    void UpDateComBox();
    /**
     * @brief 更新车辆选择提示
     */
    void UpdateCarComBox();
    /**
     * @brief 初始化开始时间
     * @param  car_id           车辆编号
     * @param  record_date      记录日期
     */
    void UpDateStartTime(int car_id, QString record_date);
    /**
     * @brief 更新时间选择函数
     */
    void UpDateTimeComBox();
    /**
     * @brief  查询记录主键
     * @param  car_id           车辆编号
     * @param  record_date      记录日期
     * @param  start_time       开始时间段
     */
    void UpDateRecordId(int car_id, QString record_date, QString start_time);
    /**
     * @brief 更新视频选择按钮，必须为2的倍数，一般为4个,只能是1,2,4;
     * @param  record_id       记录ID
     */
    void UpDateVideoShow(int record_id);
    /**
     * @brief  通过记录编号，查找视频文件路径
     * @param  record_id        记录编号
     * @return QList<QString>   视频信息列表
     */
    QList<QString> SelectVideosInfo(int record_id);
signals:
    /**
     * @brief 请求发送响应函数
     */
    void SendShowMessage(MainSendMessage);
private slots:
    /**
     * @brief 取消查询，关闭窗口
     */
    void on_btnCancel_clicked();
    /**
     * @brief  车辆编号下拉框响应
     * @param  index            车辆编号
     */
    void on_cboxCarId_activated(int index);
    /**
     * @brief  选择日期下拉框响应
     * @param  arg1        最终确定的值
     */
    void on_cboxSelectDate_activated(const QString &arg1);
    /**
     * @brief 查询按钮点击函数，查询历史记录
     */
    void on_btnSelect_clicked();
    /**
     * @brief 确定键槽函数，主要是更新回放视频列表
     */
    void on_btnOk_clicked();

private:
    Ui::RecordSelectDialog *ui;    ///< ui数据指针
    MainSendMessage send_message_; ///< 获取的消息结构体
    //数据列表
    QList<int> car_id_list_;       ///< 车辆列表
    QList<QString> date_list_;     ///< 日期列表
    QList<QString> time_list_;     ///< 时间列表
    int record_id = NULL;          ///< 最终输出记录编号
};

#endif // RECORDSELECTDIALOG_H
