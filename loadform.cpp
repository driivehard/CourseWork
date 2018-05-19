#include "loadform.h"
#include "ui_loadform.h"
#include <QFileDialog>
#include "institute.h"
#include "schemework.h"

#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"
#include "xlsxsheetmodel.h"

#include <QDebug>
#include "setupform.h"



LoadForm::LoadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadForm)
{
    ui->setupUi(this);
}

LoadForm::~LoadForm()
{
    delete ui;
}

void LoadForm::setFile1(QString file)
{
    m_filename1 = file;
}
QString LoadForm::getFile1()
{
    return m_filename1;
}
QString LoadForm::getFile2()
{
    return m_filename2;
}
void LoadForm::setFile2(QString file)
{
    m_filename2 = file;
}

QStringList LoadForm::getListGroups()
{
    return listgroups;
}

void LoadForm::on_btnOpenTimeTable_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Timetable *.xlsx"),
                                                 "C://", "Excel File (*.xlsx)");
    ui->timeTableLineEdit->setText(filename);
    setFile1(filename);
}

void LoadForm::on_btnOpenSchemework_clicked()
{
    QString filename2 = QFileDialog::getOpenFileName(this, tr("Open Scheme of Work *.xlsx"),
                                                    "C://", "Excel File (*.xlsx)");
    ui->schemeworkLineEdit->setText(filename2);
    setFile2(filename2);
}

void LoadForm::on_btnLoadFiles_clicked()
{
    ui->btnLoadFiles->setEnabled(false);
    QString filename1 = ui->timeTableLineEdit->text();

    loadFiles(filename1);

    emit btnOkClicked();
    emit groupListComputed();
    emit fileNamesReady();

}

void LoadForm::loadFiles(QString file){
    if(file.isEmpty())
    {
        return;
    }
    QXlsx::Document* timetable = new QXlsx::Document(file);

    QString group_russian("Группа");
    for (int i=1; i<=timetable->dimension().lastColumn(); ++i) {
        if(timetable->read(1, i).toString() == group_russian)
        {
            for(int j=i+4; j<=i+12; j+=4)
            {
                if(!timetable->read(1,j).toString().isEmpty())
                listgroups.append(timetable->read(1, j).toString());
            }
        }
    }
}




