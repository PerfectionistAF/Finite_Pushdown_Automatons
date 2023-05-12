QT       += core gui



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph.cpp \
    index.cpp \
    main.cpp \
    nfa.cpp \
    transition.cpp \
    utility.cpp

HEADERS += \
    graph.h \
    index.h \
    nfa.h \
    transition.h \
    utility.h

FORMS += \
    index.ui \
    nfa.ui \
    transition.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/boost_1_82_0
LIBS += -LC:/boost_1_82_0/stage/lib -llibboost_graph-mgw11-mt-x64-1_82.dll

RESOURCES += \
    resources.qrc


