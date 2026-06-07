cmake_minimum_required(VERSION 3.8)
project(gripper_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

find_package(gz-sim8 REQUIRED)

add_library(gripper_plugin SHARED
  src/gripper_plugin.cpp
)

target_link_libraries(gripper_plugin
  gz-sim8::gz-sim8
)

install(
  TARGETS gripper_plugin
  LIBRARY DESTINATION lib
)

ament_package()