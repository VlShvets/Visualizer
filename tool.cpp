#include "Tool.h"

Tool::Tool(Painter *_painter) : painter(_painter)
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    hBoxLayout->addWidget(new QLabel, 1);

    QCheckBox *isEtalon = new QCheckBox(QObject::tr("Эталоны"));
    isEtalon->setChecked(true);
    QObject::connect(isEtalon, SIGNAL(clicked(bool)), painter, SLOT(setVisualEtalon(bool)));
    hBoxLayout->addWidget(isEtalon, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    QCheckBox *isTrack = new QCheckBox(QObject::tr("Трассы"));
    isTrack->setChecked(true);
    QObject::connect(isTrack, SIGNAL(clicked(bool)), painter, SLOT(setVisualTrack(bool)));
    hBoxLayout->addWidget(isTrack, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    QCheckBox *isGroup = new QCheckBox(QObject::tr("Лидеры групп"));
    isGroup->setChecked(false);
    QObject::connect(isGroup, SIGNAL(clicked(bool)), painter, SLOT(setVisualGroup(bool)));
    hBoxLayout->addWidget(isGroup, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    QCheckBox *isTrace = new QCheckBox(QObject::tr("Cлед"));
    isTrace->setChecked(false);
    QObject::connect(isTrace, SIGNAL(clicked(bool)), painter, SLOT(setVisualTrace(bool)));
    hBoxLayout->addWidget(isTrace, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    hBoxLayout->addWidget(new QLabel(QObject::tr("Время") + ":\t"));
    time = new QLabel;
    hBoxLayout->addWidget(time, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    hBoxLayout->addWidget(new QLabel(QObject::tr("Количество воздуных трасс") + ":"));
    countTrcAir = new QLCDNumber(3);
    hBoxLayout->addWidget(countTrcAir, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    hBoxLayout->addWidget(new QLabel(QObject::tr("Количество поверхностных трасс") + ":"));
    countTrcSurface = new QLCDNumber(3);
    hBoxLayout->addWidget(countTrcSurface, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    pbFixed = new QPushButton;
    pbFixed->setMinimumWidth(100);
    pbFixed->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    QObject::connect(pbFixed, SIGNAL(clicked()), painter, SLOT(setFixed()));
    QObject::connect(pbFixed, SIGNAL(clicked()), this, SLOT(changePushButtonFixedIcon()));
    hBoxLayout->addWidget(pbFixed, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    hBoxLayout->addWidget(new QLabel(QObject::tr("Макс. количество трасс") + ":"));
    maxCountTrc = new QLCDNumber(3);
    hBoxLayout->addWidget(maxCountTrc, 1);

    hBoxLayout->addWidget(new QLabel, 1);

    setLayout(hBoxLayout);
}

Tool::~Tool()
{
    delete time;
    delete countTrcAir;
    delete countTrcSurface;
    delete pbFixed;
    delete maxCountTrc;
}

void Tool::showInfo(TypeOfInfo _typeOfInfo, double _info)
{
    switch(_typeOfInfo)
    {
    case Time:
        time->setText(QString::number(_info));
        break;
    case TrackAir:
        countTrcAir->display((int) _info);
        if(maxCountTrc->value() < (int) _info + countTrcSurface->value())
            maxCountTrc->display((int) _info + countTrcSurface->value());
        break;
    case TrackSurface:
        countTrcSurface->display((int) _info);
        if(maxCountTrc->value() < countTrcAir->value() + (int) _info)
            maxCountTrc->display(countTrcAir->value() + (int) _info);
        break;
    default:
        break;
    }
}
