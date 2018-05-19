#include "startup.h"
#include "mainview.h"
#include "loadform.h"
#include "correctform.h"
#include "resultform.h"
#include "setupform.h"
#include "settings.h"
#include "provider.h"

Startup::Startup() : QObject(nullptr),
    m_loadForm(*new LoadForm(nullptr)),
    m_setupForm(*new SetupForm(nullptr, m_loadForm)),
    m_correctForm(*new CorrectForm(nullptr, m_loadForm, m_setupForm)),
    m_resultForm(*new ResultForm(nullptr, m_correctForm)),
    m_mainView(*new MainView(nullptr, m_loadForm, m_correctForm, m_resultForm, m_setupForm))
{
    Settings& my_settings = Provider::GetSettingsAsSingleton();
    my_settings.ParseJsonData();

}

void Startup::show() const
{
 m_mainView.show();
}

Startup::~Startup()
{
    delete &m_mainView;
}
