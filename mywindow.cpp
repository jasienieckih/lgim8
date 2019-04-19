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

    images.emplace_back(":lab09/resources/exploration6lgim.jpg");
    images.emplace_back(":lab09/resources/morning_glories.jpg");

    updateBlending();
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
    p.drawImage(img_x0, img_y0, workingImage.getImage());
}

void MyWindow::initializeCheckerboardBackground()
{
    uchar* bits = img->bits();
    for (int x = 0; x < img_width; ++x)
    {
        for (int y = 0; y < img_height; ++y)
        {
            int pixel = 4 * (img_width * y + x);
            uchar color = 0x66;
            if (((x / 8) % 2) ^ ((y / 8) % 2))
                color = 0x99;
            for (int c = 0; c < 3; ++c)
            {
                bits[pixel + c] = color;
            }
        }
    }
}

void MyWindow::blendLayer(Image &source)
{
    uchar *target_bits = workingImage.getBits();
    uchar *source_bits = source.getBits();

    for (int x = 0; x < img_width; ++x)
    {
        for (int y = 0; y < img_height; ++y)
        {
            int pixel = 4 * (y * img_width + x);
            for (int c = 0; c < 4; ++c)
            {
                target_bits[pixel + c] = source_bits[pixel + c];
            }
        }
    }
}

void MyWindow::updateBlending()
{
    int number_of_images = images.size();
    initializeCheckerboardBackground();
    workingImage.clean();
    for (int image_index = number_of_images - 1; image_index >= 0; --image_index)
    {
        if (images[image_index].visible_)
        {
            blendLayer(images[image_index]);
        }
    }
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

BlendingMode stdStringToBlendingMode(const QString &arg)
{
    if (arg == "Normal")
        return BlendingMode::Normal;
    if (arg == "Lighten only")
        return BlendingMode::LightenOnly;
    if (arg == "Darken only")
        return BlendingMode::DarkenOnly;
    if (arg == "Add")
        return BlendingMode::Add;
    if (arg == "Multiply")
        return BlendingMode::Multiply;
    if (arg == "Saturation")
        return BlendingMode::Saturation;
    if (arg == "Grain effect")
        return BlendingMode::GrainEffect;
    return BlendingMode::Normal;
}

void MyWindow::on_checkBoxVisible01_toggled(bool checked)
{
    images[0].visible_ = checked;
    updateBlending();
}

void MyWindow::on_comboBoxMode01_activated(const QString &arg1)
{
    images[0].mode = stdStringToBlendingMode(arg1);
    updateBlending();
}

void MyWindow::on_sliderAlpha01_valueChanged(int value)
{
    images[0].alpha_ = value / 1000.0;
    updateBlending();
}

void MyWindow::on_checkBoxVisible02_toggled(bool checked)
{
    images[1].visible_ = checked;
    updateBlending();
}

void MyWindow::on_comboBoxMode02_activated(const QString &arg1)
{
    images[1].mode = stdStringToBlendingMode(arg1);
    updateBlending();
}

void MyWindow::on_sliderAlpha02_valueChanged(int value)
{
    images[1].alpha_ = value / 1000.0;
    updateBlending();
}
