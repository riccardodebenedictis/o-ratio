cmake_minimum_required(VERSION 3.7)

project ( java-api-lib )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

if( WIN32 )
  include_directories( "C:/Program Files (x86)/LIBANTLR4/include/antlr4-runtime" "C:/Program Files/Java/jdk1.8.0_121/include" "C:/Program Files/Java/jdk1.8.0_121/include/win32" )
  link_directories( "C:/Program Files (x86)/LIBANTLR4/lib" )
endif()

if( UNIX )
  include_directories( /usr/local/include/antlr4-runtime /usr/lib/jvm/java-8-openjdk-amd64/include /usr/lib/jvm/java-8-openjdk-amd64/include/linux )
  link_directories( /usr/local/lib )
endif()

include_directories( ${CMAKE_SOURCE_DIR}/smt-lib ${CMAKE_SOURCE_DIR}/core-lib ${CMAKE_SOURCE_DIR}/cg-lib )

file( GLOB SOURCES "*.cpp" )

add_library( java-api-lib SHARED ${SOURCES} )

target_link_libraries( java-api-lib smt-lib core-lib cg-lib )

if( WIN32 )
  target_link_libraries( java-api-lib libantlr4-runtime.dll )
  install( TARGETS java-api-lib DESTINATION "C:/Program Files (x86)/o-ratio" )
endif()

if( UNIX )
  target_link_libraries( java-api-lib libantlr4-runtime.so )
  install( TARGETS java-api-lib DESTINATION /usr/lib )
endif()