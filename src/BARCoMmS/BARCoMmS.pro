#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T08:35:10
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BARCoMmS
TEMPLATE = app

# QMAKE_CXXFLAGS += -O2
QMAKE_CFLAGS += -std=c99

SOURCES += main.cpp \
    ../modules/BARCoMmS_Bulletin/bc_bulletin.cpp \
    ../modules/BARCoMmS_Bulletin/fswitem.cpp \
    ../modules/BARCoMmS_Bulletin/item.cpp \
    ../modules/BARCoMmS_Bulletin/sorting.cpp \
    ../modules/BARCoMmS_CFDP/barcomms_cfdp.cpp \
    ../modules/BARCoMmS_CFDP/buffer.cpp \
    ../modules/BARCoMmS_CFDP/classmessages.cpp \
    ../modules/BARCoMmS_CFDP/help.cpp \
    ../modules/BARCoMmS_CFDP/options.cpp \
    ../modules/BARCoMmS_CFDP/output.cpp \
    ../modules/BARCoMmS_CFDP/requests.cpp \
    ../modules/BARCoMmS_CFDP/setter.cpp \
    ../modules/BARCoMmS_CFDP/sim.cpp \
    ../modules/BARCoMmS_CFDP/updatecycles.cpp \
    ../modules/BARCoMmS_CFDP/worker.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_addEvent.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_colorLib.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_event.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_graph.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_initEventNameList.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_initTimes.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_legend.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_pduReceived.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_repaint.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_sevTreeItem.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_treeItemClicked.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_utils.cpp \
    ../modules/BARCoMmS_DITL/bc_ditl_constants.cpp \
    ../modules/BARCoMmS_CFDP/cfdpstructs.c \
    ../dependencies/CFDP/CODE/cfdp.cpp \
    ../dependencies/CFDP/CODE/user.cpp \
    ../dependencies/net/EndPoint.cpp \
    ../dependencies/net/UDPConnection.cpp \
    ../dependencies/trek/command/AbortCommPass_Command.cpp \
    ../dependencies/trek/command/CameraCaptureImg_Command.cpp \
    ../dependencies/trek/command/ChangeMode_Command.cpp \
    ../dependencies/trek/command/CommSchedule_Command.cpp \
    ../dependencies/trek/command/Decom_Commit_Command.cpp \
    ../dependencies/trek/command/Decom_Enable_Command.cpp \
    ../dependencies/trek/command/EventRetrans_Command.cpp \
    ../dependencies/trek/command/FSW_Control_Command.cpp \
    ../dependencies/trek/command/FSWReboot_Command.cpp \
    ../dependencies/trek/command/FSWRestart_Command.cpp \
    ../dependencies/trek/command/OperMode_Command.cpp \
    ../dependencies/trek/command/PropSchedule_Command.cpp \
    ../dependencies/trek/command/ResetDev_Command.cpp \
    ../dependencies/trek/command/SafeMode_Command.cpp \
    ../dependencies/trek/command/SetDevAvail_Command.cpp \
    ../dependencies/trek/command/SetDevPower_Command.cpp \
    ../dependencies/trek/command/TelemQuery_Command.cpp \
    ../dependencies/trek/command/TransmitDataRate_Command.cpp \
    ../dependencies/trek/telemetry/Event_Telemetry.cpp \
    ../dependencies/trek/telemetry/GNC1_Telemetry.cpp \
    ../dependencies/trek/CCSDSTelemetryHeader.cpp \
    ../dependencies/bc_PacketListenerThread.cpp \
    ../dependencies/CFDP/CODE/comm.c \
    ../dependencies/CFDP/CODE/indication.c \
    ../dependencies/CFDP/CODE/link_sim.c \
    ../dependencies/CFDP/CODE/link_type.c \
    ../dependencies/CFDP/CODE/trans_list.c \
    ../dependencies/CFDP/CODE/udp.c \
    ../dependencies/CFDP/CODE/usleep.c \
    ../dependencies/CFDP/PRI/aaa.c \
    ../dependencies/CFDP/PRI/callbacks.c \
    ../dependencies/CFDP/PRI/cfdp_lib.c \
    ../dependencies/CFDP/PRI/default_filestore.c \
    ../dependencies/CFDP/PRI/default_indication.c \
    ../dependencies/CFDP/PRI/event.c \
    ../dependencies/CFDP/PRI/machine_list.c \
    ../dependencies/CFDP/PRI/message_class.c \
    ../dependencies/CFDP/PRI/mib.c \
    ../dependencies/CFDP/PRI/misc.c \
    ../dependencies/CFDP/PRI/nak.c \
    ../dependencies/CFDP/PRI/nak_mem.c \
    ../dependencies/CFDP/PRI/pdu.c \
    ../dependencies/CFDP/PRI/pdu_as_string.c \
    ../dependencies/CFDP/PRI/r1.c \
    ../dependencies/CFDP/PRI/r2.c \
    ../dependencies/CFDP/PRI/s1.c \
    ../dependencies/CFDP/PRI/s2.c \
    ../dependencies/CFDP/PRI/timer.c \
    ../dependencies/CFDP/PRI/utils.c \
    ../dependencies/utils/ByteBuffer.cpp \
    ../dependencies/utils/String.cpp \
    ../../../../utils/EventDatabase.cpp \
    ../modules/BARCoMmS_Command/bc_fswcommand.cpp \
    ../dependencies/bc_Event.cpp \
    ../modules/BARCoMmS_Bulletin/bc_bulletin_navigate.cpp \
    ../modules/BARCoMmS_Command/camera_download_imgs_window.cpp \
    ../modules/BARCoMmS_Command/camera_capture_img_window.cpp \
    ../modules/BARCoMmS_Camera/glwidget.cpp \
    ../dependencies/trek/command/CameraDownloadImgs_Command.cpp \
    ../dependencies/trek/command/DownlinkBuffer_Command.cpp \
    ../dependencies/trek/command/Ping_Command.cpp \
    ../dependencies/trek/telemetry/HealthStatus_Telemetry.cpp \
    ../modules/BARCoMmS_Camera/barcomms_camera.cpp

HEADERS  += \
    ../modules/BARCoMmS_Bulletin/bc_bulletin.h \
    ../modules/BARCoMmS_Bulletin/fswitem.h \
    ../modules/BARCoMmS_Bulletin/item.h \
    ../modules/BARCoMmS_Bulletin/sorting.h \
    ../modules/BARCoMmS_CFDP/barcomms_cfdp.h \
    ../modules/BARCoMmS_CFDP/buffer.h \
    ../modules/BARCoMmS_CFDP/cfdpstructs.h \
    ../modules/BARCoMmS_CFDP/classmessages.h \
    ../modules/BARCoMmS_CFDP/help.h \
    ../modules/BARCoMmS_CFDP/options.h \
    ../modules/BARCoMmS_CFDP/output.h \
    ../modules/BARCoMmS_CFDP/requests.h \
    ../modules/BARCoMmS_CFDP/setter.h \
    ../modules/BARCoMmS_CFDP/sim.h \
    ../modules/BARCoMmS_CFDP/updatecycles.h \
    ../modules/BARCoMmS_CFDP/worker.h \
    ../modules/BARCoMmS_DITL/bc_ditl.h \
    ../modules/BARCoMmS_DITL/bc_ditl_colorLib.h \
    ../modules/BARCoMmS_DITL/bc_ditl_event.h \
    ../modules/BARCoMmS_DITL/bc_ditl_graph.h \
    ../modules/BARCoMmS_DITL/bc_ditl_legend.h \
    ../modules/BARCoMmS_DITL/bc_ditl_paintlabel.h \
    ../modules/BARCoMmS_DITL/bc_ditl_sevTreeItem.h \
    ../dependencies/CFDP/CODE/cfdp_code.h \
    ../dependencies/CFDP/CODE/link_sim.h \
    ../dependencies/CFDP/CODE/link_type.h \
    ../dependencies/CFDP/CODE/pdu_input.h \
    ../dependencies/CFDP/CODE/pdu_output.h \
    ../dependencies/CFDP/CODE/trans_list.h \
    ../dependencies/CFDP/CODE/udp.h \
    ../dependencies/CFDP/CODE/user.h \
    ../dependencies/CFDP/CODE/user_input.h \
    ../dependencies/CFDP/CODE/usleep.h \
    ../dependencies/CFDP/PRI/aaa.h \
    ../dependencies/CFDP/PRI/callbacks.h \
    ../dependencies/CFDP/PRI/cfdp_private.h \
    ../dependencies/CFDP/PRI/event.h \
    ../dependencies/CFDP/PRI/machine.h \
    ../dependencies/CFDP/PRI/machine_list.h \
    ../dependencies/CFDP/PRI/message_class.h \
    ../dependencies/CFDP/PRI/mib.h \
    ../dependencies/CFDP/PRI/misc.h \
    ../dependencies/CFDP/PRI/nak.h \
    ../dependencies/CFDP/PRI/nak_mem.h \
    ../dependencies/CFDP/PRI/pdu.h \
    ../dependencies/CFDP/PRI/pdu_as_string.h \
    ../dependencies/CFDP/PRI/r1.h \
    ../dependencies/CFDP/PRI/r2.h \
    ../dependencies/CFDP/PRI/s1.h \
    ../dependencies/CFDP/PRI/s2.h \
    ../dependencies/CFDP/PRI/structures.h \
    ../dependencies/CFDP/PRI/timer.h \
    ../dependencies/CFDP/PRI/utils.h \
    ../dependencies/CFDP/PRI/validate_user_config.h \
    ../dependencies/CFDP/PUB/cfdp.h \
    ../dependencies/CFDP/PUB/cfdp_config.h \
    ../dependencies/CFDP/PUB/cfdp_data_structures.h \
    ../dependencies/CFDP/PUB/cfdp_provides.h \
    ../dependencies/CFDP/PUB/cfdp_requires.h \
    ../dependencies/CFDP/PUB/cfdp_syntax.h \
    ../dependencies/net/EndPoint.h \
    ../dependencies/net/PDU.h \
    ../dependencies/net/UDPConnection.h \
    ../dependencies/net/UDPConnectionListener.h \
    ../dependencies/trek/command/AbortCommPass_Command.h \
    ../dependencies/trek/command/CameraCaptureImg_Command.h \
    ../dependencies/trek/command/ChangeMode_Command.h \
    ../dependencies/trek/command/CommSchedule_Command.h \
    ../dependencies/trek/command/Decom_Commit_Command.h \
    ../dependencies/trek/command/Decom_Enable_Command.h \
    ../dependencies/trek/command/EventRetrans_Command.h \
    ../dependencies/trek/command/FSW_Control_Command.h \
    ../dependencies/trek/command/FSWReboot_Command.h \
    ../dependencies/trek/command/FSWRestart_Command.h \
    ../dependencies/trek/command/OperMode_Command.h \
    ../dependencies/trek/command/PropSchedule_Command.h \
    ../dependencies/trek/command/ResetDev_Command.h \
    ../dependencies/trek/command/SafeMode_Command.h \
    ../dependencies/trek/command/SetDevAvail_Command.h \
    ../dependencies/trek/command/SetDevPower_Command.h \
    ../dependencies/trek/command/TelemQuery_Command.h \
    ../dependencies/trek/command/TransmitDataRate_Command.h \
    ../dependencies/trek/telemetry/Event_Telemetry.h \
    ../dependencies/trek/telemetry/GNC1_Telemetry.h \
    ../dependencies/trek/AbstractCommandPDU.h \
    ../dependencies/trek/AbstractTelemetryPDU.h \
    ../dependencies/trek/CCSDSTelemetryHeader.h \
    ../dependencies/trek/CommandIds.h \
    ../dependencies/trek/Packet.h \
    ../dependencies/trek/TelemetryIds.h \
    ../dependencies/bc_Event.h \
    ../dependencies/bc_PacketListenerThread.h \
    ../dependencies/utils/ArrayList.h \
    ../dependencies/utils/ByteBuffer.h \
    ../dependencies/utils/String.h \
    ../../../../utils/EventDatabase.h \
    ../modules/BARCoMmS_Command/bc_fswcommand.h \
    ../modules/BARCoMmS_Command/camera_download_imgs_window.h \
    ../modules/BARCoMmS_Command/camera_capture_img_window.h \
    ../modules/BARCoMmS_Camera/glwidget.h \
    ../modules/BARCoMmS_Camera/openglwidgetsubclass.h \
    ../modules/BARCoMmS_Camera/vertex.h \
    ../dependencies/trek/command/CameraDownloadImgs_Command.h \
    ../dependencies/trek/command/DownlinkBuffer_Command.h \
    ../dependencies/trek/command/Ping_Command.h \
    ../dependencies/trek/telemetry/HealthStatus_Telemetry.h \
    ../modules/BARCoMmS_Camera/barcomms_camera.h
FORMS += \
    ../modules/BARCoMmS_Bulletin/bc_bulletin.ui \
    ../modules/BARCoMmS_Bulletin/sorting.ui \
    ../modules/BARCoMmS_CFDP/barcomms_cfdp.ui \
    ../modules/BARCoMmS_CFDP/buffer.ui \
    ../modules/BARCoMmS_CFDP/classmessages.ui \
    ../modules/BARCoMmS_CFDP/help.ui \
    ../modules/BARCoMmS_CFDP/options.ui \
    ../modules/BARCoMmS_CFDP/requests.ui \
    ../modules/BARCoMmS_CFDP/setter.ui \
    ../modules/BARCoMmS_CFDP/sim.ui \
    ../modules/BARCoMmS_CFDP/updatecycles.ui \
    ../modules/BARCoMmS_DITL/bc_ditl.ui \
    ../modules/BARCoMmS_DITL/legend.ui \
    ../modules/BARCoMmS_Command/bc_fswcommand.ui \
    ../modules/BARCoMmS_Command/camera_download_imgs_window.ui \
    ../modules/BARCoMmS_Command/camera_capture_img_window.ui \
    ../modules/BARCoMmS_Camera/barcomms_camera.ui

DISTFILES += \
    ../dependencies/CFDP/CODE/mib.nodes \
    ../resources/ss.qss \
    ../../../../resources/fsw/config_data/event.list \
    ../resources/color.reference \
    ../resources/simple.vert \
    ../resources/simple.frag

RESOURCES += \
    ../resources/resources.qrc
