#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace parbati {
enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
    Off
};

/**
 * @brief Main logger class providing a wrapper around spdlog
 *
 * This class manages logging for different subsystems of the Himalayan
 * landscape visualization project, allowing for categorized and leveled logging.
 */
class Logger {
public:
    /**
     * @brief Get the singleton instance of the logger
     * @return Reference to the logger instance
     */
    static Logger& get_instance();

    /**
     * @brief Initialize the logging system
     * @param logDir Directory to store log files
     * @param consoleLevel Minimum level for console output
     * @param fileLevel Minimum level for file output
     * @param maxFileSize Maximum size per log file in bytes
     * @param maxFiles Maximum number of rotating files
     */
    void initialize(
        const std::string& logDir = "logs",
        LogLevel consoleLevel = LogLevel::Info, LogLevel fileLevel = LogLevel::Debug,
        size_t maxFileSize = 5 * 1024 * 1024, size_t maxFiles = 3);

    /**
     * @brief Get or create a logger for a specific subsystem
     * @param name Name of the subsystem (e.g., "terrain", "renderer", "water")
     * @return Logger for the specified subsystem
     */
    std::shared_ptr<spdlog::logger> get_logger(const std::string& name);

    /**
     * @brief Set the global console logging level
     * @param level Minimum level to display in console
     */
    void set_console_level(LogLevel level);

    /**
     * @brief Set the global file logging level
     * @param level Minimum level to write to log files
     */
    void set_file_level(LogLevel level);

    /**
     * @brief Set logging level for a specific subsystem
     * @param name Subsystem name
     * @param level Log level to set
     */
    void set_logger_level(const std::string& name, LogLevel level);

    /**
     * @brief Convert LogLevel enum to spdlog level
     * @param level Our LogLevel enum
     * @return Corresponding spdlog level
     */
    static spdlog::level::level_enum to_spd_log_level(LogLevel level);

    /**
     * @brief Shutdown logging system properly
     */
    void shutdown();

private:
    Logger() = default;
    ~Logger();

    // Disable copy/move
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    bool initialized_ = false;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _console_sink;
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> _file_sink;
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> _loggers;
}; // class Logger

// Convenience macros for logging
#define LOG_TRACE(logger, ...)    logger->trace(__VA_ARGS__)
#define LOG_DEBUG(logger, ...)    logger->debug(__VA_ARGS__)
#define LOG_INFO(logger, ...)     logger->info(__VA_ARGS__)
#define LOG_WARN(logger, ...)     logger->warn(__VA_ARGS__)
#define LOG_ERROR(logger, ...)    logger->error(__VA_ARGS__)
#define LOG_CRITICAL(logger, ...) logger->critical(__VA_ARGS__)

// Convenience macros for specific subsystems
#define CORE_LOG        parbati::Logger::get_instance().get_logger("core")
#define TERRAIN_LOG     parbati::Logger::get_instance().get_logger("terrain")
#define WATER_LOG       parbati::Logger::get_instance().get_logger("water")
#define SKY_LOG         parbati::Logger::get_instance().get_logger("sky")
#define VEGETATION_LOG  parbati::Logger::get_instance().get_logger("vegetation")
#define RENDERER_LOG    parbati::Logger::get_instance().get_logger("renderer")
#define SHADER_LOG      parbati::Logger::get_instance().get_logger("shader")
#define RESOURCE_LOG    parbati::Logger::get_instance().get_logger("resource")
#define UI_LOG          parbati::Logger::get_instance().get_logger("ui")
#define INPUT_LOG       parbati::Logger::get_instance().get_logger("input")
} // namespace parbati
