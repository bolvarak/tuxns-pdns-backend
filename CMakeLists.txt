## Includes
## Includes
include_directories(
	/usr/include/qt
	/usr/include/x86_64-linux-gnu/qt5
)
## Helpers
if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColorReset  "${Esc}[m")
	set(ColorBold   "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
endif()
## CMake Policy
cmake_policy(SET CMP0005 NEW)
## CMake Minimum Version
cmake_minimum_required(VERSION 3.2)
## Project Name
project(tuxns-pdns-backend)
## CMake Settings & Configuration
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -F/usr/lib/x86_64-linux-gnu/qca-qt5/crypto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
## Source Headers & Files
set(SOURCE_FILES
	./sqlqueries.qrc
	./TuxNS/PowerDNS/Request.hpp
	./TuxNS/PowerDNS/Method.hpp
	./TuxNS/PowerDNS/Response.hpp
	./TuxNS/DNS.hpp
	./TuxNS/Listener.hpp
	./TuxNS/Connection.hpp
	./TuxNS/Task.hpp
	./TuxNS/Log.hpp
	./TuxNS/Bootstrap.hpp
	./TuxNS/Configuration.hpp
	./TuxNS/DNS.cpp
	./TuxNS/PowerDNS/Method.cpp
	./TuxNS/PowerDNS/Response.cpp
	./TuxNS/PowerDNS/Request.cpp
	./TuxNS/Listener.cpp
	./TuxNS/Connection.cpp
	./TuxNS/Task.cpp
	./TuxNS/Log.cpp
	./TuxNS/Bootstrap.cpp
	./TuxNS/Configuration.cpp
	./main.cpp
)
## Automoc
set(CMAKE_AUTOMOC ON)
## Auto RCC files
set(CMAKE_AUTORCC ON)
## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)
## Executable
add_executable(tuxns-pdns-backend ${SOURCE_FILES})
## Links
#target_link_libraries(app.hgi Qt5::Core Qt5::Network Qt5::Sql qca-qt5)
target_link_libraries(tuxns-pdns-backend Qt5::Core Qt5::Network Qt5::Sql)
