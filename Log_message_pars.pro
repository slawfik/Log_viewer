#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T17:39:18
#
#-------------------------------------------------

QT       += core gui
INCLUDEPATH = c:/libxl-3.8.3.0/include_cpp
LIBS += c:/libxl-3.8.3.0/lib/libxl.lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Log_message_pars
TEMPLATE = app
RC_FILE = resources\resources.rc

#C:\Users\Tomas\Documents\qtProject\Log_message_pars\
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    mesage.cpp \
    parser_inst.cpp \
    log_pars.cpp \
    my_t_model.cpp \
    my_tmanual_model.cpp \
    statictic_msg.cpp \
    statistic_msg_parser.cpp \
    write_excel.cpp

HEADERS += \
    definition.h \
    mesage.h \
    parser_inst.h \
    log_pars.h \
    directory_watcher_action.h \
    my_t_model.h \
    my_tmanual_model.h \
    statictic_msg.h \
    statistic_msg_parser.h \
    write_excel.h

FORMS += \
    log_pars.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#IDI_ICON1 ICON DISCARDABLE "C:\Users\Tomas\Pictures\parser.png"
