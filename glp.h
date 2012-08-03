#ifndef GLP_FW
#define GLP_FW

#include <string>
#include <vector>

#include <GL/gl.h>
#ifndef GLP_EXCLUDE_GLU
#  include <GL/glu.h>
#endif

#if defined(_WIN32)
#  define GLP_WINDOWS
#  include "windows/glp_windows.h"
#endif
#if defined (__linux) || defined(__linux__)
#  define GLP_LINUX
#  include "linux/glp_linux.h"
#endif

class GLPWindow{
    GLPWindowData wd;
    int width, height;
    std::string title;
    std::string error;
    bool needsRedraw;
    bool bRunning;      //still running?
    bool destroyed;
    bool initDone;
public:
    GLPWindow(std::string, int, int);
    virtual ~GLPWindow();
    
    int init();
    void destroy();
    
    void resized(int, int);
    
    bool invalid();
    bool running();
    
    GLPWindow& setTitle(std::string);
    GLPWindow& setSize(int, int);
    
    
    virtual void initGL();
    virtual void render();
    void swapBuffers();
    void processEvents();
    
    static void sleep(unsigned int);
};

#endif //not defined GLP_H