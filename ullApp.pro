TEMPLATE = app

QT += qml quick widgets svg core gui

SOURCES += main.cpp \
    gamehandler.cpp

RESOURCES += \
    qml/qml.qrc \
    images/images.qrc \
    fonts/fonts.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml \

HEADERS += \
    gamehandler.h

macx:CONFIG += x86

