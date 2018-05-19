#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T01:27:23
#
#-------------------------------------------------

QT       += core gui

include(qtxlsxwriter-master/src/xlsx/qtxlsx.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hardLearn3
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    loadform.cpp \
    setupform.cpp \
    correctform.cpp \
    resultform.cpp \
    startup.cpp \
    lesson.cpp \
    group.cpp \
    institute.cpp \
    subjectplan.cpp \
    schemework.cpp \
    excelreader.cpp \
    excelwriter.cpp \
    settings.cpp \
    provider.cpp \
    utils.cpp \
    xlsxsheetmodel.cpp \
    sheet.cpp


HEADERS  += mainview.h \
    loadform.h \
    setupform.h \
    correctform.h \
    resultform.h \
    startup.h \
    lesson.h \
    group.h \
    institute.h \
    subjectplan.h \
    schemework.h \
    excelreader.h \
    excelwriter.h \
    settings.h \
    provider.h \
    utils.h \
    xlsxsheetmodel_p. \
    xlsxsheetmodel.h \
    sheet.h \

FORMS    += mainview.ui \
    loadform.ui \
    setupform.ui \
    correctform.ui \
    resultform.ui

RESOURCES += \
    myresources.qrc
