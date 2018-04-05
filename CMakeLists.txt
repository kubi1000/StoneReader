cmake_minimum_required(VERSION 3.8)
project(gui)

MESSAGE ("\n==> Finding 3rd Party Packages")
find_package( OpenCV REQUIRED )
find_package( PkgConfig REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake,
# it contains documentation

SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W" )
SET( CMAKE_C_FLAGS_RELEASE "-O3" )
SET( CMAKE_C_FLAGS_DEBUG "-g3" )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -std=c++11" )
SET( CMAKE_CXX_FLAGS_RELEASE "-O3" )
SET( CMAKE_CXX_FLAGS_DEBUG "-g3" )


SET( BASE_DIR ${CMAKE_SOURCE_DIR} )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin )


# Make include directories available for all..
INCLUDE_DIRECTORIES(
        ${OpenCV_INCLUDE_DIR}
        ${GTKMM_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/main.cpp
        src/MainApp.cpp
        src/MainApp.h
        src/DialogFileOpen.cpp
        src/DialogFileOpen.h
        src/MainWindow.cpp
        src/MainWindow.h
        src/Picture.cpp
        src/Picture.h src/Controller.cpp src/Controller.h src/SRefBuilder.h)

add_executable(gui ${SOURCE_FILES})
target_link_libraries(gui
        ${OpenCV_LIBS}
        ${GTKMM_LIBRARIES}
        )