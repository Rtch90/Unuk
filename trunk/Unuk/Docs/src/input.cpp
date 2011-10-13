#include "input.h"
#include <string.h>

static mouse_t mouse;
static keyboard_t keyboard;

bool _curr_key(int index)
{
	return (keyboard.keys[index] != 0);
}

bool _old_key(int index)
{
	return (keyboard.old_keys[index] != 0);
};

bool _curr_mouse(int button)
{
	return ((mouse.buttons & SDL_BUTTON(button)) != 0);
};

bool _old_mouse(int button)
{
	return ((mouse.old_buttons & SDL_BUTTON(button)) != 0);
};

bool create_input()
{
	memset(&keyboard, 0, sizeof(keyboard_t));
	memset(&mouse, 0, sizeof(mouse_t));
	SDL_PumpEvents();
	SDL_PumpEvents();
	unsigned char *temp_keys = SDL_GetKeyState(&keyboard.keycount);
	keyboard.keys = (unsigned char *)malloc(sizeof(char) * keyboard.keycount);
	keyboard.old_keys = (unsigned char *)malloc(sizeof(char) * keyboard.keycount);

	memcpy(keyboard.keys, temp_keys, sizeof(char) * keyboard.keycount);
	mouse.buttons = SDL_GetMouseState(&mouse.dx, &mouse.dy);
	return true;
};

void update_input()
{
	SDL_PumpEvents();
	keyboard.last_char = -1;
	mouse.old_x = mouse.dx;
	mouse.old_y = mouse.dy;
	mouse.old_buttons = mouse.buttons;
	mouse.buttons = SDL_GetMouseState(&mouse.dx, &mouse.dy);

	memcpy(keyboard.old_keys, keyboard.keys, sizeof(char) * keyboard.keycount);

	unsigned char *tmp = SDL_GetKeyState(&keyboard.keycount);
	memcpy(keyboard.keys, tmp, sizeof(char) * keyboard.keycount);

	keyboard.mods = SDL_GetModState();

	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
			keyboard.last_char = event.key.keysym.sym;
	}
};

char get_key()
{
	if(keyboard.last_char != -1)
		return keyboard.last_char;
	return 0;
};

unsigned int get_x()
{
	return mouse.dx;
};

unsigned int get_y()
{
	return mouse.dy;
};

unsigned int get_old_x()
{
	return mouse.old_x;
};

unsigned int get_old_y()
{
	return mouse.old_y;
};

unsigned int get_mods()
{
	return keyboard.mods;
};

bool key_down(int index)
{
	return(_curr_key(index) && !_old_key(index));
};

bool key_still_down(int index)
{
	return(_curr_key(index) && _old_key(index));
};

bool key_up(int index)
{
	return(!_curr_key(index) && _old_key(index));
};

bool key_still_up(int index)
{
	return (!_curr_key(index) && !_old_key(index));
};

bool mouse_down(int button)
{
	return (_curr_mouse(button) && !_old_mouse(button));
};

bool mouse_still_down(int button)
{
	return (_curr_mouse(button) && _old_mouse(button));
};

bool mouse_up(int button)
{
	return (!_curr_mouse(button) && _old_mouse(button));
};

bool mouse_still_up(int button)
{
	return (!_curr_mouse(button) && !_old_mouse(button));
};

void destroy_input()
{
	free(keyboard.keys);
	free(keyboard.old_keys);
};
