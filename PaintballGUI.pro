#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T14:16:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintballGUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11




SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp \
    MotionTrack/frame.cpp \
    MotionTrack/frameAnalyzer.cpp \
    MotionTrack/frameManager.cpp \
    MotionTrack/motionCapture.cpp \
    MotionTrack/motionTrack.cpp \
    MotionTrack/sections.cpp \
    MotionTrack/targetDatabase.cpp \
    MotionTrack/targetPair.cpp \
    MotionTrack/threeDTarget.cpp \
    MotionTrack/twoDTargets.cpp \
    MotionTrack/units.cpp \
    MotionTrack/unitsToTargets.cpp \
    MotionTrack/accumTarget.cpp \
    visualobjects.cpp \
    settings.cpp \
    MotionTrack/calibration.cpp \
    calibrate.cpp \
    FireControl/aim.cpp \
    FireControl/command.cpp \
    FireControl/fireControl.cpp \
    FireControl/drvMotorSim.cpp \
    FireControl/laserAim.cpp \
    FireControl/motorSimulator.cpp \
    CommandToSerial/commandToSerial.cpp

HEADERS  += mainwindow.h \
    thread.h \
    MotionTrack/frame.h \
    MotionTrack/frameAnalyzer.h \
    MotionTrack/frameManager.h \
    MotionTrack/motionCapture.h \
    MotionTrack/motionTrack.h \
    MotionTrack/sections.h \
    MotionTrack/targetDatabase.h \
    MotionTrack/targetPair.h \
    MotionTrack/threeDTarget.h \
    MotionTrack/twoDTargets.h \
    MotionTrack/units.h \
    MotionTrack/unitsToTargets.h \
    MotionTrack/accumTarget.h \
    visualobjects.h \
    settings.h \
    MotionTrack/calibration.h \
    MotionTrack/cameraSettings.h \
    calibrate.h \
    FireControl/aim.h \
    FireControl/command.h \
    FireControl/fireControl.h \
    FireControl/drvMotorSim.h \
    FireControl/laserAim.h \
    FireControl/motorSimulator.h \
    CommandToSerial/commandToSerial.h


FORMS    += mainwindow.ui \
    settings.ui \
    calibrate.ui




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_core
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_imgproc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_imgproc
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_photo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_photo
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_photo

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_video
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_video
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_video

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_features2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_features2d
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_features2d

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_objdetect
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_objdetect
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_objdetect

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_calib3d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_calib3d
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_calib3d

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_imgcodecs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_imgcodecs
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_imgcodecs

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_videoio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_videoio
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_videoio

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_highgui
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lopencv_ml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lopencv_ml
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lopencv_ml

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
