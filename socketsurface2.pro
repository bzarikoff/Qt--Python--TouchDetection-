android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}

!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

SOURCES += main.cpp \
           surfacegraph.cpp \
    chartview.cpp

HEADERS += surfacegraph.h \
           chartview.h

QT += widgets
QT += charts
requires(qtConfig(combobox))

RESOURCES += surface.qrc

OTHER_FILES += doc/src/* \
               doc/images/*

LIBS += -lws2_32


#QT = core
QT += serialport


target.path = $$[QT_INSTALL_EXAMPLES]/charts/scatterchart
INSTALLS += target
