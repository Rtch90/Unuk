#ifndef _STATIC_H_
#define _STATIC_H_

/*
 * Inheriting from this class will make the class uncopyable.
 * It is useful to do this because a lot of the time we won't
 * want to be able to copy stuff, like the window or the game class.
 *
 * I probably chose a bad name for this.
 *
 */

class Static {
protected:
  Static() {}
  ~Static() {}
private:
  Static(const Static&);
  Static& operator=(const Static &);
};

#endif
