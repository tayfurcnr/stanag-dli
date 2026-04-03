#ifndef DLI_I_LOGGER_HPP
#define DLI_I_LOGGER_HPP

#include <string>
#include <iostream>
#include <memory>

namespace dli {

/**
 * @brief Severity levels for SDK logging.
 */
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

/**
 * @brief Abstract interface for SDK logging.
 * 
 * Implement this interface to redirect DLI SDK logs to your own logging system
 * (e.g., spdlog, ROS2 logs, or a file).
 */
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(LogLevel level, const std::string& message) = 0;
};

/**
 * @brief Default console-based logger implementation.
 */
class ConsoleLogger : public ILogger {
public:
    void log(LogLevel level, const std::string& message) override {
        const char* prefix = "[DLI] ";
        switch (level) {
            case LogLevel::DEBUG:   prefix = "[DLI:DEBUG] "; break;
            case LogLevel::INFO:    prefix = "[DLI:INFO] ";  break;
            case LogLevel::WARNING: prefix = "[DLI:WARN] ";  break;
            case LogLevel::ERROR:   prefix = "[DLI:ERROR] "; break;
        }
        std::cout << prefix << message << std::endl;
    }
};

/**
 * @brief Global logger access point for the SDK.
 */
class Logger {
public:
    static void set(std::shared_ptr<ILogger> logger) {
        instance() = std::move(logger);
    }

    static void debug(const std::string& msg)   { log(LogLevel::DEBUG, msg); }
    static void info(const std::string& msg)    { log(LogLevel::INFO, msg); }
    static void warn(const std::string& msg)    { log(LogLevel::WARNING, msg); }
    static void error(const std::string& msg)   { log(LogLevel::ERROR, msg); }

private:
    static void log(LogLevel level, const std::string& msg) {
        if (instance()) {
            instance()->log(level, msg);
        }
    }

    static std::shared_ptr<ILogger>& instance() {
        static std::shared_ptr<ILogger> s_instance = std::make_shared<ConsoleLogger>();
        return s_instance;
    }
};

} // namespace dli

#endif // DLI_I_LOGGER_HPP
