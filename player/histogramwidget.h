#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          histogramwidget.h
** @brief         频率显示分布类，在Player类中使用，已经废弃
** @details       Player中的关键组件
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:41:20
** @example
**
** 示例代码
**
*****************************************************************************/

#include <QThread>
#include <QVideoFrame>
#include <QAudioBuffer>
#include <QWidget>

class QAudioLevel;

class FrameProcessor: public QObject
{
    Q_OBJECT

public slots:
    void processFrame(QVideoFrame frame, int levels);

signals:
    void histogramReady(const QVector<qreal> &histogram);
};

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = nullptr);
    ~HistogramWidget();
    void setLevels(int levels) { m_levels = levels; }

public slots:
    void processFrame(const QVideoFrame &frame);
    void processBuffer(const QAudioBuffer &buffer);
    void setHistogram(const QVector<qreal> &histogram);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<qreal> m_histogram;
    int m_levels = 128;
    FrameProcessor m_processor;
    QThread m_processorThread;
    bool m_isBusy = false;
    QVector<QAudioLevel *> m_audioLevels;
};

#endif // HISTOGRAMWIDGET_H
