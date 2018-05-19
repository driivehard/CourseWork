#include "resultform.h"
#include "ui_resultform.h"
#include "correctform.h"

ResultForm::ResultForm(QWidget *parent, CorrectForm& correctForm) :
    QWidget(parent),
    m_correctForm(correctForm),
    ui(new Ui::ResultForm)
{
    ui->setupUi(this);
    connect(&correctForm, SIGNAL(NotifyButtonClicked()), this, SLOT(printFinalResults()));
}

ResultForm::~ResultForm()
{
    delete ui;
}


void ResultForm::printFinalResults()
{
    auto finalresults = m_correctForm.getFinalResults();
    auto schmresults = m_correctForm.getSchWorkResults();


    for(auto e: schmresults)
    {
        ui->infoText->append(QString(" %1 >> %2").arg(e.first).arg(e.second));
    }

    for(auto group: finalresults.keys())
    {
        ui->infoText->append(group);
        for(auto subject: finalresults.value(group).keys())
        {
            ui->infoText->append(QString("\t %1 -> %2").arg(subject).arg(finalresults.value(group).value(subject)*8) );
        }
    }


}
