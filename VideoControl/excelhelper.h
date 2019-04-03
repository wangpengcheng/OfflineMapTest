#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QObject>

class ExcelHelper : public QObject
{
    Q_OBJECT
private:
    explicit ExcelHelper(QObject *parent = 0);
    static ExcelHelper *_instance;

public:
    static ExcelHelper *Instance() {
        if (!_instance) {
            _instance = new ExcelHelper;
        }
        return _instance;
    }

    void ToExcel(QString fileName, QString sheetName,
                 QString title, QString columnNames[],
                 int columnWidths[], int columnCount, QStringList content);

signals:

public slots:

};

#endif // EXCELHELPER_H
