#include "correctform.h"
#include "ui_correctform.h"
#include "QFileDialog"
#include <QtWidgets>
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxsheetmodel.h"
#include "loadform.h"
#include "setupform.h"
#include "sheet.h"
#include <QDebug>
#include <QMap>

using namespace QXlsx;

CorrectForm::CorrectForm(QWidget *parent, LoadForm& loadform, SetupForm& setupform ) :
    QWidget(parent),
    ui(new Ui::CorrectForm),
    m_loadForm(loadform),
    m_setupForm(setupform)
{
    ui->setupUi(this);
    connect(&setupform, SIGNAL(setupFormReady()), this, SLOT(setupSettings()));

    connect(&loadform, SIGNAL(fileNamesReady()), this, SLOT(collectingFiles()));

    connect(this, SIGNAL(openExcelSpreadsheet()), this, SLOT(onActionOpen()));
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start(1000);
    connect(this, SIGNAL(NotifyNewSubjects()), this, SLOT(getNewSubjectNames()));
    connect(this, SIGNAL(NotifyCalculatingHrs()), this, SLOT(calculateFromTimetable()));

}

CorrectForm::~CorrectForm()
{
    delete ui;
}

LoadForm &CorrectForm::getLoadForm()
{
    return m_loadForm;
}

SetupForm &CorrectForm::getSetupForm()
{
    return m_setupForm;
}

void CorrectForm::setFile2(QString file)
{
    m_filename2 = file;
}

QString CorrectForm::getFile1()
{
    return m_filename1;
}

QString CorrectForm::getFile2()
{
    return m_filename2;
}

void CorrectForm::setCourse(QString course)
{
    m_course = course;
}

void CorrectForm::setSemester(QString semester)
{
    m_semester = semester;
}

void CorrectForm::setGroup(QStringList grp)
{
    m_group = grp;
}

QString CorrectForm::getCourse()
{
    return m_course;
}

QString CorrectForm::getSemester()
{
    return m_semester;
}

QStringList CorrectForm::getGroup()
{
    return m_group;
}

void CorrectForm::setFile1(QString file)
{
    m_filename1 = file;
}

void CorrectForm::getNewSubjectNames()
{
    Document *timetable = new Document("time.xlsx");
    for(int row = 2; row <= timetable->dimension().lastRow(); ++row )
    {
        if( old_new_subjects.contains(timetable->read(row, 1).toString()))
        {
            old_new_subjects[timetable->read(row, 1).toString()] = timetable->read(row, 2).toString();
        }
    }
//emit signal to start calculating the # of hours in each week
    emit NotifyCalculatingHrs();

}

void CorrectForm::collectingFiles()
{
    setFile1(getLoadForm().getFile1());
    setFile2(getLoadForm().getFile2());

}

void CorrectForm::setupSettings()
{
    setGroup(getSetupForm().getGroup());
    setCourse(getSetupForm().getCourse());
    setSemester(getSetupForm().getSemester());

    for(int i=0; i<getGroup().size(); ++i)
    {
        qDebug() << getGroup().takeAt(i);
    }
    emit openExcelSpreadsheet();
}

void CorrectForm::onActionOpen()
{
    {
        QString fileName = getFile1();
        QXlsx::Document* file = new QXlsx::Document(fileName);

        QXlsx::Document* showntime = new QXlsx::Document;
        QString group_russian("Группа");
        QSet<QString> not_need;
        
        not_need << "Занятия по адресу:" << "ул. М.Пироговская, д.1" << "День"
                 << "самостоятельных" << "занятий";
        
        int k = 1;
        for(int p = 0; p < getGroup().size(); ++p)
        {
            for (int i=1; i<=file->dimension().lastColumn(); ++i) {

                if(file->read(1, i).toString() == getGroup().takeAt(p) && !file->read(1,i).toString().isEmpty())
                {
                    for(int l=3; l <=file->dimension().lastRow(); ++l)
                    {
                        if(file->read(l, i).toString().isEmpty()){
                        }else if(old_new_subjects.find(file->read(l, i).toString()) == old_new_subjects.end() && not_need.find(file->read(l, i).toString()) == not_need.end()){
                            old_new_subjects.insert(file->read(l, i).toString(), "");
                        }
                    }
                    ++k;

                }
            }
        }
        int i = 2;
        Format heading;
        heading.setFontBold(true);
        heading.setFontSize(16);
        showntime->write(1,1,QString("Current Subject Names"),heading);
        showntime->write(1,2,QString("New Subject Names"),heading);

        for(auto item: old_new_subjects.keys())
        {
            showntime->write(i,1,item);
            showntime->write(i, 2, "");
            ++i;
        }


        showntime->renameSheet(QString("Sheet1"), QString("Timetable"));
        QString nsheetName = "Timetable";
        Worksheet *workSheet = dynamic_cast<Worksheet *>(showntime->sheet(nsheetName));
        if(workSheet)
        {
            QTableView *view = new QTableView(this->ui->tabWidget);
            SheetModel* sheetModel = new SheetModel(workSheet, view);
            view->setModel(sheetModel);

            foreach(CellRange range, workSheet->mergedCells())
            {

                view->setSpan(range.firstRow()-1, range.firstColumn()-1, range.rowCount(), range.columnCount());
            }
            int iAddedTab = this->ui->tabWidget->addTab(view, nsheetName);
            m_lSheets.append(new Sheet(fileName, nsheetName, showntime, sheetModel, view, workSheet, this->ui->tabWidget, iAddedTab, this));
        }
    }

    {
        QString fileName = getFile2();
        QXlsx::Document* file1 = new QXlsx::Document(fileName);

        QXlsx::Document* schemewrk = new QXlsx::Document;
        QString sheetName = "SchemeWork";
        schemewrk->renameSheet(QString("Sheet1"), sheetName);


        QSet<QString> not_needed;
        not_needed << "Вариативная часть" << "Обязательные дисциплины" << "Дисциплины по выбору"
                   << "Наименование" << "Практики" << "Учебная практика" <<
                      "Практика по получению первичных профессиональных умений и навыков, в том числе первичных умений и навыков научно-исследовательской деятельности"
                   << "Производственная практика" << "Практика по получению профессиональных умений и опыта профессиональной деятельности"
                   << "Преддипломная практика" << "Государственная итоговая аттестация"
                   << "Подготовка и сдача государственного экзамена" << "Подготовка и сдача государственного экзамена"
                   << "Подготовка и защита ВКР" << "Факультативы";


        Format heading;
        heading.setFontBold(true);
        heading.setFontSize(16);
        schemewrk->write(1,1,QString("Scheme Of Work"),heading);
        schemewrk->renameSheet(QString("Sheet1"), sheetName);
        CellRange rg;
        rg.setFirstColumn(1);
        schemewrk->setColumnWidth(rg,40);

        QPair<QString,qint32> myPair;

        QString nsemester = "Семестр "+getSemester()+" [16 нед]";
        int q = 0;
        for(int j=1; j<=file1->dimension().lastColumn(); ++j)
        {
            if(file1->read(3,j).toString() == nsemester){
                q = j;
                break;
            }
        }
        int r = 1;
        for (int i=21; i<=file1->dimension().lastRow(); ++i) {
            if(!file1->read(i,1).toString().isEmpty() && not_needed.find(file1->read(i,1).toString()) == not_needed.end())
            {
                qint32 sum = 0;
                for(int j=q+1; j<=q+3; j++)
                {
                    sum += file1->read(i,j).toInt();
                }
                if( sum <= 0){
                    continue;
                }
                schemewrk->write(++r,1, file1->read(i,1).toString());
                myPair.first = file1->read(i,1).toString();
                myPair.second = sum;
                schwrk_vec.append(myPair);
            }
        }
        for(int i=0; i<schwrk_vec.size(); ++i)
        qDebug() << schwrk_vec.value(i).first << " -> " << schwrk_vec.value(i).second;
//        QString ncourse = "Курс " + getCourse();

//        for(int i=3; i<=file1->dimension().lastRow(); ++i)
//        {


//            for (int i=21; i<=file1->dimension().lastRow(); ++i) {
//                qint32 sum = 0;
//                for(int j=q+1; j<=q+4; j++)
//                {
//                    sum += file1->read(i,j).toInt();
//                    if(!file1->read(i,1).toString().isEmpty() && not_needed.find(file1->read(i,1).toString()) == not_needed.end())
//                    {
//                        schemewrk->write(++j,1, file1->read(i,1).toString());
//                        myPair.first = file1->read(i,1).toString();
//                        myPair.second = 0;
//                        schwrk_vec.append(myPair);
//                    }
//                }
//            }

        //}

        Worksheet *workSheet = dynamic_cast<Worksheet *>(schemewrk->sheet(sheetName));
        if(workSheet)
        {
            QTableView *view = new QTableView(this->ui->rightTabWidget);
            SheetModel* sheetModel = new SheetModel(workSheet, view);
            view->setModel(sheetModel);


            foreach(CellRange range, workSheet->mergedCells())
            {
                view->setSpan(range.firstRow()-1, range.firstColumn()-1, range.rowCount(), range.columnCount());
            }
            int iAddedTab = this->ui->rightTabWidget->addTab(view, sheetName);
            m_lSheets.append(new Sheet(fileName, sheetName, file1, sheetModel, view, workSheet, this->ui->rightTabWidget, iAddedTab, this));
        }
    }
}

void CorrectForm::on_actionSave_triggered()
{
    QString fileName = "time.xlsx";
    if (fileName.isEmpty())
    {
        return;
    }

    m_lSheets[0]->m_pXlsx->saveAs(fileName);
}

void CorrectForm::keyPressEvent(QKeyEvent* event)
{
//    if((this->m_lSheets.size() > 0) && (event->key() == Qt::Key_C && (event->modifiers() & Qt::ControlModifier)))
//    {
//        on_actionCopy_triggered();
//        event->accept();
//    }
}

void CorrectForm::on_actionCopy_triggered()
{
//    if(this->m_lSheets.size() > 0)
//    {
//        sheet* curSheet = this->m_lSheets[this->ui->leftWidget->currentIndex()];
//        QModelIndexList cells = curSheet->m_pTableView->selectionModel()->selectedIndexes();

//        QString text;
//        int currentRow = 0; // To determine when to insert newlines
//        foreach (const QModelIndex& cell, cells)
//        {
//            if (text.length() == 0)
//            {
//                // First item
//            }
//            else if (cell.row() != currentRow)
//            {
//                // New row
//                text += '\n';
//            }
//            else
//            {
//                // Next cell
//                text += '\t';
//            }
//            currentRow = cell.row();
//            text += cell.data().toString();
//        }

//        if (text.length() == 0)
//        {
//            QMessageBox::information(0, "ctrl+c","Please select the cells to be copied!", 1,0,0);
//            return;
//        }

//        QApplication::clipboard()->setText(text);
//    }
}

void CorrectForm::update()
{
    bool hasSelected = false;

        Sheet *curSheet = this->m_lSheets[this->ui->tabWidget->currentIndex()];
        QModelIndexList cells = curSheet->m_pTableView->selectionModel()->selectedIndexes();
        hasSelected = cells.size() > 0;

//    this->ui->actionCopy->setEnabled(hasSelected);
}

void CorrectForm::on_actionClose_File_triggered()
{
//    {
//        this->ui->Widget->clear();
//        this->setWindowTitle("Universal Timetable Checker!");
//        foreach(sheet* sheet, m_lSheets)
//        {
//            delete sheet;
//        }
    //    }
}



//I ended here today sunday 13 May






//void CorrectForm::synthesizingSubjectInfo()
//{
//    QMap<QString,QMap<QString, qint32>> ;

//    for(auto group: final_results.keys())
//    {
//        for(auto subject: final_results.value(group).keys())
//        {
//            if(old_new_subjects.find(subject) != old_new_subjects.end())
//        }
//    }

//}



QMap<QString, QString> CorrectForm::getSubjectFile()
{
    return old_new_subjects;
}

QMap<QString, QMap<QString, qint32> > CorrectForm::getFinalResults()
{
    return final_results;
}

QVector<QPair<QString, qint32> > CorrectForm::getSchWorkResults()
{
    return schwrk_vec;
}

void CorrectForm::calculateFromTimetable()
{
    QString fileName = getFile1();
    QXlsx::Document* file = new QXlsx::Document(fileName);
    QSet<QString> not_need;

    not_need << "Занятия по адресу:" << "ул. М.Пироговская, д.1" << "День"
             << "самостоятельных" << "занятий";



    for(int p = 0; p < getGroup().size(); ++p)
    {
        for (int i=1; i<=file->dimension().lastColumn(); ++i) {

            if(file->read(1, i).toString() == getGroup().takeAt(p) && !file->read(1,i).toString().isEmpty())
            {
                QString group = getGroup().takeAt(p);
                QMap<QString, qint32> results;
                for(int l=3; l <=file->dimension().lastRow(); ++l)
                {

                    if(results.find(file->read(l, i).toString()) == results.end() && !file->read(l, i).toString().isEmpty()
                            && not_need.find(file->read(l, i).toString()) == not_need.end())
                    {
                            results.insert(file->read(l, i).toString(),1);

                    } else if(not_need.find(file->read(l, i).toString()) != not_need.end())
                    {

                    } else if(file->read(l, i).toString().isEmpty())
                    {

                    } else
                    {
                         ++results[file->read(l, i).toString()];
                    }

                }
                final_results.insert(group, results);
            }
        }
    }
}

void CorrectForm::on_btnCorrectDone_clicked()
{
    on_actionSave_triggered();
    emit NotifyNewSubjects();
    emit NotifyCheckingDone();
    emit NotifyButtonClicked();
}
