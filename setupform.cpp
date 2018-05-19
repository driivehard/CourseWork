#include "setupform.h"
#include "ui_setupform.h"
#include "loadform.h"
#include "settings.h"
#include <QStringListModel>
#include <QDebug>


SetupForm::SetupForm(QWidget *parent, LoadForm& load) :
    QWidget(parent),
    ui(new Ui::SetupForm),
    m_loadForm(load)
{
    ui->setupUi(this);

    connect(&load, SIGNAL(groupListComputed()), this, SLOT(UpdateGroup()));

    Settings* my_settings = new Settings(nullptr,"settings.json");
    my_settings->ParseJsonData();
    ui->btnRemoveItem->setEnabled(false);
    ui->btnSelectOption->setEnabled(false);

    connect(ui->btnSelectOption, SIGNAL(pressed()), this, SLOT(UpdateRightWidget()));
    connect(ui->btnRemoveItem, SIGNAL(pressed()), this, SLOT(RemoveItemRightWidget()));

    connect(ui->leftListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(setbtnSelectEnabled()));
    connect(ui->rightListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(setbtnRemoveEnabled()));

    QStringList lists;
    lists << my_settings->getFirstyr() << my_settings->getSecondyr()
          << my_settings->getThirdyr() << my_settings->getFourthyr();

    ui->comboCourse->addItems(lists);
    ui->comboSemester->addItems(my_settings->getFirstyrSemester().stringList());

    connect(ui->comboCourse, SIGNAL(currentIndexChanged(int)), this , SLOT(UpdateSemester(int)));

}

SetupForm::~SetupForm()
{
    delete ui;
}

void SetupForm::setbtnSelectEnabled()
{
    ui->btnSelectOption->setEnabled(true);
}

void SetupForm::setbtnRemoveEnabled()
{
    ui->btnRemoveItem->setEnabled(true);
}

void SetupForm::UpdateRightWidget()
{
    if(ui->rightListWidget->findItems(ui->leftListWidget->currentItem()->text(),
                                      Qt::MatchExactly).isEmpty())
    {
        ui->rightListWidget->addItem(ui->leftListWidget->currentItem()->text());
    }
}

void SetupForm::RemoveItemRightWidget()
{
    qDebug() << ui->rightListWidget->currentRow() << "current row";
    qDebug() << ui->rightListWidget->count() << "count";
    if(ui->rightListWidget->count() > 0)
    {
        delete    ui->rightListWidget->takeItem(ui->rightListWidget->currentRow());
    }
    else if(ui->rightListWidget->count() == 0 && ui->rightListWidget->currentRow() <= 0)
    {
        ui->btnRemoveItem->setEnabled(false);
    }
}

LoadForm& SetupForm::getLoad()
{
    return m_loadForm;
}

void SetupForm::setGroup(QStringList grp)
{
    m_group = grp;
}

void SetupForm::setCourse(QString course)
{
    m_course = course;
}

void SetupForm::setSemester(QString semester)
{
    m_semester = semester;
}

QString SetupForm::getCourse()
{
    return m_course;
}

QString SetupForm::getSemester()
{
    return m_semester;
}

QStringList SetupForm::getGroup()
{
    return m_group;
}

void SetupForm::UpdateGroup()
{
    auto myvar = getLoad().getListGroups();
    qDebug() << myvar ;
    ui->leftListWidget->addItems(getLoad().getListGroups());
}


void SetupForm::UpdateSemester(int v)
{
    Settings* my_settings = new Settings(nullptr,"settings.json");
    switch(v)
    {
    case 0:
    {
        ui->comboSemester->clear();
        ui->comboSemester->addItems(my_settings->getFirstyrSemester().stringList());
        break;
    }
    case 1:
    {
        ui->comboSemester->clear();
        ui->comboSemester->addItems(my_settings->getSecondyrSemester().stringList());
    break;
    }
    case 2:
    {
        ui->comboSemester->clear();
        ui->comboSemester->addItems(my_settings->getThirdyrSemester().stringList());
    break;
    }
    case 3:
    {
        ui->comboSemester->clear();
        ui->comboSemester->addItems(my_settings->getFourthyrSemester().stringList());
    break;
    }
    default:
        break;
    }
}


void SetupForm::on_btnOkSetup_clicked()
{
    QStringList list;
    for(int row = 0; row < ui->rightListWidget->count(); row++)
    {
        list.push_back(ui->rightListWidget->item(row)->text());
    }
    setGroup(list);
    setCourse(ui->comboCourse->currentText());
    setSemester(ui->comboSemester->currentText());

    emit setupFormReady();
}
