#include "Visualizer.h"

Visualizer::Visualizer()
{
    MainWindow *mainWindow = new MainWindow;
    mainWindow->showMaximized();

    MainThread *mainThread = new MainThread(mainWindow);
    mainThread->start();
}

Visualizer::~Visualizer()
{
}
