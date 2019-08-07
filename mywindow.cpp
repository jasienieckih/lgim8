// We include the header file of MyWindow class - main widget (window) of our application
#include "mywindow.h"

// Include the header file containing definitions GUI
// This file is automatically generated when you build the project
// It is based on data from an XML file "mywindow.ui"
#include "ui_mywindow.h"

#include "matrix.h"

// The definition of the constructor of MyWindow class
// First call the constructor of the parent class,
// next create object representing the GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    // Function creating GUI elements (defined in "ui_mywindow.h")
    ui->setupUi(this);

    // Get the dimensions and coordinates of the top left corner of the frame
    // and set the corresponding parameters of the image
    // Note: we use 'drawFrame' only for handy setting these values,
    // the image will be displayed directly on the main application window.
    img_width = ui->drawFrame->width();
    img_height = ui->drawFrame->height();
    img_x0 = ui->drawFrame->x();
    img_y0 = ui->drawFrame->y();

    // Create an object of QImage class of appropriate width
    // and height. Set its format for 32-bit RGB (0xffRRGGBB).
    img = new QImage(img_width,img_height,QImage::Format_RGB32);


    points.emplace_back(Point( 0.000000000, -0.612372436,  0.000000000 ));
    points.emplace_back(Point( 0.000000000,  0.306186218,  0.530330056 ));
    points.emplace_back(Point( 0.459279327,  0.306186218, -0.2651650430));
    points.emplace_back(Point(-0.459279327,  0.306186218, -0.2651650430));

    polygons.emplace_back(Polygon(&points[0], &points[1], &points[2]));
    polygons.emplace_back(Polygon(&points[0], &points[1], &points[3]));
    polygons.emplace_back(Polygon(&points[0], &points[2], &points[3]));
    polygons.emplace_back(Polygon(&points[1], &points[2], &points[3]));

    updateProjection();
}

// Definition of destructor
MyWindow::~MyWindow()
{
    delete ui;
}

bool MyWindow::areCoordsValid(int x, int y)
{
    return x >= 0 and x < img_width and y >= 0 and y < img_height;
}

void MyWindow::drawLine(Point p0, Point p1)
{
    drawLine(p0.x(), p0.y(), p1.x(), p1.y());
}

void MyWindow::drawLine(int x0, int y0, int x1, int y1)
{
    const uchar color[3] = {0x80, 0x80, 0x80};

    uchar *ptr;
    ptr = img->bits();

    int x;
    int y;
    int pixel;

    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);

    if (dx > dy)
    {
        if (x0 == x1)
        {
            for (y = y0; y <= y1; ++y)
            {
                x = x0;
                if (areCoordsValid(x, y))
                {
                    pixel = img_width * 4 * y + 4 * x;
                    for (int component = 0; component < 3; ++component)
                    {
                        ptr[pixel + component] = color[component];
                    }
                }
            }
        }
        else
        {
            if (x0 > x1)
            {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            double a = double(y1 - y0)/double(x1 - x0);
            double b = y0 - a * x0;

            for (x = x0; x <= x1; ++x)
            {
                y = int(round(a * x + b));
                if (areCoordsValid(x, y))
                {
                    pixel = img_width * 4 * y + 4 * x;
                    for (int component = 0; component < 3; ++component)
                    {
                        ptr[pixel + component] = color[component];
                    }
                }
            }
        }
    }
    else
    {
        if (y0 == y1)
        {
            for (x = x0; x <= x1; ++x)
            {
                y = y0;
                if (areCoordsValid(x, y))
                {
                    pixel = img_width * 4 * x + 4 * y;
                    for (int component = 0; component < 3; ++component)
                    {
                        ptr[pixel + component] = color[component];
                    }
                }
            }
        }
        else
        {
            if (y0 > y1)
            {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            double a = double(x1 - x0)/double(y1 - y0);
            double b = x0 - a * y0;

            for (y = y0; y <= y1; ++y)
            {
                x = int(round(a * y + b));
                if (areCoordsValid(x, y))
                {
                    pixel = img_width * 4 * y + 4 * x;
                    for (int component = 0; component < 3; ++component)
                    {
                        ptr[pixel + component] = color[component];
                    }
                }
            }
        }
    }
}

void MyWindow::drawTriangle(Point a, Point b, Point c)
{
    drawLine(a, b);
    drawLine(b, c);
    drawLine(c, a);
}

void MyWindow::updateProjection()
{
    img_clean();

    Matrix projectionMatrix;
    projectionMatrix = projectionMatrix * 300;
    projectionMatrix.set(0, 3, 300.0);
    projectionMatrix.set(1, 3, 300.0);
    projectionMatrix.set(2, 3, 300.0);

    double distance = 5.0;

    Matrix finalMatrix;
    finalMatrix = finalMatrix * translationMatrix;
    finalMatrix = finalMatrix * rotationMatrixXAxis;
    finalMatrix = finalMatrix * rotationMatrixYAxis;
    finalMatrix = finalMatrix * shearingXMatrix;
    finalMatrix = finalMatrix * shearingYMatrix;
    finalMatrix = finalMatrix * shearingZMatrix;
    finalMatrix = finalMatrix * scalingMatrix;

    for (auto polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        Point points[3];
        for (int i = 0; i < 3; ++i)
        {
            points[i] = polygon->point(i);
            points[i] = finalMatrix * points[i];
            points[i].setX(points[i].x() * (distance / (points[i].z() + distance)));
            points[i].setY(points[i].y() * (distance / (points[i].z() + distance)));
            points[i] = projectionMatrix * points[i];
        }
        drawTriangle(points[0], points[1], points[2]);
    }

    update();
}

// Function (slot) called when user push the button 'Quit' (ExitButton)
// Note: The connection of this function with the signal "clicked"
// emitted by the button is created by using the built QMetaObject :: connectSlotsByName (MyWindow)
// located in the automatically generated file "ui_mywindow.h"
// so we do not need create connection manually using 'connect' function.
void MyWindow::on_exitButton_clicked()
{
    // qApp is a global pointer referring to the unique application object,
    // in GUI applications, it is a pointer to a QApplication instance.
    // quit() is a function telling the application to exit with return code 0 (success).
    qApp->quit();
}


// A paint event is a request to repaint all or part of a widget. It can happen for one of the following reasons:
// repaint() or update() was invoked, the widget was obscured and has now been uncovered, or many other reasons.
void MyWindow::paintEvent(QPaintEvent*)
{

    // The QPainter class performs low-level painting on widgets and other paint devices.
    QPainter p(this);

    // Draws an image 'img' by copying it into the paint device.
    // (img_x0, img_y0) specifies the top-left point in the paint device that is to be drawn onto.
    p.drawImage(img_x0,img_y0,*img);
}


// Function (slot) called when the user clicks button "Clean" (cleanButton)
void MyWindow::on_cleanButton_clicked()
{
    // Function 'img_clean()' cleans the image (create all white image)
    // definition is provided below
    img_clean();

    // Invoke the 'paintEvent' and repaint the entire widget
    update();
}

// Function (slot) called when the user clicks button "Draw 1" (draw1Button)
void MyWindow::on_draw1Button_clicked()
{
    update();
}

// Function (slot) called when the user clicks button "Draw 2" (draw2Button)
void MyWindow::on_draw2Button_clicked()
{
    update();
}

// Function cleaning the image (painting it in all white)
void MyWindow::img_clean()
{
    unsigned char *ptr;

    // 'bits()' returns a pointer to the first pixel of the image
    ptr = img->bits();

    int i,j;

    // i - current row, it changes from 0 to img_height-1
    for(i=0; i<img_height; i++)
    {
        // j - current column, it changes from 0 to img_width
        // each row has img_width pixels and 4 * img_width bytes (1 pixel = 4 bytes)
        for(j=0; j<img_width; j++)
        {
            // to obtain a white color we set each component on max value (255)
            ptr[img_width*4*i + 4*j]=255; // BLUE component
            ptr[img_width*4*i + 4*j + 1] = 255; // GREEN component
            ptr[img_width*4*i + 4*j + 2] = 255; // RED component
        }
    }
}

// Function (slot) called when the user press mouse button
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x -= img_x0;
    y -= img_y0;
}

void MyWindow::on_translationXSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    translationMatrix.set(0, 3, dvalue);
    updateProjection();
}

void MyWindow::on_translationYSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    translationMatrix.set(1, 3, dvalue);
    updateProjection();
}

void MyWindow::on_translationZSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    translationMatrix.set(2, 3, dvalue);
    updateProjection();
}

void MyWindow::on_rotationSlider1_valueChanged(int value)
{
    double angle = value / 1000.0 * 2 * M_PI;
    double sine = sin(angle);
    double cosine = cos(angle);
    rotationMatrixXAxis.set(1, 1, cosine);
    rotationMatrixXAxis.set(1, 2, -sine);
    rotationMatrixXAxis.set(2, 1, sine);
    rotationMatrixXAxis.set(2, 2, cosine);
    updateProjection();
}

void MyWindow::on_rotationSlider2_valueChanged(int value)
{
    double angle = value / 1000.0 * 2 * M_PI;
    double sine = sin(angle);
    double cosine = cos(angle);
    rotationMatrixYAxis.set(0, 0, cosine);
    rotationMatrixYAxis.set(0, 2, sine);
    rotationMatrixYAxis.set(2, 0, -sine);
    rotationMatrixYAxis.set(2, 2, cosine);
    updateProjection();
}

void MyWindow::on_scalingXSlider_valueChanged(int value)
{
    double dvalue = value / 500.0;
    scalingMatrix.set(0, 0, dvalue);
    updateProjection();
}

void MyWindow::on_scalingYSlider_valueChanged(int value)
{
    double dvalue = value / 500.0;
    scalingMatrix.set(1, 1, dvalue);
    updateProjection();
}

void MyWindow::on_scalingZSlider_valueChanged(int value)
{
    double dvalue = value / 500.0;
    scalingMatrix.set(2, 2, dvalue);
    updateProjection();
}

void MyWindow::on_shearingXSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    shearingXMatrix.set(0, 1, dvalue);
    shearingXMatrix.set(0, 2, dvalue);
    updateProjection();
}

void MyWindow::on_shearingYSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    shearingYMatrix.set(1, 0, dvalue);
    shearingYMatrix.set(1, 2, dvalue);
    updateProjection();
}

void MyWindow::on_shearingZSlider_valueChanged(int value)
{
    double dvalue = (value - 1000.0) / 500.0;
    shearingZMatrix.set(2, 0, dvalue);
    shearingZMatrix.set(2, 1, dvalue);
    updateProjection();
}

void MyWindow::on_resetButton_clicked()
{
    ui->translationXSlider->setValue(1000);
    ui->translationYSlider->setValue(1000);
    ui->translationZSlider->setValue(1000);
    ui->scalingXSlider->setValue(1000);
    ui->scalingYSlider->setValue(1000);
    ui->scalingZSlider->setValue(1000);
    ui->rotationSlider1->setValue(0);
    ui->rotationSlider2->setValue(0);
    ui->shearingXSlider->setValue(1000);
    ui->shearingYSlider->setValue(1000);
    ui->shearingZSlider->setValue(1000);
    updateProjection();
}
