#ifndef GROUP_H
#define GROUP_H

#include <QList>
#include "lesson.h"

class Group
{
public:
    explicit Group(QString name, QString department, QList<Lesson>& lessons);

private:
    QString m_name;
    QString m_department;
    QList<Lesson> m_lessons;
};

#endif // GROUP_H
