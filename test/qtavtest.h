#ifndef QTAVTEST_H
#define QTAVTEST_H

#include <QObject>
#include <QWidget>
#include "3rdpart/QtAV/include/QtAV/QtAV.h"

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

class QtAVTest : public QWidget
{
    Q_OBJECT
public:
    explicit QtAVTest(QWidget *parent = nullptr);

public Q_SLOTS:
    void openMedia();
    void seekBySlider(int value);
    void seekBySlider();
    void playPause();
private Q_SLOTS:
    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();

private:
    QtAV::VideoOutput *m_vo;
    QtAV::AVPlayer *m_player;
    QSlider *m_slider;
    QPushButton *m_openBtn;
    QPushButton *m_playBtn;
    QPushButton *m_stopBtn;
    int m_unit;
};

#endif // QTAVTEST_H
