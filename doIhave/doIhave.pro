#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T20:08:07
#
#-------------------------------------------------

QT       += core gui     sql    printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doIhave
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog1.cpp \
    editing.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    editing.h

FORMS    += mainwindow.ui \
    dialog1.ui \
    editing.ui


contains(QT_ARCH, i386) {
    message("32-bit")
} else {
    message("64-bit")
}

RESOURCES += \
    images.qrc

#Windows Icon
win32 {
RC_FILE = winadmin.rc
}
