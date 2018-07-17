#ifndef PLAYPAUSE_H
#define PLAYPAUSE_H

#include "mainthread.h"
#include "painter.h"
#include "status.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QPushButton>
#include <QStyle>
#include <QLabel>
#include <QComboBox>
#include <QStringList>

namespace Visualizer
{

/// Класс виджета управления потоком вычислений
class PlayPause : public QWidget
{
    Q_OBJECT

public:
    explicit    PlayPause(Painter *_painter, Status *_status, QWidget *_parent = 0);
    ~PlayPause();

private slots:
    /// Перезапуск потока вычислений
    void        reStart();

    /// Запуск и остановка потока вычислений
    void        stateChanged();

    /// Остановка потока вычислений
    void        stop();

private:
    /// Создание нового потока вычислений
    void        createOfThread();

    /// Завершение имеющегося потока вычислений
    void        completeOfThread();

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Указатели на виджеты
    QPushButton     *pPlayPause;    /// Виджет кнопки запуска и остановки потока вычислений
    QComboBox       *cDeltaTime;    /// Виджет регулирования времени между итерациями потока вычислений

    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    Painter         *painter;       /// Класс виджета отрисовки эталонов и трасс
    Status          *status;        /// Класс виджета отображения текущего состояния потока вычислений
    MainThread      *mainThread;    /// Класс главного потока вычислений
};

}

#endif // PLAYPAUSE_H
