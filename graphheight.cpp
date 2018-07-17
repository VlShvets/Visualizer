#include "graphheight.h"

namespace Visualizer
{

/// Класс виджета отображения графика высоты
GraphHeight::GraphHeight(QWidget *_parent)
    : Grapher2D(_parent), etalonIsSelected(false), trackIsSelected(false)
{
    setCSZoom(GEN_ZOOM);
    setCSZoomStep(H_STEP_ZOOM);
    setCSOrdMeasure(H_MEASURE);
    setCSOrdExpansion(H_EXPANSION);
    setCSAngles(false, true, false, false);
    setCSAbsValues(false);
    setCSZoomCenter(true);

    startTimer(H_INTERVAL);
}

GraphHeight::~GraphHeight()
{
    resetGraph();
}

/// Очистка графика высоты
void GraphHeight::resetGraph()
{
    etalonIsSelected = false;
    trackIsSelected = false;
}

/// Установка отслеживаемого эталона
void GraphHeight::setEtalon(Etalon *_etalon)
{
    if(_etalon->getTPubEtalon() == NULL)
    {
        delEtalon();
        return;
    }

    etalon = _etalon;
    etalonIsSelected = true;

    if(etalon->getMemoryHeight(0) * getCSOrdScale() <
            - height() / 2 - getCSOrdShift() + H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(- height() / 2 - etalon->getMemoryHeight(0) * getCSOrdScale() + H_SHIFT * getCSOrdExpansion() * getCSZoom());
    else if (etalon->getMemoryHeight(0) * getCSOrdScale() >
             height() / 2 - getCSOrdShift() - H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(height() / 2 - etalon->getMemoryHeight(0) * getCSOrdScale() - H_SHIFT * getCSOrdExpansion() * getCSZoom());
}

/// Установка отслеживаемой трассы
void GraphHeight::setTrack(Track *_track)
{
    if(_track->getTGenTrc() == NULL)
    {
        delTrack();
        return;
    }

    track = _track;
    trackIsSelected = true;

    if(track->getMemoryHeight(0) * getCSOrdScale() <
            - height() / 2 - getCSOrdShift() + H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(- height() / 2 - track->getMemoryHeight(0) * getCSOrdScale() + H_SHIFT * getCSOrdExpansion() * getCSZoom());
    else if (track->getMemoryHeight(0) * getCSOrdScale() >
             height() / 2 - getCSOrdShift() - H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(height() / 2 - track->getMemoryHeight(0) * getCSOrdScale() - H_SHIFT * getCSOrdExpansion() * getCSZoom());
}

/// Обновление отрисовки
void GraphHeight::timerEvent(QTimerEvent *)
{
    repaint();
}

/// Отрисовка графика высоты
void GraphHeight::paintEvent(QPaintEvent *_pEvent)
{
    Grapher2D::paintEvent(_pEvent);

    QPainter p(this);
    p.translate(getCSAbsTranslate() - H_SHIFT * getCSZoom(), getCSOrdTranslate());
    p.scale(getCSAbsScale(), getCSOrdScale());

    QPen pen;
    pen.setCosmetic(true);

    /// Отрисовка высот эталона
    if(etalonIsSelected)
    {
        /// Эталон
        pen.setColor(Qt::GlobalColor(CLR_ETALON));
        pen.setWidth(WDT_LAST_POINT);
        p.setPen(pen);
        p.drawPoint(QPointF(0, etalon->getMemoryHeight(0)));

        /// История эталона
        for(int i = 1; i < etalon->getCountPoints(); ++i)
        {
            /// Отрисовка местоположений
            pen.setWidth(WDT_MEMORY_POINT);
            p.setPen(pen);
            p.drawPoint(QPointF((int)(etalon->getMemoryTime(i) - etalon->getMemoryTime(0)), etalon->getMemoryHeight(i)));

            /// Отрисовка траекторий
            pen.setWidth(WDT_PATH);
            p.setPen(pen);
            p.drawLine(QPointF((int)(etalon->getMemoryTime(i - 1) - etalon->getMemoryTime(0)), etalon->getMemoryHeight(i - 1)),
                       QPointF((int)(etalon->getMemoryTime(i) - etalon->getMemoryTime(0)), etalon->getMemoryHeight(i)));
        }
    }

    /// Отрисовка высот трассы
    if(trackIsSelected)
    {
        /// Трасса
        if(track->getMemorySensCount(0) > 1.0)
            pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
        else
            pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
        pen.setWidth(WDT_LAST_POINT);
        p.setPen(pen);
        if(etalonIsSelected)
            p.drawPoint(QPointF(track->getMemoryTime(0) - etalon->getMemoryTime(0), track->getMemoryHeight(0)));
        else
            p.drawPoint(QPointF(0, track->getMemoryHeight(0)));

        /// История трассы
        for(int i = 1; i < track->getCountPoints(); ++i)
        {
            /// Отрисовка местоположений
            if(track->getMemorySensCount(0) > 1.0)
                pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
            else
                pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
            pen.setWidth(WDT_MEMORY_POINT);
            p.setPen(pen);
            if(etalonIsSelected)
                p.drawPoint(QPointF((int)(track->getMemoryTime(i) - etalon->getMemoryTime(0)), track->getMemoryHeight(i)));
            else
                p.drawPoint(QPointF((int)(track->getMemoryTime(i) - track->getMemoryTime(0)), track->getMemoryHeight(i)));

            /// Отрисовка траекторий
            pen.setWidth(WDT_PATH);
            p.setPen(pen);
            if(etalonIsSelected)
                p.drawLine(QPointF((int)(track->getMemoryTime(i - 1) - etalon->getMemoryTime(0)), track->getMemoryHeight(i - 1)),
                           QPointF((int)(track->getMemoryTime(i) - etalon->getMemoryTime(0)), track->getMemoryHeight(i)));
            else
                p.drawLine(QPointF((int)(track->getMemoryTime(i - 1) - track->getMemoryTime(0)), track->getMemoryHeight(i - 1)),
                           QPointF((int)(track->getMemoryTime(i) - track->getMemoryTime(0)), track->getMemoryHeight(i)));
        }
    }

    p.end();
}

}
