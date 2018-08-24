#ifndef STATUS_H
#define STATUS_H

#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QLCDNumber>

namespace Visualizer
{

enum TypeOfInfo     /// Тип передаваемой информации
{
    Time,           /// Текущее время
    AirTrack,       /// Количество воздушных трасс
    SurfaceTrack    /// Количество поверхностных трасс
};

/// Класс виджета отображения текущего состояния потока вычислений
class Status : public QWidget
{
    Q_OBJECT

public:
    explicit    Status();
    ~Status();

    /// Отображение полученной информации в строке состояния
    void        showInfo(TypeOfInfo _typeOfInfo, const float _info);

    /// Очищение виджета отображения текущего состояния потока вычислений
    void        clearing();

private:
    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Указатели на виджеты
    QLCDNumber  *time;                  /// Текущее время
    QLCDNumber  *countAirTracks;        /// Текущее количество воздушных трасс
    QLCDNumber  *countSurfaceTracks;    /// Текущее количество поверхностных трасс
    QLCDNumber  *maxCountTracks;        /// Максимальное количество трасс
};

}

#endif // STATUS_H
