cmake_minimum_required(VERSION 3.16)

project(Sculptor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sculptor main.cpp
    main.cpp sculptor.cpp sculptor.h )

include(GNUInstallDirs)
install(TARGETS Sculptor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
