#pragma once
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/spdlog.h"
#include <QDateTime>
#include <QDir>
#include <QString>

#define log_dev_trace(...) SPDLOG_LOGGER_TRACE(spdlog::default_logger_raw(), __VA_ARGS__)
#define log_dev_debug(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define log_dev_info(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define log_dev_warning(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define log_dev_error(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)
#define log_dev_critical(...) SPDLOG_LOGGER_CRITICAL(spdlog::default_logger_raw(), __VA_ARGS__)

namespace spdlog {
inline void init_logger()
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QDir dir("logs/");
    if (!dir.exists())
        dir.mkpath(dir.absolutePath());
    QString fileName = "logs/" + dateTime + ".log";
    QString devFileName = "logs/" + dateTime + "_dev.log";

    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("[%T.%e][%^%l%$] %v");

    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName.toStdString(), true);
    fileSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$] %v");

    auto developerSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(devFileName.toStdString(), true);
    developerSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$][thread %t][file:%s - line:%#] %v");

    // set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({ consoleSink, fileSink, developerSink })));
    spdlog::set_level(spdlog::level::trace);
    consoleSink->set_level(spdlog::level::debug);
    fileSink->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
};
}
namespace logger = spdlog;
