#pragma once
#include "BLogger.h"
#include <QObject>

class AWorker : public QObject
{
    Q_OBJECT
public:
    explicit AWorker(QObject* parent = nullptr);
    void onStartTimer();
    ~AWorker();

signals:
    void triggerPrintInHeader();
    void startTimer();

public slots:
    void doWork();
    void testPrintInHeader()
    {
        logger::info("testPrintInHeader");
        log_dev_debug("testPrintInHeader - is this in a thread?");
    }
};