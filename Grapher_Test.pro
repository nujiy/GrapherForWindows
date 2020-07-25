QT +=  testlib
QT += core
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
    Algorithm/Lexer.cpp \
    Algorithm/Tree.cpp \
    Lib/qcustomplot.cpp \
    Model/Model.cpp \
    ViewModel/Commands/PaintCommand.cpp \
    ViewModel/Commands/differentialcommand.cpp \
    ViewModel/Commands/integralcommand.cpp \
    ViewModel/Sinks/ViewModelSink.cpp \
    ViewModel/ViewModel.cpp \
    Test/Grapher_Test.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Algorithm/Lexer.h \
    Algorithm/Tree.h \
    Common/etlbase.h \
    Lib/qcustomplot.h \
    Model/Model.h \
    ViewModel/Commands/PaintCommand.h \
    ViewModel/Commands/differentialcommand.h \
    ViewModel/Commands/integralcommand.h \
    ViewModel/Sinks/ViewModelSink.h \
    ViewModel/ViewModel.h
