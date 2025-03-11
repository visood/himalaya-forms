/**
 * @class Window
 * @brief Handles the creation and management of the application window.
 *
 * The Window class is responsible for creating and managing the main application
 * window, handling resize events, processing input, and maintaining the OpenGL context.
 * It serves as the interface between our application and the underlying windowing
 * system.
 */

#pragma once

#include "opengl_includes.hpp"                 // Windowing library

#include <functional>                   // For callback functions
#include <string>                       // For std::string
#include <iostream>                     // For error reporting
#include <stdexcept>                    // For exception handling
#include <unordered_map>                // For key mapping
#include <array>                        // For fixed-size arrays
#include <optional>                     // For optional values
#include <tuple>                        // For std::tuple
#include "scene_config.hpp"             // To access window settings
#include <glm/glm.hpp>                  // For vector math
#include <glm/gtc/matrix_transform.hpp> // For camera transformations

class Window {
private:
    // Window properties
    int         _width;
    int         _height;
    int         _msaa_samples;
    std::string _title;
    bool        _fullscreen;
    bool        _vsync;
    bool        _running;

    /*
     * _windowed_<var>
     * These variables store the position and dimensions of the window when in
     * windowed mode, allowing the application to seamlessly transition between
     * fullscreen and windowed states while preserving the user's preferred window
     * configuration across mode switches.
     */
    int _windowed_pos_x;    // X position of window before fullscreen
    int _windowed_pos_y;    // Y position of window before fullscreen
    int _windowed_width;    // Width of window before fullscreen
    int _windowed_height;   // Height of window before fullscreen

    // Window handle (platform-specific)
    GLFWwindow* _window_handle;  // Using GLFW as an example

    // Event callbacks
    std::function<void(int, int)>           _resize_callback;
    std::function<void(double, double)>     _mouse_move_callback;
    std::function<void(int, int, int)>      _mouse_button_callback;
    std::function<void(int, int, int, int)> _key_callback;

    // Private initialization methods
    bool _initialize_glfw();
    bool _create_window_context();
    void _setup_callbacks();

public:
    /**
     * @brief Constructor with window configuration.
     *
     * @param width Initial window width in pixels
     * @param height Initial window height in pixels
     * @param title Window title
     * @param fullscreen Whether to start in fullscreen mode
     * @param vsync Whether to enable vertical sync
     */

    Window(int width = 1280, int height = 720,
           const std::string& title = "Himalayan Landscapes",
           bool fullscreen = false, bool vsync = true);

    Window(const SceneConfig& config);

    /**
     * @brief Destructor to clean up window resources.
     */
    ~Window();

    /**
     * @brief Initialize the window and GL context.
     *
     * @return true if initialization was successful
     */
    bool initialize();

    /**
     * @brief Check if the window should close.
     *
     * @return true if the window should close
     */
    bool should_close() const;

    /**
     * @brief Mark the window for closing.
     */
    void close();

    /**
     * @brief Process all pending window events.
     */
    void poll_events();

    /**
     * @brief Swap the frame buffers to display the rendered content.
     */
    void swap_buffers();

    /**
     * @brief Toggle fullscreen mode.
     */
    void toggle_full_screen();

    /**
     * @brief Resize the window.
     *
     * @param width New width in pixels
     * @param height New height in pixels
     */
    void resize(int width, int height);

    /**
     * @brief Set the window title.
     *
     * @param title New window title
     */
    void set_title(const std::string& title);

    /**
     * @brief Set the vertical sync option.
     *
     * @param enabled Whether to enable vsync
     */
    void set_vsync(bool enabled);

    /**
     * @brief Register a callback for window resize events.
     *
     * @param callback Function to call when window is resized
     */
    void set_resize_callback(std::function<void(int, int)> callback);

    /**
     * @brief Register a callback for mouse movement.
     *
     * @param callback Function to call when mouse moves
     */
    void set_mouse_move_callback(std::function<void(double, double)> callback);

    /**
     * @brief Register a callback for mouse button events.
     *
     * @param callback Function to call on mouse button events
     */
    void set_mouse_button_callback(std::function<void(int, int, int)> callback);

    /**
     * @brief Register a callback for keyboard events.
     *
     * @param callback Function to call on keyboard events
     */
    void set_key_callback(std::function<void(int, int, int, int)> callback);

    /*
     * @brief Get the current window width.
     *
     * @return Window width in pixels
     */
    int get_width() const { return _width; }

    /*
     * @brief Get the current window height.
     *
     * @return Window height in pixels
     */
    int get_height() const { return _height; }

    /*
     * @brief Get the window aspect ratio.
     *
     * @return Width divided by height
     */
    float get_aspect_ratio() const { return static_cast<float>(_width) / _height; }

    /*
     * @brief Get the window handle.
     *
     * @return Platform-specific window handle
     */
    GLFWwindow* get_native_handle() const { return _window_handle; }

    /*
     * @brief Check if the window is in fullscreen mode.
     *
     * @return true if fullscreen
     */
    bool is_fullscreen() const { return _fullscreen; }

    /*
     * @brief Get the current cursor position.
     *
     * @param x Reference to store the x coordinate
     * @param y Reference to store the y coordinate
     */
    void get_cursor_position(double& x, double& y) const;

    /*
     * @brief Set cursor position.
     *
     * @param x X coordinate
     * @param y Y coordinate
     */
    void set_cursor_position(double x, double y);

    /*
     * @brief Show or hide the cursor.
     *
     * @param visible Whether the cursor should be visible
     */
    void show_cursor(bool visible);

    /*
     * @brief Check if a key is currently pressed.
     *
     * @param key Key code to check
     * @return true if the key is pressed
     */
    bool is_key_pressed(int key) const;

    /*
     * @brief Check if a mouse button is currently pressed.
     *
     * @param button Mouse button code to check
     * @return true if the button is pressed
     */
    bool is_mouse_button_pressed(int button) const;
};
