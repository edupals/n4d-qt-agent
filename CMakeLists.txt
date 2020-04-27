cmake_minimum_required(VERSION 3.0)
project(n4d-qt-agent)

add_subdirectory(src)
add_subdirectory(lib)

install(DIRECTORY include/ DESTINATION include/edupals/n4d)

install(FILES "EdupalsN4DAgentConfig.cmake"
    DESTINATION "lib/cmake/EdupalsN4D"
)
