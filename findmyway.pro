#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T14:45:04
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}

TARGET = findmyway
VERSION = 0.1.1
TEMPLATE = app

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

SOURCES += main.cpp\
        mainwindow.cpp \
    widgets/dragwidget.cpp \
    dialog/projectsettingsdialog.cpp \
    core/map.cpp \
    core/node.cpp \
    core/nodes/classroom.cpp \
    core/pathnode.cpp \
    core/finalnode.cpp \
    core/link.cpp \
    core/unmapmanagement.cpp\
    widgets/graphicwidget.cpp \
    graphicsscene.cpp


HEADERS  += mainwindow.h \
    easypaintenums.h \
    widgets/dragwidget.h \
    dialog/projectsettingsdialog.h \
    core/map.h \
    core/node.h \
    core/nodes/classroom.h \
    core/pathnode.h \
    core/finalnode.h \
    core/link.h \
    core/unmapmanagement.h \
    widgets/graphicwidget.h \
    graphicsscene.h

RESOURCES += \
    resources.qrc

target.path = /usr/bin
translations.path = /usr/share/easypaint/translations
translations.files = translations/*.qm
desktop.path = /usr/share/applications
icon.path = /usr/share/pixmaps
icon.files = media/logo/findmyway_64.png
isEmpty(QMAKE_LRELEASE) {
 win32 {
  QMAKE_LRELEASE =   $$[QT_INSTALL_BINS]\\lrelease.exe
}
else:QMAKE_LRELEASE =  $$[QT_INSTALL_BINS]/lrelease-qt4
}
isEmpty(TS_DIR) {
 TS_DIR =  translations
}
;TSQM.name = $$QMAKE_LRELEASE
;TSQM.input = TRANSLATIONS
;TSQM.output = $$TS_DIR/${QMAKE_FILE_BASE}.qm
;TSQM.commands = $$QMAKE_LRELEASE
;TSQM.CONFIG = no_link
;QMAKE_EXTRA_COMPILERS += TSQM
;PRE_TARGETDEPS += compiler_TSQM_make_all
INSTALLS += target translations desktop icon

FORMS += \
    mainwindow.ui \
    dialog/projectsettingsdialog.ui








