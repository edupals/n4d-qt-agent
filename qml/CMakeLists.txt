

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 "6.7.0" REQUIRED COMPONENTS Qml Quick)

find_package(EdupalsBase REQUIRED)
find_package(EdupalsN4D REQUIRED)
find_package(Threads REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED libsystemd)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fexceptions")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -foperator-names")

add_library(edupalsn4dagentplugin SHARED plugin.cpp)

target_link_libraries (edupalsn4dagentplugin
    Qt6::Qml
    Qt6::Quick
    Edupals::Base
    Edupals::N4D
    Threads::Threads
    ${SYSTEMD_LIBRARIES}
)

install (TARGETS edupalsn4dagentplugin DESTINATION ${QT6_INSTALL_QML}/Edupals/N4D/Agent)
install(FILES qmldir DESTINATION ${QT6_INSTALL_QML}/Edupals/N4D/Agent)
install(FILES Login.qml DESTINATION ${QT6_INSTALL_QML}/Edupals/N4D/Agent)
