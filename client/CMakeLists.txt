cmake_minimum_required(VERSION 3.9)
include(../shared/traintastic.cmake)
project(traintastic-client VERSION ${TRAINTASTIC_VERSION} DESCRIPTION "Traintastic client")
include(GNUInstallDirs)
include(../shared/translations/traintastic-lang.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

configure_file(../shared/src/traintastic/version.hpp.in version.hpp)

if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Werror)
endif()

add_executable(traintastic-client
  data/data.qrc
  gfx/common.qrc
  gfx/dark/dark.qrc
  gfx/light/light.qrc
)

add_dependencies(traintastic-client traintastic-lang)

add_definitions(-DQT_DEPRECATED_WARNINGS)

target_include_directories(traintastic-client PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ../shared/src)

target_include_directories(traintastic-client SYSTEM PRIVATE
  ../shared/thirdparty
  thirdparty)

file(GLOB SOURCES
  "src/*.hpp"
  "src/*.cpp"
  "src/board/*.hpp"
  "src/board/*.cpp"
  "src/clock/*.hpp"
  "src/clock/*.cpp"
  "src/dialog/*.hpp"
  "src/dialog/*.cpp"
  "src/mainwindow/*.hpp"
  "src/mainwindow/*.cpp"
  "src/misc/*.hpp"
  "src/misc/*.cpp"
  "src/network/*.hpp"
  "src/network/*.cpp"
  "src/network/create/*.hpp"
  "src/network/create/*.cpp"
  "src/network/object/*.hpp"
  "src/network/object/*.cpp"
  "src/programming/lncv/*.hpp"
  "src/programming/lncv/*.cpp"
  "src/settings/*.hpp"
  "src/settings/*.cpp"
  "src/style/*.hpp"
  "src/style/*.cpp"
  "src/subwindow/*.hpp"
  "src/subwindow/*.cpp"
  "src/theme/*.hpp"
  "src/theme/*.cpp"
  "src/utils/*.hpp"
  "src/utils/*.cpp"
  "src/widget/*.hpp"
  "src/widget/*.cpp"
  "src/widget/list/*.hpp"
  "src/widget/list/*.cpp"
  "src/widget/object/*.hpp"
  "src/widget/object/*.cpp"
  "src/widget/objectlist/*.hpp"
  "src/widget/objectlist/*.cpp"
  "src/widget/status/*.hpp"
  "src/widget/status/*.cpp"
  "src/widget/throttle/*.hpp"
  "src/widget/throttle/*.cpp"
  "src/wizard/*.hpp"
  "src/wizard/*.cpp"
  "src/wizard/page/*.hpp"
  "src/wizard/page/*.cpp"
  "../shared/src/traintastic/locale/locale.cpp"
  "../shared/src/traintastic/utils/standardpaths.cpp"
  "thirdparty/QtWaitingSpinner/*.hpp"
  "thirdparty/QtWaitingSpinner/*.cpp")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network Svg Xml WebSockets)
if(QT_VERSION_MAJOR EQUAL 5)
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network Svg Xml WebSockets)
else()
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network Svg Xml SvgWidgets WebSockets)
endif()
message(STATUS "Found Qt ${QT_VERSION}")

target_sources(traintastic-client PRIVATE ${SOURCES})

target_link_libraries(traintastic-client PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Svg Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::WebSockets)
if(QT_VERSION_MAJOR GREATER 5)
  target_link_libraries(traintastic-client PRIVATE Qt${QT_VERSION_MAJOR}::SvgWidgets)
endif()

### PLATFORM ###

if(WIN32)
  target_sources(traintastic-client PRIVATE ../shared/gfx/appicon.rc src/version.rc)
  set_property(TARGET traintastic-client PROPERTY WIN32_EXECUTABLE true)
endif()

if (APPLE)
  find_library(CORE_FOUNDATION CoreFoundation)
  target_link_libraries(traintastic-client PRIVATE ${CORE_FOUNDATION})
  target_sources(traintastic-client PRIVATE ../shared/gfx/icon.icns)
  target_sources(traintastic-client PRIVATE ${LNCV_XML_FILES})
  target_sources(traintastic-client PRIVATE ${TRANSLATION_FILES})
  set_property(TARGET traintastic-client PROPERTY MACOSX_BUNDLE true)
endif()

### COMPILER ###

if(MSVC)

else()

  if(NOT APPLE)
    target_link_libraries(traintastic-client PRIVATE stdc++fs)
  endif()
endif()

### INSTALL ###

install(TARGETS traintastic-client
    BUNDLE    DESTINATION .
    COMPONENT traintastic-client
    RUNTIME DESTINATION "/opt/traintastic/bin/"
)

if(LINUX)
  install(FILES ${CMAKE_SOURCE_DIR}/debian/traintastic-client.desktop DESTINATION share/applications)
  install(FILES ${CMAKE_SOURCE_DIR}/debian/traintastic_256.png DESTINATION "/opt/traintastic/icons/")
endif()

### BUILD TYPE ###

if (CMAKE_BUILD_TYPE EQUAL "Release")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

### DEB package ###

if(NOT DEBIAN_PACKAGE_VERSION_EXTRA)
  set(DEBIAN_PACKAGE_VERSION_EXTRA "${PROJECT_VERSION_EXTRA}")
endif()

if (LINUX)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}${DEBIAN_PACKAGE_VERSION_EXTRA}")
  set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
  set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Reinder Feenstra")
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://traintastic.org")
  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "traintastic-data (>= ${CPACK_PACKAGE_VERSION})")
endif()

# Bundle for macOS
if (APPLE)
  set(CPACK_GENERATOR "Bundle")
  set(CPACK_BUNDLE_NAME "Traintastic")

  set(APP_ICON_MACOS "${CMAKE_CURRENT_SOURCE_DIR}/../shared/gfx/icon.icns")
  set(CPACK_BUNDLE_ICON ${APP_ICON_MACOS})
  set_source_files_properties(${APP_ICON_MACOS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
  set_source_files_properties(${LNCV_XML_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/lncv")
  set_source_files_properties(${TRANSLATION_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/translations")

  set(CPACK_BUNDLE_VERSION "${PROJECT_VERSION}${DEBIAN_PACKAGE_VERSION_EXTRA}")
  set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/../package/Info.plist")
endif()

include(CPack)
