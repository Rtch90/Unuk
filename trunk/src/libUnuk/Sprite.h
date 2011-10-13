#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <GL/glut.h>
#include <string>
#include "ImageLoader.h"

using namespace std;

class ImageLoader;

class Sprite {
public:
  static void Enable2D(void);
 
  static void Disable2D(void);

  Sprite(string filename);
  virtual ~Sprite(void);

  virtual void Render(void);
  virtual void Rotate(GLint degrees) { angle += degrees; }
  
  // Mutators.
  GLint GetAngle(void) const { return angle; }
  void SetAngle(GLint angle) { this->angle = angle; }
  void SetX(GLdouble x) { this->x = x; }
  void SetY(GLdouble y) { this->y = y; }
  GLint GetHeight(void) const { return image->GetHeight() * scaleY; }
  GLint GetWidth(void)  const { return image->GetWidth()  * scaleX; }

  void SetPivot(GLfloat pivotX, GLfloat pivotY);
  GLfloat GetPivotX(void) const { return pivotX; }
  GLfloat GetPivotY(void) const { return pivotY; }

  GLdouble GetX(void) const { return x; }
  GLdouble GetY(void) const { return y; }

  void SetPivot(const Sprite &obj);


  // =================================================================
  // Set the scale of the object. A scale of (1.0,1.0) means the sprite
  // maintains its original size. Values larger than 1 scales the sprite
  // up while values less than 1 shrink it down.
  // =================================================================
  void SetScale(GLfloat x, GLfloat y) { scaleX = x, scaleY = y; }

private:
  ImageLoader	*image;
  GLuint 	textureID;
  GLint		angle;
  GLdouble	x;
  GLdouble 	y;
  GLfloat	pivotX;
  GLfloat	pivotY;
  GLfloat	scaleX;
  GLfloat	scaleY;

  void InitScene(void);

  bool IsExtensionSupported(const char *extension) const;
};

#endif
