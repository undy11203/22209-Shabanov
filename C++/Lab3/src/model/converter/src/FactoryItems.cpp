#pragma once

#include <memory>
#include <string>

#include "../includes/FactoryItems.hpp"
#include "../includes/Tags.hpp"

#include "ChangeSpeedConverter.hpp"
#include "MixConverter.hpp"
#include "MuteConverter.hpp"

namespace Converter {
    Factory::FactoryMap factoryItems() {
        Factory::FactoryMap factoryItems;

        factoryItems.insert({muteTag.id, []() { return std::make_any<IConverterPtr>(std::make_shared<MuteConverter>()); }});

        factoryItems.insert({mixTag.id, []() { return std::make_any<IConverterPtr>(std::make_shared<MixConverter>()); }});

        factoryItems.insert({changeSpeedTag.id, []() { return std::make_any<IConverterPtr>(std::make_shared<ChangeSpeedConverter>()); }});

        return factoryItems;
    }
} // namespace Converter
