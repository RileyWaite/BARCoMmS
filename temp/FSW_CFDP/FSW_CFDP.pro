QT += core
QT -= gui

CONFIG += c++11

TARGET = FSW_CFDP
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    CFDP/CODE/comm.c \
    CFDP/CODE/link_sim.c \
    CFDP/CODE/link_type.c \
    CFDP/CODE/trans_list.c \
    CFDP/CODE/udp.c \
    CFDP/CODE/usleep.c \
    CFDP/PRI/aaa.c \
    CFDP/PRI/callbacks.c \
    CFDP/PRI/cfdp_lib.c \
    CFDP/PRI/default_filestore.c \
    CFDP/PRI/default_indication.c \
    CFDP/PRI/event.c \
    CFDP/PRI/machine_list.c \
    CFDP/PRI/message_class.c \
    CFDP/PRI/mib.c \
    CFDP/PRI/misc.c \
    CFDP/PRI/nak.c \
    CFDP/PRI/nak_mem.c \
    CFDP/PRI/pdu.c \
    CFDP/PRI/pdu_as_string.c \
    CFDP/PRI/r1.c \
    CFDP/PRI/r2.c \
    CFDP/PRI/s1.c \
    CFDP/PRI/s2.c \
    CFDP/PRI/timer.c \
    CFDP/PRI/utils.c \
    CFDP/CODE/user.c \
    main.c \
    CFDP/CODE/cfdp.c

DISTFILES += \
    CFDP/CODE/mib.nodes

HEADERS += \
    CFDP/CODE/cfdp_code.h \
    CFDP/CODE/link_sim.h \
    CFDP/CODE/link_type.h \
    CFDP/CODE/pdu_input.h \
    CFDP/CODE/pdu_output.h \
    CFDP/CODE/trans_list.h \
    CFDP/CODE/udp.h \
    CFDP/CODE/user.h \
    CFDP/CODE/user_input.h \
    CFDP/CODE/usleep.h \
    CFDP/PRI/aaa.h \
    CFDP/PRI/callbacks.h \
    CFDP/PRI/cfdp_private.h \
    CFDP/PRI/event.h \
    CFDP/PRI/machine.h \
    CFDP/PRI/machine_list.h \
    CFDP/PRI/message_class.h \
    CFDP/PRI/mib.h \
    CFDP/PRI/misc.h \
    CFDP/PRI/nak.h \
    CFDP/PRI/nak_mem.h \
    CFDP/PRI/pdu.h \
    CFDP/PRI/pdu_as_string.h \
    CFDP/PRI/r1.h \
    CFDP/PRI/r2.h \
    CFDP/PRI/s1.h \
    CFDP/PRI/s2.h \
    CFDP/PRI/structures.h \
    CFDP/PRI/timer.h \
    CFDP/PRI/utils.h \
    CFDP/PRI/validate_user_config.h \
    CFDP/PUB/cfdp.h \
    CFDP/PUB/cfdp_config.h \
    CFDP/PUB/cfdp_data_structures.h \
    CFDP/PUB/cfdp_provides.h \
    CFDP/PUB/cfdp_requires.h \
    CFDP/PUB/cfdp_syntax.h \
    CFDP/TEST/test_cfdp.h
