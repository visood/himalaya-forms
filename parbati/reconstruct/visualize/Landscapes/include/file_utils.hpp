// file_utils.hpp
#pragma once

#include <string>
#include <vector>
#include <optional>
#include <fstream>
#include <filesystem>

/**
 * @class FileUtils
 * @brief Utility functions for file operations
 */
class FileUtils {
public:
    /**
     * @brief Reads the entire content of a text file
     * @param filepath Path to the file
     * @return File content as string or empty if failed
     */
    static std::string read_text_file(const std::string& filepath);

    /**
     * @brief Reads binary file content
     * @param filepath Path to the file
     * @return Vector of bytes or empty if failed
     */
    static std::vector<unsigned char> read_binary_file(const std::string& filepath);

    /**
     * @brief Writes text content to a file
     * @param filepath Path to the file
     * @param content Text content to write
     * @return True if successful
     */
    static bool write_text_file(const std::string& filepath, const std::string& content);

    /**
     * @brief Writes binary content to a file
     * @param filepath Path to the file
     * @param data Binary data to write
     * @return True if successful
     */
    static bool write_binary_file(const std::string& filepath, const std::vector<unsigned char>& data);

    /**
     * @brief Checks if a file exists
     * @param filepath Path to the file
     * @return True if file exists
     */
    static bool file_exists(const std::string& filepath);

    /**
     * @brief Creates directory if it doesn't exist
     * @param dirpath Directory path
     * @return True if directory exists or was created successfully
     */
    static bool ensure_directory_exists(const std::string& dirpath);

    /**
     * @brief Gets all files in a directory with optional extension filter
     * @param dirpath Directory path
     * @param extension Optional extension filter
     * @return Vector of file paths
     */
    static std::vector<std::string> get_files_in_directory(
        const std::string& dirpath, const std::string& extension = "");

    /**
     * @brief Gets the base filename without extension
     * @param filepath Path to the file
     * @return Base filename
     */
    static std::string get_base_filename(const std::string& filepath);

    /**
     * @brief Gets the file extension
     * @param filepath Path to the file
     * @return File extension
     */
    static std::string get_file_extension(const std::string& filepath);

    /**
     * @brief Joins path components
     * @param components Path components to join
     * @return Joined path
     */
    static std::string join_paths(const std::vector<std::string>& components);
};
