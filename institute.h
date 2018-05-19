#ifndef INSTITUTE_H
#define INSTITUTE_H

#include <QObject>
#include "group.h"

class Institute : public QObject
{
    Q_OBJECT
public:
    explicit Institute(QObject *parent, qint16 course, qint16 semester, QList<Group>& groups);

signals:

public slots:

private:
    qint16 m_course;
    QString m_semester;
    QList<Group> m_groups;
};

#endif // INSTITUTE_H
