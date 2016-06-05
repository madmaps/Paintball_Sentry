#include "visualobjects.h"

visualObjects::visualObjects(QWidget* parent):QGLWidget(parent)
{
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    redColor=Qt::red;
    yellowColor=Qt::yellow;
    greenColor=Qt::green;
    blueColor=Qt::blue;
    motorAngleX=0;
    motorAngleY=0;
    cameraAngleX=49.134;
    cameraAngleY=36.851;
}

visualObjects::~visualObjects()
{
}

void visualObjects::inTargetsToDraw(std::vector<threeDTarget> inTargets)
{
    targetsToDraw=inTargets;
}

void visualObjects::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLineWidth(1);

    float motorXLocation=((((width/2)+((width*motorAngleX)/cameraAngleX))*2)/width)-1;
    float motorYLocation=((((height/2)+((height*motorAngleY)/cameraAngleY))*2)/height)-1;
    qglColor(blueColor);
    glBegin(GL_LINES);
        glVertex3f(motorXLocation+.1,motorYLocation+.1,-2);
        glVertex3f(motorXLocation+.1,motorYLocation-.1,-2);

        glVertex3f(motorXLocation+.1,motorYLocation-.1,-2);
        glVertex3f(motorXLocation-.1,motorYLocation-.1,-2);

        glVertex3f(motorXLocation-.1,motorYLocation-.1,-2);
        glVertex3f(motorXLocation-.1,motorYLocation+.1,-2);

        glVertex3f(motorXLocation-.1,motorYLocation+.1,-2);
        glVertex3f(motorXLocation+.1,motorYLocation+.1,-2);



       // glVertex3f(motorXLocation-1,motorYLocation-1,-25);
        //glVertex3f(motorXLocation-1,motorYLocation+1,-25);
       // glVertex3f(.5,.5,-1);//,-20);
       // glVertex3f(.5,-.5,-1);//,-20);
       //glVertex2f(.6,.6);
       //glVertex2f(.6,.4);
    glEnd();


    //glTranslatef(0.0,0.0,-10.0);
    std::vector<threeDTarget>::iterator count=targetsToDraw.begin();
    while(count!=targetsToDraw.end())
    {

        if(count==targetsToDraw.begin())
        {
            qglColor(redColor);
        }
        else
        {
            qglColor(yellowColor);
        }
        glTranslatef(count->getLocationX(),count->getLocationY(),count->getLocationZ());
        glBegin(GL_LINES);
            glVertex3f(1,-1,0);
            glVertex3f(1,1,0);

            glVertex3f(1,1,0);
            glVertex3f(-1,1,0);

            glVertex3f(-1,1,0);
            glVertex3f(-1,-1,0);

            glVertex3f(-1,-1,0);
            glVertex3f(1,-1,0);

            glVertex3f(1,-1,0);
            glVertex3f(1,-1,-2);

            glVertex3f(1,-1,-2);
            glVertex3f(-1,-1,-2);

            glVertex3f(-1,-1,-2);
            glVertex3f(-1,-1,0);

            glVertex3f(-1,1,0);
            glVertex3f(-1,1,-2);

            glVertex3f(-1,1,-2);
            glVertex3f(-1,-1,-2);

            glVertex3f(1,1,0);
            glVertex3f(1,1,-2);

            glVertex3f(1,1,-2);
            glVertex3f(1,-1,-2);

            glVertex3f(1,1,-2);
            glVertex3f(-1,1,-2);
            qglColor(greenColor);
            glVertex3f(0,0,0);
            glVertex3f(count->getDirectionX(),count->getDirectionY(),count->getDirectionZ());








        glEnd();
        glTranslatef(-count->getLocationX(),-count->getLocationY(),-count->getLocationZ());
        count++;

    }
}


void visualObjects::initializeGL()
{

    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void visualObjects::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(w)/h;
    glFrustum(-x,+x,-1.0,+1.0,1,30.0);
    //glFrustum(-1,1,-1,1,1,30);
    glMatrixMode(GL_MODELVIEW);
    width=w;
    height=h;
}

void visualObjects::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void visualObjects::inMotorAngleXY(double inMotorX,double inMotorY)
{
    motorAngleX=inMotorX;
    motorAngleY=inMotorY;
}

