//
//  InputConstants.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "InputConstants.h"

#ifdef __APPLE__
  #include "TargetConditionals.h"
  #if TARGET_OS_MAC
    //#import <Cocoa/Cocoa.h>
    #include <Carbon/Carbon.h>
  #endif
#elif WIN32
	#include <Windows.h>
	#include "GL/gl.h"
#endif


#if TARGET_OS_MAC
//Common
const int KEYCODE_TAB = kVK_Tab;
const int KEYCODE_RETURN = kVK_Return;
const int KEYCODE_ESCAPE = kVK_Escape;
const int KEYCODE_SPACE = kVK_Space;
const int KEYCODE_DELETE = kVK_Delete;
const int KEYCODE_LEFT_SHIFT = kVK_Shift;
const int KEYCODE_LEFT_ALT = kVK_Option;
const int KEYCODE_LEFT_CONTROL = kVK_Control;
const int KEYCODE_RIGHT_SHIFT = kVK_RightShift;
const int KEYCODE_RIGHT_ALT = kVK_RightOption;
const int KEYCODE_RIGHT_CONTROL = kVK_RightControl;

//Arrows
const int KEYCODE_LEFT_ARROW = kVK_LeftArrow;
const int KEYCODE_RIGHT_ARROW = kVK_RightArrow;
const int KEYCODE_UP_ARROW = kVK_UpArrow;
const int KEYCODE_DOWN_ARROW = kVK_DownArrow;

//Numbers
const int KEYCODE_0 = kVK_ANSI_0;
const int KEYCODE_1 = kVK_ANSI_1;
const int KEYCODE_2 = kVK_ANSI_2;
const int KEYCODE_3 = kVK_ANSI_3;
const int KEYCODE_4 = kVK_ANSI_4;
const int KEYCODE_5 = kVK_ANSI_5;
const int KEYCODE_6 = kVK_ANSI_6;
const int KEYCODE_7 = kVK_ANSI_7;
const int KEYCODE_8 = kVK_ANSI_8;
const int KEYCODE_9 = kVK_ANSI_9;

//Letters
const int KEYCODE_A = kVK_ANSI_A;
const int KEYCODE_B = kVK_ANSI_B;
const int KEYCODE_C = kVK_ANSI_C;
const int KEYCODE_D = kVK_ANSI_D;
const int KEYCODE_E = kVK_ANSI_E;
const int KEYCODE_F = kVK_ANSI_F;
const int KEYCODE_G = kVK_ANSI_G;
const int KEYCODE_H = kVK_ANSI_H;
const int KEYCODE_I = kVK_ANSI_I;
const int KEYCODE_J = kVK_ANSI_J;
const int KEYCODE_K = kVK_ANSI_K;
const int KEYCODE_L = kVK_ANSI_L;
const int KEYCODE_M = kVK_ANSI_M;
const int KEYCODE_N = kVK_ANSI_N;
const int KEYCODE_O = kVK_ANSI_O;
const int KEYCODE_P = kVK_ANSI_P;
const int KEYCODE_Q = kVK_ANSI_Q;
const int KEYCODE_R = kVK_ANSI_R;
const int KEYCODE_S = kVK_ANSI_S;
const int KEYCODE_T = kVK_ANSI_T;
const int KEYCODE_U = kVK_ANSI_U;
const int KEYCODE_V = kVK_ANSI_V;
const int KEYCODE_W = kVK_ANSI_W;
const int KEYCODE_X = kVK_ANSI_X;
const int KEYCODE_Y = kVK_ANSI_Y;
const int KEYCODE_Z = kVK_ANSI_Z;

#elif WIN32
//Common
const int KEYCODE_TAB = VK_TAB;
const int KEYCODE_RETURN = VK_RETURN;
const int KEYCODE_ESCAPE = VK_ESCAPE;
const int KEYCODE_SPACE = VK_SPACE;
const int KEYCODE_DELETE = VK_BACK;
const int KEYCODE_LEFT_SHIFT = VK_LSHIFT;
const int KEYCODE_LEFT_ALT = VK_LMENU;
const int KEYCODE_LEFT_CONTROL = VK_LCONTROL;
const int KEYCODE_RIGHT_SHIFT = VK_RSHIFT;
const int KEYCODE_RIGHT_ALT = VK_RMENU;
const int KEYCODE_RIGHT_CONTROL = VK_RCONTROL;

//Arrows
const int KEYCODE_LEFT_ARROW = VK_LEFT;
const int KEYCODE_RIGHT_ARROW = VK_RIGHT;
const int KEYCODE_UP_ARROW = VK_UP;
const int KEYCODE_DOWN_ARROW = VK_DOWN;

//Numbers
const int KEYCODE_0 = '0';
const int KEYCODE_1 = '1';
const int KEYCODE_2 = '2';
const int KEYCODE_3 = '3';
const int KEYCODE_4 = '4';
const int KEYCODE_5 = '5';
const int KEYCODE_6 = '6';
const int KEYCODE_7 = '7';
const int KEYCODE_8 = '8';
const int KEYCODE_9 = '9';

//Letters
const int KEYCODE_A = 'A';
const int KEYCODE_B = 'B';
const int KEYCODE_C = 'C';
const int KEYCODE_D = 'D';
const int KEYCODE_E = 'E';
const int KEYCODE_F = 'F';
const int KEYCODE_G = 'G';
const int KEYCODE_H = 'H';
const int KEYCODE_I = 'I';
const int KEYCODE_J = 'J';
const int KEYCODE_K = 'K';
const int KEYCODE_L = 'L';
const int KEYCODE_M = 'M';
const int KEYCODE_N = 'N';
const int KEYCODE_O = 'O';
const int KEYCODE_P = 'P';
const int KEYCODE_Q = 'Q';
const int KEYCODE_R = 'R';
const int KEYCODE_S = 'S';
const int KEYCODE_T = 'T';
const int KEYCODE_U = 'U';
const int KEYCODE_V = 'V';
const int KEYCODE_W = 'W';
const int KEYCODE_X = 'X';
const int KEYCODE_Y = 'Y';
const int KEYCODE_Z = 'Z';

#endif