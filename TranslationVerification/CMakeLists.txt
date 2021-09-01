cmake_minimum_required(VERSION 3.1.0)

project(TranslationVerification VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Naive platform specific implementation
# Sets a custom variable named `Qt5_BASE_DIR` that we could use further to have
# a modular import of Qt Framework's Libraries
if(WIN32)
    if(MSVC)
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(Qt5_LOCAL ~/Qt/5.15.2/msvc2019_64)
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(Qt5_LOCAL ~/Qt/5.15.2/msvc2019)
        endif()
        if(EXISTS ${Qt5_LOCAL})
            message("Local Qt found!")
            set(Qt5_BASE_DIR ${Qt5_LOCAL})
        else()
            message("No user installed Qt5 found!")
        endif()
    endif()
elseif(UNIX)
    set(Qt5_LOCAL $ENV{HOME}/Qt/5.15.2/gcc_64)
    if(EXISTS ${Qt5_LOCAL})
        message("Local Qt found!")
        set(Qt5_BASE_DIR ${Qt5_LOCAL})
    else()
        message("No user installed Qt5 found!")
    endif()
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# This variable tells CMake to create appropriate library path, binary path and
# packages path
if(DEFINED Qt5_BASE_DIR)
    message("Adjusting CMAKE_PREFIX_PATH")
    set(CMAKE_PREFIX_PATH ${Qt5_BASE_DIR};${CMAKE_PREFIX_PATH})
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
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
    main.cpp
    addlanguagedialog.cpp
    addlanguagedialog.ui
    verification.cpp
    widgetwindow.ui
    widgetwindow.cpp
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

#include(GNUInstallDirs)
install(TARGETS translationVerification
DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CPACK_PACKAGE_NAME "Translation Verification")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ranslation Verification Installation")
set(CPACK_PACKAGE_VERSION "1.0.0") # Version of installer
include(CPack)
include(CPackIFW)

cpack_add_install_type(End user DISPLAY_NAME "Translation Verification")


if(QT_VERSION_MAJOR EQUAL 5)
    qt_finalize_executable(translationVerification)
endif()

