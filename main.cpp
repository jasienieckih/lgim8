// The main application file, created automatically by Qt Creator
// In most cases we do not need to change anything here


// The QApplication class manages the GUI application's control flow and main settings.
#include <QApplication>

// We include the header file of MyWindow class - main widget (window) of our application
#include "mywindow.h"

int main(int argc, char *argv[])
{


    // For any GUI application using Qt, there is precisely one QApplication object,
    // no matter whether the application has 0, 1, 2 or more windows at any given time.
    QApplication a(argc, argv);

    // We create the main window of our application - the object of MyWindow class
    // This class is defined in files mainwindow.h and mainwindow.cpp
    MyWindow w;

    // Shows the main window on the screen. By default it is not visible.
    // All its child widgets (GUI components contained in the main window) will also appear.
    w.show();


    // Enters the main event loop and waits for users actions
    // It is necessary to call this function to start event handling.
    // The main event loop receives events from the window system and dispatches these to the application widgets.
    return a.exec();
}
