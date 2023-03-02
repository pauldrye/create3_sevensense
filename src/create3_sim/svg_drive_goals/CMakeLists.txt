cmake_minimum_required(VERSION 3.8)
project(svg_drive_goals)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(irobot_create_msgs REQUIRED)

add_executable(svg_drive_goals src/svg_path_converter.cpp)
ament_target_dependencies(svg_drive_goals rclcpp irobot_create_msgs)

install(TARGETS
  svg_drive_goals
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()