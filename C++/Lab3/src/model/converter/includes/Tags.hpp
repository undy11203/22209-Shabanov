#pragma once

#include "Fwd.hpp"

#include <Factory/Tag.hpp>

namespace Converter {
    const Factory::Tag<IConverterPtr> muteTag{"mute"};
    const Factory::Tag<IConverterPtr> mixTag{"mix"};
    const Factory::Tag<IConverterPtr> changeSpeedTag{"change_speed"};

} // namespace Converter
