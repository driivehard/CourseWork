#include "institute.h"

Institute::Institute(QObject *parent, qint16 course, qint16 semester, QList<Group> &groups) : QObject(parent),
    m_course(course), m_semester(semester), m_groups(groups)
{

}
