#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T15:41:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BARCoMmS_CFDP
TEMPLATE = app


SOURCES += main.cpp\
    help.cpp \
    setter.cpp \
    updatecycles.cpp \
    sim.cpp \
    buffer.cpp \
    classmessages.cpp \
    output.cpp \
    ../dependencies/CFDP/CODE/user.cpp \
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
    ../dependencies/CFDP/PRI/nak_mem.c \
    ../dependencies/CFDP/PRI/nak.c \
    ../dependencies/CFDP/PRI/pdu_as_string.c \
    ../dependencies/CFDP/PRI/pdu.c \
    ../dependencies/CFDP/PRI/r1.c \
    ../dependencies/CFDP/PRI/r2.c \
    ../dependencies/CFDP/PRI/s1.c \
    ../dependencies/CFDP/PRI/s2.c \
    ../dependencies/CFDP/PRI/timer.c \
    ../dependencies/CFDP/PRI/utils.c \
    ../dependencies/CFDP/TEST/test_cfdp.c \
    options.cpp \
    ../BARCoMmS_Bulletin/bc_bulletin.cpp \
    ../dependencies/net/UDPConnection.cpp \
    ../dependencies/trek/CCSDSTelemetryHeader.cpp \
    ../dependencies/trek/command/ChangeMode_Command.cpp \
    ../dependencies/trek/command/Decom_Commit_Command.cpp \
    ../dependencies/trek/command/Decom_Enable_Command.cpp \
    ../dependencies/trek/command/FSW_Control_Command.cpp \
    ../dependencies/trek/command/TelemQuery_Command.cpp \
    ../dependencies/trek/telemetry/HealthStatus_Telemetry.cpp \
    ../dependencies/utils/ByteBuffer.cpp \
    ../dependencies/net/EndPoint.cpp \
    ../dependencies/utils/String.cpp \
    ../dependencies/bc_PacketListenerThread.cpp \
    ../BARCoMmS_Bulletin/item.cpp \
    ../BARCoMmS_Bulletin/fswitem.cpp \
    ../dependencies/CFDP/CODE/cfdp.cpp \
    ../dependencies/trek/command/AbortCommPass_Command.cpp \
    ../dependencies/trek/command/CameraCaptureImg_Command.cpp \
    ../dependencies/trek/command/CommSchedule_Command.cpp \
    ../dependencies/trek/command/Downlink_Command.cpp \
    ../dependencies/trek/command/DownloadImage_Command.cpp \
    ../dependencies/trek/command/EventRetrans_Command.cpp \
    ../dependencies/trek/command/FSWReboot_Command.cpp \
    ../dependencies/trek/command/FSWRestart_Command.cpp \
    ../dependencies/trek/command/OperMode_Command.cpp \
    ../dependencies/trek/command/Ping_Command.cpp \
    ../dependencies/trek/command/PropSchedule_Command.cpp \
    ../dependencies/trek/command/ResetDev_Command.cpp \
    ../dependencies/trek/command/SafeMode_Command.cpp \
    ../dependencies/trek/command/SetDevAvail_Command.cpp \
    ../dependencies/trek/command/SetDevPower_Command.cpp \
    ../dependencies/trek/command/TransmitDataRate_Command.cpp \
    ../BARCoMmS_Bulletin/sorting.cpp \
    ../BARCoMmS_Bulletin/bc_fswcommand.cpp \
    requests.cpp \
    detailedstatus.cpp \
    barcomms_cfdp.cpp \
    cfdpstructs.c

HEADERS  += \
    help.h \
    setter.h \
    updatecycles.h \
    sim.h \
    buffer.h \
    classmessages.h \
    output.h \
    ../dependencies/CFDP/CODE/cfdp_code.h \
    ../dependencies/CFDP/CODE/link_sim.h \
    ../dependencies/CFDP/CODE/link_type.h \
    ../dependencies/CFDP/CODE/pdu_input.h \
    ../dependencies/CFDP/CODE/pdu_output.h \
    ../dependencies/CFDP/CODE/trans_list.h \
    ../dependencies/CFDP/CODE/udp.h \
    ../dependencies/CFDP/CODE/user_input.h \
    ../dependencies/CFDP/CODE/user.h \
    ../dependencies/CFDP/CODE/usleep.h \
    ../dependencies/CFDP/PRI/aaa.h \
    ../dependencies/CFDP/PRI/callbacks.h \
    ../dependencies/CFDP/PRI/cfdp_private.h \
    ../dependencies/CFDP/PRI/event.h \
    ../dependencies/CFDP/PRI/machine_list.h \
    ../dependencies/CFDP/PRI/machine.h \
    ../dependencies/CFDP/PRI/message_class.h \
    ../dependencies/CFDP/PRI/mib.h \
    ../dependencies/CFDP/PRI/misc.h \
    ../dependencies/CFDP/PRI/nak_mem.h \
    ../dependencies/CFDP/PRI/nak.h \
    ../dependencies/CFDP/PRI/pdu_as_string.h \
    ../dependencies/CFDP/PRI/pdu.h \
    ../dependencies/CFDP/PRI/r1.h \
    ../dependencies/CFDP/PRI/r2.h \
    ../dependencies/CFDP/PRI/s1.h \
    ../dependencies/CFDP/PRI/s2.h \
    ../dependencies/CFDP/PRI/structures.h \
    ../dependencies/CFDP/PRI/timer.h \
    ../dependencies/CFDP/PRI/utils.h \
    ../dependencies/CFDP/PRI/validate_user_config.h \
    ../dependencies/CFDP/PUB/cfdp_config.h \
    ../dependencies/CFDP/PUB/cfdp_config.h.flight \
    ../dependencies/CFDP/PUB/cfdp_config.h.ground \
    ../dependencies/CFDP/PUB/cfdp_data_structures.h \
    ../dependencies/CFDP/PUB/cfdp_provides.h \
    ../dependencies/CFDP/PUB/cfdp_requires.h \
    ../dependencies/CFDP/PUB/cfdp_syntax.h \
    ../dependencies/CFDP/PUB/cfdp.h \
    ../dependencies/CFDP/TEST/test_cfdp.h \
    options.h \
    ../BARCoMmS_Bulletin/bc_bulletin.h \
    ../dependencies/net/PDU.h \
    ../dependencies/net/UDPConnection.h \
    ../dependencies/net/UDPConnectionListener.h \
    ../dependencies/trek/AbstractCommandPDU.h \
    ../dependencies/trek/AbstractTelemetryPDU.h \
    ../dependencies/trek/CCSDSTelemetryHeader.h \
    ../dependencies/trek/Packet.h \
    ../dependencies/trek/command/ChangeMode_Command.h \
    ../dependencies/trek/command/Decom_Commit_Command.h \
    ../dependencies/trek/command/Decom_Enable_Command.h \
    ../dependencies/trek/command/FSW_Control_Command.h \
    ../dependencies/trek/command/TelemQuery_Command.h \
    ../dependencies/utils/ByteBuffer.h \
    ../dependencies/trek/telemetry/HealthStatus_Telemetry.h \
    ../dependencies/net/EndPoint.h \
    ../dependencies/utils/String.h \
    ../dependencies/bc_PacketListenerThread.h \
    ../BARCoMmS_Bulletin/item.h \
    ../BARCoMmS_Bulletin/fswitem.h \
    ../dependencies/trek/command/AbortCommPass_Command.h \
    ../dependencies/trek/command/CameraCaptureImg_Command.h \
    ../dependencies/trek/command/CommSchedule_Command.h \
    ../dependencies/trek/command/Downlink_Command.h \
    ../dependencies/trek/command/DownloadImage_Command.h \
    ../dependencies/trek/command/EventRetrans_Command.h \
    ../dependencies/trek/command/FSWReboot_Command.h \
    ../dependencies/trek/command/FSWRestart_Command.h \
    ../dependencies/trek/command/OperMode_Command.h \
    ../dependencies/trek/command/Ping_Command.h \
    ../dependencies/trek/command/PropSchedule_Command.h \
    ../dependencies/trek/command/ResetDev_Command.h \
    ../dependencies/trek/command/SafeMode_Command.h \
    ../dependencies/trek/command/SetDevAvail_Command.h \
    ../dependencies/trek/command/SetDevPower_Command.h \
    ../dependencies/trek/command/TransmitDataRate_Command.h \
    ../BARCoMmS_Bulletin/sorting.h \
    ../BARCoMmS_Bulletin/bc_fswcommand.h \
    requests.h \
    detailedstatus.h \
    barcomms_cfdp.h \
    cfdpstructs.h

FORMS    += \
    help.ui \
    setter.ui \
    updatecycles.ui \
    sim.ui \
    buffer.ui \
    classmessages.ui \
    options.ui \
    ../BARCoMmS_Bulletin/bc_bulletin.ui \
    ../BARCoMmS_Bulletin/sorting.ui \
    ../BARCoMmS_Bulletin/bc_fswcommand.ui \
    requests.ui \
    detailedstatus.ui \
    barcomms_cfdp.ui

DISTFILES += \
    ../dependencies/CFDP/CODE/mib.nodes \
    ../dependencies/CFDP/CODE/makefile \
    ../dependencies/CFDP/PRI/makefile \
    ../dependencies/CFDP/TEST/enable_pipes \
    ../dependencies/CFDP/TEST/test_loop.ksh \
    ../dependencies/CFDP/TEST/test.all \
    ../dependencies/CFDP/TEST/test.cancelling \
    ../dependencies/CFDP/TEST/test.ccsds \
    ../dependencies/CFDP/TEST/test.faults \
    ../dependencies/CFDP/TEST/test.freeze \
    ../dependencies/CFDP/TEST/test.full \
    ../dependencies/CFDP/TEST/test.gpm \
    ../dependencies/CFDP/TEST/test.infinite \
    ../dependencies/CFDP/TEST/test.overnight \
    ../dependencies/CFDP/TEST/test.requests \
    ../dependencies/CFDP/TEST/test.stress \
    ../dependencies/CFDP/TEST/test.syntax \
    ../dependencies/CFDP/TEST/makefile \
    ../dependencies/CFDP/makefile
