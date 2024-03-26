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
#include "src\BLogger.h"
#endif

int main()
{
    // std::cout << "Hello, World!" << std::endl;
#ifdef TEST_LOGGER
    Logger::trace("Hello, World!");
#endif

    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QDir dir("logs/");
    if (!dir.exists())
        dir.mkpath(dir.absolutePath());
    QString fileName = "logs/" + dateTime + ".log";
    QString devFileName = "logs/" + dateTime + "_dev.log";

    auto consoleSink = std::make_shared<logger::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("[%T.%e][%^%l%$] %v");

    auto fileSink = std::make_shared<logger::sinks::basic_file_sink_mt>(fileName.toStdString(), true);
    fileSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$] %v");

    auto developerSink = std::make_shared<logger::sinks::basic_file_sink_mt>(devFileName.toStdString(), true);
    developerSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$][thread %t][file:%s - line:%#] %v");

    // set multi_sink logger as default logger
    logger::set_default_logger(std::make_shared<logger::logger>("multi_sink", logger::sinks_init_list({ consoleSink, fileSink, developerSink })));
    logger::set_level(logger::level::trace);
    consoleSink->set_level(logger::level::debug);
    fileSink->set_level(logger::level::trace);
    logger::flush_on(logger::level::trace);

    logger::debug("Logger -- The logger is initialized, {}, {}", 0, 2.3);

    logger::error("Hello, World!");
    logger::critical("User did something!");

    // logger::dev::info("I made a developer log!");
    SPDLOG_INFO("I made a developer log!");
    log_dev_error("I made a developer log using new macro!");
    return 0;
}