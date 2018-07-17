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
    explicit        GraphHeight(QWidget *_parent = 0);
    ~GraphHeight();

    /// Очистка графика высоты
    void            resetGraph();

    /// Установка отслеживаемого эталона
    void            setEtalon(Etalon *_etalon);

    /// Удаление отслеживаемого эталона
    inline void     delEtalon();

    /// Установка отслеживаемой трассы
    void            setTrack(Track *_track);

    /// Удаление отслеживаемой трассы
    inline void     delTrack();

protected:
    /// Обновление отрисовки
    void            timerEvent(QTimerEvent *);

    /// Отрисовка графика высоты
    void            paintEvent(QPaintEvent *_pEvent);

private:
    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    bool    etalonIsSelected;   /// Флаг наличия эталона
    bool    trackIsSelected;    /// Флаг наличия трассы

    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    Etalon  *etalon;            /// Отслеживаемый эталон
    Track   *track;             /// Отслеживаемая трасса    
};



/// Удаление отслеживаемой трассы
void GraphHeight::delEtalon()
{
    etalonIsSelected = false;
}

/// Удаление отслеживаемого эталона
void GraphHeight::delTrack()
{
    trackIsSelected = false;
}

}

#endif // GRAPHHEIGHT_H
