#include "utilities/logger.hpp"

namespace parbati {
// source/utilities/logger.cpp

Logger::~Logger() {
    if (initialized_) {shutdown();}
}

Logger& Logger::get_instance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(
    const std::string& logDir,
    LogLevel consoleLevel, LogLevel fileLevel,
    size_t maxFileSize, size_t maxFiles)
{
    if (initialized_) {return;}

    try {
        // Create log directory if it doesn't exist
        std::filesystem::create_directories(logDir);

        // Create sinks
        _console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _console_sink->set_level(to_spd_log_level(consoleLevel));

        std::string logFilePath = logDir + "/himalayan_landscapes.log";
        _file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            logFilePath, maxFileSize, maxFiles);
        _file_sink->set_level(to_spd_log_level(fileLevel));

        // Create default logger
        auto defaultLogger = std::make_shared<spdlog::logger>("default",
            spdlog::sinks_init_list{_console_sink, _file_sink});
        defaultLogger->set_level(spdlog::level::trace); // Accept all messages

        // Set as default and register
        spdlog::set_default_logger(defaultLogger);
        _loggers["default"] = defaultLogger;

        // Configure pattern
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%s:%#] %v");

        // Set flush policy
        spdlog::flush_every(std::chrono::seconds(3));

        initialized_ = true;

        // Log initialization success
        LOG_INFO(get_logger("core"), "Logging system initialized");
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}

std::shared_ptr<spdlog::logger> Logger::get_logger(const std::string& name) {
    // Return existing logger if available
    auto it = _loggers.find(name);
    if (it != _loggers.end()) {return it->second;}

    // Create new logger if system is initialized
    if (initialized_) {
        try {
            auto logger =
                std::make_shared<spdlog::logger>(
                    name, spdlog::sinks_init_list{_console_sink, _file_sink});
            logger->set_level(spdlog::level::trace);
            _loggers[name] = logger;

            LOG_DEBUG(get_logger("core"), "Created logger: {}", name);
            return logger;
        }
        catch (const spdlog::spdlog_ex& ex) {
            LOG_ERROR(get_logger("core"), "Failed to create logger {}: {}", name, ex.what());
        }
    }

    // Fallback to default logger
    return spdlog::default_logger();
}

void Logger::set_console_level(LogLevel level) {
    if (initialized_ && _console_sink) {
        _console_sink->set_level(to_spd_log_level(level));
        LOG_DEBUG(get_logger("core"), "Console log level set to {}",
                 static_cast<int>(level));
    }
}

void Logger::set_file_level(LogLevel level) {
    if (initialized_ && _file_sink) {
        _file_sink->set_level(to_spd_log_level(level));
        LOG_DEBUG(get_logger("core"), "File log level set to {}",
                 static_cast<int>(level));
    }
}

void Logger::set_logger_level(const std::string& name, LogLevel level) {
    auto logger = get_logger(name);
    if (logger) {
        logger->set_level(to_spd_log_level(level));
        LOG_DEBUG(get_logger("core"), "Logger '{}' level set to {}",
                 name, static_cast<int>(level));
    }
}

spdlog::level::level_enum Logger::to_spd_log_level(LogLevel level) {
    switch (level) {
        case LogLevel::Trace:    return spdlog::level::trace;
        case LogLevel::Debug:    return spdlog::level::debug;
        case LogLevel::Info:     return spdlog::level::info;
        case LogLevel::Warning:  return spdlog::level::warn;
        case LogLevel::Error:    return spdlog::level::err;
        case LogLevel::Critical: return spdlog::level::critical;
        case LogLevel::Off:      return spdlog::level::off;
        default:                 return spdlog::level::info;
    }
}

void Logger::shutdown() {
    if (initialized_) {
        // Log shutdown
        LOG_INFO(get_logger("core"), "Logging system shutting down");

        // Clear loggers
        _loggers.clear();

        // Shutdown spdlog
        spdlog::shutdown();

        initialized_ = false;
    }
}
} // namespace parbati
