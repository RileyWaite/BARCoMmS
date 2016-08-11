#-------------------------------------------------
#
# Project created by QtCreator 2016-06-10T10:51:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BARCoMmS_DITL
TEMPLATE = app

SOURCES += main.cpp\
        bc_ditl.cpp \
    ../../../utils/EventDatabase.cpp \
    ../dependencies/net/EndPoint.cpp \
    ../dependencies/net/UDPConnection.cpp \
    ../dependencies/utils/ByteBuffer.cpp \
    ../dependencies/utils/String.cpp \
    ../dependencies/bc_event.cpp \
    bc_ditl_graph.cpp \
    bc_ditl_utils.cpp \
    bc_ditl_legend.cpp \
    bc_ditl_initTimes.cpp \
    bc_ditl_addEvent.cpp \
    bc_ditl_colorLib.cpp \
    bc_ditl_sevTreeItem.cpp \
    bc_ditl_treeItemClicked.cpp \
    bc_ditl_initEventNameList.cpp \
    bc_ditl_pduReceived.cpp \
    ../dependencies/bc_PacketListenerThread.cpp \
    bc_ditl_repaint.cpp

HEADERS  += bc_ditl.h \
    bc_ditl_graph.h \
    ../../../utils/EventDatabase.h \
    ../dependencies/net/EndPoint.h \
    ../dependencies/net/PDU.h \
    ../dependencies/net/UDPConnection.h \
    ../dependencies/net/UDPConnectionListener.h \
    ../dependencies/utils/ArrayList.h \
    ../dependencies/utils/ByteBuffer.h \
    ../dependencies/utils/String.h \
    bc_ditl_constants.h \
    bc_ditl_legend.h \
    bc_ditl_colorLib.h \
    bc_ditl_sevTreeItem.h \
    ../dependencies/bc_PacketListenerThread.h \
    ../dependencies/bc_Event.h

FORMS    += bc_ditl.ui \
    legend.ui

DISTFILES += ../resources/ss.qss

CONFIG += c++11
