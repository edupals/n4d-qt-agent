
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 "6.7.0" REQUIRED COMPONENTS Core Widgets Quick QuickWidgets)

find_package(EdupalsBase REQUIRED)
find_package(EdupalsN4D REQUIRED)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fexceptions")

add_executable(n4d-qt-agent agent.cpp loginwindow.cpp ../rsrc/resources.qrc)
target_link_libraries(n4d-qt-agent Qt6::Core Qt6::Widgets Qt6::Quick Qt6::QuickWidgets Edupals::Base Edupals::N4D)

install(TARGETS n4d-qt-agent RUNTIME DESTINATION bin)
