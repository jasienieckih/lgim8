// The header file of MyWindow class
// The object of this class is the main window of our application
// The skeleton of this file is created by the Qt Creator
// You can add here your own fields and methods

#ifndef MYWINDOW_H
#define MYWINDOW_H

// MyWindow class inherits from class QMainWindow
// Class QMainWindow has its own layout.
// You can easily add to it the menu bar, toolbar and status bar.
// In the middle of the window displayed by QMainWindow
// is located area that you can fill with different widgets.
#include <QMainWindow>

// QPainter is the class allowing low-level drawing on the GUI elements
#include <QPainter>

// QImage is the class providing independent of hardware representations of the image.
// Allows direct access to individual pixels,
// We will use it for creating and storing our pictures
#include <QImage>

// The QMouseEvent class contains parameters that describe a mouse event.
// Mouse events occur when a mouse button is pressed
// or released inside a widget, or when the mouse cursor is moved.
#include <QMouseEvent>

#include "triangleptr.h"

namespace Ui {
    class MyWindow;
}

// MyWindow is a subclass of QMainWindow class.
class MyWindow : public QMainWindow
{

    // The Q_OBJECT macro is mandatory for any class
    // that implements signals, slots or properties.
    Q_OBJECT

public:
    // A typical declaration of constructor in Qt.
    // In the case of our class 'parent' parameter indicates to null
    // because it is a top-level component
    explicit MyWindow(QWidget *parent = nullptr);

    // Declaration of destructor
    ~MyWindow();

private:
    // Qt Creator allows you to create GUI using a graphical wizard.
    // Interface components and their properties are then stored in an XML file 'class_name.ui'
    // Access to individual elements of the GUI is obtained by the variable "ui"
    Ui::MyWindow *ui;

    // 'img' is a field storing the image
    QImage *img;

    // width of the image
    int img_width;

    // height of the image
    int img_height;

    // coordinates of the upper left corner of the image
    int img_x0;
    int img_y0;

    // Declarations of drawing functions
    void img_clean();
    void img_draw1();
    void img_draw2();

    // task-specific fields
    const int HANDLE_RADIUS = 4;
    const int NUMBER_OF_TRIANGLES = 2;
    const int NUMBER_OF_POINTS = 4;
    Point points[2][4];
    TrianglePtr *triangles[2][2];
    QImage outputImage;
    QImage sourceImage;
    int outputImage_x0;
    int outputImage_y0;
    int whichPointDragged;
    bool isDragging;
    bool hidingMode;

    // task-specific functions
    void updateTexturing();
    int bitsCoordFromXy(int x, int y);
    int bitsCoordFromXy(int x, int y, int width);
    bool areCoordsValid(int x, int y);
    void drawTriangleHandles();
    void drawTriangles();
    void drawLine(QImage& image, int x0, int y0, int x1, int y1);
    void drawLine(QImage& image, Point p0, Point p1);
    void drawOriginalImage();
    void updateOutputImage();
    void updateOutputTriangle(int index);
private slots:
    // Declarations of slots
    // A slot is a function that is called in response to a particular event,
    // eg. event associated with the GUI (mouse move, button press, etc.)
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void on_hideCheckBox_toggled(bool checked);
};

#endif // MYWINDOW_H
