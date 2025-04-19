#include "core/application.hpp"

Application::Application(std::shared_ptr<SceneConfig> config)
    : _config(config)
    , _last_frame_time(std::chrono::high_resolution_clock::now())
    , _random_generator(std::make_shared<std::mt19937>(config->run.random_seed))
{}

void Application::initialize() {
    // Initialize logger with settings
    LOG_INFO(CORE_LOG, "Application::initialize()");

    _window =
        std::make_unique<Window>(*_config);
    if (!_window->initialize()) {
        LOG_ERROR(CORE_LOG,
                  "Application::initialize()::Problem initializing a window.");
        throw std::runtime_error("Application failed to initialize a valid window.");
    } else {
        LOG_DEBUG(CORE_LOG,
                  "Application::initialize():: SUCCESS Got a window.");
    }

    glViewport(0, 0, _window->get_width(), _window->get_height());

    // Set a slightly lighter background color to ensure it's visible
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Dark teal color for testing

    // Set color from configuration
    glClearColor(
        _config->window.bg_clear_color[0],
        _config->window.bg_clear_color[1],
        _config->window.bg_clear_color[2],
        _config->window.bg_clear_color[3]);

    // Set up basic OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    LOG_INFO(CORE_LOG, "Application::initialize()::DONE");
}

int Application::run() {
    LOG_INFO(CORE_LOG, "Application::run()::Run");

    try {
        _last_frame_time =
            std::chrono::high_resolution_clock::now();
        auto dt_epoch =
            _last_frame_time.time_since_epoch();
        using DType =
            std::chrono::duration<float>;
        auto seconds =
            std::chrono::duration_cast<DType>(dt_epoch).count();

        LOG_DEBUG(CORE_LOG,
                  "Application::run()::Frame time set to: {} seconds since epoch", seconds);

        while (!_window->should_close()) {
            auto current_frame_time = std::chrono::high_resolution_clock::now();

            // add some delay
            //LOG_DEBUG(CORE_LOG, "Application::run() --- with delay to debug develop");
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));

            float delta_time = DType(current_frame_time - _last_frame_time).count();

            LOG_DEBUG(CORE_LOG, "Application::run()::delta_time={} seconds", delta_time);

            _last_frame_time = current_frame_time;

            update(delta_time);
            render();

            _window->poll_events();
            _window->swap_buffers();
        }

        return 0;
    } catch (const std::exception& e) {
        LOG_ERROR(CORE_LOG, "Application::run()::ERROR: {}", e.what());
        return 1;
    }
}

void Application::update(float delta_time) {
    LOG_WARN(CORE_LOG, "Application::update({})::...NOTIMPLEMENTED YET", delta_time);
    //_input_handler -> update(delta_time);

    //_scene -> update(delta_time);
    LOG_INFO(CORE_LOG, "Application::update({})::...DONE", delta_time);
}

void Application::render() {
    // Set a clear color that's distinctly visible (not black if you want to test)
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Dark teal color for testing

    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);

    // If you want to draw a colored rectangle for testing visibility:
    // (This would require adding simple rendering code)

    LOG_DEBUG(CORE_LOG, "Application::render() - cleared screen");

}

Application::~Application() {
    // unique_ptr members will automatically
    // clean up their resources when they go out of scope.
    // However, we might have to clean up in a specific order

    // First destroy the UI manager as it might depend on other components
    //_ui_manager.reset();

    // Then destroy the renderer
    //_renderer.reset();

    // Then the scene
    //_scene.reset();

    // Input handler next
    //_input_handler.reset();

    // Window last, since other components need it during their cleanup
    _window.reset();

    // shared_ptr Config will clean itself up when no longer referenced
}
