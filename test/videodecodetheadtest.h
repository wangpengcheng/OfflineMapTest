#ifndef VIDEOCODETHEADTEST_H
#define VIDEOCODETHEADTEST_H
/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.3
** This file is part of the OfflineMapTest project.
** @file          videocodetheadtest.h
** @brief         VideoCodeThead类的测试类
** @details       VideoCodeThead类的测试类，主要是为了完成测试。
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-11 周二  19:44:09
** @example
**
** 示例代码
**
*****************************************************************************/
#include <QLabel>
#include <QSharedPointer>
class VideoDecodeThread;
class StreamVideoWidget;
class VideoDecodeTheadTest
{
public:
    VideoDecodeTheadTest();
    ~VideoDecodeTheadTest();
    void MainTest();
    void LocalFileTest();
    StreamVideoWidget* test_show_label_=nullptr;
    QSharedPointer<VideoDecodeThread> test_videocodethead_=nullptr;
};

#endif // VIDEOCODETHEADTEST_H
