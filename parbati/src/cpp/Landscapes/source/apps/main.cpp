#include "core/application.hpp"

int main(int argc, char* argv[]) {
    parbati::Logger::get_instance()
        .initialize("logs",                    // log directory
                    parbati::LogLevel::Debug,  // console log level
                    parbati::LogLevel::Trace,  // file log level
                    10 * 1024 * 1024,          // 10MB max file size
                    5);                        // keep 5 rotating files

    LOG_INFO(CORE_LOG, "Himalayan Landscapes application initializing...");

    try {
        auto config = std::make_shared<SceneConfig>();

        if (argc > 1) {
            LOG_DEBUG(CORE_LOG, "Parse command line...", *argv);
            config->parse_command_line(argc, argv);
        } else {
            LOG_ERROR(CORE_LOG, "No arguments");
            config->load_from_file("config/default_scene.yaml");
        }

        LOG_DEBUG(CORE_LOG, "Construct and initialize the application...");
        Application app(config);
        app.initialize();

        LOG_DEBUG(CORE_LOG, "App initialized --- ready to run...");

        int result = app.run();
        LOG_INFO(CORE_LOG, "Application terminated normally: code, ", result);
        return result;

    } catch (const std::exception& e) {
        LOG_ERROR(CORE_LOG, "Fatal initialization error: code, ", -1);
        LOG_ERROR(CORE_LOG, "Exception: ", e.what());
        return -1;
    }
}
