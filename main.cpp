// #define TEST_SPDLOG
#define TEST_BLOGGER
// #include <iostream>

#ifdef TEST_LOGGER
#include "src\Logger.h"
using Logger = ultrast::infrastructure::utility::Logger;
#endif

#ifdef TEST_SPDLOG
#include "spdlog\sinks\basic_file_sink.h"
#include "spdlog\sinks\stdout_color_sinks.h"
#include "spdlog\spdlog.h"
#include <QDateTime>
#include <QDir>
#include <QString>
namespace logger = spdlog;
#endif

#ifdef TEST_BLOGGER
#include "src\AWorker.h"
#include "src\BLogger.h"
#include <QApplication>
#include <QThread>
#endif

int main(int argc, char* argv[])
{
    // std::cout << "Hello, World!" << std::endl;
#ifdef TEST_LOGGER
    Logger::trace("Hello, World!");
#endif
    QApplication app(argc, argv);
    logger::init_logger();

    logger::debug("Logger -- The logger is initialized, {}, {}", 0, 2.3);
    logger::error("Hello, World!");
    logger::critical("User did something!");

    // logger::dev::info("I made a developer log!");
    SPDLOG_INFO("I made a developer log!");
    log_dev_error("I made a developer log using new macro!");

    QThread* thread = new QThread();
    AWorker* worker = new AWorker();
    worker->moveToThread(thread);
    thread->start();

    worker->testPrintInHeader();

    emit worker->triggerPrintInHeader();

    emit worker->startTimer();
    return app.exec();
}