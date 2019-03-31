#include "excelhelper.h"
#include "myhelper.h"

ExcelHelper *ExcelHelper::_instance = 0;
ExcelHelper::ExcelHelper(QObject *parent) :
    QObject(parent)
{
}

void ExcelHelper::ToExcel(QString fileName, QString sheetName, QString title, QString columnNames[], int columnWidths[], int columnCount, QStringList content)
{
    //逐个拼接xml字符,再保存为xls文件
    QStringList html;

    //固定头部信息
    html.append("<?xml version=\"1.0\"?>\n");
    html.append("<?mso-application progid=\"Excel.Sheet\"?>\n");
    html.append("<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"\n");
    html.append(" xmlns:o=\"urn:schemas-microsoft-com:office:office\"\n");
    html.append(" xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n");
    html.append(" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"\n");
    html.append(" xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n");

    //文档信息
    html.append(" <DocumentProperties xmlns=\"urn:schemas-microsoft-com:office:office\">\n");
    html.append("  <LastAuthor>安防周界报警系统</LastAuthor>\n");
    html.append(QString("  <Created>%1</Created>\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
    html.append("  <Version>11.6360</Version>\n");
    html.append(" </DocumentProperties>\n");

    html.append(" <OfficeDocumentSettings xmlns=\"urn:schemas-microsoft-com:office:office\">\n");
    html.append("  <AllowPNG/>\n");
    html.append(" </OfficeDocumentSettings>\n");

    html.append(" <ExcelWorkbook xmlns=\"urn:schemas-microsoft-com:office:excel\">\n");
    html.append("  <WindowHeight>9795</WindowHeight>\n");
    html.append("  <WindowWidth>21435</WindowWidth>\n");
    html.append("  <WindowTopX>120</WindowTopX>\n");
    html.append("  <WindowTopY>75</WindowTopY>\n");
    html.append("  <WindowTopY>75</WindowTopY>\n");
    html.append("  <ProtectWindows>False</ProtectWindows>\n");
    html.append(" </ExcelWorkbook>\n");

    //样式表
    html.append(" <Styles>\n");
    html.append("  <Style ss:ID=\"Default\" ss:Name=\"Normal\">\n");
    html.append("   <Alignment ss:Vertical=\"Center\"/>\n");
    html.append("   <Borders/>\n");
    html.append("   <Font ss:FontName=\"宋体\" x:CharSet=\"134\" ss:Size=\"11\" ss:Color=\"#000000\"/>\n");
    html.append("   <Interior/>\n");
    html.append("   <NumberFormat/>\n");
    html.append("   <Protection/>\n");
    html.append("  </Style>\n");
    //标题样式
    html.append("  <Style ss:ID=\"s64\">\n");
    html.append("   <Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Center\"/>\n");
    html.append("   <Font ss:FontName=\"宋体\" x:CharSet=\"134\" ss:Size=\"14\" ss:Color=\"#000000\" ss:Bold=\"1\"/>\n");
    html.append("  </Style>\n");
    //带边框样式
    html.append("  <Style ss:ID=\"s91\">\n");
    html.append("  <Borders>\n");
    html.append("   <Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>\n");
    html.append("   <Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>\n");
    html.append("   <Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>\n");
    html.append("   <Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/>\n");
    html.append("  </Borders>\n");
    html.append(" </Style>\n");

    html.append(" </Styles>\n");

    //工作表名称
    html.append(QString(" <Worksheet ss:Name=\"%1\">\n").arg(sheetName));
    int rowCount = content.count(); //计算总行数

    //表格开始
    html.append(QString("  <Table ss:ExpandedColumnCount=\"%1\" ss:ExpandedRowCount=\"%2\" x:FullColumns=\"1\"\n").arg(columnCount).arg(rowCount + 2));
    html.append("   x:FullRows=\"1\" ss:DefaultColumnWidth=\"54\" ss:DefaultRowHeight=\"18\">\n");

    //设置字段宽度
    for (int i = 0; i < columnCount; i++) {
        html.append(QString("   <Column ss:AutoFitWidth=\"0\" ss:Width=\"%1\"/>\n").arg(QString::number(columnWidths[i])));
    }

    //表格标题
    html.append("   <Row ss:AutoFitHeight=\"0\" ss:Height=\"26.25\">\n");
    html.append(QString("    <Cell ss:MergeAcross=\"%1\" ss:StyleID=\"s64\"><Data ss:Type=\"String\">%2</Data></Cell>\n").arg(columnCount - 1).arg(title));
    html.append("   </Row>");

    //逐个添加字段名称
    html.append("   <Row ss:AutoFitHeight=\"0\">\n");
    for (int i = 0; i < columnCount; i++) {
        html.append("    <Cell ss:StyleID=\"s91\"><Data ss:Type=\"String\">" + columnNames[i] + "</Data></Cell>\n");
    }
    html.append("   </Row>\n");

    //逐个添加数据
    for (int i = 0; i < rowCount; i++) {
        html.append("   <Row ss:AutoFitHeight=\"0\">\n");
        QString temp = content[i];
        QStringList value = temp.split(";");
        foreach (QString str, value) {
            html.append("    <Cell ss:StyleID=\"s91\"><Data ss:Type=\"String\">" + str + "</Data></Cell>\n");
        }
        html.append("   </Row>\n");
    }
    html.append("  </Table>\n");

    //固定结尾格式
    html.append("  <WorksheetOptions xmlns=\"urn:schemas-microsoft-com:office:excel\">\n");
    html.append("   <PageSetup>\n");
    html.append("    <Header x:Margin=\"0.3\"/>\n");
    html.append("    <Footer x:Margin=\"0.3\"/>\n");
    html.append("    <PageMargins x:Bottom=\"0.75\" x:Left=\"0.7\" x:Right=\"0.7\" x:Top=\"0.75\"/>\n");
    html.append("   </PageSetup>\n");
    html.append("   <Unsynced/>\n");
    html.append("   <Selected/>\n");
    html.append("   <ProtectObjects>False</ProtectObjects>\n");
    html.append("   <ProtectScenarios>False</ProtectScenarios>\n");
    html.append("  </WorksheetOptions>\n");
    html.append(" </Worksheet>\n");
    html.append("</Workbook>\n");

    //写入文件
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QIODevice::Text)) {
        QTextStream text(&file);
        text.setCodec("UTF-8");
        text << html.join("");
    }
}
