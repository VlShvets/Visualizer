#ifndef GRAPHHEIGHT_H
#define GRAPHHEIGHT_H

#include "target.h"

#include "grapher2d.h"

namespace Visualizer
{

/// Класс виджета отображения графика высоты
class GraphHeight : public Grapher2D
{
public:
    explicit    GraphHeight(QWidget *_parent = nullptr);
    ~GraphHeight();

    /// Установка указателя на словарь эталонов
    inline void setEtalons(QMap <int, Etalon> &_etalons);

    /// Установка указателя на словарь воздушных трасс
    inline void setAirTracks(QMap <int, Track> &_airTracks);

    /// Очистка графика высоты
    void        resetGraph();

    /// Установка отслеживаемого эталона
    void        setEtalon(int _indexOfEtalons);

    /// Установка отслеживаемой трассы
    void        setAirTrack(int _indexOfAirTracks);

protected:
    /// Обновление отрисовки
    void        timerEvent(QTimerEvent *);

    /// Отрисовка графика высоты
    void        paintEvent(QPaintEvent *_pEvent);

private:
    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    /// Номера выбранных эталонов и трасс
    int     indexOfEtalons;     /// Номер выбранного эталона
    int     indexOfAirTracks;   /// Номер выбранной трассы

    /// Указатели на словари параметров ЗКВ, эталонов и трасс
    QMap <int, Etalon>  *etalons;       /// Словарь эталонов                <номер, структура параметров>
    QMap <int, Track>   *airTracks;     /// Словарь воздушных трасс         <номер, структура параметров>
};

/// Установка указателя на словарь эталонов
void GraphHeight::setEtalons(QMap <int, Etalon> &_etalons)
{
    etalons = &_etalons;
}

/// Установка указателя на словарь воздушных трасс
void GraphHeight::setAirTracks(QMap<int, Track> &_airTracks)
{
    airTracks = &_airTracks;
}

}

#endif // GRAPHHEIGHT_H
