#include "streamvideowidget.h"

StreamVideoWidget::StreamVideoWidget(QWidget *parent) : QWidget(parent)
{
    Init();
}
StreamVideoWidget::StreamVideoWidget(QSharedPointer<VideoDecodeThread> new_decode)
{
    set_decode_thread(new_decode);
}
//StreamVideoWidget::~StreamVideoWidget(){

//}
void StreamVideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成白色

    if (display_image.size().width() <= 0)
        return;

    //将图像按比例缩放成和窗口一样大小
    QImage img = display_image.scaled(this->size(), Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x, y), img); //画出图像
}
void StreamVideoWidget::slot_get_frame(QImage img)
{
    //图像复制
    display_image = img;
    //更新
    update();
}
void StreamVideoWidget::set_decode_thread(QSharedPointer<VideoDecodeThread> new_decode)
{
    //解除原有连接
    if (this->decode_thread_ != nullptr)
    {
        //断开连接
        disconnect(this->decode_thread_.get(), SIGNAL(SendFrame(QImage)), this, SLOT(slot_get_frame(QImage)));
    }
    //更改连接
    decode_thread_ = new_decode;
    //重新连接，信号
    Init();
}
void StreamVideoWidget::Init()
{
    if (decode_thread_ != nullptr)
    {
        connect(this->decode_thread_.get(), SIGNAL(SendFrame(QImage)), this, SLOT(slot_get_frame(QImage)));
        decode_thread_.get()->StartDecode();
        is_play_ = true;
    }
    else
    {
        qDebug() << "please input decode thread";
    }
}
void StreamVideoWidget::VideoPlay()
{
    if (decode_thread_ != nullptr)
    {
        Init();
    }
    else
    {
        qDebug() << "this point is empty";
    }
}
void StreamVideoWidget::VideoPause()
{
    if (is_play_)
    {
        if (decode_thread_ != nullptr)
        {
            //与原来的信号断开连接
            disconnect(this->decode_thread_.get(), SIGNAL(SendFrame(QImage)), this, SLOT(slot_get_frame(QImage)));
        }
        else
        {
            qDebug() << "this decode is empyt";
        }
        is_play_ = false;
    }
    else
    {
        qDebug() << "this file is already pause";
    }
}
