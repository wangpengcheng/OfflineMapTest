#include "qtavvideowidget.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "QtAV/AudioOutput.h"
#include "MapItems/tool.h"
QtAVVideoWidget::QtAVVideoWidget(QWidget *parent) : QWidget(parent)
{
    //初始化相关数据
    Init();
}
QtAVVideoWidget::QtAVVideoWidget(QSharedPointer<QtAV::AVPlayer> new_player, QString new_vid)
{
    av_player_ = new_player;
    vid = new_vid;
    Init();
    av_player_->addVideoRenderer(this->video_render_);
    //绑定
}
QtAVVideoWidget::QtAVVideoWidget(const QtAVVideoWidget &rhs)
{
    if (this != &rhs)
    {
        /// TODO
    }
}

QtAVVideoWidget::~QtAVVideoWidget()
{
    DELETE_OBJECT(video_render_);
    DELETE_QOBJECT(video_layer_out_);
}
void QtAVVideoWidget::Init()
{
    //选择渲染模式。注意渲染模式一定要在初始化之前更改
    QtAV::VideoDecoderId v = QtAV::VideoRendererId_Widget;
    if (vid == QLatin1String("gl"))
    {
        v = QtAV::VideoRendererId_GLWidget2;
    }
    else if (vid == QLatin1String("wg"))
    {
        v = QtAV::VideoRendererId_Widget;
    }
    else if (vid == QLatin1String("d2d"))
    {
        v = QtAV::VideoRendererId_Direct2D;
    }
    else if (vid == QLatin1String("gdi"))
    {
        v = QtAV::VideoRendererId_GDI;
    }
    else if (vid == QLatin1String("xv"))
    {
        v = QtAV::VideoRendererId_XV;
    }
    //创建渲染器
    video_render_ = QtAV::VideoRenderer::create(v);
    video_render_->setRegionOfInterest(0, 0, 0, 0); //设置显示偏移为0；
    //创建水平布局
    video_layer_out_ = new QHBoxLayout(this);
    video_layer_out_->setMargin(1); //设置边距
    video_layer_out_->setSpacing(1);
    this->setLayout(video_layer_out_); //添加布局
    //将显示输出绑定到布局
    video_layer_out_->addWidget(video_render_->widget());
}
void QtAVVideoWidget::ChangeVideoRender(QtAV::VideoRenderer *new_render)
{
    if (new_render == video_render_)
    {
        qDebug() << "Same Render!!!!";
        return;
    }
    if (av_player_.isNull())
    {
        qDebug() << "Please set Player";
        return;
    }
    else
    {
        QList<QtAV::VideoRenderer *> render_list = av_player_->videoOutputs();
        if (render_list.isEmpty())
        {
            //先将旧render从布局删除
            video_layer_out_->replaceWidget(video_render_->widget(), new_render->widget());
            DELETE_OBJECT(video_render_);
            this->video_render_ = new_render;
            av_player_->addVideoRenderer(video_render_);
        }
        if (render_list.contains(new_render))
        {
            qDebug() << "this render is already in Playlist";
        }
        else
        {
            video_layer_out_->replaceWidget(video_render_->widget(), new_render->widget());
            av_player_->removeVideoRenderer(video_render_);
            DELETE_OBJECT(video_render_);
            video_render_ = new_render;
            av_player_->addVideoRenderer(video_render_);
        }
    }
}
//注意一定要先有再改
void QtAVVideoWidget::ChangeAVPlayer(QSharedPointer<QtAV::AVPlayer> new_player)
{
    qDebug() << "start av player change";
    if (!av_player_.isNull())
    {
        av_player_->removeVideoRenderer(this->video_render_);
    }
    av_player_ = new_player;
    av_player_->addVideoRenderer(this->video_render_);
}
