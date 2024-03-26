#pragma once

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/spdlog.h"
#include <QObject>
#include <qmap>

#ifdef SPDLOG_TRACE
#undef SPDLOG_TRACE
#define SPDLOG_TRACE(logger, ...)                                                                   \
    if (logger->should_log(level::trace))                                                           \
    {                                                                                               \
        logger->trace("{}::{}()#{}: ", __FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__)); \
    }
#endif

namespace ultrast {
namespace infrastructure {
namespace utility {
class Logger : public QObject
{
    Q_OBJECT

public:
    enum Level
    {
        LEVEL_TRACE,
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARNING,
        LEVEL_ERROR,
        LEVEL_CRITICAL
    };

protected:
    Logger();
    virtual ~Logger();

public:
    static Logger* getInstance();
    void updateSpdLoggerLevel();

    /**
     * @brief record log messages
     *
     * @param message The message to be recorded
     * @param updateIndex Unique index for different log messages. When it's set to a non-zero variable, a new message with the same updateIndex value will overwrite the old one in log panel.
     */
    static void trace(const QString& message, int updateIndex = 0);
    static void debug(const QString& message, int updateIndex = 0);
    static void info(const QString& message, int updateIndex = 0);
    static void warning(const QString& message, int updateIndex = 0);
    static void error(const QString& message, int updateIndex = 0);
    static void critical(const QString& message, int updateIndex = 0);
    static int startTimer(const QString& name);
    static void endTimer(const int& id);

signals:
    void logged(int level, const QString& message, int updateIndex);

private:
    void setSpdLogger();
    static Logger* m_instance;
    int m_logPanelLevel;
    void log(int level, const QString& message, int updateIndex);
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_consoleSink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
    QMap<int, QString> m_loggerTimer;
    QMap<int, QTime> m_timerStartTime;
    int m_timerNumber = 1;
};

}
}
};
