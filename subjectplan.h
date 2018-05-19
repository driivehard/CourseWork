#ifndef SUBJECTPLAN_H
#define SUBJECTPLAN_H

#include <QString>

class SubjectPlan
{
public:
    SubjectPlan(QString name, qint32 lectures, qint32 labs, qint32 practicals);

private:
    QString m_name;
    qint32 m_lectures;
    qint32 m_labs;
    qint32 m_practicals;
};

#endif // SUBJECTPLAN_H
