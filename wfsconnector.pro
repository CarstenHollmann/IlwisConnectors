#-------------------------------------------------
#
# Project created by QtCreator 2012-02-07T19:05:01
#
#-------------------------------------------------

QT = sql network xmlpatterns

CONFIG += plugin
TARGET = wfsconnector

include(global.pri)

DESTDIR = $$PWD/../libraries/$$PLATFORM$$CONF/$$TARGET
DLLDESTDIR = $$PWD/../output/$$PLATFORM$$CONF/bin/extensions/$$TARGET

TEMPLATE = lib

DEFINES += WFSCONNECTOR_LIBRARY
DEFINES +=TEST_WFS

SOURCES += \
    wfsconnector/wfsobjectfactory.cpp \
    wfsconnector/wfsconnector.cpp \
    wfsconnector/wfscatalogconnector.cpp \
    wfsconnector/wfsmodule.cpp \
    wfsconnector/wfsfeatureconnector.cpp \
    wfsconnector/wfs.cpp \
    wfsconnector/wfsresponse.cpp \
    wfsconnector/wfsfeature.cpp \
    wfsconnector/wfscontainerconnector.cpp \
    wfsconnector/wfscapabilitiesparser.cpp \
    wfsconnector/xmlstreamparser.cpp \
    wfsconnector/xpathparser.cpp \
    wfsconnector/wfsfeatureparser.cpp \
    wfsconnector/wfsfeaturedescriptionparser.cpp

HEADERS += \
    wfsconnector/wfsobjectfactory.h \
    wfsconnector/wfsconnector.h \
    wfsconnector/wfscatalogconnector.h \
    wfsconnector/wfsmodule.h \
    wfsconnector/wfsfeatureconnector.h \
    wfsconnector/wfs.h \
    wfsconnector/wfsconnector_global.h \
    wfsconnector/wfsresponse.h \
    wfsconnector/wfsfeature.h \
    wfsconnector/wfscontainerconnector.h \
    wfsconnector/wfscapabilitiesparser.h \
    wfsconnector/xmlstreamparser.h \
    wfsconnector/xpathparser.h \
    wfsconnector/wfsfeatureparser.h \
    wfsconnector/wfsfeaturedescriptionparser.h \
    wfsconnector/wfsutils.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore \
                                              -L$$PWD/../libraries/$$PLATFORM$$CONF/ -llibgeos
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libraries/$$PLATFORM$$CONF/core/ -lilwiscore \
                                              -L$$PWD/../libraries/$$PLATFORM$$CONF/ -llibgeos

INCLUDEPATH += $$PWD/core \
            $$PWD/../external/
DEPENDPATH += $$PWD/core

OTHER_FILES += \
    wfsconnector/wfsconnector.json \
    wfsconnector/scratch_pad.txt


