#include "mainwindow.h"
#include "ui_mainwindow.h"

void imageCleanup(void* inData);
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow),behindThread(new Thread),theSettings(new Settings),autoCalibrate(new calibrate)
{
    ui->setupUi(this);
    qRegisterMetaType<threeDTargetArray>("threeDTargetArray");

    connect(this,SIGNAL(changePixelCuttoff(int)),behindThread,SLOT(setPixelCuttoff(int)));
    connect(this,SIGNAL(changeUnitCuttoff(int)),behindThread,SLOT(setUnitCuttoff(int)));
    connect(behindThread,SIGNAL(setViewImage(frame*,frame*)),this,SLOT(setViewImage(frame*,frame*)));
    connect(behindThread,SIGNAL(setDebugImage(frame*,frame*)),this,SLOT(setDebugImage(frame*,frame*)));
    connect(behindThread,SIGNAL(setCameraMovement(double,double)),this,SLOT(setCameraMovement(double,double)));
    connect(this,SIGNAL(setDebugMode(const bool&)),behindThread,SLOT(setDebugMode(const bool&)));
    connect(behindThread,SIGNAL(changeText(QString,QString,QString,QString)),this,SLOT(changeText(QString,QString,QString,QString)));
    connect(behindThread,SIGNAL(sendTargets(threeDTargetArray)),this,SLOT(sendTargetsToUI(threeDTargetArray)));
    connect(this,SIGNAL(changeColorAcc(int)),behindThread,SLOT(colorAccChange(int)));
    connect(this,SIGNAL(changeSizeAcc(int)),behindThread,SLOT(sizeAccChange(int)));
    connect(this,SIGNAL(changeYAcc(int)),behindThread,SLOT(yAccChange(int)));
    connect(this,SIGNAL(changeKeyFrameUpdate(bool)),behindThread,SLOT(changeKeyFrameUpdate(bool)));
    connect(this,SIGNAL(changeCamera0Reset(double)),behindThread,SLOT(setCamera0Reset(double)));
    connect(this,SIGNAL(changeCamera1Reset(double)),behindThread,SLOT(setCamera1Reset(double)));
    connect(theSettings,SIGNAL(yShiftChanged(int)),behindThread,SLOT(yShiftChanged(int)));
    connect(theSettings,SIGNAL(xShiftChanged(int)),behindThread,SLOT(xShiftChanged(int)));
    connect(theSettings,SIGNAL(xCalibrationChanged(int)),behindThread,SLOT(xCalibrationChanged(int)));
    connect(theSettings,SIGNAL(xCameraAngleChanged(int)),behindThread,SLOT(xCameraAngleChanged(int)));
    connect(theSettings,SIGNAL(yCalibrationChanged(int)),behindThread,SLOT(yCalibrationChanged(int)));
    connect(theSettings,SIGNAL(yCameraAngleChanged(int)),behindThread,SLOT(yCameraAngleChanged(int)));
    connect(autoCalibrate,SIGNAL(setTarget0Calibration(double)),behindThread,SLOT(setTarget0Calibration(double)));
    connect(autoCalibrate,SIGNAL(setTarget1Calibration(double)),behindThread,SLOT(setTarget1Calibration(double)));
    connect(autoCalibrate,SIGNAL(startCalibration()),behindThread,SLOT(startCalibration()));
    connect(behindThread,SIGNAL(sendDatabaseSize(int)),this,SLOT(setDatabaseSize(int)));
    connect(behindThread,SIGNAL(sendMotorXY(double,double)),this,SLOT(setMotorAngleXY(double,double)));
    connect(this,SIGNAL(changeTimeBuffer(int)),behindThread,SLOT(changeTimeBuffer(int)));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    if(behindThread->isRunning())
    {
        ui->pushButton->setText(tr("Start"));
        behindThread->stop();
    }
    else
    {
        ui->pushButton->setText(tr("Stop"));
        behindThread->start();
    }

}

void MainWindow::sendTargetsToUI(threeDTargetArray inTargets)
{
    ui->targetList->clear();
    threeDTargetArray::iterator counter = inTargets.begin();
    while(counter!=inTargets.end())
    {
        QString tempString;
        tempString+="X:";
        tempString+=QString::number(counter->getLocationX(),'f',2);
        tempString+="  Y:";
        tempString+=QString::number(counter->getLocationY(),'f',2);
        tempString+="  Z:";
        tempString+=QString::number(counter->getLocationZ(),'f',2);
        ui->targetList->addItem(tempString);
        counter++;
    }
    ui->widget->inTargetsToDraw(inTargets);
}

void MainWindow::changeText(QString inSpeed,QString inLocX,QString inLocY,QString inLocZ)
{
    ui->speedOutput->setText(inSpeed);
    ui->locXOutput->setText(inLocX);
    ui->locYOutput->setText(inLocY);
    ui->locZOutput->setText(inLocZ);
}



void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->checkState()==Qt::Unchecked)
    {
        setDebugMode(0);
    }
    else
    {
        setDebugMode(1);
    }
}

void MainWindow::setDebugImage(frame* inFrame,frame* inFrame2)
{
    if(ui->checkBox->checkState()==Qt::Checked && inFrame!=0 && inFrame2!=0)
    {
        //QImage* tempImage=new QImage(inFrame->getData(),inFrame->getWidth(),inFrame->getHeight(),1920,QImage::Format_RGB888,imageCleanup,inFrame->getData());
        QImage* tempImage=new QImage(inFrame->getData(),inFrame->getWidth(),inFrame->getHeight(),inFrame->getWidth()*3,QImage::Format_RGB888,imageCleanup,inFrame->getData());

        QImage* scaledImage=new QImage(tempImage->scaled(320,240));
        inFrame->releaseData();
        delete inFrame;
        QPixmap debugPixmap = QPixmap::fromImage(*scaledImage);
        ui->DebugWIndow->setPixmap(debugPixmap);
        delete tempImage;
        delete scaledImage;

        //QImage* tempImage2=new QImage(inFrame2->getData(),inFrame2->getWidth(),inFrame2->getHeight(),1920,QImage::Format_RGB888,imageCleanup,inFrame2->getData());
        QImage* tempImage2=new QImage(inFrame2->getData(),inFrame2->getWidth(),inFrame2->getHeight(),inFrame2->getWidth()*3,QImage::Format_RGB888,imageCleanup,inFrame2->getData());

        QImage* scaledImage2=new QImage(tempImage2->scaled(320,240));
        inFrame2->releaseData();
        delete inFrame2;
        QPixmap debugPixmap2 = QPixmap::fromImage(*scaledImage2);
        ui->DebugWIndow_2->setPixmap(debugPixmap2);
        delete tempImage2;
        delete scaledImage2;

    }
}

void MainWindow::setViewImage(frame* inFrame,frame* inFrame2)
{
    if(inFrame!=0 && inFrame2!=0)
    {
        //QImage* tempImage=new QImage(inFrame->getData(),inFrame->getWidth(),inFrame->getHeight(),1920,QImage::Format_RGB888,imageCleanup,inFrame->getData());
        QImage* tempImage=new QImage(inFrame->getData(),inFrame->getWidth(),inFrame->getHeight(),inFrame->getWidth()*3,QImage::Format_RGB888,imageCleanup,inFrame->getData());

        QImage* scaledImage=new QImage(tempImage->scaled(320,240));
        *scaledImage=scaledImage->rgbSwapped();
        inFrame->releaseData();
        delete inFrame;
        QPixmap debugPixmap = QPixmap::fromImage(*scaledImage);
        ui->ViewWindow_0->setPixmap(debugPixmap);
        delete tempImage;
        delete scaledImage;

        //QImage* tempImage2=new QImage(inFrame2->getData(),inFrame2->getWidth(),inFrame2->getHeight(),1920,QImage::Format_RGB888,imageCleanup,inFrame2->getData());
        QImage* tempImage2=new QImage(inFrame2->getData(),inFrame2->getWidth(),inFrame2->getHeight(),inFrame2->getWidth()*3,QImage::Format_RGB888,imageCleanup,inFrame2->getData());

        QImage* scaledImage2=new QImage(tempImage2->scaled(320,240));
        *scaledImage2=scaledImage2->rgbSwapped();
        inFrame2->releaseData();
        delete inFrame2;
        QPixmap debugPixmap2 = QPixmap::fromImage(*scaledImage2);
        ui->ViewWindow_1->setPixmap(debugPixmap2);
        delete tempImage2;
        delete scaledImage2;

    }
    ui->widget->updateGL();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    changePixelCuttoff(position);
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    changeUnitCuttoff(position);
}

void imageCleanup(void* inData)
{
    unsigned char* theData=static_cast<unsigned char*> (inData);
    delete[] theData;
}

void MainWindow::setCameraMovement(const double& inCameraMovement0,const double& inCameraMovement1)
{
    int temp0=(int)(inCameraMovement0*10);
    int temp1=(int)(inCameraMovement1*10);
    //std::cout << temp0 << "   ";
    if(temp0>=100)
    {
        temp0=100;
    }
    if(temp1>=100)
    {
        temp1=100;
    }
    ui->frameMovement0->setValue(temp0);
    ui->frameMovement1->setValue(temp1);
}


void MainWindow::on_yAccSlider_valueChanged(int value)
{
    double inValue=(double)(value)/100;
    ui->yAccLabel->setText(QString::number(inValue,'f',2));
    changeYAcc(value);
}

void MainWindow::on_sizeAccSlider_valueChanged(int value)
{
    double inValue=(double)(value)/100;
    ui->sizeAccLabel->setText(QString::number(inValue,'f',2));
    changeSizeAcc(value);
}

void MainWindow::on_colorAccSlider_valueChanged(int value)
{
    double inValue=(double)(value)/100;
    ui->colorAccLabel->setText(QString::number(inValue,'f',2));
    changeColorAcc(value);
}

void MainWindow::on_updateKeyCheckbox_clicked(bool checked)
{
    changeKeyFrameUpdate(checked);
}

void MainWindow::on_camera0ResetSlider_valueChanged(int value)
{
    ui->camera0ResetLabel->setText(QString::number(value));
    changeCamera0Reset(value);
}

void MainWindow::on_camera1ResetSlider_valueChanged(int value)
{
    ui->camera1ResetLabel->setText(QString::number(value));
    changeCamera1Reset(value);
}

void MainWindow::on_settingsButton_clicked()
{
    theSettings->show();
}

void MainWindow::on_autoCalibrateButton_clicked()
{
    autoCalibrate->show();
}

void MainWindow::setDatabaseSize(int inSize)
{
    ui->databaseCount->setText(QString::number(inSize));
}

void MainWindow::setMotorAngleXY(double inMotorX,double inMotorY)
{
    ui->widget->inMotorAngleXY(inMotorX,inMotorY);
}


void MainWindow::on_timeBuffer_valueChanged(int value)
{
    changeTimeBuffer(value);
}
