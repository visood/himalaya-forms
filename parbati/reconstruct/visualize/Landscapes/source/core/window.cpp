#include "window.hpp"
#include <iostream>

Window::Window(
    int width, int height, const std::string& title, bool fullscreen, bool vsync)
    : _width(width)
    , _height(height)
    , _title(title)
    , _fullscreen(fullscreen)
    , _vsync(vsync)
    , _running(false)
    , _window_handle(nullptr)
{
    // Constructor only initializes member variables
    // Actual window creation happens in initialize()
    /*
      * _windowed_<var>
      * These variables store the position and dimensions of the window when in
      * windowed mode, allowing the application to seamlessly transition between
      * fullscreen and windowed states while preserving the user's preferred window
      * configuration across mode switches.
      */
    _windowed_pos_x = 0;
    _windowed_pos_y = 0;
    _windowed_width = _width;
    _windowed_height = _height;

    // Initialize callback functions to empty lambdas as defaults
    _resize_callback = [](int, int) {};
    _mouse_move_callback = [](double, double) {};
    _mouse_button_callback = [](int, int, int) {};
    _key_callback = [](int, int, int, int) {};
}

Window::Window(const SceneConfig& config)
    : _width(config.window.width)
    , _height(config.window.height)
    , _title(config.window.title)
    , _fullscreen(config.window.fullscreen)
    , _vsync(config.window.vsync)
    , _running(false)
    , _window_handle(nullptr)
{
    _windowed_pos_x = 0;
    _windowed_pos_y = 0;
    _windowed_width = _width;
    _windowed_height = _height;
    // Initialize callback functions to empty lambdas as defaults
    _resize_callback = [](int, int) {};
    _mouse_move_callback = [](double, double) {};
    _mouse_button_callback = [](int, int, int) {};
    _key_callback = [](int, int, int, int) {};
}


Window::~Window()
{
    if (_window_handle)
    {
        glfwDestroyWindow(_window_handle);
        _window_handle = nullptr;
    }
    glfwTerminate();
}

bool Window::initialize()
{
    if (!_initialize_glfw())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    if (!_create_window_context())
    {
        std::cerr << "Failed to create window context" << std::endl;
        return false;
    }

    _setup_callbacks();

    _running = true;
    return true;
}

bool Window::_initialize_glfw()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return false;
    }

    // Set error callback
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });

    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable multisample anti-aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Set forward compatibility for macOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    return true;
}

bool Window::_create_window_context()
{
    // Get primary monitor for fullscreen
    GLFWmonitor* monitor = _fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    // Create the window
    _window_handle =
        glfwCreateWindow(_width, _height, _title.c_str(), monitor, nullptr);

    if (!_window_handle) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent(_window_handle);

    // Get actual window size (may differ from requested size)
    int actual_width, actual_height;
    glfwGetFramebufferSize(_window_handle, &actual_width, &actual_height);
    _width = actual_width;
    _height = actual_height;

    if (!_fullscreen)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        int xpos = (mode->width - _width) / 2;
        int ypos = (mode->height - _height) / 2;
        glfwSetWindowPos(_window_handle, xpos, ypos);
    }

    // Initialize GLAD (or another GL loader) if we're using it
    // This part would depend on our GL loading strategy
    // For example, with GLAD, we would do:
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Window::_setup_callbacks() {
    // Set up framebuffer size callback
    glfwSetFramebufferSizeCallback(
        _window_handle,
        [](GLFWwindow* window, int width, int height) {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win) {
                win->_width = width;
                win->_height = height;

                // Notify the application through resize callback if registered
                if (win->_resize_callback) {
                    win->_resize_callback(width, height);
                }

                // Adjust viewport to new dimensions
                glViewport(0, 0, width, height);
            }
        });

    // Set up cursor position callback
    glfwSetCursorPosCallback(
        _window_handle,
        [](GLFWwindow* window, double x_pos, double y_pos) {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win && win->_mouse_move_callback) {
                win->_mouse_move_callback(x_pos, y_pos);
            }
        });

    // Set up mouse button callback
    glfwSetMouseButtonCallback(
        _window_handle,
        [](GLFWwindow* window, int button, int action, int mods) {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win && win->_mouse_button_callback) {
                win->_mouse_button_callback(button, action, mods);
            }
        });

    // Set up key callback
    glfwSetKeyCallback(
        _window_handle,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win && win->_key_callback) {
                win->_key_callback(key, scancode, action, mods);
            }

            // Additional built-in keyboard shortcuts
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            // F11 to toggle fullscreen (useful during our travels!)
            if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
                Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                if (win) {
                    win->toggle_full_screen();
                }
            }
        });

    // Window close callback
    glfwSetWindowCloseCallback(
        _window_handle,
        [](GLFWwindow* window) {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win) {
                win->_running = false;
            }
        });

    // Error callback for window-specific errors
    glfwSetWindowSizeCallback(
        _window_handle,
        [](GLFWwindow* window, int width, int height) {
        // This callback is different from framebuffer size callback
        // because on high-DPI displays, framebuffer size != window size
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (win) {
                // Update internal state but don't change OpenGL viewport here
                // as that's handled by the framebuffer size callback
                win->_width = width;
                win->_height = height;
            }
        });
}

bool Window::should_close() const {
    return glfwWindowShouldClose(_window_handle);
}

void Window::close() {
    if (_window_handle) {
        glfwSetWindowShouldClose(_window_handle, GLFW_TRUE);
        _running = false;
    }
}

void Window::poll_events() {
    // Process all pending events

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;

        // Report error based on code
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM: "
                          << " Unacceptable value specified for an enum."
                          << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE:"
                          << " A numeric argument is out of range."
                          << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION:"
                          << " Operation is not allowed in the current state."
                          << std::endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION:"
                          << " The framebuffer object is not complete."
                          << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY:"
                          << " Not enough memory left to execute the command."
                          << std::endl;
                break;
            default:
                std::cerr << "Unknown error code." << std::endl;

        }
    }

    // Update frame timing statistics if needed
    // This could be useful for maintaining consistent animations
    // of dynamic landscape elements like flowing water or moving clouds
    static double last_time = glfwGetTime();
    double current_time = glfwGetTime();
    double delta_time = current_time - last_time;

    // We could store delta_time for use in animation timing
    // _delta_time = delta_time;

    last_time = current_time;

    // Update window title with FPS information if desired
    // Useful during development to ensure our landscape visualizations
    // maintain real-time performance
    /*
    static int frame_count = 0;
    static double fps_timer = 0.0;

    frame_count++;
    fps_timer += delta_time;

    if (fps_timer >= 1.0) {
        double fps = frame_count / fps_timer;

        std::string new_title =
            _title + " | FPS: " + std::to_string(static_cast<int>(fps));
        glfwSetWindowTitle(_window_handle, new_title.c_str());

        frame_count = 0;
        fps_timer = 0.0;
    }
    */
}

void Window::swap_buffers()
{
    if (_window_handle) {
        // Swap front and back buffers to display the rendered content
        glfwSwapBuffers(_window_handle);
    }
}

#include "window.hpp"

// Note: Most of these getters are already defined inline in the header,
// but I'll implement them here for completeness and consistency

void Window::get_cursor_position(double& x, double& y) const
{
    if (_window_handle) {
        // Retrieve the cursor position through GLFW
        glfwGetCursorPos(_window_handle, &x, &y);
    } else {
        // If window handle is invalid, return (0,0)
        x = 0.0;
        y = 0.0;
    }
}

bool Window::is_key_pressed(int key) const
{
    if (!_window_handle) {
        return false;
    }

    // Check if the specified key is currently pressed
    return glfwGetKey(_window_handle, key) == GLFW_PRESS;
}

bool Window::is_mouse_button_pressed(int button) const
{
    if (!_window_handle) {
        return false;
    }

    // Check if the specified mouse button is currently pressed
    return glfwGetMouseButton(_window_handle, button) == GLFW_PRESS;
}

#include "window.hpp"
#include <iostream>

void Window::resize(int width, int height)
{
    if (!_window_handle || width <= 0 || height <= 0) {
        return;
    }

    // Store the new dimensions
    _width = width;
    _height = height;

    // Resize the GLFW window
    glfwSetWindowSize(_window_handle, width, height);

    // Note: We don't need to update the viewport here as it will be
    // handled by the framebuffer size callback we set up in _setup_callbacks()
}

void Window::set_title(const std::string& title)
{
    if (!_window_handle) {
        return;
    }

    // Store the new title
    _title = title;

    // Update the window title
    glfwSetWindowTitle(_window_handle, _title.c_str());
}

void Window::set_vsync(bool enabled)
{
    if (!_window_handle) {
        return;
    }

    // Store the vsync setting
    _vsync = enabled;

    // Apply the vsync setting
    // 0 = no vsync, 1 = vsync, -1 = adaptive vsync (if supported)
    glfwSwapInterval(_vsync ? 1 : 0);
}

void Window::toggle_full_screen()
{
    if (!_window_handle) {
        return;
    }

    // Toggle fullscreen state
    _fullscreen = !_fullscreen;

    if (_fullscreen) {
        // Store current window position and size before going fullscreen
        glfwGetWindowPos(_window_handle, &_windowed_pos_x, &_windowed_pos_y);
        glfwGetWindowSize(_window_handle, &_windowed_width, &_windowed_height);

        // Get the primary monitor
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        if (!primary) {
            std::cerr << "Failed to get primary monitor, cannot enter fullscreen"
                      << std::endl;
            _fullscreen = false;
            return;
        }

        // Get the monitor's current video mode
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        if (!mode) {
            std::cerr << "Failed to get video mode, cannot enter fullscreen" << std::endl;
            _fullscreen = false;
            return;
        }

        // Switch to fullscreen
        glfwSetWindowMonitor(_window_handle, primary, 0, 0,
                             mode->width, mode->height, mode->refreshRate);

        // Update internal dimensions
        _width = mode->width;
        _height = mode->height;
    }
    else {
        // Return to windowed mode with previous dimensions and position
        glfwSetWindowMonitor(_window_handle, nullptr,
                             _windowed_pos_x, _windowed_pos_y,
                             _windowed_width, _windowed_height, GLFW_DONT_CARE);

        // Update internal dimensions
        _width = _windowed_width;
        _height = _windowed_height;
    }

    // If there's a resize callback registered, notify it about the new dimensions
    if (_resize_callback) {
        _resize_callback(_width, _height);
    }

    // Since we changed window size, we need to update the viewport
    glViewport(0, 0, _width, _height);
}

void Window::set_resize_callback(std::function<void(int, int)> callback)
{
    _resize_callback = callback;
}

void Window::set_mouse_move_callback(std::function<void(double, double)> callback)
{
    _mouse_move_callback = callback;
}

void Window::set_mouse_button_callback(std::function<void(int, int, int)> callback)
{
    _mouse_button_callback = callback;
}

void Window::set_key_callback(std::function<void(int, int, int, int)> callback)
{
    _key_callback = callback;
}

void Window::set_cursor_position(double x, double y)
{
    if (_window_handle) {
        glfwSetCursorPos(_window_handle, x, y);
    }
}

void Window::show_cursor(bool visible)
{
    if (_window_handle) {
        glfwSetInputMode(_window_handle, GLFW_CURSOR,
                         visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
}
