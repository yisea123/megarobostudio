#TEMPLATE=lib
TEMPLATE=app

# QT += core gui widgets network

CONFIG += static

TARGET = mrq 

win32 {
# visa
INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"
LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
LIBS += -lvisa32
DEFINES += NI_VISA
}

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
          visa_adapter.c \
                  C_MRQ.c \
          midevice.c \
          test.c
		  
HEADERS = visa_adapter.h

