cmake_minimum_required(VERSION 3.7)

project ( cg-lib )

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

include_directories( ${CMAKE_SOURCE_DIR}/smt-lib ${CMAKE_SOURCE_DIR}/core-lib )

file( GLOB SOURCES "*.cpp" )

add_library( cg-lib SHARED ${SOURCES} )

target_link_libraries( cg-lib smt-lib core-lib )

if( WIN32 )
  target_link_libraries( cg-lib libantlr4-runtime.dll )
  install( TARGETS cg-lib DESTINATION "C:/Program Files (x86)/o-ratio" )
endif()

if( UNIX )
  target_link_libraries( cg-lib libantlr4-runtime.so )
  install( TARGETS cg-lib DESTINATION /usr/lib )
endif()