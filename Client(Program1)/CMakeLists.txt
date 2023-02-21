project(Client)

set(HEADERS
        include/Utils.hpp
        include/BlockingBuffer.hpp
        include/Client.hpp
        include/ClientApplication.hpp
        )

set(SOURCES
        src/Client.cpp
        src/ClientApplication.cpp
        src/main.cpp
        )

add_executable(Client ${HEADERS} ${SOURCES})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(Client ${Boost_LIBRARIES})