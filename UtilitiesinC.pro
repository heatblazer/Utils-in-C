TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++03
QT     += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    vector.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    utils.h \
    LOGFILES.h\
    DList.h\
    LNode.h \
    vector.h

SOURCES += \
    utils.c \
    LOGFILES.c\
    DList.c
