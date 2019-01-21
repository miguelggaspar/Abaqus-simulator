#My CMakeLists.txt
cmake_minimum_required (VERSION 2.8)
project (ProjectoFinal)
set(PROG1 Gtkgui)
set(PROG2 server)

#---------------------------------

set(SOURCES1 src/mainsrc/main.c src/mainsrc/myf.c src/mainsrc/callbacks.c src/mainsrc/gui.c src/mainsrc/manager.c src/client/client.c src/client/myfclient.c) #alternative command for wildcards: file(GLOB SOURCES "src/*.c")
set(SOURCES2 src/server/server.c src/server/auxfuncs.c)

#---- Include libraries ---#
include_directories ("${PROJECT_SOURCE_DIR}/srcmyutils")
link_directories ("${PROJECT_SOURCE_DIR}/lib")

add_executable(${PROG1} ${SOURCES1})
add_executable(${PROG2} ${SOURCES2})

#-----------------------------------------------
#The recommended way to find packages automatically using PkgConfig
#See more on http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
find_package(PkgConfig REQUIRED)  #necessary for next command to work
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})


target_link_libraries(${PROG1} myutils)

#include_directories ("${PROJECT_SOURCE_DIR}/../srcmyutils")
#link_directories ("${PROJECT_SOURCE_DIR}/../lib")

target_link_libraries(${PROG1} ${GTK_LIBRARIES} )
#target_link_libraries (${PROG1} myutils)
#-----------------------------------------------------
# --- add custom mtargets (and dependencies)
add_custom_target( cpfiles
                COMMAND cp "${PROJECT_SOURCE_DIR}/src/*.glade" "${PROJECT_BINARY_DIR}"
                COMMAND cp "${PROJECT_SOURCE_DIR}/src/*.png" "${PROJECT_BINARY_DIR}"
                 )

#Add dependencies
add_dependencies(${PROG1} cpfiles)


# The project version number. Used in documentation generation and similar.
# Optional but recommended
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

#-- add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install doc (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in" )
    set(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    set(doxy_main_page "${CMAKE_CURRENT_SOURCE_DIR}/doc/mainpage.dox")
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
