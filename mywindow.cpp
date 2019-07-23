// We include the header file of MyWindow class - main widget (window) of our application
#include "mywindow.h"

// Include the header file containing definitions GUI
// This file is automatically generated when you build the project
// It is based on data from an XML file "mywindow.ui"
#include "ui_mywindow.h"

#include <QFileDialog>

// The definition of the constructor of MyWindow class
// First call the constructor of the parent class,
// next create object representing the GUI
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow),
    maskSize(1)
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
    img_clean();
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
            ptr[img_width*4*i + 4*j] = 255; // BLUE component
            ptr[img_width*4*i + 4*j + 1] = 255; // GREEN component
            ptr[img_width*4*i + 4*j + 2] = 255; // RED component
        }
    }
}

bool isPixelDark(QRgb pixel)
{
    unsigned int blue = pixel % 0xff;
    pixel /= 0xff;
    unsigned int green = pixel % 0xff;
    pixel /= 0xff;
    unsigned int red = pixel % 0xff;
    return blue + green + red < 0x17f;
}

void MyWindow::loadPictureFromFile(QString filename)
{
    QImage loadedImage(filename);

    img_clean();

    int xmargin = 0;
    int xdelta = img_width - loadedImage.width();
    if (xdelta > 0)
    {
        xmargin = xdelta / 2;
    }
    int ymargin = 0;
    int ydelta = img_height - loadedImage.height();
    if (ydelta > 0)
    {
        ymargin = ydelta / 2;
    }

    for (int x = 0; x < loadedImage.width() and x < img_width; ++x)
    {
        for (int y = 0; y < loadedImage.height() and y < img_height; ++y)
        {
            const QRgb black = 0x000000;
            QRgb pixel = loadedImage.pixel(x, y);
            if (isPixelDark(pixel))
            {
                img->setPixel(xmargin + x, ymargin + y, black);
            }
        }
    }

    update();
}

bool MyWindow::arePixelCoordsValid(int x, int y)
{
    if (x >= 0 and x < img_width and y >= 0 and y < img_height)
        return true;
    return false;
}

void MyWindow::dilate()
{
    QImage copy = img->copy(0, 0, img_width, img_height);
    const QRgb black = 0x000000;
    for (int x = 0; x < img_width; ++x)
    {
        for (int y = 0; y < img_height; ++y)
        {
            bool encountered = false;
            for (int xd = -maskSize; xd <= maskSize /*and !encountered*/; ++xd)
            {
                for (int yd = -maskSize; yd <= maskSize /*and !encountered*/; ++yd)
                {
                    if ((xd != 0 or yd != 0)
                            and arePixelCoordsValid(x + xd, y + yd)
                            and copy.pixel(x + xd, y + yd) % 2 == 0)
                    {
                        encountered = true;
                    }
                }
            }
            if (encountered)
            {
                img->setPixel(x, y, black);
            }
        }
    }

    update();
}

// Function (slot) called when the user press mouse button
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x -= img_x0;
    y -= img_y0;
}

void MyWindow::on_maskSizeBox_valueChanged(int arg1)
{
    maskSize = arg1;
}

void MyWindow::on_dilateButton_clicked()
{
    dilate();
}

void MyWindow::on_erodeButton_clicked()
{
    //
}

void MyWindow::on_openingButton_clicked()
{
    //
}

void MyWindow::on_closureButton_clicked()
{
    //
}

void MyWindow::on_openFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose image..."), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    if (filename != "")
        loadPictureFromFile(filename);
}
