#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	
	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;

	int mouseX = 0;
	int mouseY = 0;
	bool mouseLMBDown = false;
};
