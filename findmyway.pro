#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T14:45:04
#
#-------------------------------------------------

QT       += core gui

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
    datasingleton.cpp \
    additionaltools.cpp \
    undocommand.cpp \
    widgets/toolbar.cpp \
    widgets/shortcutedit.cpp \
    dialogs/resizedialog.cpp \
    dialogs/settingsdialog.cpp \
    dialogs/textdialog.cpp \
    instruments/abstractinstrument.cpp \
    instruments/abstractselection.cpp \
    instruments/lineinstrument.cpp \
    instruments/rectangleinstrument.cpp \
    instruments/ellipseinstrument.cpp \
    instruments/magnifierinstrument.cpp \
    instruments/selectioninstrument.cpp \
    dialogs/effectsettingsdialog.cpp \
    widgets/customfiltersettings.cpp \
    widgets/sharpenfiltersettings.cpp \
    widgets/imagepreview.cpp \
    widgets/gaussianblurfiltersettings.cpp \
    instruments/dragwidget.cpp \
    widgets/liste_graphe.cpp

HEADERS  += mainwindow.h \
    easypaintenums.h \
    imagearea.h \
    datasingleton.h \
    additionaltools.h \
    undocommand.h \
    widgets/toolbar.h \
    widgets/shortcutedit.h \
    dialogs/resizedialog.h \
    dialogs/settingsdialog.h \
    dialogs/textdialog.h \
    instruments/abstractinstrument.h \
    instruments/abstractselection.h \
    instruments/lineinstrument.h \
    instruments/rectangleinstrument.h \
    instruments/ellipseinstrument.h \
    instruments/magnifierinstrument.h \
    instruments/selectioninstrument.h \
    dialogs/effectsettingsdialog.h \
    widgets/customfiltersettings.h \
    widgets/abstracteffectsettings.h \
    widgets/sharpenfiltersettings.h \
    widgets/imagepreview.h \
    widgets/gaussianblurfiltersettings.h \
    instruments/dragwidget.h \
    widgets/liste_graphe.h


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








