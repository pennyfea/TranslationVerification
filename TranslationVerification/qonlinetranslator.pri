QT += network multimedia

HEADERS += $$PWD/../QOnlineTranslator/src/qonlinetranslator.h \
    $$PWD/../QOnlineTranslator/src/qonlinetts.h \
    $$PWD/../QOnlineTranslator/src/qoption.h \
    $$PWD/../QOnlineTranslator/src/qexample.h

SOURCES += $$PWD/../QOnlineTranslator/src/qonlinetranslator.cpp \
     $$PWD/../QOnlineTranslator/src/qonlinetts.cpp \
     $$PWD/../QOnlineTranslator/src/qoption.cpp \
     $$PWD/../QOnlineTranslator/src/qexample.cpp

INCLUDEPATH +=   $$PWD/../QOnlineTranslator/src

CONFIG += c++17

DESTDIR = $$PWD/../TranslationVerification-Installer/packages/ics.component/data
