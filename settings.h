#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);
    void ParseJsonData();
    QString getFirstyr() const {return m_firstyr;}
    QString getSecondyr() const {return m_secondyr;}
    QString getThirdyr() const {return m_thirdyr;}
    QString getFourthyr() const {return m_fourthyr;}

    QStringListModel& getFirstyrSemester() const {return m_firstyrsemester;}
    QStringListModel& getSecondyrSemester() const {return m_secondyrsemester;}
    QStringListModel& getThirdyrSemester() const {return m_thirdyrsemester;}
    QStringListModel& getFourthyrSemester() const {return m_fourthyrsemester;}

signals:
    void NotifyStatusMessage(QString message);

private:
    QString m_filename;
    QString m_firstyr;
    QString m_secondyr;
    QString m_thirdyr;
    QString m_fourthyr;
    QStringListModel& m_firstyrsemester;
    QStringListModel& m_secondyrsemester;
    QStringListModel& m_thirdyrsemester;
    QStringListModel& m_fourthyrsemester;

    QString ReadJsonFile();
    QString ReadJsonFromInternalResource();
    void SendErrorMessage(const QString &msg);
    JsonObjErrPair GetJsonObject(const QString &rawJson);
    void SetupCommands(QJsonObject json_obj);
    void ShowJsonParseError(QJsonParseError jsonError);
    QDir OpenConfigDirectory();
    void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);
};

#endif // SETTINGS_H
