#include <Factory/Factory.hpp>
#include <string>

namespace Factory {
    Factory::Factory(FactoryMap factroryMap) : m_factoryMap{factroryMap} {}

    std::optional<std::any> Factory::createImpl(const std::string &id) {
        auto it = m_factoryMap.find(id);
        if (it != m_factoryMap.end()) {
            return it->second();
        }

        return std::nullopt;
    }
} // namespace Factory
