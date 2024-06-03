QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = VeterinarClinic
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(debug, debug|release) {
    DESTDIR = build/debug

    unix {
        UI_DIR = build/debug/build_trash/.ui
        MOC_DIR = build/debug/build_trash/.moc
        OBJECTS_DIR = build/debug/build_trash/debug/.obj
    }
}

CONFIG(release, debug|release) {
    DESTDIR = build/release

    unix {
        UI_DIR = build/release/build_trash/.ui
        MOC_DIR = build/release/build_trash/.moc
        OBJECTS_DIR = build/release/build_trash/debug/.obj
    }
}

DIR_MODULES = src/modules
DIR_APP = src/apps
DIR_SRC = src
INCLUDEPATH += $${DIR_SRC}
INCLUDEPATH += $${DIR_MODULES}

SOURCES += \
    src/apps/authPanel/main.cpp \
    src/apps/authPanel/mainwindow.cpp \
    src/apps/doctorPanel/doctorpanel.cpp \
    src/apps/pacientPanel/changepassword.cpp \
    src/apps/pacientPanel/myanimals.cpp \
    src/apps/pacientPanel/patientpanel.cpp \
    src/apps/registraturePanel/registeranimal.cpp \
    src/apps/registraturePanel/registerpatient.cpp \
    src/apps/registraturePanel/registervisit.cpp \
    src/apps/registraturePanel/registraturepanel.cpp \
    src/modules/module_database/dbworker.cpp

HEADERS += \
    src/apps/authPanel/mainwindow.h \
    src/apps/doctorPanel/doctorpanel.h \
    src/apps/pacientPanel/changepassword.h \
    src/apps/pacientPanel/myanimals.h \
    src/apps/pacientPanel/patientpanel.h \
    src/apps/registraturePanel/registeranimal.h \
    src/apps/registraturePanel/registerpatient.h \
    src/apps/registraturePanel/registervisit.h \
    src/apps/registraturePanel/registraturepanel.h \
    src/modules/module_database/dbworker.h

FORMS += \
    src/apps/authPanel/mainwindow.ui \
    src/apps/doctorPanel/doctorpanel.ui \
    src/apps/pacientPanel/changepassword.ui \
    src/apps/pacientPanel/myanimals.ui \
    src/apps/pacientPanel/patientpanel.ui \
    src/apps/registraturePanel/registeranimal.ui \
    src/apps/registraturePanel/registerpatient.ui \
    src/apps/registraturePanel/registervisit.ui \
    src/apps/registraturePanel/registraturepanel.ui

INCLUDEPATH += $${DIR_MODULES}/module_database
INCLUDEPATH += $${DIR_APP}/pacientPanel
INCLUDEPATH += $${DIR_APP}/doctorPanel
INCLUDEPATH += $${DIR_APP}/registraturePanel

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
