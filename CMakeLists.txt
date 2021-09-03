cmake_minimum_required(VERSION 3.10.0)

project(TranslationVerification VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

## Default Qt5 path
if(WIN32)
    set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64" CACHE PATH "directory where Qt5Config.cmake exists.")
    if(EXISTS ${Qt5_DIR})
        message("Local Qt found!")
    endif()
elseif(UNIX)
  set(Qt5_DIR $ENV{HOME}/Qt/5.15.2/gcc_64 CACHE PATH "directory where Qt5Config.cmake exists.")
  if(EXISTS ${Qt5_DIR})
      message("Local Qt found!")
  endif()
endif()

find_package(Qt5 5.15 COMPONENTS Widgets REQUIRED)
if(Qt5Widgets_FOUND)
    if(${Qt5Widgets_VERSION} VERSION_LESS 5.15)
        message(FATAL_ERROR "Minimum supported Qt5 version is 5.15!")
     endif()
endif()

include(FetchContent)

FetchContent_Declare(qonlinetranslator
    GIT_REPOSITORY https://github.com/crow-translate/QOnlineTranslator.git
)

FetchContent_GetProperties(qonlinetranslator)
if(NOT qonlinetranslator_POPULATED)
    FetchContent_Populate(qonlinetranslator)
    add_subdirectory(${qonlinetranslator_SOURCE_DIR} ${qonlinetranslator_BINARY_DIR})
endif()

set(PROJECT_SOURCES
    src/main.cpp
    src/addlanguagedialog.cpp
    src/addlanguagedialog.ui
    src/verification.cpp
    src/widgetwindow.ui
    src/widgetwindow.cpp
)

if(QT_VERSION_MAJOR GREATER_EQUAL 5)
    qt_add_executable(translationVerification
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
else()
    add_executable(translationVerification
        ${PROJECT_SOURCES})
endif()

target_include_directories(translationVerification PUBLIC
    "${qonlinetranslator_BINARY_DIR}/src"
    "${qonlinetranslator_SOURCE_DIR}/src")

target_link_libraries(translationVerification PUBLIC QOnlineTranslator PRIVATE Qt5::Widgets)

install(TARGETS translationVerification RUNTIME DESTINATION .)

##CPack
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

set(CPACK_PACKAGE_NAME "Translation Verification")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Translation Verification Installation")
set(CPACK_PACKAGE_VERSION "1.0.0") # Version of installer

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/translationVerification.desktop DESTINATION share/applications/)
    add_custom_command(TARGET translationVerification POST_BUILD
                       COMMAND  wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
                       COMMAND  export VERSION=continuous
#                       COMMAND  chmod a+x linuxdeployqt-continuous-x86_64.AppImage
#                       COMMAND ./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/*.desktop -unsupported-allow-new-glibc -appimage -extra-plugins=iconengines,platformthemes/libqxdgdesktopportal.so
                      )
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-linux-${ARCHITECTURE}")
    set(CPACK_GENERATOR "TXZ")

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "TranslationVerification")
    set(CPACK_NSIS_DISPLAY_NAME ${CMAKE_PACKAGE_NAME})
    set(CPACK_NSIS_COMPRESSOR lzma)
    set(CPACK_NSIS_INSTALLED_ICON_NAME TranslationVerification.exe)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
    set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
    include(InstallRequiredSystemLibraries)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

    add_custom_command(TARGET translationVerification POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/qtDeploy/"
                       COMMAND "${CMAKE_COMMAND}" -E
                               env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
                               --verbose 0
                               --no-compiler-runtime
                               --no-angle
                               --no-webkit2
                               --no-quick-import
                               --no-translations
                               --dir "${CMAKE_BINARY_DIR}/qtDeploy/" $<TARGET_FILE:translationVerification>
                       COMMENT "Deploying Qt..."
    )

    install(
        DIRECTORY "${CMAKE_BINARY_DIR}/qtDeploy/"
        DESTINATION .
    )
    set(CPACK_GENERATOR "ZIP;NSIS")
endif()


set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
include(CPack)



