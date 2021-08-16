#ifndef GAMECONFIGS_H
#define GAMECONFIGS_H
#pragma once

struct GameColor {
    unsigned int r, g, b, a;
};

class GameConfigs {
	public:
		// general
		static const char* gameTitle;
		static const int initWindowWidth;
		static const int initWindowHeight;
		static int CURRENT_WIDTH;
		static int CURRENT_HEIGHT;
		static const int cubeEdgeSize;
		static bool debugMode;
		static bool PLAYER_INFINITE_ITEMS_MODE;
		static const int PLAYER_INTERACTION_RANGE;
		static const int MAX_ITEMS_PER_SLOT;
		static const int PLAYER_INVENTORY_SLOTS_COUNT;
		static const float PLAYER_BODY_RADIUS;
		static const float PLAYER_CAMERA_HEIGHT;
		// keyboard
		static const unsigned char KEYBOARD_FORWARD;
		static const unsigned char KEYBOARD_RIGHT;
		static const unsigned char KEYBOARD_BACK;
		static const unsigned char KEYBOARD_LEFT;
		static const unsigned char KEYBOARD_SPACE;
		static const int KEYBOARD_PLAYER_BOOST_KEY_CODE;
		static const int KEYBOARD_DEBUG_MODE_KEY_CODE;
		// mouse
		static const float MOUSE_SENSITIVITY;
		static const int MOUSE_MAX_VERTICAL_ANGLE;
		static const int MOUSE_MIN_VERTICAL_ANGLE;
		// colors
		static const GameColor COLOR_WHITE;
		static const GameColor COLOR_BLACK;
		static const GameColor COLOR_RED;
};

#endif