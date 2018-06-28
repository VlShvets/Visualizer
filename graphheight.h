#ifndef GRAPHHEIGHT_H
#define GRAPHHEIGHT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "Target.h"

#include "Grapher2D.h"

class GraphHeight : public Grapher2D
{
public:
    GraphHeight();
    ~GraphHeight();

    /// Установка отслеживаемого эталона
    void setEtalon(Etalon *_etalon);

    /// Удаление отслеживаемого эталона
    void delEtalon();

    /// Установка отслеживаемой трассы
    void setTrack(Track *_track);

    /// Удаление отслеживаемой трассы
    void delTrack();

protected:
    void paintEvent(QPaintEvent *_pEvent);

private:
    bool etalonIsSelected;  /// Флаг наличия эталона
    bool trackIsSelected;   /// Флаг наличия трассы

    Etalon *etalon;         /// Отслеживаемый эталон
    Track *track;           /// Отслеживаемая трасса
};

#endif // GRAPHHEIGHT_H
