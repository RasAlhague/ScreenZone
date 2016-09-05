#-------------------------------------------------
#
# Project created by QtCreator 2016-09-04T00:21:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui


unix:!macx: LIBS += -L$$PWD/../UGlobalHotkey/ -lUGlobalHotkey

HEADERS  += $$PWD/../UGlobalHotkey/uglobalhotkeys.h
INCLUDEPATH += $$PWD/../UGlobalHotkey
DEPENDPATH += $$PWD/../UGlobalHotkey


unix:!macx: LIBS += -L$$PWD/../ImageMagick/Magick++/lib/.libs/ -lMagick++-7.Q16HDRI

HEADERS  += $$PWD/../ImageMagick/Magick++/lib/Magick++.h
INCLUDEPATH += $$PWD/../ImageMagick \
               $$PWD/../ImageMagick/Magick++/lib \
               $$PWD/../ImageMagick/Magick++/lib/Magick++

DEPENDPATH += $$PWD/../ImageMagick \
               $$PWD/../ImageMagick/Magick++/lib \
               $$PWD/../ImageMagick/Magick++/lib/Magick++



unix:!macx: LIBS += -L$$PWD/../ImageMagick/MagickCore/.libs/ -lMagickCore-7.Q16HDRI

INCLUDEPATH += $$PWD/../ImageMagick/MagickCore/.libs
DEPENDPATH += $$PWD/../ImageMagick/MagickCore/.libs
