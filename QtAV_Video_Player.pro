#-------------------------------------------------
#
# Project created by QtCreator 2021-04-19T17:42:54
#
#-------------------------------------------------

QT       += core gui avwidgets opengl
# avwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

Release:LIBS += -L$$quote(C:\Qt\5.9.8\mingw53_32\lib) -L$$quote(C:\Users\Administrator\Desktop\QtAV-depends-windows-x86+x64\lib)  -lQt5AV  -lQt5AVWidgets
Debug:LIBS +=-L$$quote(C:\Qt\5.9.8\mingw53_32\lib) -L$$quote(C:\Users\Administrator\Desktop\QtAV-depends-windows-x86+x64\lib) -lQt5AVd  -lQt5AVWidgetsd

TARGET = QtAV_Video_Player
TEMPLATE = app

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
        GUI/VideoMain.cpp \
    Public/Qss.cpp \
    Gui/BaseVideoMain.cpp \
    Gui/VideoInfo.cpp \
    Gui/QtAVPlayer.cpp \
    Gui/VideoImg.cpp \
    Gui/PreviewVideo.cpp \
    Model/VoiceListView.cpp \
    Model/VoiceModelDelegate.cpp

HEADERS += \
        GUI/VideoMain.h \
    Public/Qss.h \
    Gui/BaseVideoMain.h \
    Gui/VideoInfo.h \
    Gui/QtAVPlayer.h \
    Gui/VideoImg.h \
    Gui/PreviewVideo.h \
    Model/VoiceListView.h \
    Model/VoiceModelDelegate.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    paint.qrc
