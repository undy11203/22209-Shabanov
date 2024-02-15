#pragma once

#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>

namespace Factory {
    struct IFactory;
    using IFactoryPtr = std::shared_ptr<IFactory>;

    using Creator = std::function<std::any()>;
    using FactoryMap = std::map<std::string, Creator>;
} // namespace Factory
