// We include the header file of MyWindow class - main widget (window) of our application
#include "mywindow.h"

// Include the header file containing definitions GUI
// This file is automatically generated when you build the project
// It is based on data from an XML file "mywindow.ui"
#include "ui_mywindow.h"

// The definition of the constructor of MyWindow class
// First call the constructor of the parent class,
// next create object representing the GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow),
    outputImage(600, 600, QImage::Format::Format_RGB32),
    sourceImage(":res/keskesej4_600x600.jpg"),
    outputImage_x0(730),
    outputImage_y0(10),
    isDragging(false),
    hidingMode(true)
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

    for (int i = 0; i < 2; ++i)
    {
        points[i][0] = Point(200, 100);
        points[i][1] = Point(100, 500);
        points[i][2] = Point(500, 400);
        points[i][3] = Point(400, 100);
        triangles[i][0] = new TrianglePtr(&points[i][0], &points[i][1], &points[i][2]);
        triangles[i][1] = new TrianglePtr(&points[i][0], &points[i][2], &points[i][3]);
    }

    updateTexturing();
}

// Definition of destructor
MyWindow::~MyWindow()
{
    delete ui;
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
    p.drawImage(outputImage_x0, outputImage_y0, outputImage);
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
    for (int h = 0; h < 2; ++h)
    {
        unsigned char *ptr;

        // 'bits()' returns a pointer to the first pixel of the image
        ptr = (h == 0) ? img->bits() : outputImage.bits();

        int i, j;

        // i - current row, it changes from 0 to img_height-1
        for(i = 0; i < img_height; i++)
        {
            // j - current column, it changes from 0 to img_width
            // each row has img_width pixels and 4 * img_width bytes (1 pixel = 4 bytes)
            for(j=0; j < img_width; j++)
            {
                // to obtain a white color we set each component on max value (255)
                ptr[img_width*4*i + 4*j] = 0xff; // BLUE component
                ptr[img_width*4*i + 4*j + 1] = 0xff; // GREEN component
                ptr[img_width*4*i + 4*j + 2] = 0xff; // RED component
            }
        }
    }
}

bool MyWindow::areCoordsValid(int x, int y)
{
    return x >= 0 and x < img_width and y >= 0 and y < img_height;
}

int MyWindow::bitsCoordFromXy(int x, int y)
{
    return 4 * (img_width * y + x);
}

int MyWindow::bitsCoordFromXy(int x, int y, int width)
{
    return 4 * (width * y + x);
}

void MyWindow::drawOriginalImage()
{
    uchar *bits = img->bits();
    uchar *sourceBits = sourceImage.bits();
    for (int x = 0; x < img_width; ++x)
    {
        for (int y = 0; y < img_height; ++y)
        {
            int coords = bitsCoordFromXy(x, y);
            for (int component = 0; component < 3; ++component)
            {
                bits[coords + component] = sourceBits[coords + component];
            }
        }
    }
}

void MyWindow::updateOutputTriangle(int index)
{
    Point oa = triangles[1][index]->point(0);
    Point ob = triangles[1][index]->point(1);
    Point oc = triangles[1][index]->point(2);

    Point ia = triangles[0][index]->point(0);
    Point ib = triangles[0][index]->point(1);
    Point ic = triangles[0][index]->point(2);

    uchar* inputBits = sourceImage.bits();
    uchar* outputBits = outputImage.bits();

    for (int x = 0; x < img_width; ++x)
    {
        for (int y = 0; y < img_height; ++y)
        {
            // calculating input coordinates to source from through barycentrics
            double coeffs[3][2];
            for (int i = 0; i < 2; ++i)
            {
                double ai = oa.coord(i);
                coeffs[0][i] = (i == 0 ? x : y) - ai;
                coeffs[1][i] = oc.coord(i) - ai;
                coeffs[2][i] = ob.coord(i) - ai;
            }
            double denominator = coeffs[2][0] * coeffs[1][1] - coeffs[1][0] * coeffs[2][1];
            double v = (coeffs[0][0] * coeffs[1][1] - coeffs[1][0] * coeffs[0][1]) / denominator;
            double w = (coeffs[2][0] * coeffs[0][1] - coeffs[0][0] * coeffs[2][1]) / denominator;
            double u = 1 - v - w;
            if (not hidingMode or not (u < 0.0 or u > 1.0 or v < 0.0 or v > 1.0 or w < 0.0 or w > 1.0))
            {
                Point inputCoords = ia * u + ib * v + ic * w;
                int floorX = floor(inputCoords.x());
                int floorY = floor(inputCoords.y());
                int bitsCoords[2][2];
                bitsCoords[0][0] = bitsCoordFromXy(floorX,     floorY    );
                bitsCoords[0][1] = bitsCoordFromXy(floorX + 1, floorY    );
                bitsCoords[1][0] = bitsCoordFromXy(floorX,     floorY + 1);
                bitsCoords[1][1] = bitsCoordFromXy(floorX + 1, floorY + 1);
                if (        areCoordsValid(inputCoords.x(), inputCoords.y())
                        and areCoordsValid(x,               y              ))
                {
                    // bilinear interpolation of color
                    int outputBitsCoords = bitsCoordFromXy(x, y);
                    for (int component = 0; component < 3; ++component)
                    {
                        double neighbours[2][2];
                        for (int i = 0; i < 2; ++i)
                        {
                            for (int j = 0; j < 2; ++j)
                            {
                                neighbours[i][j] = inputBits[bitsCoords[i][j] + component];
                            }
                        }
                        double interpolated[2];
                        double factor = inputCoords.x() - floor(inputCoords.x());
                        for (int i = 0; i < 2; ++i)
                        {
                            interpolated[i] = (1 - factor) * neighbours[i][0] + factor * neighbours[i][1];
                        }
                        factor = inputCoords.y() - floor(inputCoords.y());
                        double finalInterpolated = (1 - factor) * interpolated[0] + factor * interpolated[1];
                        outputBits[outputBitsCoords + component] = round(finalInterpolated);
                    }
                }
            }
        }
    }
}

void MyWindow::updateOutputImage()
{
    for (int i = 0; i < NUMBER_OF_TRIANGLES; ++i)
    {
        updateOutputTriangle(i);
    }
}

void MyWindow::drawLine(QImage& image, Point p0, Point p1)
{
    drawLine(image, p0.x(), p0.y(), p1.x(), p1.y());
}

void MyWindow::drawLine(QImage& image, int x0, int y0, int x1, int y1)
{
    const uchar color[3] = {0x80, 0x80, 0x80};

    uchar *ptr;
    ptr = image.bits();

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
                pixel = img_width * 4 * y + 4 * x;
                for (int component = 0; component < 3; ++component)
                {
                    ptr[pixel + component] = color[component];
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
        if (y0 == y1)
        {
            for (x = x0; x <= x1; ++x)
            {
                y = y0;
                pixel = img_width * 4 * x + 4 * y;
                for (int component = 0; component < 3; ++component)
                {
                    ptr[pixel + component] = color[component];
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
                pixel = img_width * 4 * y + 4 * x;
                for (int component = 0; component < 3; ++component)
                {
                    ptr[pixel + component] = color[component];
                }
            }
        }
    }
}

void MyWindow::drawTriangles()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int t = 0; t < NUMBER_OF_TRIANGLES; ++t)
        {
            QImage& image = (i == 0) ? *img : outputImage;
            TrianglePtr& triangle = *triangles[i][t];
            drawLine(image, triangle.point(0), triangle.point(1));
            drawLine(image, triangle.point(1), triangle.point(2));
            drawLine(image, triangle.point(2), triangle.point(0));
        }
    }
}

void MyWindow::drawTriangleHandles()
{
    const uchar HANDLE_COLORS[2][3][3] = {{{0x10, 0xc8, 0x10},
                                           {0x10, 0xc8, 0x10},
                                           {0x10, 0xc8, 0x10}},
                                          {{0x10, 0xc8, 0x10},
                                           {0x10, 0xc8, 0x10},
                                           {0x10, 0xc8, 0x10}}};

    uchar* bits[2];
    bits[0] = img->bits();
    bits[1] = outputImage.bits();

    for (int image = 0; image < 2; ++image)
    {
        for (int triangle = 0; triangle < NUMBER_OF_TRIANGLES; ++triangle)
        {
            for (int point = 0; point < 3; ++point)
            {
                for (int x = triangles[image][triangle]->point(point).x() - HANDLE_RADIUS;
                     x < triangles[image][triangle]->point(point).x() + HANDLE_RADIUS; ++x)
                {
                    for (int y = triangles[image][triangle]->point(point).y() - HANDLE_RADIUS;
                         y < triangles[image][triangle]->point(point).y() + HANDLE_RADIUS; ++y)
                    {
                        if (areCoordsValid(x, y))
                        {
                            int coords = bitsCoordFromXy(x, y);
                            for (int component = 0; component < 3; ++component)
                            {
                                bits[image][coords + component] = HANDLE_COLORS[image][point][component];
                            }
                        }
                    }
                }
            }
        }
    }
}

void MyWindow::updateTexturing()
{
    img_clean();

    drawOriginalImage();
    updateOutputImage();
    drawTriangles();
    drawTriangleHandles();

    update();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int image_index = (x < 672) ? 0 : 1;
    if (image_index == 0)
    {
        x -= img_x0;
        y -= img_y0;
    }
    else
    {
        x -= outputImage_x0;
        y -= outputImage_y0;
    }

    for (int point = 0; point < NUMBER_OF_POINTS; ++point)
    {
        Point delta = points[image_index][point] - Point(x, y);
        delta = delta.getAbsolute();
        if (delta.x() <= HANDLE_RADIUS and delta.y() <= HANDLE_RADIUS)
        {
            whichPointDragged = point;
            isDragging = true;
            break;
        }
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int image_index = (x < 672) ? 0 : 1;
    if (image_index == 0)
    {
        x -= img_x0;
        y -= img_y0;
    }
    else
    {
        x -= outputImage_x0;
        y -= outputImage_y0;
    }

    if (isDragging)
    {
        isDragging = false;
        points[image_index][whichPointDragged].set(x, y);
        updateTexturing();
    }
}

void MyWindow::on_hideCheckBox_toggled(bool checked)
{
    hidingMode = checked;
    updateTexturing();
}
