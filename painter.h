#ifndef PAINTER_H
#define PAINTER_H

#include "aboutetalon.h"
#include "abouttrack.h"
#include "graphheight.h"

namespace Visualizer
{

class AboutEtalon;
class AboutTrack;
class GraphHeight;

/// Класс виджета отрисовки эталонов и трасс
class Painter : public Grapher2D
{
    Q_OBJECT

public:
    explicit        Painter(AboutEtalon *_aboutEtalon, AboutTrack *_aboutTrack, GraphHeight *_graphHeight,
                            QWidget *_parent = 0);
    ~Painter();

    /// Установка стационарных объектов
//    void            setStationary();

    /// Установка эталонов
    void            setEtalons(TPubEtalon *_tPubEtalon, double _time);

    /// Установка трасс
    void            setTracks(PTPV_TGenTrc *_tGenTrc);

    /// Очищение отрисовки
    void            clearing();

public slots:
    /// Установка флага отображения зон видимости
    inline void     setVisibleOfAreas(bool _isVisibleOfAreas);

    /// Установка флага отображения эталонов
    inline void     setVisibleOfEtalons(bool _isVisibleOfEtalons);

    /// Установка флага отображения воздушных трасс
    inline void     setVisibleOfAirTracks(bool _isVisibleOfAirTracks);

    /// Установка флага отображения поверхностных трасс
    inline void     setVisibleOfSurfaceTracks(bool _isVisibleOfSurfaceTracks);

    /// Установка флага отображения лидеров групп
    inline void     setVisibleOfGroupLeaders(bool _isVisibleOfGroupLeaders);

    /// Установка флага отображения следов трасс
    inline void     setVisibleOfTrackTraces(bool _isVisibleOfTrackTraces);

protected:
    /// События нажатия кнопки мыши
    void            mousePressEvent(QMouseEvent * _mEvent);

    /// События перемещения мыши
    void            mouseMoveEvent(QMouseEvent * _mEvent);

    /// События отпускания кнопки мыши
    void            mouseReleaseEvent(QMouseEvent * _mEvent);

    /// События колеса мыши
    void            wheelEvent(QWheelEvent * _wEvent);

    /// Обновление отрисокви
    void            timerEvent(QTimerEvent *);

    /// Отрисовка эталонов и трасс
    void            paintEvent(QPaintEvent * _pEvent);

private:
    /// Определение номера эталона под курсором мыши
    int indexOfEtalons(int _posX, int _posY);

    /// Определение номера трассы под курсором мыши
    int indexOfTracks(int _posX, int _posY);

    /// --------------------------------------------------
    /// Указатели на объекты классов
    /// --------------------------------------------------

    AboutEtalon     *aboutEtalon;   /// Виджет информации об эталоне
    AboutTrack      *aboutTrack;    /// Виджет информации о трассе
    GraphHeight     *graphHeight;   /// Виджет отрисовки графика высот

    /// --------------------------------------------------
    /// Переменные
    /// --------------------------------------------------

    int numberHighlightedEtalon;    /// Номер выделенного эталона
    int numberSelectedEtalon;       /// Номер выбранного эталона

    int numberHighlightedTrack;     /// Номер выделенной цели
    int numberSelectedTrack;        /// Номер выбранной цели

    bool bFixed;                    /// Флаг фиксации изображения на экране

    /// Указатели на словари параметров ЗКВ, эталонов и трасс
//    const QMap <int, Stationary>    *stationary;    /// Словарь стационарных объектов   <номер, структура параметров>
    const QMap <int, Etalon>        *etalons;       /// Словарь эталонов                <номер, структура параметров>
    const QMap <int, Track>         *airTracks;     /// Словарь воздушных трасс         <номер, структура параметров>
    const QMap <int, Track>         *surfaceTrack;  /// Словарь поверхностных трасс     <номер, структура параметров>

    /// Флаги отображения
    bool    isVisibleOfAreas;           /// Флаг отображения зон видимостиы
    bool    isVisibleOfEtalons;         /// Флаг отображения эталонов
    bool    isVisibleOfAirTracks;       /// Флаг отображения воздушных трасс
    bool    isVisibleOfSurfaceTracks;   /// Флаг отображения поверхностных трасс
    bool    isVisibleOfGroupLeaders;    /// Флаг отображения лидеров групп
    bool    isVisibleOfTrackTraces;     /// Флаг отображения следов трасс
};

/// Установка флага отображения зон видимости
void Painter::setVisibleOfAreas(bool _isVisibleOfAreas)
{
    isVisibleOfAreas = _isVisibleOfAreas;
}

/// Установка флага отображения эталонов
void Painter::setVisibleOfEtalons(bool _isVisibleOfEtalons)
{
    isVisibleOfEtalons = _isVisibleOfEtalons;
}

/// Установка флага отображения воздушных трасс
void Painter::setVisibleOfAirTracks(bool _isVisibleOfAirTracks)
{
    isVisibleOfAirTracks = _isVisibleOfAirTracks;
}

/// Установка флага отображения поверхностных трасс
void Painter::setVisibleOfSurfaceTracks(bool _isVisibleOfSurfaceTracks)
{
    isVisibleOfSurfaceTracks = _isVisibleOfSurfaceTracks;
}

/// Установка флага отображения лидеров групп
void Painter::setVisibleOfGroupLeaders(bool _isVisibleOfGroupLeaders)
{
    isVisibleOfGroupLeaders = _isVisibleOfGroupLeaders;
}

/// Установка флага отображения следов трасс
void Painter::setVisibleOfTrackTraces(bool _isVisibleOfTrackTraces)
{
    isVisibleOfTrackTraces = _isVisibleOfTrackTraces;
}

}

#endif // PAINTER_H
