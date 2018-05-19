#include "settings.h"
#include <QString>
#include <QDir>
#include <QFile>
#include <utility>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>
#include <QStringListModel>
#include <QStandardPaths>
#include <QDebug>

static auto RESOURCE_PREFIX = QStringLiteral(":/json");

Settings::Settings(QObject *parent, QString filename) : QObject(parent),
    m_filename(filename),
    m_firstyrsemester(*new QStringListModel (this)),
    m_secondyrsemester(*new QStringListModel (this)),
    m_thirdyrsemester(*new QStringListModel (this)),
    m_fourthyrsemester(*new QStringListModel (this))
{
    ParseJsonData();
}

void Settings::ParseJsonData()
{
    QString raw_json = ReadJsonFile();
    if(raw_json.size() == 0) return;

    auto json_result = GetJsonObject(raw_json);
    auto json_err = json_result.second;
    if(json_err.error != QJsonParseError::NoError)
    {
        ShowJsonParseError(json_err);
    }
    auto json_obj = json_result.first;

    m_firstyr = json_obj.keys()[0];
    m_secondyr = json_obj.keys()[1];
    m_thirdyr = json_obj.keys()[2];
    m_fourthyr = json_obj.keys()[3];
    SetupCommands(json_obj);
}

void Settings::SetupCommands(QJsonObject json_obj)
{
    QJsonArray firstyr_array = json_obj["1"].toArray();
    QStringList firstyr_list;

    for(auto item: firstyr_array)
    {
        firstyr_list.append(QString::number(item.toInt()));

    }

    m_firstyrsemester.setStringList(firstyr_list);
    QJsonArray secondyr_array = json_obj["2"].toArray();
    QStringList secondyr_list;
    for(auto item: secondyr_array)
    {
        secondyr_list.append(QString::number(item.toInt()));
    }

    m_secondyrsemester.setStringList(secondyr_list);

    QJsonArray thirdyr_array = json_obj["3"].toArray();
    QStringList thirdyr_list;
    for(auto item: thirdyr_array)
    {
        thirdyr_list.append(QString::number(item.toInt()));
    }
    m_thirdyrsemester.setStringList(thirdyr_list);

    QJsonArray fourthyr_array = json_obj["4"].toArray();
    QStringList fourthyr_list;
    for(auto item: fourthyr_array)
    {
        fourthyr_list.append(QString::number(item.toInt()));
    }
    m_fourthyrsemester.setStringList(fourthyr_list);
}

void Settings::ShowJsonParseError(QJsonParseError jsonError)
{
    QString msg = tr("Error parsing Json settings file.\n");
    msg.append(jsonError.errorString());
    QMessageBox::critical(0,tr("Universal Timetable Checker"), msg);
}

JsonObjErrPair Settings::GetJsonObject(const QString & rawJson){
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(), &json_parse_error);
    QJsonObject json_obj = json_doc.object();
    return std::make_pair(json_obj, json_parse_error);
}

QString Settings::ReadJsonFile()
{
    auto default_settings = ReadJsonFromInternalResource();
    QDir config_dir = OpenConfigDirectory();
    auto path = config_dir.filePath(m_filename);
    QFile std_file(path);
    if(std_file.exists())
    {
        if(!std_file.open(QFile::ReadOnly|QFile::Text))
        {
            SendErrorMessage("Could not open " + path);
            return default_settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else
    {
        WriteDefaultsToStdConfigFile(std_file, default_settings);
        return default_settings;
    }
}

void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile, const QString &settings)
{
    int length = settings.length();
    if(!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
    {
        SendErrorMessage("Could not open file to write - " + stdConfigFile.fileName());
    }

    auto bytes_written = stdConfigFile.write(qPrintable(settings), length);
    if(bytes_written != length)
    {
        SendErrorMessage("Could not write the settings to -"+ stdConfigFile.fileName());
        if(!stdConfigFile.remove())
        {
            SendErrorMessage("Couldn't remove configuration file. Please delete " + stdConfigFile.fileName());
        }
    }
    stdConfigFile.close();
}

QDir Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if(!config_dir.exists())
    {
        QDir dir;
        dir.mkpath((config_dir.path()));
    }
    return config_dir;
}

QString Settings::ReadJsonFromInternalResource()
{
    QDir res_dir(RESOURCE_PREFIX);
    if (!res_dir.exists())
    {
        SendErrorMessage("Internal resource path missing "+ res_dir.canonicalPath());
        return "";
    }
    auto path = res_dir.filePath(m_filename);
    QFile res_file(path);

    if(!res_file.open(QFile::ReadOnly| QFile::Text))
    {
        SendErrorMessage("Could not open internal resource " + path);
        return "";
    }

    QString settings = res_file.readAll();
    return settings;
}

void Settings::SendErrorMessage(const QString& msg)
{
    emit NotifyStatusMessage(msg);
}
