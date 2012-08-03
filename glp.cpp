#include "glp.h"

GLPWindow::GLPWindow(std::string t, int w, int h):width(w), height(h),title(t),
            needsRedraw(false),bRunning(true),destroyed(false),
            initDone(false){

}

GLPWindow::~GLPWindow(){
    if (!destroyed){
        destroy();
    }
}

void GLPWindow::initGL(){
    float aspectRatio = double(width)/height;
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);    /* pedantic, GL_LESS is the default */
    glClearDepth(1.0);       /* pedantic, 1.0 is the default */

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,aspectRatio,1,10.0);

    glMatrixMode(GL_MODELVIEW);
}

void GLPWindow::render(){
    glLoadIdentity();

    gluLookAt(7,2,5,0,0,0,0,1,0);
    static GLuint displayList = 0;

    if (!displayList){
        displayList = glGenLists(1);
        glNewList(displayList, GL_COMPILE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* front face */
        glBegin(GL_QUADS);
            glColor3f(0.0, 0.7, 0.1);  /* green */
            glVertex3f(-1.0, 1.0, 1.0);
            glVertex3f(1.0, 1.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);

            /* back face */
            glColor3f(0.9, 1.0, 0.0);  /* yellow */
            glVertex3f(-1.0, 1.0, -1.0);
            glVertex3f(1.0, 1.0, -1.0);
            glVertex3f(1.0, -1.0, -1.0);
            glVertex3f(-1.0, -1.0, -1.0);

            /* top side face */
            glColor3f(0.2, 0.2, 1.0);  /* blue */
            glVertex3f(-1.0, 1.0, 1.0);
            glVertex3f(1.0, 1.0, 1.0);
            glVertex3f(1.0, 1.0, -1.0);
            glVertex3f(-1.0, 1.0, -1.0);

            /* bottom side face */
            glColor3f(0.7, 0.0, 0.1);  /* red */
            glVertex3f(-1.0, -1.0, 1.0);
            glVertex3f(1.0, -1.0, 1.0);
            glVertex3f(1.0, -1.0, -1.0);
            glVertex3f(-1.0, -1.0, -1.0);
        glEnd();
        glEndList();
    }
    glCallList(displayList);
}
    
    
void GLPWindow::resized(int, int){
    
}

bool GLPWindow::running(){
    return bRunning;
}
bool GLPWindow::invalid(){
    return needsRedraw;
}