#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotRight;
	bool rotLeft;

	int mouseX = 0;
	int mouseY = 0;
	bool mouseLMBDown = false;
};
