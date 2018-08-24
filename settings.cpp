#include "settings.h"

namespace Visualizer
{

/// Класс виджета настроек отображения
Settings::Settings(Painter *_painter, QWidget *_parent)
    : QWidget(_parent), painter(_painter)
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);

    hBoxLayout->addWidget(new QSplitter(this));

    /// Опция отображения зон видимости
    QCheckBox *cAreas = new QCheckBox(tr("Зоны видимости"), this);
    cAreas->setChecked(true);
    connect(cAreas, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfAreas(bool)));
    hBoxLayout->addWidget(cAreas);

    /// Опция отображения эталонов
    QCheckBox *cEtalons = new QCheckBox(tr("Эталоны"), this);
    cEtalons->setChecked(true);
    connect(cEtalons, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfEtalons(bool)));
    hBoxLayout->addWidget(cEtalons);

    /// Опция отображения воздушных трасс
    QCheckBox *cAirTracks = new QCheckBox(tr("Воздушые трассы"), this);
    cAirTracks->setChecked(true);
    connect(cAirTracks, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfAirTracks(bool)));
    hBoxLayout->addWidget(cAirTracks);

    /// Опция отображения поверхностных трасс
    QCheckBox *cSurfaceTracks = new QCheckBox(tr("Поверхностные трассы"), this);
    cSurfaceTracks->setChecked(true);
    connect(cSurfaceTracks, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfSurfaceTracks(bool)));
    hBoxLayout->addWidget(cSurfaceTracks);

    /// Опция отображения лидеров групп
    QCheckBox *cGroupLeaders = new QCheckBox(tr("Лидеры групп"), this);
    cGroupLeaders->setChecked(false);
    connect(cGroupLeaders, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfGroupLeaders(bool)));
    hBoxLayout->addWidget(cGroupLeaders);

    /// Опция отображения следов трасс
    QCheckBox *cTrajectories = new QCheckBox(tr("Траектории"), this);
    cTrajectories->setChecked(false);
    connect(cTrajectories, SIGNAL(clicked(bool)), painter, SLOT(setVisibleOfTrajectories(bool)));
    hBoxLayout->addWidget(cTrajectories);

    hBoxLayout->addWidget(new QSplitter(this));

    setLayout(hBoxLayout);
}

Settings::~Settings()
{
}

}
