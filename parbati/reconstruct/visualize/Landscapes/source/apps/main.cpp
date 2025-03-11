#include "application.hpp"
#include "scene_config.hpp"

int main(int argc, char* argv[]) {
    try {
        auto config = std::make_shared<SceneConfig>();

        if (argc > 1) {
            std::cout << "Parse command line " << *argv << std::endl;
            config->parse_command_line(argc, argv);

            std::cout << "Construct App" << std::endl;
            Application app(config);
            app.initialize();
            std::cout << "App initialized" << std::endl;

            int result = app.run();

            std::cout << "Application terminated normally: code, " << result
                      << std::endl;
            return result;
        } else {
            std::cout << "No arguments" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal initialization error: code, " << -1
                  << std::endl << "Exception: " << e.what() << std::endl;
        return -1;
    }
}
