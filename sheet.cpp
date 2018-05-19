#include "sheet.h"

Sheet::Sheet(QString sXlsFilePathName, QString sSheetName, Document *pXlsx,
             SheetModel *pSheetModel, QTableView *pTableView, Worksheet *pSheet,
             QTabWidget *tabWidget, int iTabIndex, QObject *parent) : QObject(parent),
    m_sXlsFilePathName(sXlsFilePathName), m_sSheetName(sSheetName), m_pXlsx(pXlsx),
    m_pSheetModel(pSheetModel), m_pTableView(pTableView), m_pSheet(pSheet),
    m_pTabWidget(tabWidget), m_iTabIndex(iTabIndex)
{

}
