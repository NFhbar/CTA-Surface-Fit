#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T10:01:45
#
#-------------------------------------------------

QT       += core gui

TARGET = DataAnalysisV2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    genratedata.cpp \
    plot.cpp \
    calculate.cpp \
    calculateresiduals.cpp \
    loadresiduals.cpp \
    modeanalysis.cpp \
    modefactors.cpp \
    suppressresiduals.cpp \
    cutresiduals.cpp \
    label_info.cpp \
    infodialog.cpp \
    modeanalysis2.cpp

HEADERS  += mainwindow.h \
    genratedata.h \
    plot.h \
    calculate.h \
    calculateresiduals.h \
    loadresiduals.h \
    modeanalysis.h \
    modefactors.h \
    suppressresiduals.h \
    cutresiduals.h \
    label_info.h \
    infodialog.h \
    modeanalysis2.h

FORMS    += mainwindow.ui \
    infodialog.ui

QMAKE_LFLAGS += -larmadillo

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lgsl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lgsl
else:symbian: LIBS += -lgsl
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lgsl

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/release/gsl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/debug/gsl.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/libgsl.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -lgslcblas
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -lgslcblas
else:symbian: LIBS += -lgslcblas
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -lgslcblas

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/release/gslcblas.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/lib/debug/gslcblas.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/lib/libgslcblas.a

LIBS += -lmgl-qt -lmgl


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl
else:symbian: LIBS += -lmgl
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/mgl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/mgl.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libmgl.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl-qt
else:symbian: LIBS += -lmgl-qt
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl-qt

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/mgl-qt.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/mgl-qt.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libmgl-qt.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl-fltk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl-fltk
else:symbian: LIBS += -lmgl-fltk
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl-fltk

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/mgl-fltk.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/mgl-fltk.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libmgl-fltk.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl-glut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl-glut
else:symbian: LIBS += -lmgl-glut
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl-glut

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/mgl-glut.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/mgl-glut.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libmgl-glut.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl
else:symbian: LIBS += -lmgl
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl-qt
else:symbian: LIBS += -lmgl-qt
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl-qt

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lmgl-fltk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lmgl-fltk
else:symbian: LIBS += -lmgl-fltk
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmgl-fltk

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

RESOURCES += \
    Resource.qrc
