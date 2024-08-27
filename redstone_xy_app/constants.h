/*constants for redstone.cpp --minecraft redstone 2d*/
#ifndef CONSTANTS_H
#define CONSTANTS_H
const int TEXT_MAX_SIZE = 1000;
const int WHEN_NEWLINE = sqrt(TEXT_MAX_SIZE);  //<!>WARNING: THE PROGRAM MAY LOOK ABNORMAL WHEN EDITED! PLEASE CONSIDER CAREFULLY
const std::string REDSTONE_BLOCK = "█"; //type 0
const std::string READSTONE_WIRE_HORIZONTAL = "▁"; //type 1
const std::string READSTONE_WIRE_Vertical = "▕"; //type 2
const std::string BUTTON_LEFT = "<"; //type 3
const std::string BUTTON_RIGHT = ">"; //type 4
const std::string BUTTON_UP = "^"; //type 5
const std::string BUTTON_DOWN = "v"; //type 6
const std::string DAYLIGHT_DETECTOR = "▚"; //type 7
const std::string OBSERVER_LEFT = "▛"; //type 8
const std::string OBSERVER_RIGHT = "▜"; //type 9
const std::string OBSERVER_UP = "▀"; //type 10
const std::string OBSERVER_DOWN = "▄"; //type 11
const std::string REDSTONE_TORCH_D = "▓"; //type 12
const std::string REDSTONE_TORCH_L = "O"; //type 13

#endif // !CONSTANTS_H
