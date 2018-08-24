#include "status.h"

namespace Visualizer
{

/// Класс виджета отображения текущего состояния потока вычислений
Status::Status()
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);

    hBoxLayout->addWidget(new QSplitter(this));

    hBoxLayout->addWidget(new QLabel(tr("Время"), this));
    time = new QLCDNumber(5, this);
    time->setSegmentStyle(QLCDNumber::Flat);
    hBoxLayout->addWidget(time);

    hBoxLayout->addWidget(new QSplitter(this));

    hBoxLayout->addWidget(new QLabel(tr("Количество воздушных трасс"), this));
    countAirTracks = new QLCDNumber(3, this);
    countAirTracks->setSegmentStyle(QLCDNumber::Flat);
    hBoxLayout->addWidget(countAirTracks);

    hBoxLayout->addWidget(new QSplitter(this));

    hBoxLayout->addWidget(new QLabel(tr("Количество поверхностных трасс"), this));
    countSurfaceTracks = new QLCDNumber(3, this);
    countSurfaceTracks->setSegmentStyle(QLCDNumber::Flat);
    hBoxLayout->addWidget(countSurfaceTracks);

    hBoxLayout->addWidget(new QSplitter(this));

    hBoxLayout->addWidget(new QLabel(tr("Максимальное количество трасс"), this));
    maxCountTracks = new QLCDNumber(3);
    maxCountTracks->setSegmentStyle(QLCDNumber::Flat);
    hBoxLayout->addWidget(maxCountTracks);

    hBoxLayout->addWidget(new QSplitter(this));

    setLayout(hBoxLayout);
}

Status::~Status()
{
    delete time;
    delete countAirTracks;
    delete countSurfaceTracks;
    delete maxCountTracks;
}

/// Отображение полученной информации в строке состояния
void Status::showInfo(TypeOfInfo _typeOfInfo, const float _info)
{
    switch(_typeOfInfo)
    {
    case Time:
        time->display((int) _info);
        break;
    case AirTrack:
        countAirTracks->display((int) _info);
        if(maxCountTracks->value() < (int) _info + countSurfaceTracks->value())
            maxCountTracks->display((int) _info + countSurfaceTracks->value());
        break;
    case SurfaceTrack:
        countSurfaceTracks->display((int) _info);
        if(maxCountTracks->value() < countAirTracks->value() + (int) _info)
            maxCountTracks->display(countAirTracks->value() + (int) _info);
        break;
    default:
        break;
    }
}

/// Очищение виджета отображения текущего состояния потока вычислений
void Status::clearing()
{
    time->display(0);
    countAirTracks->display(0);
    countSurfaceTracks->display(0);
    maxCountTracks->display(0);
}

}
