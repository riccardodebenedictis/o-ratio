cmake_minimum_required(VERSION 3.7)

project (o-ratio)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

if( WIN32 )
  include_directories( "C:/Program Files (x86)/LIBANTLR4/include/antlr4-runtime" )
  link_directories( "C:/Program Files (x86)/LIBANTLR4/lib" )
endif()

if( UNIX )
  include_directories( /usr/local/include/antlr4-runtime )
  link_directories( /usr/local/lib )
endif()

include_directories( smt-lib core-lib/parser core-lib cg-lib )

file( GLOB SOURCES "smt-lib/*.cpp" "core-lib/*.cpp" "core-lib/parser/*.cpp" "cg-lib/*.cpp" )

add_library( o-ratio SHARED ${SOURCES} )

if( WIN32 )
  target_link_libraries( o-ratio libantlr4-runtime.dll )
  install( TARGETS o-ratio DESTINATION "C:/Program Files (x86)/o-ratio" )
endif()

if( UNIX )
  target_link_libraries( o-ratio libantlr4-runtime.so )
  install( TARGETS o-ratio DESTINATION /usr/lib )
endif()