#ifndef PROVIDER_H
#define PROVIDER_H
#include <memory>

class Settings;
class Provider final
{
public:
    Provider();
    static Settings& GetSettingsAsSingleton();

private:
    static std::unique_ptr<Settings> m_instanceSettings;
};

#endif // PROVIDER_H
