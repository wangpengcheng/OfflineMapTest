#ifndef MAINSHOWDIALOG_H
#define MAINSHOWDIALOG_H

#include <QDialog>
#include <QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QQuickWidget>
#include <QQuickView>
#include <QVBoxLayout>
#include <QSharedPointer>
#include <QComboBox>
#include <iostream>
#include <memory>
//地图类
#include <QtLocation/private/qdeclarativegeomap_p.h>
#include "VideoControl/videoshowwidget.h"

#include <QVideoWidget>

namespace Ui {
    class MainShowDialog;
}
class MainShowDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MainShowDialog(QWidget *parent = nullptr);
    ~MainShowDialog();
    void InitStackWidget();
    //简单的存取函数
    inline QQuickWidget* map_page(){return map_page_;}
    inline QWidget* video_page(){return video_page_;}
    inline QStackedWidget* stacked_widget(){return stacked_widget_;}
    inline VideoShowWidget<StreamVideoWidget>* video_widget(){return video_widget_;}
    inline std::shared_ptr<QDeclarativeGeoMap> show_map(){return show_map_;}
    inline std::shared_ptr<QDeclarativeGeoMap> re_show_map(){return re_show_map_;}
    inline QVideoWidget*  video_review_show_widget(){return video_review_show_widget_;}
private slots:
    void on_show_tab_choose_currentChanged(int arg1);
    void print_layout(int index);
    //void on_pushButton_clicked();

private:
    Ui::MainShowDialog *ui;
    //私有成员类
    QStackedWidget* stacked_widget_=nullptr;//中间间隔类
    QQuickWidget* map_page_=nullptr;//qml地图
    QWidget* video_page_=nullptr;//自定义视频展示页
    VideoShowWidget<StreamVideoWidget>* video_widget_=nullptr; //自定义视频展示widget
    QVBoxLayout* map_show_vbox_layout_=nullptr;// 地图水平布局
    QHBoxLayout* video_show_vbox_layout_=nullptr;// 视频水平布局
    QVBoxLayout* video_vbox_layout_=nullptr;//视频水平布局
    std::shared_ptr<QDeclarativeGeoMap> show_map_=nullptr;//地图指针方便获取地图
    QWidget* aggregative_show_page_=nullptr;//综合模式新的page;
    QGridLayout *aggregative_gridLayout_=nullptr;//综合模式的布局，方便设置
    QQuickWidget *speed_show_chart_widget_=nullptr;//仪表盘数据指针，/*ToDo 单独构造它的类，方便复用 */
    //设置视频回放显示
    QHBoxLayout* video_review_layout_=nullptr;
    QVideoWidget* video_review_show_widget_=nullptr;
    //回放地图显示窗口
    QQuickWidget* re_map_widget_=nullptr;
    std::shared_ptr<QDeclarativeGeoMap> re_show_map_=nullptr;//视频回放的地图

};

#endif // MAINSHOWDIALOG_H
