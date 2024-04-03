#include "AWorker.h"
#include <QTimer>

AWorker::AWorker(QObject* parent) :
    QObject(parent)
{
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &AWorker::doWork);
    timer->start();
}

AWorker::~AWorker()
{
}

void AWorker::doWork()
{
    logger::info("doWork");
    log_dev_info("doWork - is this in a thread?");
}
