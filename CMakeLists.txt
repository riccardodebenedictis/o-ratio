cmake_minimum_required(VERSION 3.7)

project (o-ratio)

option(BUILD_JAVA_API "Build the Java API" ON)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

add_subdirectory( smt-lib )
add_subdirectory( core-lib )
add_subdirectory( cg-lib )

if( BUILD_JAVA_API )
  add_subdirectory( api/java/native-api )
endif()