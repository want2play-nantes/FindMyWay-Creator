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
    imagearea.cpp \
    widgets/dragwidget.cpp \
    widgets/listgraph.cpp \
    dialog/projectsettingsdialog.cpp \
<<<<<<< HEAD
    core/map.cpp \
    core/node.cpp \
    core/edge.cpp \
    core/nodes/classroom.cpp \
    core/pathnode.cpp \
    core/finalnode.cpp
=======
    graphicview.cpp \
    graphicscene.cpp \
    widgets/graphicwidget.cpp \
    widgets/cornerN.cpp
>>>>>>> b67e33d1a688b777088c8ba75fe764a84c8c1072

HEADERS  += mainwindow.h \
    easypaintenums.h \
    imagearea.h \
    widgets/dragwidget.h \
    widgets/listgraph.h \
    dialog/projectsettingsdialog.h \
<<<<<<< HEAD
    core/map.h \
    core/node.h \
    core/edge.h \
    core/nodes/classroom.h \
    core/pathnode.h \
    core/finalnode.h
=======
    graphicview.h \
    graphicscene.h \
    widgets/graphicwidget.h \
    widgets/cornerN.h
>>>>>>> b67e33d1a688b777088c8ba75fe764a84c8c1072

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








