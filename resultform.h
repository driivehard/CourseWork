#ifndef RESULTFORM_H
#define RESULTFORM_H

#include <QWidget>

namespace Ui {
class ResultForm;
}
class CorrectForm;

class ResultForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultForm(QWidget *parent , CorrectForm& correctForm);
    ~ResultForm();

public slots:
    void printFinalResults();
private:
    CorrectForm& m_correctForm;
    Ui::ResultForm *ui;

};

#endif // RESULTFORM_H
