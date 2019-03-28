#include "painter.h"

namespace Visualizer
{

/// Класс виджета отрисовки эталонов и трасс
Painter::Painter(AboutEtalon *_aboutEtalon, AboutTrack *_aboutTrack, GraphHeight *_graphHeight,
                 QWidget *_parent)
    : Grapher2D(_parent),
      aboutEtalon(_aboutEtalon), aboutTrack(_aboutTrack), graphHeight(_graphHeight),
      isVisibleOfAreas(true), isVisibleOfEtalons(true),
      isVisibleOfAirTracks(true), isVisibleOfSurfaceTracks(true),
      isVisibleOfGroupLeaders(false), isVisibleOfTrajectories(false)
{
    setCSZoom(GEN_ZOOM);
    setCSAbsMeasure(XY_MEASURE);
    setCSOrdMeasure(XY_MEASURE);
    setMouseTracking(true);     /// Определение координат указателя мыши

    clearing();

    startTimer(XY_INTERVAL);
}

Painter::~Painter()
{
    clearing();
}

/// Установка указателя на словарь стационарных объектов
//void Painter::setStationary(QMap<int, Stationary> &_stationary)
//{
//    stationary = &_stationary;
//}

/// Установка указателя на словарь эталонов
void Painter::setEtalons(QMap <int, Etalon> &_etalons)
{
    etalons = &_etalons;

    /// Отправка указателя на
    if(graphHeight != nullptr)
        graphHeight->setEtalons(_etalons);
}

/// Установка указателя на словарь воздушных трасс
void Painter::setAirTracks(QMap <int, Track> &_airTracks)
{
    airTracks = &_airTracks;

    if(graphHeight != nullptr)
        graphHeight->setAirTracks(_airTracks);
}

/// Установка указателя на словарь поверхностных трасс
void Painter::setSurfaceTracks(QMap <int, Track> &_surfaceTracks)
{
    surfaceTracks = &_surfaceTracks;
}

/// Очищение отрисовки
void Painter::clearing()
{
    /// Очищение указателей на словари параметров ЗКВ, эталонов и трасс
//    stationary      = nullptr;
    etalons         = nullptr;
    airTracks       = nullptr;
    surfaceTracks   = nullptr;

    /// Очищение номеров выделенных и выбранных эталонов и трасс
    numberHighlightedEtalon = -1;
    numberSelectedEtalon    = -1;
    numberHighlightedTrack  = -1;
    numberSelectedTrack     = -1;

    /// Очищение виджета отображения параметров эталона
    aboutEtalon->resetInfoAboutEtalon();

    /// Очищение виджета отображения параметров трассы
    aboutTrack->resetInfoAboutTrack();

    /// Очищение виджета отображения графика высоты
    graphHeight->resetGraph();
}

/// События нажатия кнопки мыши
void Painter::mousePressEvent(QMouseEvent *_mEvent)
{
    Grapher2D::mousePressEvent(_mEvent);

    if(numberHighlightedEtalon == -1 && numberHighlightedTrack == -1)
    {
        setMCursorShape(Qt::ClosedHandCursor);
        setCursor(Qt::CursorShape(getMCursorShape()));
    }

    repaint();
}

/// События перемещения мыши
void Painter::mouseMoveEvent(QMouseEvent *_mEvent)
{
    Grapher2D::mouseMoveEvent(_mEvent);

    if(_mEvent->buttons() != Qt::LeftButton)
    {
        numberHighlightedEtalon = indexOfEtalons(getMPosNoClick().x(), getMPosNoClick().y());
        numberHighlightedTrack = indexOfTracks(getMPosNoClick().x(), getMPosNoClick().y());

        if(numberHighlightedEtalon != -1 || numberHighlightedTrack != -1)
            setCursor(Qt::CursorShape(Qt::PointingHandCursor));
        else
            setCursor(Qt::CursorShape(getMCursorShape()));
    }

    repaint();
}

/// События отпускания кнопки мыши
void Painter::mouseReleaseEvent(QMouseEvent *_mEvent)
{
    Grapher2D::mouseReleaseEvent(_mEvent);

    /// Выбор эталона
    if(etalons && isVisibleOfEtalons)
    {
        if(numberHighlightedEtalon != -1)
        {
            if(numberHighlightedEtalon != numberSelectedEtalon)
            {
                if(etalons->contains(numberHighlightedEtalon))
                {
                    numberSelectedEtalon = numberHighlightedEtalon;

                    aboutEtalon->setInfoAboutEtalon((*etalons)[numberSelectedEtalon].getTPubEtalon(), numberSelectedEtalon);
                    graphHeight->setEtalon(numberSelectedEtalon);
                }
            }
        }
    }

    /// Выбор трассы
    if(numberHighlightedTrack != -1)
    {
        if(numberHighlightedTrack != numberSelectedTrack)
        {
            /// Выбор воздушной трасс
            if(numberHighlightedTrack < 1000)
            {
                if(airTracks && isVisibleOfAirTracks)
                {
                    if(airTracks->contains(numberHighlightedTrack))
                    {
                        numberSelectedTrack = numberHighlightedTrack;

                        aboutTrack->setInfoAboutTrack((*airTracks)[numberSelectedTrack].getTGenTrc(), numberSelectedTrack);
                        graphHeight->setAirTrack(numberSelectedTrack);
                    }
                }
            }
            /// Выбор поверхностной трассы
            else
            {
                if(surfaceTracks && isVisibleOfSurfaceTracks)
                {
                    if(surfaceTracks->contains(numberHighlightedTrack - 1000))
                    {
                        numberSelectedTrack = numberHighlightedTrack;

                        aboutTrack->setInfoAboutTrack((*surfaceTracks)[numberSelectedTrack - 1000].getTGenTrc(), numberSelectedTrack - 1000);
                        graphHeight->resetGraph();
                    }
                }
            }
        }
    }

    repaint();
}

/// События двойного нажатия кнопки мыши
void Painter::mouseDoubleClickEvent(QMouseEvent *_mEvent)
{
    /// Очищение номеров выделенных эталонов и трасс
    numberSelectedEtalon    = -1;
    numberSelectedTrack     = -1;

    /// Очищение виджета отображения параметров эталона
    aboutEtalon->resetInfoAboutEtalon();

    /// Очищение виджета отображения параметров трассы
    aboutTrack->resetInfoAboutTrack();

    /// Очищение виджета отображения графика высоты
    graphHeight->resetGraph();
}

/// События колеса мыши
void Painter::wheelEvent(QWheelEvent *_wEvent)
{
    Grapher2D::wheelEvent(_wEvent);

    /// Изменение технического масштаба символов
    Target::setScale(getCSAbsScale());

    /// Перерисовка символов эталонов
    if(etalons && isVisibleOfEtalons)
    {
        QMap <int, Etalon>::iterator etalon = etalons->begin();
        for(; etalon != etalons->end(); ++etalon)
            etalon.value().setSymbol();
    }

    /// Изменение символов воздушных трасс
    if(airTracks && isVisibleOfAirTracks)
    {
        QMap <int, Track>::iterator airTrack = airTracks->begin();
        for(; airTrack != airTracks->end(); ++airTrack)
            airTrack.value().setSymbol();
    }

    /// Изменение символов поверхностных трасс
    if(surfaceTracks && isVisibleOfSurfaceTracks)
    {
        QMap <int, Track>::iterator surfaceTrack = surfaceTracks->begin();
        for(; surfaceTrack != surfaceTracks->end(); ++surfaceTrack)
            surfaceTrack.value().setSymbol();
    }

    repaint();
}

/// Обновление отрисокви
void Painter::timerEvent(QTimerEvent *)
{
    /// Перерисовка символов эталонов
    if(etalons && isVisibleOfEtalons)
    {
        QMap <int, Etalon>::iterator etalon = etalons->begin();
        for(; etalon != etalons->end(); ++etalon)
            etalon.value().setSymbol();
    }

    /// Перерисовка символов воздушных трасс
    if(airTracks && isVisibleOfAirTracks)
    {
        QMap <int, Track>::iterator airTrack = airTracks->begin();
        for(; airTrack != airTracks->end(); ++airTrack)
            airTrack.value().setSymbol();
    }

    /// Перерисовка символов поверхностных трасс
    if(surfaceTracks && isVisibleOfSurfaceTracks)
    {
        QMap <int, Track>::iterator surfaceTrack = surfaceTracks->begin();
        for(; surfaceTrack != surfaceTracks->end(); ++surfaceTrack)
            surfaceTrack.value().setSymbol();
    }

    /// Удаление отслеживаемого эталона с виджета отображения параметров эталона
    if(numberSelectedEtalon != -1 && !etalons->contains(numberSelectedEtalon))
        aboutEtalon->resetInfoAboutEtalon();


    /// Удаление отслеживаемой трассы с виджета отображения параметров трассы
    if(numberSelectedTrack != -1 && !airTracks->contains(numberSelectedTrack) && !surfaceTracks->contains(numberSelectedTrack - 1000))
        aboutTrack->resetInfoAboutTrack();

    repaint();
}

/// Определение номера эталона под курсором мыши
int Painter::indexOfEtalons(int _posX, int _posY)
{
    /// Определение номера эталона
    if(etalons && isVisibleOfEtalons)
    {
        QMap <int, Etalon>::const_iterator etalon = etalons->constBegin();
        for(; etalon != etalons->constEnd(); ++etalon)
        {
            if(etalon.value().containsPoint(QPoint(_posX - width() / 2 - getCSAbsShift(), _posY - height() / 2 - getCSOrdShift()),
                                            Qt::WindingFill))
            {
                return etalon.key();
            }
        }
    }

    return -1;
}

/// Определение номера трассы под курсором мыши
int Painter::indexOfTracks(int _posX, int _posY)
{
    /// Определение номера воздушной трассы
    if(airTracks && isVisibleOfAirTracks)
    {
        QMap <int, Track>::const_iterator airTrack = airTracks->constBegin();
        for(; airTrack != airTracks->constEnd(); ++airTrack)
        {
            if(airTrack.value().containsPoint(QPoint(_posX - width() / 2 - getCSAbsShift(), _posY - height() / 2 - getCSOrdShift()),
                                              Qt::WindingFill))
            {
                return airTrack.key();
            }
        }
    }

    /// Определение номера поверхностной трассы
    if(surfaceTracks && isVisibleOfSurfaceTracks)
    {
        QMap <int, Track>::const_iterator surfaceTrack = surfaceTracks->constBegin();
        for(; surfaceTrack != surfaceTracks->constEnd(); ++surfaceTrack)
        {
            if(surfaceTrack.value().containsPoint(QPoint(_posX - width() / 2 - getCSAbsShift(), _posY - height() / 2 - getCSOrdShift()),
                                                  Qt::WindingFill))
            {
                return 1000 + surfaceTrack.key();
            }
        }
    }

    return -1;
}

/// Отрисовка эталонов и трасс
void Painter::paintEvent(QPaintEvent *_pEvent)
{
    QPainter p(this);
    p.translate(getCSAbsTranslate(), getCSOrdTranslate());
    p.scale(getCSAbsScale(), getCSOrdScale());

    /// Карта
    QPixmap map;
    bool mapload = map.load(":/map/0.jpg");
    if(!mapload){
        map.load(":/map/12.jpg");
    }

    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(QRect(- map.width() / 2.0 * 75.0 - 456125.0, - map.height() / 2.0 * 75.0 + 327075.0, map.width() * 75.0, map.height() * 75.0), map);
    p.restore();

    /// Координатные оси
    p.save();
    Grapher2D::paintEvent(_pEvent);
    p.restore();

    QPen pen;
    pen.setCosmetic(true);

    /// --------------------------------------------------

    /// Командные пункты

    QPixmap pic;
    QRect rect;

    /// Свой командный пункт №1 (Ростов)
    pic.load(":/pic/fr/cc/0.png");
    rect.setRect(CC_FR_1_X, CC_FR_1_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();
    pic.load(":/pic/fr/cc/1.png");
    rect.setRect(CC_FR_1_X, CC_FR_1_Y + 1.6 * pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Свой командный пункт №2 (Севастополь)
    pic.load(":/pic/fr/cc/0.png");
    rect.setRect(CC_FR_2_X, - CC_FR_2_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();
    pic.load(":/pic/fr/cc/2.png");
    rect.setRect(CC_FR_2_X, - CC_FR_2_Y + 1.6 * pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Свой командный пункт №3 (Феодосия)
    pic.load(":/pic/fr/cc/2.png");
    rect.setRect(CC_FR_3_X, - CC_FR_3_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Свой командный пункт №4 (Армянск)
    pic.load(":/pic/fr/cc/2.png");
    rect.setRect(CC_FR_4_X, - CC_FR_4_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Чужой командный пункт №1
    pic.load(":/pic/al/cc/0.png");
    rect.setRect(CC_AL_1_X, - CC_AL_1_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Чужой командный пункт №2
    pic.load(":/pic/al/ap/0.png");
    rect.setRect(CC_AL_2_X - 0.5 * pic.width() / getCSAbsScale(), - CC_AL_2_Y + 0.5 * pic.height() / getCSOrdScale(),
                 pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// Чужой командный пункт №3
    pic.load(":/pic/al/cc/0.png");
    rect.setRect(CC_AL_3_X, - CC_AL_3_Y + pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
    p.save();
    p.scale(1.0, -1.0);
    p.drawPixmap(rect, pic);
    p.restore();

    /// --------------------------------------------------

    /// Стационарные зоны видимости

    if(isVisibleOfAreas)
    {
        p.save();
        pen.setColor(Qt::GlobalColor(CLR_LINE_AREA));
        pen.setWidth(WDT_AREA);
        p.setPen(pen);
        QColor clr(Qt::GlobalColor(CLR_AREA));
        clr.setAlpha(ALPHA_AREA);
        p.setBrush(QBrush(clr));
        p.drawEllipse(AREA_1_X - AREA_1_R, AREA_1_Y - AREA_1_R, 2 * AREA_1_R, 2 * AREA_1_R);
        p.drawEllipse(AREA_2_X - AREA_2_R, AREA_2_Y - AREA_2_R, 2 * AREA_2_R, 2 * AREA_2_R);
        p.restore();
    }

    /// --------------------------------------------------

    QPixmap pxm;
    QRect rct;

    /// Эталоны

    if(etalons != nullptr && isVisibleOfEtalons)
    {

        QMap <int, Etalon>::const_iterator etalon = etalons->constBegin();
        for(; etalon != etalons->constEnd(); ++etalon)
        {
            TPubEtalon *p_TPubEtalon = etalon.value().getTPubEtalon();
            if(p_TPubEtalon != nullptr)
            {
                /// Отрисовка траекторий
                if(isVisibleOfTrajectories)
                {
                    for(int j = 1; j < etalon.value().getTrajectoryCount(); ++j)
                    {
                        /// Отрисовка местоположений
                        pen.setColor(Qt::GlobalColor(CLR_ETALON));
                        pen.setWidth(WDT_TRAJECTORY_POINT);
                        p.setPen(pen);
                        p.drawPoint(etalon.value().getTrajectoryCoord(j));

                        /// Отрисовка траекторий
                        pen.setWidth(WDT_TRAJECTORY);
                        p.setPen(pen);
                        p.drawLine(etalon.value().getTrajectoryCoord(j - 1), etalon.value().getTrajectoryCoord(j));
                    }
                }

                /// Отрисовка эталонов

                p.scale(1.0 / getCSAbsScale(), 1.0 / getCSOrdScale());

                p.setPen(QPen(Qt::GlobalColor(CLR_ETALON), WDT_ARROW));

                p.save();
                pen.setWidth(5);
                pen.setColor(Qt::green);
                p.setPen(pen);

                ///Отрисовка картинок

                p.translate(p_TPubEtalon->y*getCSAbsScale(), p_TPubEtalon->x*(getCSOrdScale()));
                p.rotate(5 - 180/M_PI*qAtan2(p_TPubEtalon->vx, p_TPubEtalon->vy));

                if(etalon.key() != numberHighlightedEtalon && etalon.key() != numberSelectedEtalon){
                    pxm.load(":/pic/foto/" + etalon.value().getPathImg() + "_Etalon.png");
                }else{
                    pxm.load(":/pic/foto/" + etalon.value().getPathImg() + "_Click.png");
                }

                rct.setRect(-pxm.width()/12, -pxm.height()/12, pxm.width()/6, pxm.height()/6);
                //etalon.value().load(":/pic/foto/" + etalon.value().getPathImg() + "_Etalon.png");
                //p.drawPixmap(rct, pxm);
                p.drawPixmap(rct, etalon.value());
                p.restore();
                p.scale(getCSAbsScale(), getCSOrdScale());

            }
        }
    }

    /// --------------------------------------------------

    /// Воздушные трассы

    if(airTracks != nullptr && isVisibleOfAirTracks)
    {

        QMap <int, Track>::const_iterator airTrack = airTracks->constBegin();
        for(; airTrack != airTracks->constEnd(); ++airTrack)
        {
            QString pathImg = "";

            if(airTrack.value().getTGenTrc() != nullptr)
            {
                if(!isVisibleOfGroupLeaders || airTrack.value().getTGenTrc()->grpInfo.trcCount > 0)
                {
                    /// Отрисовка подвижных зон видимости
                    if(isVisibleOfAreas)
                    {
                        p.save();
                        pen.setColor(Qt::GlobalColor(CLR_LINE_MOVE_AREA));
                        pen.setWidth(WDT_AREA);
                        p.setPen(pen);
                        QColor clr(Qt::GlobalColor(CLR_MOVE_AREA));
                        clr.setAlpha(ALPHA_AREA);
                        p.setBrush(QBrush(clr));
                        switch(airTrack.value().getTGenTrc()->TO)
                        {
                        case 17:
                        {
                            p.drawEllipse(airTrack.value().getTrajectoryCoord(0).x() - AREA_17_R,
                                          airTrack.value().getTrajectoryCoord(0).y() - AREA_17_R, 2 * AREA_17_R, 2 * AREA_17_R);
                        }
                            break;
                        case 51:
                        {
                            p.drawEllipse(airTrack.value().getTrajectoryCoord(0).x() - AREA_51_R,
                                          airTrack.value().getTrajectoryCoord(0).y() - AREA_51_R, 2 * AREA_51_R, 2 * AREA_51_R);
                        }
                            break;
                        case 53:
                        {
                            p.drawEllipse(airTrack.value().getTrajectoryCoord(0).x() - AREA_53_R,
                                          airTrack.value().getTrajectoryCoord(0).y() - AREA_53_R, 2 * AREA_53_R, 2 * AREA_53_R);
                        }
                            break;
                        default:
                            break;

                        }
                        p.restore();
                    }

                    /// Отрисовка траекторий
                    if(isVisibleOfTrajectories)
                    {
                        for(int j = 1; j < airTrack.value().getTrajectoryCount(); ++j)
                        {
                            /// Отрисовка местоположений
                            if(airTrack.value().getTGenTrc()->OGP == 1)
                            {
                                if(airTrack.value().getTrajectorySensCount(j) > 1.0)
                                    pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));   //Синий
                                else
                                    pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));        //Темно-синий
                            }else{
                                if(airTrack.value().getTrajectorySensCount(j) > 1.0)
                                    pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));   //Красный
                                else
                                    pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));        //Темно-красный
                            }

                            pen.setWidth(WDT_TRAJECTORY_POINT);
                            p.setPen(pen);
                            p.drawPoint(airTrack.value().getTrajectoryCoord(j));

                            /// Отрисовка траекторий
                            pen.setWidth(WDT_TRAJECTORY);
                            p.setPen(pen);
                            p.drawLine(airTrack.value().getTrajectoryCoord(j - 1), airTrack.value().getTrajectoryCoord(j));
                        }
                    }

                    /// Отрисовка трасс

                    p.scale(1.0 / getCSAbsScale(), 1.0 / getCSOrdScale());

                    /// Отрисовка лидеров групп
                    if(isVisibleOfGroupLeaders)
                    {
                        QString str = QString::number(airTrack.value().getTGenTrc()->grpInfo.num) + ", " +
                                      QString::number(airTrack.value().getTGenTrc()->grpInfo.trcCount);
                        p.drawText(airTrack.value().at(0) - QPoint(20, 5), str);
                    }

//                    /// Отрисовка выделения при выборе
//                    if(airTrack.key() == numberSelectedTrack)
//                    {
//                        p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
//                        p.drawPolygon(airTrack.value());
//                    }

//                    /// Отрисовка выделения при наведении
//                    if(airTrack.key() == numberHighlightedTrack)
//                    {
//                        p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
//                        p.drawPolygon(airTrack.value());
//                    }

                    if(airTrack.value().getTGenTrc()->OGP == 1)
                    {
                        pathImg += ANOTHERS;
                        if(airTrack.value().getTGenTrc()->sensCount > 1.0){
                            pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                            pathImg += MANY;
                        }else{
                            pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
                            pathImg += ONE;
                            }
                    }
                    else
                    {
                        pathImg += OUR;
                        if(airTrack.value().getTGenTrc()->sensCount > 1.0){
                            pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                            pathImg += MANY;
                        }else{
                            pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
                            pathImg += ONE;
                            }
                    }

                    pen.setWidth(WDT_ARROW);
                    p.setPen(pen);
                    //p.drawPolygon(airTrack.value());

                    /// Change code Block
                    p.save();
                    p.translate(airTrack.value().getTGenTrc()->y*getCSAbsScale(), airTrack.value().getTGenTrc()->x*(getCSOrdScale()));
                    p.rotate(5 - 180/M_PI*qAtan2(airTrack.value().getTGenTrc()->vX, airTrack.value().getTGenTrc()->vY));
                    //qDebug()<<"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC:"<<airTrack.value().getTGenTrc()->y*getCSAbsScale()<<airTrack.value().getTGenTrc()->x*(getCSOrdScale());

                    if(airTrack.key() != numberHighlightedTrack && airTrack.key() != numberSelectedTrack){
                        pxm.load(":/pic/foto/" + airTrack.value().getPathImg() + pathImg + ".png");
                        //pxm.load(":/pic/foto/SA_Etalon.png");
                    }else{
                        pxm.load(":/pic/foto/" + airTrack.value().getPathImg() + "_Click.png");
                        //pxm.load(":/pic/foto/SA_Click.png");
                    }
                    //qDebug()<<":/pic/foto/" + airTrack.value().getPathImg() + pathImg + ".png";
                    //qDebug()<<":/pic/foto/" + airTrack.value().getPathImg() + pathImg + ".png";
                    rct = QRect(-pxm.width()/12, -pxm.height()/12, pxm.width()/6, pxm.height()/6);
                    p.drawPixmap(rct, pxm);
                    //p.drawRect(-30, -30, 60, 60);
                    ///endChange Block code
                    p.restore();
                    p.scale(getCSAbsScale(), getCSOrdScale());
                }
            }
        }
    }

    /// --------------------------------------------------

    /// Поверхностные трассы

    if(surfaceTracks != nullptr && isVisibleOfSurfaceTracks)
    {

        QMap <int, Track>::const_iterator surfaceTrack = surfaceTracks->constBegin();
        for(; surfaceTrack != surfaceTracks->constEnd(); ++surfaceTrack)
        {
            QString pathImg = "";
            if(surfaceTrack.value().getTGenTrc() != nullptr)
            {
                if(!isVisibleOfGroupLeaders || surfaceTrack.value().getTGenTrc()->grpInfo.trcCount > 0)
                {
                    /// Отрисовка подвижных зон видимости
                    if(isVisibleOfAreas)
                    {
                        p.save();
                        pen.setColor(Qt::GlobalColor(CLR_LINE_MOVE_AREA));
                        pen.setWidth(WDT_AREA);
                        p.setPen(pen);
                        QColor clr(Qt::GlobalColor(CLR_MOVE_AREA));
                        clr.setAlpha(ALPHA_AREA);
                        p.setBrush(QBrush(clr));
                        switch(surfaceTrack.value().getTGenTrc()->TO)
                        {
                        case 17:
                        {
                            p.drawEllipse(surfaceTrack.value().getTrajectoryCoord(0).x() - AREA_17_R,
                                          surfaceTrack.value().getTrajectoryCoord(0).y() - AREA_17_R, 2 * AREA_17_R, 2 * AREA_17_R);
                        }
                            break;
                        case 51:
                        {
                            p.drawEllipse(surfaceTrack.value().getTrajectoryCoord(0).x() - AREA_51_R,
                                          surfaceTrack.value().getTrajectoryCoord(0).y() - AREA_51_R, 2 * AREA_51_R, 2 * AREA_51_R);
                        }
                            break;
                        case 53:
                        {
                            p.drawEllipse(surfaceTrack.value().getTrajectoryCoord(0).x() - AREA_53_R,
                                          surfaceTrack.value().getTrajectoryCoord(0).y() - AREA_53_R, 2 * AREA_53_R, 2 * AREA_53_R);
                        }
                            break;
                        default:
                            break;

                        }
                        p.restore();
                    }

                    /// Отрисовка траекторий
                    if(isVisibleOfTrajectories)
                    {
                        for(int j = 1; j < surfaceTrack.value().getTrajectoryCount(); ++j)
                        {
                            /// Отрисовка местоположений
                            if(surfaceTrack.value().getTGenTrc()->OGP == 1)
                            {
                                if(surfaceTrack.value().getTrajectorySensCount(j) > 1.0)
                                    pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                                else
                                    pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
                            }
                            else
                            {
                                if(surfaceTrack.value().getTrajectorySensCount(j) > 1.0)
                                    pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                                else
                                    pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
                            }
                            pen.setWidth(WDT_TRAJECTORY_POINT);
                            p.setPen(pen);
                            p.drawPoint(surfaceTrack.value().getTrajectoryCoord(j));

                            /// Отрисовка траекторий
                            pen.setWidth(WDT_TRAJECTORY);
                            p.setPen(pen);
                            p.drawLine(surfaceTrack.value().getTrajectoryCoord(j - 1), surfaceTrack.value().getTrajectoryCoord(j));
                        }
                    }

                    /// Отрисовка трасс

                    p.scale(1.0 / getCSAbsScale(), 1.0 / getCSOrdScale());

                    if(surfaceTrack.value().getTGenTrc()->OGP == 1)
                    {
                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0)
                            p.setPen(QPen(Qt::GlobalColor(CLR_TRUE_AL_TRACK)));
                        else
                            p.setPen(QPen(Qt::GlobalColor(CLR_AL_TRACK)));
                    }
                    else
                    {
                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0)
                            p.setPen(QPen(Qt::GlobalColor(CLR_TRUE_FR_TRACK)));
                        else
                            p.setPen(QPen(Qt::GlobalColor(CLR_FR_TRACK)));
                    }





                    p.drawPoint(surfaceTrack.value().at(0));

                    /// Отрисовка лидеров групп
                    if(isVisibleOfGroupLeaders)
                    {
                        QString str = QString::number(surfaceTrack.value().getTGenTrc()->grpInfo.num) + ", " +
                                QString::number(surfaceTrack.value().getTGenTrc()->grpInfo.trcCount);
                        p.drawText(surfaceTrack.value().at(0) - QPoint(20, 5), str);
                    }

//                    /// Отрисовка выделения при выборе
//                    if(surfaceTrack.key() == numberSelectedTrack - 1000)
//                    {
//                        p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
//                        p.drawPolygon(surfaceTrack.value());
//                    }

//                    /// Отрисовка выделения при наведении
//                    if(surfaceTrack.key() == numberHighlightedTrack - 1000)
//                    {
//                        p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
//                        p.drawPolygon(surfaceTrack.value());
//                    }

//                    if(surfaceTrack.value().getTGenTrc()->OGP == 1)
//                    {
//                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0)
//                            pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
//                        else
//                            pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
//                    }
//                    else
//                    {
//                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0)
//                            pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
//                        else
//                            pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
//                    }

                    if(surfaceTrack.value().getTGenTrc()->OGP == 1)
                    {
                        pathImg += ANOTHERS;
                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0){
                            pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                            pathImg += MANY;
                        }else{
                            pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
                            pathImg += ONE;
                            }
                    }
                    else
                    {
                        pathImg += OUR;
                        if(surfaceTrack.value().getTGenTrc()->sensCount > 1.0){
                            pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                            pathImg += MANY;
                        }else{
                            pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
                            pathImg += ONE;
                            }
                    }

                    pen.setWidth(WDT_ARROW);
                    p.setPen(pen);
                    //p.drawPolygon(surfaceTrack.value());

                    /// Change code Block
                    p.save();
                    p.translate(surfaceTrack.value().getTGenTrc()->y*getCSAbsScale(), surfaceTrack.value().getTGenTrc()->x*(getCSOrdScale()));
                    p.rotate(5 - 180/M_PI*qAtan2(surfaceTrack.value().getTGenTrc()->vX, surfaceTrack.value().getTGenTrc()->vY));
                    //qDebug()<<"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC:"<<airTrack.value().getTGenTrc()->y*getCSAbsScale()<<airTrack.value().getTGenTrc()->x*(getCSOrdScale());

                    if(surfaceTrack.key() != numberHighlightedTrack - 1000 && surfaceTrack.key() != numberSelectedTrack - 1000){
                        pxm.load(":/pic/foto/" + surfaceTrack.value().getPathImg() + pathImg + ".png");
                        //pxm.load(":/pic/foto/SA_Etalon.png");
                    }else{
                        pxm.load(":/pic/foto/" + surfaceTrack.value().getPathImg() + "_Click.png");
                        //pxm.load(":/pic/foto/SA_Click.png");
                    }


                    rct = QRect(-pxm.width()/12, -pxm.height()/12, pxm.width()/6, pxm.height()/6);
                    p.drawPixmap(rct, pxm);
                    //p.drawRect(-30, -30, 60, 60);
                    ///endChange Block code
                    p.restore();


                    p.scale(getCSAbsScale(), getCSOrdScale());
                }
            }
        }
    }

    p.end();
}

}
