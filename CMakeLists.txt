cmake_minimum_required(VERSION 3.7)

project (o-ratio)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

add_subdirectory(smt-lib)
add_subdirectory(core-lib)
add_subdirectory(cg-lib)