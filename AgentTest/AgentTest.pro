QT += testlib
QT -= gui
QT += core gui widgets network multimedia

TARGET = tst_agenttest
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_agenttest.cpp \
  ../Student/agent.cpp

HEADERS += \
  ../Student/agent.hh

INCLUDEPATH += ../Student\
    $$PWD/../course/Course
DEPENDPATH += ../Student\
    $$PWD/../course/Course
