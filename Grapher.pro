QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/MainWindowProSink/mainwindowprosink.cpp \
    View/MainWindowSetSink/mainwindowsetsink.cpp \
    ViewModel/Commands/PaintCommand.cpp \
    ViewModel/Commands/differentialcommand.cpp \
    ViewModel/Commands/integralcommand.cpp \
    ViewModel/Sinks/ViewModelSink.cpp \
    Algorithm/Lexer.cpp \
    Algorithm/Tree.cpp \
    App/StartUICommand/StartUICommand.cpp \
    App/APP.cpp \
    Lib/qcustomplot.cpp \
    View/mainwindow.cpp \
    App/main.cpp \
    View/startinterface.cpp \
    ViewModel/ViewModel.cpp \
    Model/Model.cpp

HEADERS += \
    View/MainWindowProSink/mainwindowprosink.h \
    View/MainWindowSetSink/mainwindowsetsink.h \
    ViewModel/Commands/PaintCommand.h \
    ViewModel/Commands/differentialcommand.h \
    ViewModel/Commands/integralcommand.h \
    ViewModel/Sinks/ViewModelSink.h \
    Algorithm/Lexer.h \
    Algorithm/Tree.h \
    App/StartUICommand/StartUICommand.h \
    App/APP.h \
    Lib/qcustomplot.h \
    Common/etlbase.h \
    View/mainwindow.h \
    View/startinterface.h \
    ViewModel/ViewModel.h \
    Model/Model.h

FORMS += \
    View/mainwindow.ui \
    View/startinterface.ui

RC_FILE = Grapher.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
