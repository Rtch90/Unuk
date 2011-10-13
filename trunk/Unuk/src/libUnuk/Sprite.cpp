#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include "Sprite.h"
#include "ImageLoader.h"
#include "Debug.h"

Sprite::Sprite(string filename) {
  image = new ImageLoader(filename.c_str());
  angle = 0;
  x	= 0.0f;
  y	= 0.0f;
  SetPivot(0.0f, 0.0f);
  SetScale(1.0f, 1.0f);
}

Sprite::~Sprite(void) {
  delete image;
}

// Enable 2D drawing mode to draw our sprites. This function MUST be
// called before any sprite is drawn on screen using the Draw method.
void Sprite::Enable2D(void) {
  GLint iViewport[4];
  
  // Get a copy of the viewport.
  glGetIntegerv(GL_VIEWPORT, iViewport);
  glPushMatrix();
  glLoadIdentity();

  // Save a copy of the projection atrix so that we can restore
  // it when it's time to do 3D rendering again.
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  // Set upt the orthographic projection.
  glOrtho( iViewport[0], iViewport[0] + iViewport[2],
	    iViewport[1] + iViewport[3], iViewport[1], -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Make sure depth testing and lighting are disabled for 2D rendering 
  //until we are finished rendering in 2D.
  glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}

// Disables the 2D drawing. This can be called before you are done 
// drawing all 2D sprites on screen using the Draw method.
void Sprite::Disable2D(void) {
  glPopAttrib();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

// Initializes extensions, textures, render states, etc. before rendering.
void Sprite::InitScene(void) {
  // Disable lighting.
  glDisable(GL_LIGHTING);
  // Disable dithering.
  glDisable(GL_DITHER);
  // Disable blending (for now).
  glDisable(GL_BLEND);
  // Disable depth testing.
  glDisable(GL_DEPTH_TEST);

  // Is the extension supported on this driver/card?
  if(!IsExtensionSupported("GL_ARB_texture_rectangle")) {
    Debug::logger->message("\nERROR: Texture rectangles not supported on this video card!");
    exit(-1);
  }

  // TODO:
  // If your machine does not support GL_NV_texture_rectangle, you can try
  // using GL_EXT_texture_rectangle. Maybe I will run a test so I can support both.

  // Enable the texture rectangle extension.
  glEnable(GL_TEXTURE_RECTANGLE_ARB);

  // Generate one texture ID.
  glGenTextures(1, &textureID);
  // Bind the texture using GL_TEXTURE_RECTANGLE_NV
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textureID);
  // Enable bilinear filtering on this texture.
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Write the 32-bit RGBA texture buffer to video memory.
  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, image->GetWidth(), image->GetHeight(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetPixelData());
}

// =================================================================
// Set the pivot point in relation to the sprite itself, that is
// using the object coordinates system. In this coordinate system
// the bottom left point of the object is at (0,0) and the top
// right is at (1,1).
//
// Example: To set the pivot to be in the middle of the sprite use
// (0.5, 0.5) default values are (1,1).
// pivotX can be any value, but when x is in the range [0,1] the
// pivot is inside the sprite where 0 is the left edge of the sprite
// and 1 is the right edge of the sprite.
// pivotY is the same as pivotX but when y is in the range of [0,1]
// the pivot is inside the sprite where 0 is the bottom edge of the
// sprite and 1 is the top edge of the sprite.
// =================================================================
void Sprite::SetPivot(GLfloat pivotX, GLfloat pivotY) {
  GLfloat deltaPivotX = pivotX - GetPivotX();
  GLfloat deltaPivotY = pivotY - GetPivotY();

  this->pivotX = pivotX;
  this->pivotY = pivotY;

  x += deltaPivotX * image->GetWidth();
  y += deltaPivotY * image->GetHeight();
}

// =================================================================
// Sets the pivot to be at the point where object's pivot is set.
// obj is the reference object to whose pivot we will set this pivot
// to be.
// Note: If the obj pivot changes or the obj moves after the SetPivot
// call has been issued, the pivot of this object will not reflect these
// changes. You must call SetPivot again with that object to update the
// pivot information.
// =================================================================
void Sprite::SetPivot(const Sprite &obj) {
  // This x location if the pivot was at SetPivot(0, 0);
  GLint worldX;
  // This y location it the pivot was at SetPivot(0, 0);
  GLint worldY;
  GLfloat newPivotX;
  GLfloat newPivotY;
 
  worldX = x - GetPivotX() * image->GetWidth();
  worldY = y - GetPivotY() * image->GetHeight();

  newPivotX = (float)(obj.x - worldX) / image->GetWidth();
  newPivotY = (float)(obj.y - worldY) / image->GetHeight();

  SetPivot(newPivotX, newPivotY);
}

// Help determine if an OpenGL extension is supported on the target machine
// at runtime.
bool Sprite::IsExtensionSupported(const char *extension) const {
  const GLubyte *extensions = NULL;
  const GLubyte *start;
  GLubyte *where, *terminator;

  // Extension names should not have spaces.
  where = (GLubyte *) strchr(extension, ' ');

  if (where || *extension == '\0')  {
    return false;
  }

  extensions = glGetString(GL_EXTENSIONS);

  // It takes a bit of care to be fool-proof about parsing the
  // OpenGL extensions string. Don't be fooled by sub-strings, etc.
  start = extensions;

  for (;;)  {
    where = (GLubyte *) strstr((const char *) start, extension);

    if (!where) {
       break;
    }

    terminator = where + strlen(extension);
    if (where == start || *(where - 1) == ' ') {
      if (*terminator == ' ' || *terminator == '\0') {
        return true;
      }
    }

    start = terminator;
  }

  return false;
}

void Sprite::Render(void) {
  InitScene();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

  // Set the primitive color to white
  glColor3f(1.0f, 1.0f, 1.0f);
  // Bind the texture to the polygons
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textureID);

  glPushMatrix();

  GLfloat transX = 1;
  GLfloat transY = 1;

  if(x != 0.0) {
    transX = x;
  }

  if(y != 0.0) {
    transY = y;
  }

  glLoadIdentity();
  glTranslatef(transX, transY, 0);
  glScalef(scaleX, scaleY, 1.0);
  glRotatef(angle, 0.0, 0.0, 1.0);

  // =================================================================
  // Render a quad
  // Instead of the using (s,t) coordinates, with the GL_NV_texture_rectangle
  // extension, you need to use the actual dimensions of the texture.
  // This makes using 2D sprites for games and emulators much easier now
  // that you won't have to convert :)
  //
  // convert the coordinates so that the bottom left corner changes to
  // (0, 0) -> (1, 1) and the top right corner changes from (1, 1) -> (0, 0)
  // we will use this new coordinate system to calculate the location of the sprite
  // in the world coordinates to do the rotation and scaling. This mapping is done in
  // order to make implementation simpler in this class and let the caller keep using
  // the standard OpenGL coordinates system (bottom left corner at (0, 0))
  // =================================================================
  glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(-pivotX * image->GetWidth(), -pivotY * image->GetHeight());
    
    glTexCoord2i(0, image->GetHeight());
    glVertex2i(-pivotX * image->GetWidth(), (1 - pivotY) * image->GetHeight());

    glTexCoord2i(image->GetWidth(), image->GetHeight());
    glVertex2i( (1 - pivotX) * image->GetWidth(), (1 - pivotY) * image->GetHeight());

    glTexCoord2i(image->GetWidth(), 0);
    glVertex2i( (1 - pivotX) * image->GetWidth(), -pivotY * image->GetHeight());
  glEnd();

  glPopMatrix();
}
