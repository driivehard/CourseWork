#include "schemework.h"

SchemeWork::SchemeWork(QString course, QString semester, QList<SubjectPlan>& subjects) :
    m_course(course), m_semester(semester), m_subjects(subjects)
{

}
