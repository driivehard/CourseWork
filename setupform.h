#ifndef SETUPFORM_H
#define SETUPFORM_H

#include <QWidget>

namespace Ui {
class SetupForm;
}

class Settings;
class LoadForm;

class SetupForm : public QWidget
{
    Q_OBJECT

public:
    explicit SetupForm(QWidget *parent, LoadForm &load);
    ~SetupForm();
    LoadForm& getLoad();
    void setGroup(QStringList grp);
    void setCourse(QString course);
    void setSemester(QString semester);
    QString getCourse();
    QString getSemester();
    QStringList getGroup();

signals:
    void NotifyCourseChanged();
    void setupFormReady();

public slots:
    void UpdateSemester(int);
    void UpdateGroup();

    void UpdateRightWidget();
    void RemoveItemRightWidget();
    void setbtnSelectEnabled();
    void setbtnRemoveEnabled();
private slots:
    void on_btnOkSetup_clicked();

private:
    Ui::SetupForm *ui;
    int value;
    LoadForm& m_loadForm;
    QStringList m_group;
    QString m_course;
    QString m_semester;
};

#endif // SETUPFORM_H
