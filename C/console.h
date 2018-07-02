/*
//////////////////////////////////////////////
// Created 	By: Danny Avramov	    //
// Description: Created for console use.    //
// 		Control sizing and enable   //
//		disabling window functions. //
//////////////////////////////////////////////
*/
#ifndef CONSOLE_H
#define CONSOLE_H
#pragma comment(lib, "user32") // For Full-screen
#ifndef _INC_STDIO
	#include <stdio.h>
#endif
#ifndef _STDBOOL
	#include <stdbool.h>
#endif
#ifndef _INC_CONIO
	#include <conio.h>
#endif
#ifndef _WINDOWS_H
	#include <Windows.h>
#endif

void pause(void);
/*
///////////////////////////////////////////////////////////////
// Documentation:                                            //
// - Equivalent to typing "pause" into command prompt. (cmd) //
// - Pauses the console until a random key is pressed.       //
///////////////////////////////////////////////////////////////
*/


void clear(void);
/*
/////////////////////////////////////////////////////////////
// Documentation:										   //
// - Equivalent to typing "cls" into command prompt. (cmd) //
// - Clears the console screen but issuing a new buffer.   //
/////////////////////////////////////////////////////////////
*/


void setTitle(const char *TITLE);
/*
/////////////////////////////////////////////////////////////////////////
// Documentation:						       //
// - Equivalent to typing "title <example>" into command prompt. (cmd) //
// - Sets a title for the window of the console.                       //
// Example:	      						       //
// > setTitle("I like big butts");				       //
/////////////////////////////////////////////////////////////////////////
*/


void WINAPI setConsoleColors(const unsigned short ATTRIBS);
/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Documentation:										             //
// - Equivalent to typing "color <example>" into command prompt. (cmd)			 		     //
// - Responsible for changing the console foreground color (characters) and the background color.	     //
// Example:											   	     //
// > setConsoleColors(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);		 		     //
// Description of Example:					 				             //
// - Sets the background color of the console towards blue, the foreground color towards red	             //
//   and makes the foreground color opacity to the max.	 					             //
// - The function's params can use bit-shifting operators to set the background and foreground separately.   //
// Example:			 	 			                                             //
// > setConsoleColors(White);                                                                                //
// Description of Example: 									             //
// - The color enum members can be used to set the foreground of the console leaving the background default. //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/


void placeCursor(const unsigned short HORIZONTAL, const unsigned short VERTICAL);
/*
//////////////////////////////////////////////////////////////////////////////////////
// Documentation:	 							    //
// - Moves the placement of a character(s) or printed character(s)	            //
//   to the coordinates assigned in the function's params.			    //
// - Can use to move or print text anywhere on the screen.		            //
// Example:						  			    //
// > placeCursor(25, 50);				 	 		    //
// Description of Example:		 					    //
// - Moves the character new position 25 spaces to the left and 50 spaces downward. //
//////////////////////////////////////////////////////////////////////////////////////
*/


void setWindow(const LPTSTR TITLE, const USHORT WIDTH, const USHORT HEIGHT, bool bEnableExit, bool bEnableMaximize, bool bEnableMinimize, bool bEnableScrollbar, bool bEnableResizing, bool bEnableFullscreen);
/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Documentation:			 						                  //
// - Uses all the console assigning functions to define the window with the characteristics	          //
//   of the user's input determine but the function's params.		 			          //
// - Can set title to window, change window size, toggle scrollbar,	 				  //
//   toggle full-screen and toggle window state buttons.	 					  //
// Example:							 				 	  //
// > setWindow("My Title" 32, 64, false, true, true, true, true, false);			 	  //
// Description of Example:								  	          //
// - Sets the title to "My Title", makes the window 32 spaces in width and 64 spaces in height,		  //
// - Disables close button, Enables the maximize buttons, Enables the minimize button,		          //
// - Enables the resizing ability, Toggles scroll bar to true & Toggles the full-screen ability to false. //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/


void setWindowSize(const unsigned short WIDTH, const unsigned short HEIGHT);
/*
/////////////////////////////////////////////////////////////////////////////////////////
// Documentation:	 					                       //
// - Equivalent to typing "mode con:cols=<example>" and "mode con:lines=<example>"     //
//   into command prompt. (cmd)					                       //
// - The params of the function define the window's width and height.                  //
// Example:						 			       //
// > setWindowSize(100, 200);				 			       //
// Description of Example:			 				       //
// - Assigns the width of the window to be 100 spaces and the height to be 200 spaces. //
/////////////////////////////////////////////////////////////////////////////////////////
*/


void setColor(const unsigned short COLOR);
/*
/////////////////////////////////////////////////////////////////////////
// Documentation:                                                      //
// - Equivalent to typing "color <example>" into command prompt. (cmd) //
// - Function is responsible for changing the foreground color	       //
//   (the character colors) of the console.		               //
// Example:			 				       //
// > setColor(Blue);			                               //
/////////////////////////////////////////////////////////////////////////
*/

enum Color {
	Black			= 0,
	Dark_Blue		= 1,
	Dark_Green		= 2,
	Dark_Turquise	= 3,
	Dark_Red		= 4,
	Dark_Purple		= 5,
	Dark_Yellow		= 6,
	Gray			= 7,
	Dark_Gray		= 8,
	Blue			= 9,
	Green			= 10,
	Turquise		= 11,
	Red				= 12,
	Purple			= 13,
	Yellow			= 14,
	White			= 15
};
/*
///////////////////////////////////////////////////////////////////////////////////
// Documentation:	    						         //
// - An enumeration of color-coded numbers to be used by		         //
//   the two console color defining functions setConsoleColors() and setColor(), //
//   also can use the enum members as params for the functions listed above.	 //
// Example:				 					 //
// > setColor(Green);                                                            //
// Description of Example:														 //
// - The enum member which holds the color-code integer of green				 //
//   is being used to set the foreground of the console.						 //
///////////////////////////////////////////////////////////////////////////////////
*/

#endif // CONSOLE_H
