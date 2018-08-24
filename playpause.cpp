#include "playpause.h"

namespace Visualizer
{

/// Класс виджета управления потоком вычислений
PlayPause::PlayPause(Painter *_painter, Status *_status, QWidget *_parent)
    :QWidget(_parent), painter(_painter), status(_status), mainThread(nullptr)
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
    pPlayPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
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
    cSleepTime = new QComboBox;
    cSleepTime->addItems(QStringList()  << "1000"
                                        << "500"
                                        << "250"
                                        << "100"
                                        << "50"
                                        << "25"
                                        << "10");
    hLayout->addWidget(cSleepTime);

    hLayout->addWidget(new QSplitter(this));

    this->setLayout(hLayout);

    createOfThread();
}

PlayPause::~PlayPause()
{
    delete pPlayPause;
    delete cSleepTime;

    /// Завершение имеющегося потока вычислений
    completeOfThread();
}

/// Перезапуск потока вычислений
void PlayPause::reStart()
{
    /// Возвращение флага приостановления потока вычислений
    bool isPaused;
    if(mainThread != nullptr)
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
    if(mainThread != nullptr)
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
    if(mainThread != nullptr)
        return;

    mainThread = new MainThread(painter, status, cSleepTime->currentText());
    QObject::connect(cSleepTime, SIGNAL(activated(QString)), mainThread, SLOT(setSleepTime(QString)));
    mainThread->start();
}

/// Завершение имеющегося потока вычислений
void PlayPause::completeOfThread()
{
    if(mainThread == nullptr)
        return;

    mainThread->complete();
    mainThread->wait();
    delete mainThread;
    mainThread = nullptr;
}

}
