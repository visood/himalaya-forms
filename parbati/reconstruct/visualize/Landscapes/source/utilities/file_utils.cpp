// file_utils.cpp
#include "file_utils.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

std::string FileUtils::read_text_file(const std::string& filepath) {
    throw std::runtime_error("FileUtils::read_text_file not implemented");
}

std::vector<unsigned char> FileUtils::read_binary_file(const std::string& filepath) {
    throw std::runtime_error("FileUtils::read_binary_file not implemented");
}

bool FileUtils::write_text_file(const std::string& filepath, const std::string& content) {
    throw std::runtime_error("FileUtils::write_text_file not implemented");
}

bool FileUtils::write_binary_file(const std::string& filepath, const std::vector<unsigned char>& data) {
    throw std::runtime_error("FileUtils::write_binary_file not implemented");
}

bool FileUtils::file_exists(const std::string& filepath) {
    throw std::runtime_error("FileUtils::file_exists not implemented");
}

bool FileUtils::ensure_directory_exists(const std::string& dirpath) {
    throw std::runtime_error("FileUtils::ensure_directory_exists not implemented");
}

std::vector<std::string> FileUtils::get_files_in_directory(
    const std::string& dirpath, const std::string& extension) {
    throw std::runtime_error("FileUtils::get_files_in_directory not implemented");
}

std::string FileUtils::get_base_filename(const std::string& filepath) {
    throw std::runtime_error("FileUtils::get_base_filename not implemented");
}

std::string FileUtils::get_file_extension(const std::string& filepath) {
    throw std::runtime_error("FileUtils::get_file_extension not implemented");
}

std::string FileUtils::join_paths(const std::vector<std::string>& components) {
    throw std::runtime_error("FileUtils::join_paths not implemented");
}
