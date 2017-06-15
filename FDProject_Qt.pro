QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    fdobject.cpp \
    checkblockobject.cpp \
    testthread.cpp \
    fdservice.cpp \
    analysisthread.cpp \
    unlockthread.cpp \
    deletethread.cpp \
    curshfilethread.cpp \
    fdtask.cpp \
    taskcenter.cpp \
    analysisthread.cpp \
    checkblockobject.cpp \
    curshfilethread.cpp \
    deletethread.cpp \
    fdobject.cpp \
    fdservice.cpp \
    fdtask.cpp \
    main.cpp \
    taskcenter.cpp \
    testthread.cpp \
    unlockthread.cpp \
    analysisthread.cpp \
    checkblockobject.cpp \
    curshfilethread.cpp \
    deletethread.cpp \
    fdobject.cpp \
    fdservice.cpp \
    fdtask.cpp \
    main.cpp \
    taskcenter.cpp \
    testthread.cpp \
    unlockthread.cpp \
    analysisthread.cpp \
    checkblockobject.cpp \
    curshfilethread.cpp \
    deletethread.cpp \
    fdobject.cpp \
    fdservice.cpp \
    fdtask.cpp \
    main.cpp \
    taskcenter.cpp \
    testthread.cpp \
    unlockthread.cpp \
    analysistask.cpp \
    curshfiletask.cpp \
    deletetask.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _UNICODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    fdobject.h \
    predefine.h \
    checkblockobject.h \
    testthread.h \
    fdservice.h \
    analysisthread.h \
    unlockthread.h \
    deletethread.h \
    curshfilethread.h \
    fdtask.h \
    taskcenter.h \
    analysisthread.h \
    checkblockobject.h \
    curshfilethread.h \
    deletethread.h \
    fdobject.h \
    fdservice.h \
    fdtask.h \
    predefine.h \
    taskcenter.h \
    testthread.h \
    unlockthread.h \
    analysisthread.h \
    checkblockobject.h \
    curshfilethread.h \
    deletethread.h \
    fdobject.h \
    fdservice.h \
    fdtask.h \
    predefine.h \
    taskcenter.h \
    testthread.h \
    unlockthread.h \
    analysisthread.h \
    checkblockobject.h \
    curshfilethread.h \
    deletethread.h \
    fdobject.h \
    fdservice.h \
    fdtask.h \
    predefine.h \
    taskcenter.h \
    testthread.h \
    unlockthread.h \
    analysistask.h \
    curshfiletask.h \
    deletetask.h

win32: LIBS += -L$$PWD/Lib/x64/ -lPsapi
