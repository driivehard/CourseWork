#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

class LoadForm;
class CorrectForm;
class ResultForm;
class SetupForm;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent, LoadForm& load, CorrectForm& correct, ResultForm& result, SetupForm& setup);
    ~MainView();

public slots:
    void onLoadClicked();
    void onbtnSetupClicked();
    void onCheckedClicked();
private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
