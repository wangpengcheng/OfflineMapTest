#include "recordselectdialog.h"
#include "ui_recordselectdialog.h"
#include "src/tool.h"
#include "VideoControl/myhelper.h"
RecordSelectDialog::RecordSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordSelectDialog)
{
    ui->setupUi(this);
    InitCarList();
}

RecordSelectDialog::~RecordSelectDialog()
{
    delete ui;
}

void RecordSelectDialog::on_btnCancel_clicked()
{
    this->close();
}
void RecordSelectDialog::InitCarList()
{
    QJsonObject temp_data;
    temp_data.insert("date_time","");
    QString request_url="http://localhost/re_get_cars.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    car_id_list_.clear();
    qDebug()<<result_array.at(0).toObject().value("car_id");

    for(int i=0;i<result_array.size();++i){
        car_id_list_.append(result_array.at(i).toObject().value("car_id").toString().toInt());
    }
    //更新显示界面
    UpdateCarComBox();
}
void RecordSelectDialog::UpdateCarComBox()
{
    ui->cboxCarId->clear();

    for(int i=0;i<car_id_list_.size();++i)
    {
        ui->cboxCarId->insertItem(i,QStringLiteral("车辆 %1").arg(i));
    }
}

void RecordSelectDialog::on_cboxCarId_activated(int car_id)
{
    UpDateList(car_id);
    UpDateComBox();
}
void RecordSelectDialog::UpDateList(int car_id){
    //点击更新日期选项
    QJsonObject temp_data;
    temp_data.insert("car_id",car_id);
    QString request_url="http://localhost/re_get_cars.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    qDebug()<<result_array.at(0).toObject().value("record_date");
    date_list_.clear();
    for(int i=0;i<result_array.size();++i){
        date_list_.append(result_array.at(i).toObject().value("record_date").toString());
    }
}
void RecordSelectDialog::UpDateComBox()
{
    if(!date_list_.isEmpty())
    {
        ui->cboxSelectDate->clear();
        ui->cboxSelectDate->addItems(date_list_);
    }
}

void RecordSelectDialog::UpDateStartTime(int car_id,QString record_date)
{
    QJsonObject temp_data;
    temp_data.insert("car_id",car_id);
    temp_data.insert("record_date",record_date);//注意时间用短字符`-`连接
    QString request_url="http://localhost/re_get_datetime.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    qDebug()<<result_array.at(0).toObject().value("start_time");
    time_list_.clear();
    for(int i=0;i<result_array.size();++i){
        time_list_.append(result_array.at(i).toObject().value("start_time").toString());
    }
}
void RecordSelectDialog::UpDateTimeComBox()
{
    if(!time_list_.isEmpty()){
        ui->cboxStartTime->clear();
        ui->cboxStartTime->addItems(time_list_);
    }
}
//日期选择槽
void RecordSelectDialog::on_cboxSelectDate_activated(const QString &arg1)
{
    UpDateStartTime(ui->cboxCarId->currentIndex(),arg1);
    UpDateTimeComBox();
}
//查询按钮点击槽
void RecordSelectDialog::on_btnSelect_clicked()
{
    //获取前面的3个信息
    if(ui->cboxCarId->currentIndex()!=NULL&&
       !ui->cboxSelectDate->currentText().isEmpty()&&
       !ui->cboxStartTime->currentText().isEmpty())
    {
        UpDateRecordId(ui->cboxCarId->currentIndex(),
                       ui->cboxSelectDate->currentText(),
                       ui->cboxStartTime->currentText());
    }else{
        myHelper::ShowMessageBoxError(QStringLiteral("条件筛选错误"));
    }
}
void RecordSelectDialog::UpDateRecordId(int car_id,QString record_date,QString start_time)
{
    QJsonObject temp_data;
    temp_data.insert("car_id",car_id);
    temp_data.insert("record_date",record_date);//注意时间用短字符`-`连接
    temp_data.insert("start_time",start_time);
    QString request_url="http://localhost/re_get_datetime.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    record_id=result_array.at(0).toObject().value("record_id").toString().toInt();
    ui->boxRecordNumber->setValue(record_id);
    if(record_id!=NULL){
        myHelper::ShowMessageBoxInfo(QStringLiteral("查询成功"));
    }else{
         myHelper::ShowMessageBoxError(QStringLiteral("查询失败，请检查错误信息"));
    }


}
void RecordSelectDialog::UpDateVideoShow(int record_id)
{


}
QList<QString> RecordSelectDialog::SelectVideosInfo(int record_id)
{
    QList<QString> result;
    QJsonObject temp_data;
    temp_data.insert("record_id",record_id);
    QString request_url="http://localhost/re_get_videos.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    qDebug()<<result_array.at(0).toObject().value("video_path").toString();
    for(int i=0;i<result_array.size();++i){
        result.append(result_array.at(i).toObject().value("video_path").toString());
    }
    qDebug()<<result.size();
    return result;
}

void RecordSelectDialog::on_btnOk_clicked()
{
    //点击按钮，发送关键信号
    if(record_id!=NULL){
        //获取视频的播放源地址
        QList<QString> video_path=SelectVideosInfo(record_id);
        //更新对象
        send_message_.record_id=this->record_id;
        send_message_.start_datetime=ui->cboxSelectDate->currentText()+" "+ui->cboxStartTime->currentText();
        send_message_.video_paths=video_path;
        qDebug()<<send_message_.start_datetime;
        emit(SendShowMessage(send_message_));
        myHelper::ShowMessageBoxInfo(QStringLiteral("更新回放列表成功"));
        this->hide();

    }else{
        myHelper::ShowMessageBoxError(QString("Pealse Select Infomation Frist"));
    }
}
