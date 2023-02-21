project(Server)

set(HEADERS
        include/Utils.hpp
        include/Server.hpp
        include/ServerApplication.hpp
        )

set(SOURCES
        src/Server.cpp
        src/ServerApplication.cpp
        src/main.cpp
        )

add_executable(Server ${HEADERS} ${SOURCES})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(Client ${Boost_LIBRARIES})