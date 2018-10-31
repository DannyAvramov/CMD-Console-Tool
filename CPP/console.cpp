/*
////////////////////////////////////////////////////
// Created By: Danilo Avramovski (Danny Avramov)  //
// Description: Created for console use.          //
//              Control sizing and enable         //
//              disabling window functions.       //
////////////////////////////////////////////////////
*/
#include "Avramov\console.hpp"

namespace con {
	void pause(void) {
		std::cout << "\n\n> Press any key to continue. . ." << std::endl;
		while (_kbhit()) {
			_getch(); 		// Empty the input buffer
		}
		_getch(); 			// Wait for a key
		while (_kbhit()) {
			_getch(); 		// Empty the input buffer (some keys sends two messages)
		}
		return;
	}
	///
	void clear(void) {
		HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		DWORD count;
		DWORD cellCount;

		COORD coord = {
			0,
			0
		};

		if (outHandle == INVALID_HANDLE_VALUE) {
			return;
		}

		if (!GetConsoleScreenBufferInfo(outHandle, &bufferInfo)) { 										// Get the number of cells in the current buffer
			return;
		}

		cellCount = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

		if (!FillConsoleOutputCharacter(outHandle, (TCHAR) ' ', cellCount, coord, &count)) { 			// Fill the entire buffer with spaces
			return;
		}

		if (!FillConsoleOutputAttribute(outHandle, bufferInfo.wAttributes, cellCount, coord, &count)) { // Fill the entire buffer with the current colors and attributes
			return;
		}

		SetConsoleCursorPosition(outHandle, coord); 													// Move the cursor home
		return;
	}
	///
	void setTitle(const std::string TITLE) {
		TCHAR consoleTitle[256];
		wsprintfA(consoleTitle, TITLE.c_str());
		SetConsoleTitleA(consoleTitle);
		return;
	}
	///
	void __stdcall setConsoleColors(const unsigned short ATTRIBS) {
		CONSOLE_SCREEN_BUFFER_INFOEX cbi;
		cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfoEx(handle, &cbi);
		cbi.wAttributes = ATTRIBS;
		SetConsoleScreenBufferInfoEx(handle, &cbi);
		return;
	}
	///
	void placeCursor(const unsigned short HORIZONTAL, const unsigned short VERTICAL) {
		COORD coord;
		coord.X = HORIZONTAL;
		coord.Y = VERTICAL;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		return;
	}
	///
	void setWindow(std::string title, unsigned short width, unsigned short height, bool bEnableExit, bool bEnableMaximize, bool bEnableMinimize, bool bEnableScrollbar, bool bEnableResizing, bool bEnableFullscreen) {
		/// Console Title
		TCHAR consoleTitle[256];
		wsprintfA(consoleTitle, title.c_str());
		SetConsoleTitleA(consoleTitle);
		/// Console Dimensions
		HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		if (outHandle == INVALID_HANDLE_VALUE) {
			throw std::runtime_error("Unable to get stdout outHandle.");
			COORD coord = GetLargestConsoleWindowSize(outHandle);
			if (width > coord.X) {
				throw std::runtime_error("The width (X) dimension is too large.");
			}else if (height > coord.Y) {
				throw std::runtime_error("The height (Y) dimension is too large.");
			};
		}

		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

		if (!GetConsoleScreenBufferInfo(outHandle, &bufferInfo)) {
			throw std::runtime_error("Unable to retrieve screen buffer info.");
		}

		SMALL_RECT &winInfo = bufferInfo.srWindow;

		COORD coordWindowSize = {
			winInfo.Right  - winInfo.Left + 1,
			winInfo.Bottom - winInfo.Top  + 1
		};

		if (coordWindowSize.X > width || coordWindowSize.Y > height) {
			SMALL_RECT info = {
				0,
				0,
				width  < coordWindowSize.X ? width  - 1 : coordWindowSize.X - 1,
				height < coordWindowSize.Y ? height - 1 : coordWindowSize.Y - 1
			};

			if (!SetConsoleWindowInfo(outHandle, TRUE, &info)) {
				throw std::runtime_error("Unable to resize window before resizing buffer.");
			};
		}

		COORD coordSize = {
			(SHORT)width,
			(SHORT)height
		};

		if (!SetConsoleScreenBufferSize(outHandle, coordSize)) {
			throw std::runtime_error("Unable to resize screen buffer.");
		}

		SMALL_RECT info = {
			0,
			0,
			width  - 1,
			height - 1
		};

		if (!SetConsoleWindowInfo(outHandle, TRUE, &info)) {
			throw std::runtime_error("Unable to resize window after resizing buffer.");
		}
		/// Window Buttons
		HWND consoleWindow = GetConsoleWindow();
		LONG Style = GetWindowLongA(consoleWindow, GWL_STYLE);

		if (!bEnableExit) {
			HMENU hmenu = GetSystemMenu(consoleWindow, FALSE);
			EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED); // Use "MF_ENABLED" to enable close button
		}

		if (!bEnableMaximize) {
			Style = Style & ~(WS_MAXIMIZEBOX);
			SetWindowLongA(consoleWindow, GWL_STYLE, Style);
		}

		if (!bEnableMinimize) {
			Style = Style & ~(WS_MINIMIZEBOX);
			SetWindowLongA(consoleWindow, GWL_STYLE, Style);
		}
		/// Window Characteristics
		if (!bEnableResizing) {
			Style = Style & ~(WS_THICKFRAME);
			SetWindowLongA(consoleWindow, GWL_STYLE, Style);
		}

		if (bEnableScrollbar) {
			GetConsoleScreenBufferInfo(outHandle, &bufferInfo);
			COORD Size = {
				bufferInfo.srWindow.Right  - bufferInfo.srWindow.Left + 1,
				bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top  + 1
			};
			SetConsoleScreenBufferSize(outHandle, Size);
			ShowScrollBar(consoleWindow, 0, false);
		}

		if (bEnableFullscreen) {
			SendMessageA(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, MNS_DRAGDROP);
		}
		return;
	}
	///
	void setWindowSize(const unsigned short WIDTH, const unsigned short HEIGHT) {
		COORD coord;
		coord.X = WIDTH;
		coord.Y = HEIGHT;
		SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = HEIGHT - 1;
		Rect.Right  = WIDTH  - 1;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);	// Set Buffer Size 
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &Rect);	// Set Window Size 
		return;
	}
	///
	void setColor(const unsigned short COLOR) {
		WORD wColor;
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo)) { 			// Use csbi for the wAttributes word											
			wColor = (bufferInfo.wAttributes & 0xF0) + (COLOR & 0x0F);  // Mask out all but the background attribute, and add in the foreground color
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
		}
		return;
	}
}
