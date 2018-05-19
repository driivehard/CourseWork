#include "group.h"

Group::Group(QString name, QString department, QList<Lesson> &lessons):
    m_name(name), m_department(department), m_lessons(lessons)
{

}
