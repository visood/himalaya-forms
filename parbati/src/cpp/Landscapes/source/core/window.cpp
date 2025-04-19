#include "core/window.hpp"

Window::Window(int width, int height, const std::string& title,
               bool fullscreen, bool vsync)
    : _width(width)
    , _height(height)
    , _title(title)
    , _fullscreen(fullscreen)
    , _vsync(vsync)
    , _running(false)
    , _window_handle(nullptr)
{
    // Only initialize member variables, use initialize() to create window
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

    // Initialize callbacks
    _resize_callback = [](int, int) {};
    _mouse_move_callback = [](double, double) {};
    _mouse_button_callback = [](int, int, int) {};
    _key_callback = [](int, int, int, int){};
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
    // Only initialize member variables, use initialize() to create window
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

    // Initialize callbacks
    _resize_callback = [](int, int) {};
    _mouse_move_callback = [](double, double) {};
    _mouse_button_callback = [](int, int, int) {};
    _key_callback = [](int, int, int, int){};
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
    LOG_DEBUG(CORE_LOG, "Window::initialize()");

    if (!_initialize_glfw()) {
        LOG_ERROR(CORE_LOG, "Failed to initialize GLFW");
        return false;
    }

    if (!_create_window_context()) {
        LOG_ERROR(CORE_LOG, "Failed to create window context");
        return false;
    }
    else {
        glfwShowWindow(_window_handle);
    }

    _setup_callbacks();

    // Some systems require explicit vsync settings
    glfwSwapInterval(_vsync ? 1 : 0);

    glfwSetWindowUserPointer(_window_handle, this);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    LOG_DEBUG(CORE_LOG, "Creating window: {}x{}, Monitor: {}x{}",
              _width, _height, mode->width, mode->height);

    LOG_DEBUG(CORE_LOG, "Window::initialize() ... run");
    _running = true;
    return true;
}

bool Window::_initialize_glfw()
{
    LOG_DEBUG(CORE_LOG, "Window::_initialize_glfw()...");
    // Initialize GLFW
    if (!glfwInit())
    {
        return false;
    }

    // Set error callback
    glfwSetErrorCallback([](int error, const char* description) {
        LOG_ERROR(CORE_LOG, "GLFW Error {}: {}", error, description);
        //std::cerr << "GLFW Error " << error << ": " << description << std::endl;
    });

    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Further hints to ensure window visibility
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

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
    LOG_DEBUG(CORE_LOG, "Window::_create_window_context()...");
    _window_handle =
        glfwCreateWindow(_width, _height, _title.c_str(), monitor, nullptr);

    if (!_window_handle) {
        LOG_ERROR(CORE_LOG,
                  "Window::_create_window_context()::FAILURE to create window handle");
        glfwTerminate();
        return false;
    } else {
        LOG_DEBUG(CORE_LOG,
                  "Window::_create_window_context()::SUCCESS to create window handle");
    }

    // Make the window's context current
    glfwMakeContextCurrent(_window_handle);

    // Get actual window size (may differ from requested size)
    int actual_width, actual_height;
    glfwGetFramebufferSize(_window_handle, &actual_width, &actual_height);
    _width = actual_width;
    _height = actual_height;

    // Center the window on screen
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
        LOG_DEBUG(CORE_LOG,
                  "Window::_create_window_context()::FAILURE to initialize GLAD");
        glfwDestroyWindow(_window_handle);
        glfwTerminate();
        return false;
    } else {
        LOG_DEBUG(CORE_LOG,
                  "Window::_create_window_context()::SUCCESS to initialize GLAD");
    }

    return true;
}

void Window::_setup_callbacks() {
    // Set up framebuffer size callback
    LOG_DEBUG(CORE_LOG, "Window::_setup_callbacks()()");

    glfwSetFramebufferSizeCallback(
        _window_handle,
        [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
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
    if (_window_handle) {
        // Poll events
        glfwPollEvents();
    }
}

void Window::swap_buffers()
{
    if (_window_handle) {
        // Swap front and back buffers to display the rendered content
        glfwSwapBuffers(_window_handle);
    }
}


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
        std::cout << "Window::is_key_pressed(): Window has no handle!"
                  << std::endl;
        return false;
    }

    // Check if the specified key is currently pressed
    return glfwGetKey(_window_handle, key) == GLFW_PRESS;
}

bool Window::is_mouse_button_pressed(int button) const
{
    if (!_window_handle) {
        std::cout << "Window::is_mouse_button_pressed(): Window has no handle!"
                  << std::endl;
        return false;
    }
    // Check if the specified mouse button is currently pressed
    return glfwGetMouseButton(_window_handle, button) == GLFW_PRESS;
}


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
