#ifndef SHEET_H
#define SHEET_H

#include <QObject>
#include <QtWidgets>
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxsheetmodel.h"

using namespace QXlsx;

class Sheet : public QObject
{
    Q_OBJECT
public:
    explicit Sheet(QString sXlsFilePathName, QString sSheetName,
                   QXlsx::Document* pXlsx, SheetModel* pSheetModel,
                   QTableView* pTableView, Worksheet* pSheet,
                   QTabWidget* tabWidget, int iTabIndex, QObject *parent = nullptr);

QString m_sXlsFilePathName;
QString m_sSheetName;
QXlsx::Document* m_pXlsx;
SheetModel* m_pSheetModel;
QTableView* m_pTableView;
Worksheet* m_pSheet;
QTabWidget* m_pTabWidget;
int m_iTabIndex;

signals:

public slots:
};

#endif // SHEET_H
