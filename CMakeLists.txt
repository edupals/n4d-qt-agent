cmake_minimum_required(VERSION 3.0)
project(n4d-qt-agent)

add_subdirectory(src)
#add_subdirectory(lib)
add_subdirectory(qml)

#install(DIRECTORY include/ DESTINATION include/edupals/n4d)

#install(FILES "EdupalsN4DAgentConfig.cmake"
#    DESTINATION "lib/cmake/EdupalsN4DAgent"
#)

add_custom_target(
    po
    COMMAND xgettext -kde -ki18nd:2 ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.qml ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.cpp -o ${CMAKE_CURRENT_SOURCE_DIR}/messages.po
    COMMENT "extracting po..." 
)
