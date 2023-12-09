#pragma once

#include <Factory/IFactory.hpp>
#include <any>
#include <optional>
#include <string>


namespace Factory {
    class Factory : public IFactory,
                    public std::enable_shared_from_this<Factory> {
    private:
        std::optional<std::any> createImpl(const std::string &id) override;

        const FactoryMap m_factoryMap;

    public:
        Factory(FactoryMap factoryMap);
    };

} // namespace Factory
