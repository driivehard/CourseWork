#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

class LoadForm;
class SetupForm;
class CorrectForm;
class ResultForm;
class MainView;

class Startup final : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    LoadForm& m_loadForm;
    SetupForm& m_setupForm;
    CorrectForm& m_correctForm;
    ResultForm& m_resultForm;
    MainView& m_mainView;

};

#endif // STARTUP_H
