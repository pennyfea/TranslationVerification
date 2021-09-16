cmake_minimum_required(VERSION 3.11.0)

project(Translation_Verification VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets )

set(QONLINETRANSLATOR_VERSION 1.4.5)
include(FetchContent)
FetchContent_Declare(qonlinetranslator
    GIT_REPOSITORY https://github.com/crow-translate/QOnlineTranslator.git
    GIT_TAG ${QONLINETRANSLATOR_VERSION}
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

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

include(GNUInstallDirs)
add_executable(Translation_Verification WIN32 MACOSX_BUNDLE ${PROJECT_SOURCES})
target_link_libraries(Translation_Verification PUBLIC QOnlineTranslator PRIVATE Qt5::Widgets )
install(TARGETS Translation_Verification
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
set_target_properties(Translation_Verification PROPERTIES
  MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}"
  MACOSX_BUNDLE_SHORT_VERSION_STRING "${CMAKE_PROJECT_VERSION}"
)

target_include_directories(Translation_Verification PUBLIC
    "${qonlinetranslator_BINARY_DIR}/src"
    "${qonlinetranslator_SOURCE_DIR}/src")
    
##CPack
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

set(CPACK_PACKAGE_NAME "Translation_Verification")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Translation Verification Installation")
set(CPACK_PACKAGE_VERSION "1.0.0") # Version of installer

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    install(FILES ${CMAKE_SOURCE_DIR}/translationVerification.desktop DESTINATION share/applications/)
    install(FILES ${CMAKE_SOURCE_DIR}/default.png DESTINATION share/pixmaps/)
    EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-linux-${ARCHITECTURE}")
    set(CPACK_GENERATOR "TXZ")

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "Translation_Verification")
    set(CPACK_NSIS_DISPLAY_NAME ${CMAKE_PACKAGE_NAME})
    set(CPACK_NSIS_COMPRESSOR lzma)
    set(CPACK_NSIS_INSTALLED_ICON_NAME Translation_Verification.exe)
    set(CPACK_NSIS_MENU_LINKS "Translation_Verification.exe" "Translation Verification")
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR})
    set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)

    include(InstallRequiredSystemLibraries)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

    add_custom_command(TARGET Translation_Verification POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/qtDeploy/
                       COMMAND ${WINDEPLOYQT_EXECUTABLE}
                               --release
                               --verbose 1
                               --no-compiler-runtime
                               --no-angle
                               --no-opengl
                               --no-opengl-sw
                               --no-webkit2
                               --no-quick-import
                               --no-translations
                               --dir ${CMAKE_BINARY_DIR}/qtDeploy $<TARGET_FILE:Translation_Verification>
    )
    install(
        DIRECTORY ${CMAKE_BINARY_DIR}/qtDeploy/
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        FILES_MATCHING PATTERN "*.*"
    )
    set(CPACK_GENERATOR "ZIP;NSIS")

elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")

    find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(
        TARGET Translation_Verification POST_BUILD
        COMMAND ${MACDEPLOYQT} Translation_Verification.app
    )
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-macos")
    set(CPACK_DMG_VOLUME_NAME "Translation_Verification")
endif()

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-src")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
include(CPack)
