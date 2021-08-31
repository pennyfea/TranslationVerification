cmake_minimum_required(VERSION 3.1.0)

project(TranslationVerification VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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

if(QT_VERSION_MAJOR EQUAL 5)
    qt_finalize_executable(translationVerification)
endif()

