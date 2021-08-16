#include "GameConfigs.hpp"

const char* GameConfigs::gameTitle = "Trash square game"; 
const int GameConfigs::initWindowWidth = 720;
const int GameConfigs::initWindowHeight = 500;
int GameConfigs::CURRENT_WIDTH = GameConfigs::initWindowWidth;
int GameConfigs::CURRENT_HEIGHT = GameConfigs::initWindowHeight;
const int GameConfigs::cubeEdgeSize = 1;
bool GameConfigs::debugMode = false;
bool GameConfigs::PLAYER_INFINITE_ITEMS_MODE = true;
const int GameConfigs::PLAYER_INTERACTION_RANGE = 5;
const int GameConfigs::MAX_ITEMS_PER_SLOT = 32;
const int GameConfigs::PLAYER_INVENTORY_SLOTS_COUNT = 8;
const float GameConfigs::PLAYER_BODY_RADIUS = 0.25;
const float GameConfigs::PLAYER_CAMERA_HEIGHT = 1.7;
const unsigned char GameConfigs::KEYBOARD_FORWARD = 'w';
const unsigned char GameConfigs::KEYBOARD_RIGHT = 'd';
const unsigned char GameConfigs::KEYBOARD_BACK = 's';
const unsigned char GameConfigs::KEYBOARD_LEFT = 'a';
const unsigned char GameConfigs::KEYBOARD_SPACE = ' ';
const int GameConfigs::KEYBOARD_PLAYER_BOOST_KEY_CODE = 112; // SHIFT
const int GameConfigs::KEYBOARD_DEBUG_MODE_KEY_CODE = 114; // CTRL
const float GameConfigs::MOUSE_SENSITIVITY = 0.06; // in percent /100
const int GameConfigs::MOUSE_MAX_VERTICAL_ANGLE = 90;
const int GameConfigs::MOUSE_MIN_VERTICAL_ANGLE = -90;
const GameColor GameConfigs::COLOR_WHITE = {255,255,255,255};
const GameColor GameConfigs::COLOR_BLACK = {0,0,0,255};
const GameColor GameConfigs::COLOR_RED = {255,0,0,255};