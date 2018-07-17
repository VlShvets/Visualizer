#ifndef SETTINGS_H
#define SETTINGS_H

#include "painter.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QCheckBox>

namespace Visualizer
{

/// Класс виджета настроек отображения
class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit    Settings(Painter *_painter, QWidget *_parent = 0);
    ~Settings();

private:
    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Указатели на виджеты
    Painter     *painter;           /// Виджет отрисовки координат
};

}

#endif // SETTINGS_H
