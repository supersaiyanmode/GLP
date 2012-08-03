#ifndef GLP_LINUX_H
#define GLP_LINUX_H


#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>

#include <X11/X.h>    /* X11 constant (e.g. TrueColor) */
#include <X11/keysym.h>


struct GLPWindowData {
    Display     *dpy;
    Window      win;
    bool        isDoubleBuffered;
};

#endif