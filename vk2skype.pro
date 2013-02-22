
QT       += core gui

TARGET = vk2skype
TEMPLATE = app


SOURCES += \
    program.cpp \
    skype/src/skype.cpp \
    vk_mail/message.cpp \
    vk_mail/vkmessage.cpp \
    vk_mail/vk.cpp \
    vk_mail/oauth.cpp \
    server.cpp

HEADERS += \
    skype/src/skype.h \
    vk_mail/message.h \
    vk_mail/vkmessage.h \
    vk_mail/vk.h \
    vk_mail/oauth.h \
    server.h

QT += dbus network webkit xml
