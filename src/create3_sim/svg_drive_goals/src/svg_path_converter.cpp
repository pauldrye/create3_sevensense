#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <regex>
#include "irobot_create_msgs/action/drive_arc.hpp"
#include "irobot_create_msgs/action/drive_distance.hpp"
#include "irobot_create_msgs/action/rotate_angle.hpp"

void case_c(double param0, double param1, double param2, double param3, double param4, double param5,double& currentX,double& currentY,double& currentTheta,double maxTranslationSpeed,double maxRotationSpeed){
    double x0 = currentX, y0 = currentY;
    int numSegments = 20;
    for (int i = 0; i < numSegments; i++) {
        // Compute the position and angle at the start of the segment
        double t1 = (double)i / numSegments;
        double t2 = (double)(i + 1) / numSegments;
        double x = std::pow(1 - t2, 3) * x0 + 3 * std::pow(1 - t2, 2) * t2 * param0 + 3 * (1 - t2) * std::pow(t2, 2) * param2 + std::pow(t2, 3) * param4;
        double y = std::pow(1 - t2, 3) * y0 + 3 * std::pow(1 - t2, 2) * t2 * param1 + 3 * (1 - t2) * std::pow(t2, 2) * param3 + std::pow(t2, 3) * param5;
        double distance = std::sqrt(std::pow(std::abs(x - currentX), 2) + std::pow(std::abs(y - currentY), 2));
        double angle = std::atan2(y - currentY, x - currentX) - currentTheta;
        currentX = x;
        currentY = y;
        currentTheta += angle;

        // Send the drive goal command
        std::string command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                    std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
        system(command.c_str());
        command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                        std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
        system(command.c_str());
    }
 }

void convertSVGPathToDriveGoals(std::string svgPathString, double maxTranslationSpeed, double maxRotationSpeed) {
    // Split the path string into an array of commands
    std::vector<std::string> pathCommands;
    std::regex commandRegex("[MmLlHhVvCcQqZz][^MmLlHhVvCcQqZz]*");
    std::sregex_iterator commandIterator(svgPathString.begin(), svgPathString.end(), commandRegex);
    std::sregex_iterator commandEnd;

    for (; commandIterator != commandEnd; ++commandIterator) {
        std::string command = commandIterator->str();
        pathCommands.push_back(command);
        std::cout << "push back command: " << command << std::endl;
    }

    // Set the initial position and orientation to (0, 0, 0)
    double currentX = 0;
    double currentY = 0;
    double currentTheta = 0;
    int i = 0;
    std::cout << "all commands pushed, generating drive goals" << std::endl;

    // Loop through the commands and generate drive goals
    for (std::string command : pathCommands) {
        
        std::cout << "start generation" << i++ << std::endl;
        // Extract the command type and parameters using regular expressions
        std::regex regex("([a-zA-Z])([^a-zA-Z]*)");
        std::smatch match;
        std::regex_match(command, match, regex);
        std::string type = match[1].str();
        std::string paramsString = match[2].str();
        std::vector<std::string> params;
        std::stringstream ss(paramsString);
        std::string param;
        while (getline(ss, param, ',')) {
            std::cout << "getline" << std::endl;
            if (!param.empty()) {
                params.push_back(param);
                std::cout << "push back params " << param << std::endl;
            }
        }
        double distance, angle;
        // Determine if the command is relative or absolute
        bool isRelative = (type[0] >= 'a' && type[0] <= 'z');
        if (isRelative) {
            std::cout << "is relative" << std::endl;
            switch (type[0]) {
                case 'm':
                    angle = std::atan2(std::stod(params[1]) - currentY, std::stod(params[0]) - currentX) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::sqrt(std::pow(std::abs(std::stod(params[0])/10), 2) +
                                 std::pow(std::abs(std::stod(params[1])/10), 2));
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX += std::stod(params[0])/10;
                    currentY += std::stod(params[1])/10;
                    currentTheta += angle;
                    break;
                case 'l':
                    angle = std::atan2(std::stod(params[1]) - currentY, std::stod(params[0]) - currentX) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::sqrt(std::pow(std::abs(std::stod(params[0])/10), 2) +
                                 std::pow(std::abs(std::stod(params[1]))/10, 2));
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX += std::stod(params[0])/10;
                    currentY += std::stod(params[1])/10;
                    currentTheta += angle;
                    break;
                case 'h':
                    angle = (std::stod(params[0])>0 ? 0 : M_1_PI) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::abs(std::stod(params[0])/10);
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX += std::stod(params[0])/10;
                    currentTheta += angle;
                    break;
                case 'v':
                    angle = (std::stod(params[1])>0 ? 0 : M_1_PI) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::abs(std::stod(params[1])/10);
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentY += std::stod(params[0])/10;
                    currentTheta += angle;
                    break;
                case 'c':
                    case_c(std::stod(params[0]), std::stod(params[1]),std::stod(params[2]),std::stod(params[3]),std::stod(params[4]),std::stod(params[5]), currentX, currentY, currentTheta, maxTranslationSpeed,maxRotationSpeed);
                    currentX += std::stod(params[4]);
                    currentY += std::stod(params[5]);
                    type[0] = 'C';
                    params[0] = std::to_string(currentX + std::stod(params[0]));
                    params[1] = std::to_string(currentY + std::stod(params[1]));
                    params[2] = std::to_string(currentX + std::stod(params[2]));
                    params[3] = std::to_string(currentY + std::stod(params[3]));
                    params[4] = std::to_string(currentX + std::stod(params[4]));
                    params[5] = std::to_string(currentY + std::stod(params[5]));
                    break;
                case 'q':
                    currentX += std::stod(params[2]);
                    currentY += std::stod(params[3]);
                    type[0] = 'Q';
                    params[0] = std::to_string(currentX);
                    params[1] = std::to_string(currentY);
                    params[2] = std::to_string(currentX + std::stod(params[2]));
                    params[3] = std::to_string(currentY + std::stod(params[3]));
                    break;
                case 'z':
                    command = "ros2 action send_goal /navigate_to_position irobot_create_msgs/action/NavigateToPosition \"{achieve_goal_heading: true,goal_pose:{pose:{position:{x: 0,y: 0.0,z: 0.0}, orientation:{x: 0.0,y: 0.0, z: 0.0, w: 1.0}}}}\"";
                    system(command.c_str());
                    currentX = 0;
                    currentY = 0;
                    break;
            }
        } else {
            std::cout << "not relative " << type[0] << std::endl;
            // Update the current position and orientation for absolute commands
            switch (type[0]) {
                case 'M':
                    std::cout << "M or L" << std::endl;
                    angle = std::atan2(std::stod(params[1]) - currentY, std::stod(params[0]) - currentX) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::sqrt(std::pow(std::abs(std::stod(params[0]) - currentX)/10, 2) +
                                 std::pow(std::abs(std::stod(params[1]) - currentY)/10, 2));
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX = std::stod(params[0])/10;
                    currentY = std::stod(params[1])/10;
                    currentTheta += angle;
                    std::cout << "hello" << std::endl;
                    break;
                case 'L':
                    std::cout << "M or L" << std::endl;
                    angle = std::atan2(std::stod(params[1]) - currentY, std::stod(params[0]) - currentX) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{angle: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::sqrt(std::pow(std::abs(std::stod(params[0]) - currentX)/10, 2) +
                                 std::pow(std::abs(std::stod(params[1])/10 - currentY), 2));
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX = std::stod(params[0])/10;
                    currentY = std::stod(params[1])/10;
                    currentTheta += angle;
                    std::cout << "hello" << std::endl;
                    break;
                case 'H':
                    angle = (std::stod(params[0])>0 ? 0 : M_1_PI) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{distance: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::abs(std::stod(params[0])/10 - currentX);
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentX = std::stod(params[0])/10;
                    currentTheta += angle;
                    break;
                case 'V':
                    angle = (std::stod(params[1])>0 ? 0 : M_1_PI) - currentTheta;
                    command = "ros2 action send_goal /rotate_angle irobot_create_msgs/action/RotateAngle \"{distance: " +
                                   std::to_string(angle) + ", max_rotation_speed: " + std::to_string(maxRotationSpeed) + "}\"";
                    system(command.c_str());
                    distance = std::abs(std::stod(params[1]) - currentY)/10;
                    command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
                    system(command.c_str());
                    currentY = std::stod(params[0])/10;
                    currentTheta += angle;
                    break;
                case 'Z':
                    command = "ros2 action send_goal /navigate_to_position irobot_create_msgs/action/NavigateToPosition \"{achieve_goal_heading: true,goal_pose:{pose:{position:{x: 0,y: 0.0,z: 0.0}, orientation:{x: 0.0,y: 0.0, z: 0.0, w: 1.0}}}}\"";
                    system(command.c_str());
                    currentX = 0;
                    currentY = 0;
                    break;
                case 'C':
                    case_c(std::stod(params[0]), std::stod(params[1]),std::stod(params[2]),std::stod(params[3]),std::stod(params[4]),std::stod(params[5]), currentX, currentY, currentTheta, maxTranslationSpeed,maxRotationSpeed);
                    break;
            }
        }
        /*std::cout << "done with params, generating drive goal command" << std::endl;
        // Generate the appropriate drive goal command based on the command type and parameters
       
        if (type == "M" || type == "L" || type == "H" || type == "V") {

            distance = std::sqrt(std::pow(std::abs(std::stod(params[0]) - currentX), 2) +
                                 std::pow(std::abs(std::stod(params[1]) - currentY), 2));
            angle = std::atan2(std::stod(params[1]) - currentY, std::stod(params[0]) - currentX) - currentTheta;
            currentTheta += angle;
            std::string command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance/10) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
            system(command.c_str());
            std::cout << "MLHV" << std::endl;
        } else if (type == "C" || type == "Q") {
            // Compute the curvature of the arc or circle
            double curvature = (2 * std::sin(angle / 2)) / ((angle / 2) * distance);
            double radius = std::abs(curvature);

            // Compute the translation direction
            double translateDirection = (curvature > 0) ? 1 : -1;

            std::string command = "ros2 action send_goal /drive_arc irobot_create_msgs/action/DriveArc \"{angle: " + std::to_string(angle) + ", radius: " + std::to_string(radius) + ", translate_direction: " + std::to_string(translateDirection) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
            system(command.c_str());
            std::cout << "CQ" << std::endl;
        } else if (type == "Z") {
            distance = std::sqrt(std::pow(std::abs(currentX), 2) + std::pow(std::abs(currentY), 2));
            angle = std::atan2(-currentY, -currentX) - currentTheta;
            currentTheta += angle;
            std::string command = "ros2 action send_goal /drive_distance irobot_create_msgs/action/DriveDistance \"{distance: " +
                                   std::to_string(distance) + ", max_translation_speed: " + std::to_string(maxTranslationSpeed) + "}\"";
            system(command.c_str());
            std::cout << "Z" << std::endl;
        }
        std::cout << "done" << i++ << std::endl;*/
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <SVG path string> <max translation speed> <max rotation speed>" << std::endl;
        return 1;
    }
    std::cout << "in main" << std::endl;
    std::string svgPathString = argv[1];
    double maxTranslationSpeed = std::stod(argv[2]);
    double maxRotationSpeed = std::stod(argv[3]);

    convertSVGPathToDriveGoals(svgPathString, maxTranslationSpeed, maxRotationSpeed);

    return 0;
}