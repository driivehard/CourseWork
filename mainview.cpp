#include "mainview.h"
#include "ui_mainview.h"
#include "loadform.h"
#include "correctform.h"
#include "resultform.h"
#include "setupform.h"


MainView::MainView(QWidget *parent, LoadForm& load, CorrectForm& correct, ResultForm& result, SetupForm& setup) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    load.setParent(this);
    correct.setParent(this);
    result.setParent(this);
    setup.setParent(this);
    ui->loLoadTab->addWidget(&load);
    ui->loSetupTab->addWidget(&setup);
    ui->loCorrectTab->addWidget(&correct);
    ui->loResultTab->addWidget(&result);


    ui->tabSetup->setEnabled(false);
    ui->tabCorrect->setEnabled(false);
    ui->tabResult->setEnabled(false);

    connect(&load, SIGNAL(btnOkClicked()), this, SLOT(onLoadClicked()));
    connect(&setup, SIGNAL(setupFormReady()), this, SLOT(onbtnSetupClicked()));
    connect(&correct, SIGNAL(NotifyCheckingDone()), this,SLOT(onCheckedClicked()));

}

void MainView::onLoadClicked()
{
    ui->tabSetup->setEnabled(true);
}

void MainView::onbtnSetupClicked()
{
    ui->tabCorrect->setEnabled(true);
}

void MainView::onCheckedClicked()
{
    ui->tabResult->setEnabled(true);
}

MainView::~MainView()
{
    delete ui;
}
