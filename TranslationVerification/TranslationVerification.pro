QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../QOnlineTranslator/qonlinetranslator.pri)

SOURCES += \
    addlanguagedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    verification.cpp \

HEADERS += \
    addlanguagedialog.h \
    mainwindow.h \
    verification.h \

FORMS += \
    addlanguagedialog.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QOnlineTranslator/build/release/ -lQOnlineTranslator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QOnlineTranslator/build/debug/ -lQOnlineTranslator
else:unix: LIBS += -L$$PWD/../QOnlineTranslator/build/ -lQOnlineTranslator

INCLUDEPATH += $$PWD/../QOnlineTranslator/build/Debug
DEPENDPATH += $$PWD/../QOnlineTranslator/build/Debug
