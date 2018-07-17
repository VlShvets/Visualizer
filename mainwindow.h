#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playpause.h"
#include "settings.h"
#include "status.h"

#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>

namespace Visualizer
{

/// Класс виджета главного окна
class MainWindow : public QMainWindow
{
public:
    explicit    MainWindow(QWidget *_parent = 0);
    ~MainWindow();

private:
    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    AboutEtalon     *aboutEtalon;   /// Класс виджета отображения параметров эталонов
    AboutTrack      *aboutTrack;    /// Класс виджета отображения параметров трасс
    GraphHeight     *graphHeight;   /// Класс виджета отображения графика высоты
    Painter         *painter;       /// Класс виджета отрисовки эталонов и трасс
    Settings        *settings;      /// Класс виджета настроек отображения
    Status          *status;        /// Класс виджета отображения текущего состояния потока вычислений
    PlayPause       *playPause;     /// Класс виджета управления потоком вычислений
};

}

#endif // MAINWINDOW_H
