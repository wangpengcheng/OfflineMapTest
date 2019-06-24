#include "recordselectdialog.h"
#include "ui_recordselectdialog.h"
#include "src/tool.h"
RecordSelectDialog::RecordSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordSelectDialog)
{
    ui->setupUi(this);
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
    //点击更新日期选项
    QJsonObject temp_data;
    temp_data.insert("car_id",car_id);
    QString request_url="http://localhost/re_get_cars.php";
    QJsonObject test=Tool::NetWorkGet(request_url,temp_data);
    qDebug()<<test.size();
    qDebug()<<test.isEmpty();
    QJsonArray result_array=test.value("result").toArray();
    car_id_list_.clear();
    qDebug()<<result_array.at(0).toObject().value("record_date");
    date_list_.clear();
    for(int i=0;i<result_array.size();++i){
        date_list_.append(result_array.at(i).toObject().value("record_date").toString());
    }
}
