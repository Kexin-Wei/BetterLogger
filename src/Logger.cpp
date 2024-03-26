#include "Logger.h"
#include <QDir>
#include <QTime>

namespace ultrast {
namespace infrastructure {
namespace utility {
Logger* Logger::m_instance = nullptr;

Logger* Logger::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Logger();
    }
    return m_instance;
}

Logger::Logger() :
    m_logPanelLevel(LEVEL_INFO)
{
    setSpdLogger();
}

Logger::~Logger()
{
}

void Logger::setSpdLogger()
{
    m_consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    m_consoleSink->set_pattern("[%T.%e][%^%l%$] %v");

    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QDir dir("logs/");
    if (!dir.exists())
        dir.mkpath(dir.absolutePath());
    QString fileName = "logs/" + dateTime + ".txt";
    m_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName.toStdString(), true);
    m_fileSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$] %v");

    // set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({ m_consoleSink, m_fileSink })));
    spdlog::set_level(spdlog::level::trace);
    m_consoleSink->set_level(spdlog::level::debug);
    m_fileSink->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    spdlog::debug("Logger -- The logger is initialized");
}

void Logger::updateSpdLoggerLevel()
{
    QString consoleLogLevel = "TRACE";
    QString fileLogLevel = "TRACE";
    QString logPanelLogLevel = "INFO";

    if (consoleLogLevel == "TRACE")
        m_consoleSink->set_level(spdlog::level::trace);
    else if (consoleLogLevel == "DEBUG")
        m_consoleSink->set_level(spdlog::level::debug);
    else if (consoleLogLevel == "INFO")
        m_consoleSink->set_level(spdlog::level::info);
    else if (consoleLogLevel == "WARN")
        m_consoleSink->set_level(spdlog::level::warn);
    else if (consoleLogLevel == "ERROR")
        m_consoleSink->set_level(spdlog::level::err);
    else if (consoleLogLevel == "CRITICAL")
        m_consoleSink->set_level(spdlog::level::critical);

    if (fileLogLevel == "TRACE")
        m_fileSink->set_level(spdlog::level::trace);
    else if (fileLogLevel == "DEBUG")
        m_fileSink->set_level(spdlog::level::debug);
    else if (fileLogLevel == "INFO")
        m_fileSink->set_level(spdlog::level::info);
    else if (fileLogLevel == "WARN")
        m_fileSink->set_level(spdlog::level::warn);
    else if (fileLogLevel == "ERROR")
        m_fileSink->set_level(spdlog::level::err);
    else if (fileLogLevel == "CRITICAL")
        m_fileSink->set_level(spdlog::level::critical);

    if (logPanelLogLevel == "TRACE")
        m_logPanelLevel = 0;
    else if (logPanelLogLevel == "DEBUG")
        m_logPanelLevel = 1;
    else if (logPanelLogLevel == "INFO")
        m_logPanelLevel = 2;
    else if (logPanelLogLevel == "WARN")
        m_logPanelLevel = 3;
    else if (logPanelLogLevel == "ERROR")
        m_logPanelLevel = 4;
    else if (logPanelLogLevel == "CRITICAL")
        m_logPanelLevel = 5;

    Logger::debug("Logger -- log levels are updated: file -- " + fileLogLevel + ", console -- " + consoleLogLevel + ", log panel -- " + logPanelLogLevel);
}

void Logger::log(int level, const QString& message, int updateIndex)
{
    if (level < m_logPanelLevel)
        return;
    QString logMessage = "[" + QTime::currentTime().toString() + "]";
    switch (level)
    {
    case LEVEL_TRACE:
        logMessage = logMessage + "[trace]";
        break;
    case LEVEL_DEBUG:
        logMessage = logMessage + "[debug]";
        break;
    case LEVEL_INFO:
        logMessage = logMessage + "[info]";
        break;
    case LEVEL_WARNING:
        logMessage = logMessage + "[warn]";
        break;
    case LEVEL_ERROR:
        logMessage = logMessage + "[error]";
        break;
    case LEVEL_CRITICAL:
        logMessage = logMessage + "[critical]";
        break;
    }
    logMessage = logMessage + " " + message;
    emit logged(level, logMessage, updateIndex);
}

void Logger::trace(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_TRACE, message, updateIndex);
    spdlog::trace(message.toStdString());
}

void Logger::debug(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_DEBUG, message, updateIndex);
    spdlog::debug(message.toStdString());
}

void Logger::info(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_INFO, message, updateIndex);
    spdlog::info(message.toStdString());
}

void Logger::warning(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_WARNING, message, updateIndex);
    spdlog::warn(message.toStdString());
}

void Logger::error(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_ERROR, message, updateIndex);
    spdlog::error(message.toStdString());
}

void Logger::critical(const QString& message, int updateIndex)
{
    Logger* logger = Logger::getInstance();
    logger->log(LEVEL_CRITICAL, message, updateIndex);
    spdlog::critical(message.toStdString());
}

int Logger::startTimer(const QString& name)
{
    Logger* logger = Logger::getInstance();
    int id = logger->m_timerNumber;
    logger->m_timerNumber++;
    QTime start_time = QTime::currentTime();
    QString message = "Timer: " + name + " has been started ";
    logger->trace(message);
    logger->m_loggerTimer.insert(id, name);
    logger->m_timerStartTime.insert(id, start_time);
    return id;
}

void Logger::endTimer(const int& id)
{
    Logger* logger = Logger::getInstance();
    QString& name = logger->m_loggerTimer[id];
    QTime start_time = logger->m_timerStartTime[id];
    QTime end_time = QTime::currentTime();
    int duration = -end_time.msecsTo(start_time);
    QString message = "Timer: " + name + " has been stopped. It has been " + QString::number(duration) + " milliseconds since its start";
    logger->trace(message);
}

}
}
}; // namespace ultrast
