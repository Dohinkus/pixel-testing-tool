#include "ScreenReader.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

void toClipboard(const std::string& s);

#define X_OFFSET 0
#define Y_OFFSET 0

#define elif else if

int main() {
	ScreenReader robot;

	//x, y
	POINT p;

	std::string stringToCopy;

	while (true) {

		std::ostringstream ss;

		if (GetKeyState('U') & 0x8000) {

			robot.updatePixels();

			if(GetCursorPos(&p)) {
				
				ss <<
					std::hex << std::showbase << std::uppercase <<
					static_cast<int>(robot.getRed(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					static_cast<int>(robot.getGreen(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					static_cast<int>(robot.getBlue(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					0;
			
				toClipboard(ss.str());
				std::cout << ss.str() << std::endl; 
			}
		}
		elif (GetKeyState('I') & 0x8000) {
			if (GetCursorPos(&p)) {
				ss <<
					std::dec << std::noshowbase <<
					p.x + X_OFFSET << ", " <<
					p.y + Y_OFFSET;

				toClipboard(ss.str());
				std::cout << ss.str() << std::endl;
			}
		}
		elif(GetKeyState('J') & 0x8000) {

			robot.updatePixels();

			if (GetCursorPos(&p)) {

				ss <<
					std::dec << std::noshowbase <<
					p.x + X_OFFSET << ", " <<
					p.y + Y_OFFSET << ", " <<
					std::hex << std::showbase << std::uppercase <<
					static_cast<int>(robot.getRed(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					static_cast<int>(robot.getGreen(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					static_cast<int>(robot.getBlue(p.x + X_OFFSET, p.y + Y_OFFSET)) << ", " <<
					0;

				toClipboard(ss.str());
				std::cout << ss.str() << std::endl;
			}
		}
	}

	return 0;
}

void toClipboard(const std::string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	//size() + 1 is always more than 0
	memcpy(GlobalLock(hg), s.c_str() + 1, s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}