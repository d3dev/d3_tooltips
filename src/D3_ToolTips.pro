# -------------------------------------------------
# Project created by QtCreator 2012-08-04T13:12:30
# -------------------------------------------------
QT += core \
    gui \
    sql
TARGET = D3_ToolTips
TEMPLATE = app
SOURCES += main.cpp \
    Widget.cpp \
    D3_ToolTip.cpp \
    TableWidget.cpp \
    D3_Export.cpp
HEADERS += Widget.h \
    D3_ToolTip.h \
    TableWidget.h \
    D3_Export.h
FORMS += Widget.ui
win32:LIBS += -luser32
