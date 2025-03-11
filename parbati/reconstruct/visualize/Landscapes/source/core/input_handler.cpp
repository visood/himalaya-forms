// input_handler.cpp
#include "input_handler.hpp"
#include <stdexcept>
#include <iostream>

InputHandler::InputHandler(Window& window)
    : _window(window)
    , _mouse_x(0.0)
    , _mouse_y(0.0)
    , _previous_mouse_x(0.0)
    , _previous_mouse_y(0.0)
    , _scroll_delta(0.0)
{
    // Get initial mouse position from window
    _window.get_cursor_position(_mouse_x, _mouse_y);
    _previous_mouse_x = _mouse_x;
    _previous_mouse_y = _mouse_y;
}

InputHandler::~InputHandler() {
    // Stub implementation
}

bool InputHandler::initialize() {
    throw std::runtime_error("InputHandler::initialize not implemented");
}


void InputHandler::update(float delta_time) {
    throw std::runtime_error("InputHandler::update not implemented");
}

void InputHandler::register_key_callback(int key, std::function<void()> callback) {
    throw std::runtime_error("InputHandler::register_key_callback not implemented");
}

void InputHandler::register_mouse_button_callback(int button, std::function<void()> callback) {
    throw std::runtime_error("InputHandler::register_mouse_button_callback not implemented");
}

void InputHandler::register_mouse_move_callback(std::function<void(double, double)> callback) {
    throw std::runtime_error("InputHandler::register_mouse_move_callback not implemented");
}

void InputHandler::register_mouse_scroll_callback(std::function<void(double)> callback) {
    throw std::runtime_error("InputHandler::register_mouse_scroll_callback not implemented");
}

std::pair<double, double> InputHandler::get_mouse_position() const {
    throw std::runtime_error("InputHandler::get_mouse_position not implemented");
}

std::pair<double, double> InputHandler::get_mouse_delta() const {
    throw std::runtime_error("InputHandler::get_mouse_delta not implemented");
}

bool InputHandler::is_key_pressed(int key) const {
    throw std::runtime_error("InputHandler::is_key_pressed not implemented");
}

bool InputHandler::was_key_pressed(int key) const {
    throw std::runtime_error("InputHandler::was_key_pressed not implemented");
}

bool InputHandler::was_key_released(int key) const {
    throw std::runtime_error("InputHandler::was_key_released not implemented");
}

bool InputHandler::is_mouse_button_pressed(int button) const {
    throw std::runtime_error("InputHandler::is_mouse_button_pressed not implemented");
}

double InputHandler::get_scroll_delta() const {
    throw std::runtime_error("InputHandler::get_scroll_delta not implemented");
}
