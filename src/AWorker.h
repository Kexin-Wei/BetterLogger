#pragma once
#include "BLogger.h"
#include <QObject>

class AWorker : public QObject
{
    Q_OBJECT
public:
    explicit AWorker(QObject* parent = nullptr);
    ~AWorker();

public:
    void testPrintInHeader()
    {
        logger::info("testPrintInHeader");
        log_dev_info("testPrintInHeader - is this in a thread?");
    }
public slots:
    void doWork();
};