find_package(EdupalsBase REQUIRED)
find_package(EdupalsN4D REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(edupals-n4d-agent SHARED agent.cpp)
target_link_libraries(edupals-n4d-agent Edupals::Base Edupals::N4D)
set_target_properties(edupals-n4d-agent PROPERTIES SOVERSION 2 VERSION "2.0.0")

#testing application
add_executable(testing testing.cpp)
target_link_libraries(testing edupals-n4d-agent Edupals::Base Edupals::N4D)

install(TARGETS edupals-n4d-agent
    LIBRARY DESTINATION "lib"
)
