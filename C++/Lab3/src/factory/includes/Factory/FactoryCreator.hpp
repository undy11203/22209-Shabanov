#pragma once

#include <Factory/Fwd.hpp>

namespace Factory {
    IFactoryPtr createFactory(FactoryMap factoryMap);
} // namespace Factory
