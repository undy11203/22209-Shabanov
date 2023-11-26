#include <iostream>
#include <string>
#include <vector>

#include <FormatExceptions.hpp>
#include <SoundController.hpp>
#include <UncorrectConfig.hpp>

namespace Error {
    const int ERROR_ARGUMENTS = -1;
    const int ERROR_FORMAT = -1;
    const int ERROR_IN_CONFIG = -1;
} // namespace

enum class ConfigProgramm {
    HelpMod,
    ConvertMod,
    Undefiend
};

void Config(std::vector<std::string> args, ConfigProgramm &configProgramm) {
    for (size_t i = 1; i < args.size(); i++) {
        if (args[i] == "-h") {
            configProgramm = ConfigProgramm::HelpMod;
            break;
        }
        if (args[i] == "-c") {
            configProgramm = ConfigProgramm::ConvertMod;
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() < 5 && args[1] != "-h") {
        std::cerr << "Not enough arguments or undefine flags. Now counts arguments: " + std::to_string(args.size()) << '\n';
        return Error::ERROR_ARGUMENTS;
    }

    ConfigProgramm configProgramm = ConfigProgramm::Undefiend;

    Config(args, configProgramm);
    SoundController soundController;

    try {
        soundController = SoundController(args);
    } catch (FormatExceptions &e) {
        std::cerr << e.what() << '\n';
        return Error::ERROR_FORMAT;
    }

    if (configProgramm == ConfigProgramm::ConvertMod) {
        try {
            soundController.Convert();
        } catch (UncorrectConfig &e) {
            std::cerr << e.what() << '\n';
            return Error::ERROR_IN_CONFIG;
        }

    } else if (configProgramm == ConfigProgramm::HelpMod) {
        soundController.PrintHelpList();
    }

    return 0;
}