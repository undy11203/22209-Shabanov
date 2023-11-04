#include <memory>
#include <string>

#include "../includes/CreateConverter.hpp"

#include "ChangeSpeedConverter.hpp"
#include "MixConverter.hpp"
#include "MuteConverter.hpp"

namespace Converter {
    IConverterPtr createConverter(const std::string &name) {
        if ("mute" == name) {
            return std::make_shared<MuteConverter>();
        } else if ("mix" == name) {
            return std::make_shared<MixConverter>();
        } else if ("change_speed" == name) {
            return std::make_shared<ChangeSpeedConverter>();
        }

        return nullptr;
    }
} // namespace Converter
