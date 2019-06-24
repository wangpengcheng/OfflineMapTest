#ifndef RECORDSELECTDIALOGTEST_H
#define RECORDSELECTDIALOGTEST_H

#include <QObject>
#include "VideoControl/recordselectdialog.h"

class RecordSelectDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit RecordSelectDialogTest(QObject *parent = nullptr);
    void InitCarsTest();
signals:

public slots:

private:
    RecordSelectDialog test_record_dialog_;
};

#endif // RECORDSELECTDIALOGTEST_H
