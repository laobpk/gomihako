#-------------------------------------------------
#
# Project created by QtCreator 2023-03-03T09:02:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gomihako
TEMPLATE = app

# 根据操作系统设置不同的变量或配置
CONFIG += c++11 force_debug_info

win32 {
    # Windows特定的配置
    message("Building for Windows")
#    LIBS += -lwinmm
    INCLUDEPATH += $$PWD/gamepad/SFML-2.6.1/include/
    LIBS += -L$$PWD/gamepad/SFML-2.6.1/lib/ -lsfml-window -lsfml-system
    LIBS += -lxinput
    DEFINES += MY_WINDOWS_DEFINE
}

linux {
    # Linux特定的配置
    message("Building for Linux")
    LIBS += -lpthread
    DEFINES += MY_LINUX_DEFINE
}

macx {
    # macOS特定的配置
    message("Building for macOS")
    LIBS += -framework CoreAudio
    DEFINES += MY_MACOS_DEFINE
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += translations/gomihako_zh_CN.ts
TRANSLATIONS += translations/gomihako_ja.ts
TRANSLATIONS += translations/gomihako_en.ts
TRANSLATIONS += translations/gomihako_ru.ts
TRANSLATIONS += translations/gomihako_de.ts
TRANSLATIONS += translations/gomihako_fr.ts
TRANSLATIONS += translations/gomihako_kr.ts
TRANSLATIONS_DIR = translations

SOURCES += \
    gamepad/gamepad.cpp \
    gamepad/joystickthread.cpp \
    gamepad/stickpos.cpp \
    gamepad/gamepaddraw.cpp \
        main.cpp \
    advancedtoolbox.cpp \
    mainwindow.cpp \
    form.cpp \
    framelesswidget.cpp \
    config.cpp \
    calcultor.cpp \
    player/player.cpp \
    gamepad/sfmltest.cpp

HEADERS += \
    advancedtoolbox.h \
    gamepad/gamepad.h \
    gamepad/joystickthread.h \
    gamepad/stickpos.h \
    gamepad/gamepaddraw.h \
    jsonioctrl.hpp \
    mainwindow.h \
    form.h \
    framelesswidget.h \
    config.h \
    calcultor.h \
    player/player.h \
    gamepad/sfmltest.h

FORMS += \
    gamepad/gamepad.ui \
    mainwindow.ui \
    form.ui \
    config.ui \
    calcultor.ui \
    player/player.ui

RESOURCES += \
    resource.qrc
