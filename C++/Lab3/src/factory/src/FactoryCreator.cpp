#include <Factory/Factory.hpp>
#include <Factory/FactoryCreator.hpp>
#include <string>

namespace Factory {
    IFactoryPtr createFactory(FactoryMap factoryMap) {
        return std::make_shared<Factory>(std::move(factoryMap));
    }
} // namespace Factory
