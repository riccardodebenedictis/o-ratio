cmake_minimum_required(VERSION 3.7)

project ( smt-lib )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

file( GLOB SOURCES "*.cpp" )

add_library( smt-lib SHARED ${SOURCES} )

if( WIN32 )
  install( TARGETS smt-lib DESTINATION "C:/Program Files (x86)/o-ratio" )
endif()

if( UNIX )
  install( TARGETS smt-lib DESTINATION /usr/lib )
endif()