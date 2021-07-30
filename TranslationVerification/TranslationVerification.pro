QT       += core gui
#QT_INSTALL_FRAMEWORK_PATH = C:/Qt/Tools/QtInstallerFramework/4.1
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
#    TranslationVerification-Installer


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


#DESTDIR = $$PWD/TranslationVerification-Installer/packages/ics.component/data

#create_package.commands = $$quote(windeployqt --qmldir $$PWD/../TranslationVerification $${DESTDIR})

#QMAKE_EXTRA_TARGETS += create_package
#PRE_TARGETDEPS  += create_package


#DISTFILES += \
#    $$PWD/TranslationVerification-Installer/config/config.xml \
#    $$PWD/TranslationVerification-Installer/packages/ics.component/meta/package.xml \
#    $$PWD/TranslationVerification-Installer/packages/ics.component/meta/installscript.qs

#INSTALLER = translationVerification-installer

#INPUT = $$PWD/TranslationVerification-Installer/config/config.xml $$PWD/TranslationVerification-Installer/packages


#translation-installer.input = INPUT
#translation-installer.output = $$INSTALLER
#translation-installer.commands = $$QT_INSTALL_FRAMEWORK_PATH/bin/binarycreator --offline-only -c $$PWD/config/config.xml -p $$PWD/packages/TranslationVerification
#translation-installer.CONFIG += target_predeps no_link combine


#QMAKE_EXTRA_COMPILERS += translation-installer




