cmake_minimum_required( VERSION 3.10 )
project( Precise-Timing )

set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )

set( LIBRARY_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Relative or absolute path to directory where built shared libraries will be placed" )

add_library( Timing SHARED ${CMAKE_CURRENT_LIST_DIR}/timing.c )
set_target_properties( Timing PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_DIR} )
target_include_directories( Timing PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_compile_definitions( Timing PUBLIC -DDEBUG )
if( UNIX AND NOT APPLE )
  target_link_libraries( Timing -lrt )
endif()
