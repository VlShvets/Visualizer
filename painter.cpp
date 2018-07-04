#include "Painter.h"

Painter::Painter(QDockWidget *_aboutEtalon, QDockWidget *_aboutTrack, QDockWidget *_graphHeight) :
    numberHighlightedEtalon(-1), numberSelectedEtalon(-1),
    numberHighlightedTrack(-1), numberSelectedTrack(-1),
    bFixed(false), aboutEtalon(_aboutEtalon), aboutTrack(_aboutTrack), graphHeight(_graphHeight)
{
    setCSZoom(GEN_ZOOM);
    setCSAbsMeasure(XY_MEASURE);
    setCSOrdMeasure(XY_MEASURE);
    setMouseTracking(true);     /// Определение координат указателя мыши
}

Painter::~Painter()
{
}

void Painter::setEtalons(TPubEtalon *_tPubEtalon, double _time)
{
    /// Проверка на наличие флага о фиксации отображения
    if(bFixed)
        return;

    /// Определение колличества заполненых формуляров
    int size = 0;
    for(int i = BIUS_A100::UGEN_TRC_MAX; i > 0; --i)
    {
        if(_tPubEtalon[i].visual == BIUS_A100::_PTPV_::EU_YES)
        {
            size = i + 1;
            break;
        }
    }

    /// Обновление информации об эталонах
    for(int i = 0; i < etalons.count(); ++i)
        etalons[i].setTPubEtalon(&_tPubEtalon[i], _time);

    /// Добавление новых эталонов
    for(int i = etalons.count(); i < size; ++i)
        etalons.push_back(Etalon(&_tPubEtalon[i], _time));

    /// Удаление старых эталонов
    while(etalons.count() > size && !etalons.isEmpty())
        etalons.removeLast();

    /// Перерисовска символов эталонов
    for(int i = 0; i < etalons.count(); ++i)
        etalons[i].setSymbol();

    /// Обновление номера выделенного эталона
    if(getMCursorShape() != Qt::ClosedHandCursor)
    {
        numberHighlightedEtalon = indexOfEtalons(getMPosNoClick().x(), getMPosNoClick().y());

        /// Изменение вида курсора мыши
        if(numberHighlightedEtalon != -1 || numberHighlightedTrack != -1)
            setCursor(Qt::CursorShape(Qt::PointingHandCursor));  
        else
            setCursor(Qt::CursorShape(getMCursorShape()));
    }

    /// Проверка существования выбранного эталона
    if(numberSelectedEtalon != -1 && numberSelectedEtalon < etalons.count())
    {
        /// Обновление отображения информации о выбранном эталоне
        ((AboutEtalon *)aboutEtalon->widget())->setInfoAboutEtalon(&etalons[numberSelectedEtalon], numberSelectedEtalon);
        ((GraphHeight *)graphHeight->widget())->setEtalon(&etalons[numberSelectedEtalon]);
    }
    else
    {
        ((AboutEtalon *)aboutEtalon->widget())->resetInfoAboutEtalon();
        ((GraphHeight *)graphHeight->widget())->delEtalon();
    }

    repaint();
}

void Painter::setTracks(PTPV_TGenTrc *_tGenTrc)
{
    /// Проверка на наличие флага о фиксации отображения
    if(bFixed)
        return;

    /// Определение колличества заполненых формуляров
    int size = 0;
    for(int i = BIUS_A100::UGEN_TRC_MAX; i > 0; --i)
    {
        if(_tGenTrc[i].tXYUpdate != 0)
        {
            size = i + 1;
            break;
        }
    }

    /// Обновление информации об целях
    for(int i = 0; i < tracks.count(); ++i)
        tracks[i].setTGenTrc(&_tGenTrc[i]);

    /// Добавление новых целей
    for(int i = tracks.count(); i < size; ++i)
        tracks.push_back(Track(&_tGenTrc[i]));

    /// Удаление старых целей
    while(tracks.count() > size && !tracks.isEmpty())
        tracks.removeLast();

    /// Изменение символов целей
    for(int i = 0; i < tracks.count(); ++i)
        tracks[i].setSymbol();

    /// Обновление номера выделенной цели
    if(getMCursorShape() != Qt::ClosedHandCursor)
    {
        numberHighlightedTrack = indexOfTracks(getMPosNoClick().x(), getMPosNoClick().y());

        /// Изменение вида курсора мыши
        if(numberHighlightedEtalon != -1 || numberHighlightedTrack != -1)
            setCursor(Qt::CursorShape(Qt::PointingHandCursor));
        else
            setCursor(Qt::CursorShape(getMCursorShape()));
    }

    /// Проверка существования выбранной цели
    if(numberSelectedTrack != -1 && numberSelectedTrack < tracks.count())
    {
        /// Обновление отображения информации о выбранной цели
        ((AboutTrack *)aboutTrack->widget())->setInfoAboutTrack(&tracks[numberSelectedTrack], numberSelectedTrack);
        ((GraphHeight *)graphHeight->widget())->setTrack(&tracks[numberSelectedTrack]);
    }
    else
    {
        ((AboutTrack *)aboutTrack->widget())->resetInfoAboutTrack();
        ((GraphHeight *)graphHeight->widget())->delTrack();
    }

    repaint();
}

void Painter::mousePressEvent(QMouseEvent *_mEvent)
{
    Grapher2D::mousePressEvent(_mEvent);

    if(numberHighlightedEtalon == -1 && numberHighlightedTrack == -1)
    {
        setMCursorShape(Qt::ClosedHandCursor);
        setCursor(Qt::CursorShape(getMCursorShape()));
    }
}

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

void Painter::mouseReleaseEvent(QMouseEvent *_mEvent)
{
    Grapher2D::mouseReleaseEvent(_mEvent);

    /// Выбор эталона
    if(numberHighlightedEtalon != -1)
    {
        if(numberHighlightedEtalon != numberSelectedEtalon)
        {
            numberSelectedEtalon = numberHighlightedEtalon;

            ((AboutEtalon *)aboutEtalon->widget())->setInfoAboutEtalon(&etalons[numberSelectedEtalon], numberSelectedEtalon);
            ((GraphHeight *)graphHeight->widget())->setEtalon(&etalons[numberSelectedEtalon]);
        }
        aboutEtalon->setVisible(true);
//        graphHeight->setVisible(true);
    }

    /// Выбор цели
    if(numberHighlightedTrack != -1)
    {
        if(numberHighlightedTrack != numberSelectedTrack)
        {
            numberSelectedTrack = numberHighlightedTrack;

            ((AboutTrack *)aboutTrack->widget())->setInfoAboutTrack(&tracks[numberSelectedTrack], numberSelectedTrack);
            ((GraphHeight *)graphHeight->widget())->setTrack(&tracks[numberSelectedTrack]);
        }
        aboutTrack->setVisible(true);
//        graphHeight->setVisible(true);
    }

    repaint();
}

void Painter::wheelEvent(QWheelEvent *_wEvent)
{
    Grapher2D::wheelEvent(_wEvent);

    /// Изменение технического масштаба символов
    Target::setScale(getCSAbsScale());

    /// Перерисовска символов эталонов
    for(int i = 0; i < etalons.count(); ++i)
        etalons[i].setSymbol();

    /// Изменение символов целей
    for(int i = 0; i < tracks.count(); ++i)
        tracks[i].setSymbol();

    repaint();
}

int Painter::indexOfEtalons(int _posX, int _posY)
{
    int index = 0;

    for(;
        index < etalons.count() && !etalons[index].containsPoint(QPoint(_posX - width() / 2 - getCSAbsShift(),
                                                                        _posY - height() / 2 - getCSOrdShift()), Qt::WindingFill);
        ++index) {}

    if(index != etalons.count())
        return index;
    else
        return -1;
}

int Painter::indexOfTracks(int _posX, int _posY)
{
    int index = 0;

    for(;
        index < tracks.count() && !tracks[index].containsPoint(QPoint(_posX - width() / 2 - getCSAbsShift(),
                                                                        _posY - height() / 2 - getCSOrdShift()), Qt::WindingFill);
        ++index) {}

    if(index != tracks.count())
        return index;
    else
        return -1;
}

void Painter::paintEvent(QPaintEvent *_pEvent)
{
    QPainter p(this);
    p.translate(getCSAbsTranslate(), getCSOrdTranslate());
    p.scale(getCSAbsScale(), getCSOrdScale());

    /// Карта
    QPixmap map(":/map/0.jpg");
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
    rect.setRect(CC_AL_2_X - 0.5 * pic.width() / getCSAbsScale(), - CC_AL_2_Y + 0.5 * pic.height() / getCSOrdScale(), pic.width() / getCSAbsScale(), pic.height() / -getCSOrdScale());
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

    /// Зоны видимости

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

    /// --------------------------------------------------

    /// Эталоны

    for(int i = 1; i < etalons.count(); ++i)
    {
        if(etalons[i].getTPubEtalon() != NULL)
        {
            /// Отрисовка истории
            for(int j = 1; j < etalons[i].getCountPoints(); ++j)
            {
                /// Отрисовка местоположений
                pen.setColor(Qt::GlobalColor(CLR_ETALON));
                pen.setWidth(WDT_MEMORY_POINT);
                p.setPen(pen);
                p.drawPoint(etalons[i].getMemoryCoord(j));

                /// Отрисовка траекторий
                pen.setWidth(WDT_PATH);
                p.setPen(pen);
                p.drawLine(etalons[i].getMemoryCoord(j - 1), etalons[i].getMemoryCoord(j));
            }

            /// Отрисовка эталонов

            p.scale(1.0 / getCSAbsScale(), 1.0 / getCSOrdScale());

            /// Отрисовка выделения при выборе
            if(i == numberSelectedEtalon)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
                p.drawPoint(etalons[i].at(0));
            }

            /// Отрисовка выделения при наведении
            if(i == numberHighlightedEtalon)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
                p.drawPoint(etalons[i].at(0));
            }

            p.setPen(QPen(Qt::GlobalColor(CLR_ETALON), WDT_LAST_POINT));
            p.drawPoint(etalons[i].at(0));

            /// Отрисовка векторов скоростей

            /// Отрисовка выделения при выборе
            if(i == numberSelectedEtalon)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
                p.drawPolygon(etalons[i]);
            }

            /// Отрисовка выделения при наведении
            if(i == numberHighlightedEtalon)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
                p.drawPolygon(etalons[i]);
            }

            p.setPen(QPen(Qt::GlobalColor(CLR_ETALON), WDT_ARROW));
            p.drawPolygon(etalons[i]);

            p.scale(getCSAbsScale(), getCSOrdScale());
        }
    }

    /// --------------------------------------------------

    /// Трассы

    for(int i = 0; i < tracks.count(); ++i)
    {
        if(tracks[i].getTGenTrc() != NULL)
        {
            /// Отрисовка истории
            for(int j = 1; j < tracks[i].getCountPoints(); ++j)
            {
                /// Отрисовка местоположений
                if(tracks[i].getTGenTrc()->OGP == 1)
                {
                    if(tracks[i].getMemorySensCount(j) > 1.0)
                        pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                    else
                        pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
                }
                else
                {
                    if(tracks[i].getMemorySensCount(j) > 1.0)
                        pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                    else
                        pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
                }
                pen.setWidth(WDT_MEMORY_POINT);
                p.setPen(pen);
                p.drawPoint(tracks[i].getMemoryCoord(j));

                /// Отрисовка траекторий
                pen.setWidth(WDT_PATH);
                p.setPen(pen);
                p.drawLine(tracks[i].getMemoryCoord(j - 1), tracks[i].getMemoryCoord(j));
            }

            /// Отрисовка зон видимости
            p.save();
            pen.setColor(Qt::GlobalColor(CLR_LINE_MOVE_AREA));
            pen.setWidth(WDT_AREA);
            p.setPen(pen);
            QColor clr(Qt::GlobalColor(CLR_MOVE_AREA));
            clr.setAlpha(ALPHA_AREA);
            p.setBrush(QBrush(clr));
            switch(tracks[i].getTGenTrc()->TVO)
            {
            case 17:
                p.drawEllipse(tracks[i].getMemoryCoord(0).x() - AREA_17_R, tracks[i].getMemoryCoord(0).y() - AREA_17_R, 2 * AREA_17_R, 2 * AREA_17_R);
                break;
            case 51:
                p.drawEllipse(tracks[i].getMemoryCoord(0).x() - AREA_51_R, tracks[i].getMemoryCoord(0).y() - AREA_51_R, 2 * AREA_51_R, 2 * AREA_51_R);
                break;
            case 53:
                p.drawEllipse(tracks[i].getMemoryCoord(0).x() - AREA_53_R, tracks[i].getMemoryCoord(0).y() - AREA_53_R, 2 * AREA_53_R, 2 * AREA_53_R);
                break;
            default:
                break;

            }
            p.restore();

            /// Отрисовка трасс

            p.scale(1.0 / getCSAbsScale(), 1.0 / getCSOrdScale());

            /// Отрисовка выделения при выборе
            if(i == numberSelectedTrack)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
                p.drawPoint(tracks[i].at(0));
            }

            /// Отрисовка выделения при наведении
            if(i == numberHighlightedTrack)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
                p.drawPoint(tracks[i].at(0));
            }

            if(tracks[i].getTGenTrc()->sensCount > 1.0)
                p.setPen(QPen(Qt::GlobalColor(CLR_TRUE_FR_TRACK), WDT_LAST_POINT));
            else
                p.setPen(QPen(Qt::GlobalColor(CLR_FR_TRACK), WDT_LAST_POINT));
            p.drawPoint(tracks[i].at(0));

            if(Track::isGroup())
            {
                QString str = QString::number(tracks[i].getTGenTrc()->grpInfo.num) + ", " + QString::number(tracks[i].getTGenTrc()->grpInfo.trcCount);
                p.drawText(tracks[i].at(0) - QPoint(20, 5), str);
            }

            /// Отрисовка выделения при выборе
            if(i == numberSelectedTrack)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_SELECT), WDT_SELECT));
                p.drawPolygon(tracks[i]);
            }

            /// Отрисовка выделения при наведении
            if(i == numberHighlightedTrack)
            {
                p.setPen(QPen(Qt::GlobalColor(CLR_HIGHLIGHT), WDT_HIGHLIGHT));
                p.drawPolygon(tracks[i]);
            }

            if(tracks[i].getTGenTrc()->OGP == 1)
            {
                if(tracks[i].getTGenTrc()->sensCount > 1.0)
                    pen.setColor(Qt::GlobalColor(CLR_TRUE_AL_TRACK));
                else
                    pen.setColor(Qt::GlobalColor(CLR_AL_TRACK));
            }
            else
            {
                if(tracks[i].getTGenTrc()->sensCount > 1.0)
                    pen.setColor(Qt::GlobalColor(CLR_TRUE_FR_TRACK));
                else
                    pen.setColor(Qt::GlobalColor(CLR_FR_TRACK));
            }
            pen.setWidth(WDT_ARROW);
            p.setPen(pen);
            p.drawPolygon(tracks[i]);

            p.scale(getCSAbsScale(), getCSOrdScale());
        }
    }

    p.end();
}
