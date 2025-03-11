#include "application.hpp"

Application::Application(std::shared_ptr<SceneConfig> config)
    : _config(config)
    , _last_frame_time(std::chrono::high_resolution_clock::now())
{initialize();}

Application::~Application() {
    // Since we're using unique_ptr for our members, they will automatically
    // clean up their resources when they go out of scope.
    // However, there's a specific order we might want to follow for clean shutdown:

    // First destroy the UI manager as it might depend on other components
    _ui_manager.reset();

    // Then destroy the renderer
    _renderer.reset();

    // Then the scene
    _scene.reset();

    // Input handler next
    _input_handler.reset();

    // Window last, since other components might need it during their cleanup
    _window.reset();

    // Config is a shared_ptr and will clean itself up when no longer referenced
}

void Application::initialize() {
    _window =
        std::make_unique<Window>(*_config);
    _input_handler =
        std::make_unique<InputHandler>(*_window);
    _scene =
        std::make_unique<Scene>(*_config);
    _renderer =
        std::make_unique<TerrainRenderer>(*_window, *_scene, *_config);
    _ui_manager =
        std::make_unique<UIManager>(*_window, *_scene, *_config);

    // Check if Application initiqlizes ui-manager
    std::cout << "Initializing UI manager..." << std::endl;
    bool ui_init_success = _ui_manager->initialize();
    std::cout << "UI manager initialization "
              << (ui_init_success ? "succeeded" : "failed") << std::endl;

    _scene->setup_empty_base_terrain();

    std::cout << "Initialized application." << std::endl;
}

int Application::run() {
    std::cout << "Run application" << std::endl;
    try {
        _last_frame_time = std::chrono::high_resolution_clock::now();
        auto duration_since_epoch = _last_frame_time.time_since_epoch();
        auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration_since_epoch).count();
        std::cout << "Frame time set to: " << seconds << " seconds since epoch" << std::endl;

        while (!_window->should_close()) {
            auto current_frame_time =
                std::chrono::high_resolution_clock::now();
            float delta_time =
                std::chrono::duration<float>(current_frame_time - _last_frame_time)
                .count();
            _last_frame_time = current_frame_time;

            update(delta_time);
            render();

            _window->poll_events();
            _window->swap_buffers();
            //_window.swapBufferAndPollEvents();
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    }
}

void Application::update(float delta_time) {
    _input_handler->update(delta_time);

    _scene->update(delta_time);
}

void Application::render() {
    _renderer->begin_frame();
    _renderer->render_terrain();
    _renderer->render_sky();

    _ui_manager->render();
    _renderer->end_frame();
}
