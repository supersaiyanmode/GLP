#include "../glp.h"
#ifdef GLP_LINUX

#include <cstdlib>
#include <iostream>

#include "XVisualInfo_fixed.h"

int GLPWindow::init() {
    XVisualInfo*         vi;
    XVisualInfo_Fixed*   vi_fixed;   
    Colormap             cmap;
    XSetWindowAttributes swa;
    GLXContext           cx;
    int                  dummy;
    int                  argc = 1;
    static char          *tempStr = "temp";
    static char**        argv = &tempStr;
    int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};
    int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
    
    wd.dpy = XOpenDisplay(NULL);
    if (wd.dpy == NULL){
        error = "Could not open display";
        return 1;
    }
    if(!glXQueryExtension(wd.dpy, &dummy, &dummy)){
        error = "X server has no OpenGL GLX extension";
        return 2;
    }

    vi = glXChooseVisual(wd.dpy, DefaultScreen(wd.dpy), dblBuf);
    vi_fixed = (XVisualInfo_Fixed*)vi;
    if (vi == NULL){
        vi = glXChooseVisual(wd.dpy, DefaultScreen(wd.dpy), snglBuf);
        if (vi == NULL){
            error = "no RGB visual with depth buffer";
            return 3;
        }
        wd.isDoubleBuffered = false;
    }
    
    if(vi_fixed->class_ != TrueColor){
        error = "TrueColor visual required for this program";
        return 4;
    }
    
    cx = glXCreateContext(wd.dpy, vi, /* no shared dlists */ None,
                        /* direct rendering if possible */GL_TRUE);
    if (cx == NULL){
        error = "could not create rendering context";
        return 5;
    }
    
    cmap = XCreateColormap(wd.dpy, RootWindow(wd.dpy, vi->screen), vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = KeyPressMask    | ExposureMask
                    | ButtonPressMask | StructureNotifyMask;
    wd.win = XCreateWindow(wd.dpy, RootWindow(wd.dpy, vi->screen), 0, 0,
                        width, height, 0, vi->depth, InputOutput, vi->visual,
                        CWBorderPixel | CWColormap | CWEventMask, &swa);
    XSetStandardProperties(wd.dpy, wd.win, title.c_str(), "GLPWindow", None,
                            argv, argc, NULL);
    
    glXMakeCurrent(wd.dpy, wd.win, cx);

    /*** (7) request the X window to be displayed on the screen ***/

    XMapWindow(wd.dpy, wd.win);
    
    initDone = true;
    
    initGL();
    
    return 0;
}

void GLPWindow::swapBuffers(){
    glXSwapBuffers(wd.dpy, wd.win);
}

void GLPWindow::processEvents(){
    XEvent event;
    while (XPending(wd.dpy)>0){
        XNextEvent(wd.dpy, &event);

        switch (event.type){
            case KeyPress: {
                KeySym     keysym;
                XKeyEvent *kevent;
                char       buffer[1];
                /* It is necessary to convert the keycode to a
                * keysym before checking if it is an escape */
                kevent = (XKeyEvent *) &event;
                if ((XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) == 1)
                    && (keysym == (KeySym)XK_Escape))
                        exit(0);
                break;
            }
            case KeyRelease: {
                
            }
            case ButtonPress: {
                switch (event.xbutton.button){
                    case 1:break;
                    case 2:break;
                    case 3:break;
                }
                break;
            }
            case ConfigureNotify: {
                width = event.xconfigure.width;
                height = event.xconfigure.height;
                glViewport(0, 0, event.xconfigure.width,
                        event.xconfigure.height);
                //fall through..
            }
            case Expose:
                needsRedraw = true;
                break;
        }
    }
}

void GLPWindow::sleep(unsigned int t){
    usleep(t%1000000);
}

void GLPWindow::destroy(){
    XDestroyWindow(wd.dpy,wd.win);
    destroyed = true;
}

GLPWindow& GLPWindow::setTitle(std::string t){
    title = t;
    if (initDone)
        XStoreName(wd.dpy, wd.win, title.c_str());
    return *this;
}
GLPWindow& GLPWindow::setSize(int w, int h){
    width = w;
    height = h;
    if (initDone){
        XResizeWindow(wd.dpy, wd.win, w, h);
        resized(w,h);
    }
    return *this;
}
    
#endif //#ifdef GLP_LINUX