#ifndef _APPLYSURFACE_H_
#define _APPLYSURFACE_H_
#include <SDL/SDL.h>
#include <assert.h>
#include "Debug.h"
#include "../Unuk/Globals.h"

/*            Use for objects.
 * Blit a surface to another surface. An
 * optioanl clip argument can be given. The surface
 * will be applied to the destination, taking into
 * account the position of the camera.
 */
void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

// This one won't take the camera into account, so we could use it for GUI stuff.
void ApplySurfaceLiteral(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

#endif
