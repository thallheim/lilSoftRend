cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # ninja/makefile only

project(lilSoftRend VERSION 0.0.1)

# FIXME: maybe bwoken; maybe I'm dumb. suss out which
find_program(GOT_GIT git
  DOC "Indicate whether git was found"
  OPTIONAL
)

###############################################
# Project options
###############################################

option(BUILD_STATIC     "Statically link the library"                       OFF)
option(BUILD_CFG_PARSER "Build the internal (TOML-ish) config file parser"  OFF)


###############################################
# GLFW (windowing, events, input handling)
###############################################
include(CheckIncludeFile)
check_include_file("GLFW/glfw3.h" OPTIONAL GLFW_SYS)

set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)
set(GLFW_DIR ${VENDOR_DIR}/glfw)
set(GLFW_LIBRARY_TYPE STATIC)

if(GLFW_SYS)
  message(STATUS "Using system GLFW headers")
elseif(EXISTS ${GLFW_DIR})
  message(STATUS "Using vendored GLFW headers")
else()
  message(STATUS "Found neither system nor vendored GLFW. Cloning...")
  # TODO: ensure git present
  if (NOT EXISTS ${VENDOR_DIR})
    file(MAKE_DIRECTORY ${VENDOR_DIR})
  endif()
  execute_process(COMMAND git clone https://github.com/glfw/glfw --depth=1
    WORKING_DIRECTORY ${VENDOR_DIR}
    COMMAND_ECHO NONE # STDERR/STDOUT/NONE
  )
endif()

add_subdirectory(${VENDOR_DIR}/glfw)



###############################################
# Main library 
###############################################
add_library(lilSoftRend)

target_sources(lilSoftRend
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS "include/"
    FILES
      "include/enums.hpp"
      "include/types.hpp"
      "include/input.hpp"
      "include/callbacks.hpp"
      "include/lilSoftRend.hpp"
      "include/windowing.hpp"
  PRIVATE
    "src/core/input.cpp"
    "src/core/windowing.cpp"
  )
  
### COMPILATION ###############################

target_compile_definitions(lilSoftRend PRIVATE
  $<$<CONFIG:Release>:NDEBUG>
)
### LINKING ###################################

target_link_libraries(lilSoftRend
  PRIVATE
  glfw
  ${CMAKE_DL_LIBS} # Unnecessary on Win
)

###############################################
# Examples bin(s)
###############################################
add_executable(example01 "examples/ex01.cpp")

target_link_libraries(example01 PRIVATE
  lilSoftRend
  glfw
)
