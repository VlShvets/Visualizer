#include "playpause.h"

namespace Visualizer
{

/// Класс виджета управления потоком вычислений
PlayPause::PlayPause(Painter *_painter, Status *_status, QWidget *_parent)
    :QWidget(_parent), painter(_painter), status(_status), mainThread(NULL)
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    hLayout->addWidget(new QSplitter(this));

    /// Кнопка "Начать с начала"
    QPushButton *pReStart = new QPushButton(this);
    pReStart->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    pReStart->setFixedWidth(50);
    connect(pReStart, SIGNAL(clicked()), this, SLOT(reStart()));
    hLayout->addWidget(pReStart);

    /// Кнопка "Play/Pause"
    pPlayPause = new QPushButton(this);
    pPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    pPlayPause->setFixedWidth(50);
    connect(pPlayPause, SIGNAL(clicked()), this, SLOT(stateChanged()));
    hLayout->addWidget(pPlayPause);

    /// Кнопка "Стоп"
    QPushButton *pStop = new QPushButton(this);
    pStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    pStop->setFixedWidth(50);
    connect(pStop, SIGNAL(clicked()), this, SLOT(stop()));
    hLayout->addWidget(pStop);

    hLayout->addWidget(new QSplitter(this));

    hLayout->addWidget(new QLabel(tr("Время между итерациями потока вычислений (в мс)"), this));

    /// Виджет регулирования времени между итерациями потока вычислений
    cDeltaTime = new QComboBox;
    cDeltaTime->addItems(QStringList()  << "1000"
                                        << "1500"
                                        << "2000"
                                        << "3000"
                                        << "5000"
                                        << "10000");
    hLayout->addWidget(cDeltaTime);

    hLayout->addWidget(new QSplitter(this));

    this->setLayout(hLayout);
}

PlayPause::~PlayPause()
{
    delete pPlayPause;
    delete cDeltaTime;

    /// Завершение имеющегося потока вычислений
    completeOfThread();
}

/// Перезапуск потока вычислений
void PlayPause::reStart()
{
    /// Возвращение флага приостановления потока вычислений
    bool isPaused;
    if(mainThread)
        isPaused = mainThread->isPaused();
    else
        isPaused = true;

    /// Завершение имеющегося потока вычислений
    completeOfThread();

    /// Создание нового потока вычислений
    createOfThread();

    /// Установление флага приостановления потока вычислений
    mainThread->setPause(isPaused);
}

/// Запуск и остановка потока вычислений
void PlayPause::stateChanged()
{
    /// Возвращение флага приостановления потока вычислений
    bool isPaused;
    if(mainThread)
        isPaused = mainThread->isPaused();
    else
        isPaused = true;

    /// Создание нового потока вычислений
    createOfThread();

    if(isPaused)
        pPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    else
        pPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    /// Установление флага приостановления потока вычислений
    mainThread->setPause(!isPaused);
}

/// Остановка потока вычислений
void PlayPause::stop()
{
    /// Завершение имеющегося потока вычислений
    completeOfThread();

    pPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

/// Создание нового потока вычислений
void PlayPause::createOfThread()
{
    if(!mainThread)
    {
        mainThread = new MainThread(painter, status, cDeltaTime->currentText());
        QObject::connect(cDeltaTime, SIGNAL(activated(QString)), mainThread, SLOT(setDeltaTime(QString)));
        mainThread->start();
    }
}

/// Завершение имеющегося потока вычислений
void PlayPause::completeOfThread()
{
    if(mainThread)
    {
        mainThread->complete();
        mainThread->wait();
        delete mainThread;
        mainThread = NULL;
    }
}

}
