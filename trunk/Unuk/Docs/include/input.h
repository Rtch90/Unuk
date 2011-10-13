#ifndef INPUT_H_
#define INPUT_H_

#include <SDL/SDL.h>

typedef struct mouse_s
{
	int dx, dy;
	int old_x, old_y;
	unsigned int buttons;
	unsigned int old_buttons;
} mouse_t;

typedef struct keyboard_s
{
	unsigned char *keys;
	unsigned char *old_keys;
	int keycount;
	int last_char;
	unsigned int mods;
} keyboard_t;

typedef struct input_s
{
	mouse_t mouse;
	keyboard_t keyboard;
} input_t;

bool create_input();
void update_input();

char get_key();
unsigned int get_x();
unsigned int get_y();
unsigned int get_old_x();
unsigned int get_old_y();
unsigned int get_mods();
bool key_down(int index);
bool key_still_down(int index);
bool key_up(int index);
bool key_still_up(int index);
bool mouse_down(int button);
bool mouse_still_down(int button);
bool mouse_up(int button);
bool mouse_still_up(int button);

void destroy_input();
#endif // INPUT_H_
