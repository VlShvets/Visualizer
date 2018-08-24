#include "graphheight.h"

namespace Visualizer
{

/// Класс виджета отображения графика высоты
GraphHeight::GraphHeight(QWidget *_parent)
    : Grapher2D(_parent), indexOfEtalons(-1), indexOfAirTracks(-1)
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
    /// Очищение флагов наличия эталонов и трасс
    indexOfEtalons      = -1;
    indexOfAirTracks    = -1;
}

/// Установка отслеживаемого эталона
void GraphHeight::setEtalon(int _indexOfEtalons)
{
    if(_indexOfEtalons < 0 || _indexOfEtalons > etalons->count() || !etalons->contains(_indexOfEtalons))
        return;

    indexOfEtalons  = _indexOfEtalons;
    Etalon *etalon  = &(*etalons)[_indexOfEtalons];

    /// Сдвиг оси ординат
    if(etalon->getTrajectoryHeight(0) * getCSOrdScale() < - height() / 2 - getCSOrdShift() + H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(- height() / 2 - etalon->getTrajectoryHeight(0) * getCSOrdScale() + H_SHIFT * getCSOrdExpansion() * getCSZoom());
    else if (etalon->getTrajectoryHeight(0) * getCSOrdScale() > height() / 2 - getCSOrdShift() - H_SHIFT * getCSOrdExpansion() * getCSZoom())
        setCSOrdShift(height() / 2 - etalon->getTrajectoryHeight(0) * getCSOrdScale() - H_SHIFT * getCSOrdExpansion() * getCSZoom());

    etalon  = nullptr;
}

/// Установка отслеживаемой трассы
void GraphHeight::setAirTrack(int _indexOfAirTracks)
{
    if(_indexOfAirTracks < 0 || _indexOfAirTracks > airTracks->count() || !airTracks->contains(_indexOfAirTracks))
        return;

    indexOfAirTracks    = _indexOfAirTracks;
    Track *airTrack     = &(*airTracks)[_indexOfAirTracks];

    /// Сдвиг оси ординат
    if(airTrack->getTrajectoryHeight(0) * getCSOrdScale() < - height() / 2 - getCSOrdShift() + H_SHIFT * getCSOrdExpansion() * getCSZoom())
       setCSOrdShift(- height() / 2 - airTrack->getTrajectoryHeight(0) * getCSOrdScale() + H_SHIFT * getCSOrdExpansion() * getCSZoom());
    else if(airTrack->getTrajectoryHeight(0) * getCSOrdScale() > height() / 2 - getCSOrdShift() - H_SHIFT * getCSOrdExpansion() * getCSZoom())
            setCSOrdShift(height() / 2 - airTrack->getTrajectoryHeight(0) * getCSOrdScale() - H_SHIFT * getCSOrdExpansion() * getCSZoom());

    airTrack = nullptr;
}

/// Обновление отрисовки
void GraphHeight::timerEvent(QTimerEvent *)
{
    /// Удаление отслеживаемого эталона с графика высоты
    if(indexOfEtalons != -1 && !etalons->contains(indexOfEtalons))
        indexOfEtalons  = -1;

    /// Удаление отслеживаемой трассы с графика высоты
    if(indexOfAirTracks != -1 && !airTracks->contains(indexOfAirTracks))
        indexOfAirTracks   = -1;

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
    Etalon *etalon;
    if(indexOfEtalons != -1 && etalons->contains(indexOfEtalons))
    {
        etalon  = &(*etalons)[indexOfEtalons];

        /// Эталон
        pen.setColor(Qt::GlobalColor(CLR_ETALON));
        pen.setWidth(WDT_CURRENT_POINT);
        p.setPen(pen);
        p.drawPoint(QPointF(0, etalon->getTrajectoryHeight(0)));

        /// История эталона
        for(int i = 1; i < etalon->getTrajectoryCount(); ++i)
        {
            /// Отрисовка местоположений
            pen.setWidth(WDT_TRAJECTORY_POINT);
            p.setPen(pen);
            p.drawPoint(QPointF((int)(etalon->getTrajectoryTime(i) - etalon->getTrajectoryTime(0)), etalon->getTrajectoryHeight(i)));

            /// Отрисовка траекторий
            pen.setWidth(WDT_TRAJECTORY);
            p.setPen(pen);
            p.drawLine(QPointF((int)(etalon->getTrajectoryTime(i - 1) - etalon->getTrajectoryTime(0)), etalon->getTrajectoryHeight(i - 1)),
                       QPointF((int)(etalon->getTrajectoryTime(i) - etalon->getTrajectoryTime(0)), etalon->getTrajectoryHeight(i)));
        }
    }

    /// Отрисовка высот трассы
    Track *airTrack;
    if(indexOfAirTracks != -1 && airTracks->contains(indexOfAirTracks))
    {
        airTrack   = &(*airTracks)[indexOfAirTracks];

        /// Трасса
        if(airTrack->getTGenTrc()->OGP == 1)
        {
            if(airTrack->getTrajectorySensCount(0) > 1.0)
                pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
            else
                pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
        }
        else
        {
            if(airTrack->getTrajectorySensCount(0) > 1.0)
                pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
            else
                pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
        }
        pen.setWidth(WDT_CURRENT_POINT);
        p.setPen(pen);
        if(indexOfEtalons != -1 && etalons->contains(indexOfEtalons))
            p.drawPoint(QPointF(airTrack->getTrajectoryTime(0) - etalon->getTrajectoryTime(0), airTrack->getTrajectoryHeight(0)));
        else
            p.drawPoint(QPointF(0, airTrack->getTrajectoryHeight(0)));

        /// История трассы
        for(int i = 1; i < airTrack->getTrajectoryCount(); ++i)
        {
            /// Отрисовка местоположений
            if(airTrack->getTGenTrc()->OGP == 1)
            {
                if(airTrack->getTrajectorySensCount(i) > 1.0)
                    pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                else
                    pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
            }
            else
            {
                if(airTrack->getTrajectorySensCount(i) > 1.0)
                    pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                else
                    pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
            }
            pen.setWidth(WDT_TRAJECTORY_POINT);
            p.setPen(pen);
            if(indexOfEtalons != -1 && etalons->contains(indexOfEtalons))
                p.drawPoint(QPointF((int)(airTrack->getTrajectoryTime(i) - etalon->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i)));
            else
                p.drawPoint(QPointF((int)(airTrack->getTrajectoryTime(i) - airTrack->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i)));

            /// Отрисовка траекторий
            pen.setWidth(WDT_TRAJECTORY);
            p.setPen(pen);
            if(indexOfEtalons != -1 && etalons->contains(indexOfEtalons))
                p.drawLine(QPointF((int)(airTrack->getTrajectoryTime(i - 1) - etalon->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i - 1)),
                           QPointF((int)(airTrack->getTrajectoryTime(i) - etalon->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i)));
            else
                p.drawLine(QPointF((int)(airTrack->getTrajectoryTime(i - 1) - airTrack->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i - 1)),
                           QPointF((int)(airTrack->getTrajectoryTime(i) - airTrack->getTrajectoryTime(0)), airTrack->getTrajectoryHeight(i)));
        }
    }

    etalon  = nullptr;
    airTrack   = nullptr;

    p.end();
}

}
