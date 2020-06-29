QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mpv_control.cpp \
    mpvradio.cpp \
    mpvradio_open.cpp

HEADERS += \
    mpvradio.h \
    mpvradio_open.h

FORMS += \
    mpvradio.ui \
    mpvradio_open.ui

target.path = /usr/local/bin
desktop.path = /usr/share/applications
desktop.files += mpvradio.desktop
INSTALLS += target desktop
CONFIG += link_pkgconfig
PKGCONFIG += mpv

DISTFILES += \
	mpvradio.desktop \
	mpvradio.spec
