
find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick QuickWidgets)

find_package(EdupalsBase REQUIRED)
find_package(EdupalsN4D REQUIRED)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fexceptions")

add_executable(n4d-qt-agent agent.cpp loginwindow.cpp ../rsrc/resources.qrc)
target_link_libraries(n4d-qt-agent Qt5::Core Qt5::Widgets Qt5::Quick Qt5::QuickWidgets Edupals::Base Edupals::N4D)

install(TARGETS n4d-qt-agent RUNTIME DESTINATION bin)
