QT += testlib
QT -= gui
QT += core gui widgets network multimedia

TARGET = tst_agenttest
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_agenttest.cpp \
  ../Student/agent.cpp \
  ../course/Course/game.cpp \
  ../course/Course/location.cpp \
  ../course/Course/deck.cpp \
  ../course/Course/settingsreader.cpp \
  ../course/Course/random.cpp \
  ../course/Course/ioexception.cpp \
  ../course/Course/keyexception.cpp \
  ../course/Course/formatexception.cpp \
  ../course/Course/rangeexception.cpp \
  ../course/Course/controlexception.cpp \
  ../course/Course/gameexception.cpp \
  ../course/Course/stateexception.cpp \
  ../course/Course/player.cpp

HEADERS += \
  ../Student/agent.hh \
  ../course/Course/game.h \
  ../course/Course/location.h \
  ../course/Course/deck.h \
  ../course/Course/settingsreader.h \
  ../course/Course/random.h \
  ../course/Course/ioexception.h \
  ../course/Course/keyexception.h \
  ../course/Course/formatexception.h \
  ../course/Course/rangeexception.h \
  ../course/Course/controlexception.h \
  ../course/Course/gameexception.h \
  ../course/Course/stateexception.h \
  ../course/Course/player.h


INCLUDEPATH += ../Student \
    $$PWD/../course/Course
DEPENDPATH += ../Student \
    $$PWD/../course/Course

RESOURCES += \
    ../course/Course/default_assets.qrc
