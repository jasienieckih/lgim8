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
    outputImage(600, 600, QImage::Format::Format_RGB32)
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
        Triangle *t = (i == 0) ? &inputTriangle : &outputTriangle;
        t->setPoint(0, Point(200, 100));
        t->setPoint(1, Point(100, 500));
        t->setPoint(2, Point(500, 400));
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
    p.drawImage(730, 10, outputImage);
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

void MyWindow::updateTexturing()
{
    img_clean();

    const int HANDLE_RADIUS = 3;
    const uchar HANDLE_COLORS[2][3][3] = {{{0xe0, 0x10, 0x10},
                                           {0x10, 0xc8, 0x10},
                                           {0x10, 0x10, 0xe0}},
                                          {{0xe0, 0x10, 0x10},
                                           {0x10, 0xc8, 0x10},
                                           {0x10, 0x10, 0xe0}}};

    uchar* bits[2];
    bits[0] = img->bits();
    bits[1] = outputImage.bits();

    Triangle* triangles[2];
    triangles[0] = &inputTriangle;
    triangles[1] = &outputTriangle;

    for (int image = 0; image < 2; ++image)
    {
        for (int point = 0; point < 3; ++point)
        {
            for (int x = triangles[image]->point(point).x() - HANDLE_RADIUS;
                 x < triangles[image]->point(point).x() + HANDLE_RADIUS; ++x)
            {
                for (int y = triangles[image]->point(point).y() - HANDLE_RADIUS;
                     y < triangles[image]->point(point).y() + HANDLE_RADIUS; ++y)
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

    update();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x -= img_x0;
    y -= img_y0;
}
