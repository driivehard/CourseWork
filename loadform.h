#ifndef LOADFORM_H
#define LOADFORM_H

#include <QWidget>
#include "xlsxdocument.h"

namespace Ui {
class LoadForm;
}

class LoadForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoadForm(QWidget *parent = 0);
    ~LoadForm();
    QString getFile1();
    QString getFile2();
    void setFile1(QString file);
    void setFile2(QString file);

    QStringList getListGroups();
signals:
    void groupListComputed();
    void fileNamesReady();
    void btnOkClicked();

private slots:
    void on_btnOpenTimeTable_clicked();

    void on_btnOpenSchemework_clicked();

    void on_btnLoadFiles_clicked();

private:
    Ui::LoadForm *ui;
    QStringList listgroups;
    void loadFiles(QString file);
    QString m_filename1;
    QString m_filename2;
};

#endif // LOADFORM_H
