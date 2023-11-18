#include <iostream>
#include <string>
#include <vector>

#include <ConsoleArgExceptions.hpp>
#include <FormatExceptions.hpp>
#include <SoundController.hpp>
#include <UncorrectConfig.hpp>

enum ConfigProgramm {
    HelpMod,
    ConvertMod,
    Undefiend
};

enum ErrorCode {
    ERROR_ARGUMENTS = -1,
    ERROR_FORMAT = -2,
    ERROR_IN_CONFIG = -3
};

void Config(std::vector<std::string> args, ConfigProgramm &configProgramm) {
    for (size_t i = 1; i < args.size(); i++) {
        if (args[i] == "-h") {
            configProgramm = HelpMod;
            break;
        }
        if (args[i] == "-c") {
            configProgramm = ConvertMod;
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);

    try {
        if (args.size() < 5 && args[1] != "-h") {
            throw ConsoleArgExceptions("Not enough arguments or undefine flags. Now counts arguments: " + std::to_string(args.size()));
        }

    } catch (ConsoleArgExceptions &e) {
        std::cerr << e.what() << '\n';
        return ErrorCode::ERROR_ARGUMENTS;
    }

    ConfigProgramm configProgramm = Undefiend;

    Config(args, configProgramm);
    SoundController soundController;

    try {
        soundController = SoundController(args);
    } catch (FormatExceptions &e) {
        std::cerr << e.what() << '\n';
        return ErrorCode::ERROR_FORMAT;
    }

    if (configProgramm == ConvertMod) {
        try {
            soundController.Convert();
        } catch (UncorrectConfig &e) {
            std::cerr << e.what() << '\n';
            return ErrorCode::ERROR_IN_CONFIG;
        }

    } else if (configProgramm == HelpMod) {
        soundController.PrintHelpList();
    }

    return 0;
}