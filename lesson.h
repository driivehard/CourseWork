#ifndef LESSON_H
#define LESSON_H
#include <QString>
class Lesson
{
public:
    explicit Lesson(QString week, QString subject, QString lessonType);

private:
    QString m_week;
    QString m_subject;
    QString m_lessonType;
};

#endif // LESSON_H
