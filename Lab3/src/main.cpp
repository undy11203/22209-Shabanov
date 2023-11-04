#include <string>
#include <vector>

#include <SoundController.hpp>

enum ConfigProgramm {
    HelpMod,
    ConvertMod,
    Undefiend
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
    ConfigProgramm configProgramm = Undefiend;

    Config(args, configProgramm);

    SoundController soundController(args);

    if (configProgramm == ConvertMod) {
        soundController.Convert();
    } else if (configProgramm == HelpMod) {
        soundController.PrintHelpList();
    }

    return 0;
}