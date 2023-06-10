QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    directmessage.cpp \
    dmwindow.cpp \
    main.cpp \
    interface.cpp \
    network.cpp \
    post.cpp \
    user.cpp

HEADERS += \
    directmessage.h \
    dmwindow.h \
    interface.h \
    network.h \
    post.h \
    user.h

FORMS += \
    dmwindow.ui \
    interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    posts.txt \
    userdata.txt
