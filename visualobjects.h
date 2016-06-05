#ifndef VISUALOBJECTS_H
#define VISUALOBJECTS_H
#include <QGLWidget>
#include <vector>
#include "MotionTrack/threeDTarget.h"
#include <iostream>

class visualObjects : public QGLWidget
{
    Q_OBJECT

public:
    visualObjects(QWidget* parent=0);
    virtual ~visualObjects();
    void inTargetsToDraw(std::vector<threeDTarget> inTargets);
    void inMotorAngleXY(double inMotorX,double inMotorY);

public slots:
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    void draw();
    std::vector<threeDTarget> targetsToDraw;
    QColor redColor;
    QColor yellowColor;
    QColor greenColor;
    QColor blueColor;
    double motorAngleX;
    double motorAngleY;
    int width;
    int height;
    double cameraAngleX;
    double cameraAngleY;
};

#endif // VISUALOBJECTS_H
