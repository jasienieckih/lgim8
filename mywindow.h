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

#include <vector>

#include "matrix.h"
#include "point.h"
#include "polygon.h"

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
    std::vector<Point> points;
    std::vector<Polygon> polygons;
    Matrix translationMatrix;
    Matrix rotationMatrixXAxis;
    Matrix rotationMatrixYAxis;
    Matrix scalingMatrix;
    Matrix shearingXMatrix;
    Matrix shearingYMatrix;
    Matrix shearingZMatrix;
    bool scalingTogether;

    // task-specific methods
    void updateProjection();
    void drawLine(int x0, int y0, int x1, int y1);
    void drawLine(Point p0, Point p1);
    void drawTriangle(Point a, Point b, Point c);
    bool areCoordsValid(int x, int y);
private slots:
    // Declarations of slots
    // A slot is a function that is called in response to a particular event,
    // eg. event associated with the GUI (mouse move, button press, etc.)
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
    void on_cleanButton_clicked();
    void on_exitButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    void on_translationXSlider_valueChanged(int value);
    void on_translationYSlider_valueChanged(int value);
    void on_translationZSlider_valueChanged(int value);
    void on_rotationSlider1_valueChanged(int value);
    void on_rotationSlider2_valueChanged(int value);
    void on_scalingXSlider_valueChanged(int value);
    void on_scalingYSlider_valueChanged(int value);
    void on_scalingZSlider_valueChanged(int value);
    void on_shearingXSlider_valueChanged(int value);
    void on_shearingYSlider_valueChanged(int value);
    void on_shearingZSlider_valueChanged(int value);
    void on_resetButton_clicked();
    void on_scalingTogetherBox_toggled(bool checked);
};

#endif // MYWINDOW_H
