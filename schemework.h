#ifndef SCHEMEWORK_H
#define SCHEMEWORK_H

#include <QList>
#include "subjectplan.h"

class SchemeWork
{
public:
    explicit SchemeWork(QString course, QString semester, QList<SubjectPlan>& subjects);

private:
    QString m_course;
    QString m_semester;
    QList<SubjectPlan> m_subjects;
};

#endif // SCHEMEWORK_H
