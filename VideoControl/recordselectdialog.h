#ifndef RECORDSELECTDIALOG_H
#define RECORDSELECTDIALOG_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          recordselectdialog.h
** @brief         回访记录查询的操作窗口
** @details       通过这个窗口执行查询操作，实现回放的控制,主要功能是查询相关的数据并传递给Player进行回放控制。
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-24 周一  19:16:27
** @example
**
** 示例代码
**
*****************************************************************************/

#include <QDialog>
struct ShowChoose{
    int show_video_number;//显示视频数量，必须是2的倍数
    QVector<int> show_videos_index;//显示视频的下标索引。
};
struct MainSendMessage{
    int record_id;//record_id 号
    QList<QString> video_paths;//视频路径列表
    ShowChoose vidoe_show_paramer;//相关的显示输出参数
};
namespace Ui {
class RecordSelectDialog;
}

class RecordSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordSelectDialog(QWidget *parent = nullptr);
    ~RecordSelectDialog();
    inline MainSendMessage send_message(){return  this->send_message_;}
    void InitCarList();//初始化车辆选择列表
    void UpDateList(int car_id); //初始化日期列表
    void InitStartTime(); //初始化开始时间
    void UpdateCarComBox();//更新车辆选择提示
signals:
    void SendShowMessage(MainSendMessage);
private slots:
    void on_btnCancel_clicked();

    void on_cboxCarId_activated(int index);

private:
    Ui::RecordSelectDialog *ui;
    MainSendMessage send_message_;
    //数据列表
    QList<int> car_id_list_;//车辆列表
    QList<QString> date_list_;//日期列表
    QList<QString> time_list_;//时间列表


};

#endif // RECORDSELECTDIALOG_H
