QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Context.cpp \
    Model/StatisticModel.cpp \
    Traversal/ITraversal.cpp \
    View/ChartCreator.cpp \
    View/ViewAdapter.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Context.h \
    MainWindow.h \
    Model/StatisticModel.h \
    Traversal/ITraversal.h \
    View/ChartCreator.h \
    View/ViewAdapter.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
