#ifndef CORRECTFORM_H
#define CORRECTFORM_H

#include <QWidget>
#include <QMap>
namespace Ui {
class CorrectForm;
}

class LoadForm;
class SetupForm;
class Sheet;

class CorrectForm : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectForm(QWidget *parent, LoadForm &loadform, SetupForm &setupform);
    ~CorrectForm();
    LoadForm& getLoadForm();
    SetupForm& getSetupForm();
    void setFile1(QString file);
    void setFile2(QString file);
    QString getFile1();
    QString getFile2();

    void setCourse(QString course);
    void setSemester(QString semester);
    void setGroup(QStringList grp);

    QString getCourse();
    QString getSemester();
    QStringList getGroup();

    void on_actionSave_triggered();
    void keyPressEvent(QKeyEvent *event);
    void on_actionCopy_triggered();
    void on_actionClose_File_triggered();
    QMap<QString, QString> getSubjectFile();
    QMap<QString,QMap<QString, qint32>> getFinalResults();
    QVector<QPair<QString,qint32>> getSchWorkResults();


public slots:


    void getNewSubjectNames();
    void calculateFromTimetable();
signals:
    void openExcelSpreadsheet();
    void NotifyCheckingDone();
    void NotifyNewSubjects();
    void NotifyCalculatingHrs();
    void NotifyButtonClicked();

private slots:
    void update();
    void onActionOpen();
    void collectingFiles();
    void setupSettings();

    void on_btnCorrectDone_clicked();

private:
    Ui::CorrectForm *ui;
    LoadForm& m_loadForm;
    SetupForm& m_setupForm;
    QString m_filename1;
    QString m_filename2;
    QString m_course;
    QString m_semester;
    QStringList m_group;
    QList<Sheet*> m_lSheets;
    QMap<QString, QString> old_new_subjects;
    QMap<QString,QMap<QString, qint32>> final_results;
    QVector<QPair<QString,qint32>> schwrk_vec;
};

#endif // CORRECTFORM_H
