#pragma once

#include <Factory/Fwd.hpp>

#include <optional>
#include <string>

namespace Factory {
    struct IFactory {
        virtual ~IFactory() = default;

        template <typename Tag>
        typename Tag::InterfaceType create(Tag tag) {
            auto result_opt = createImpl(tag.id);
            if (!result_opt) {
                return nullptr;
            }

            typename Tag::InterfaceType *result = std::any_cast<typename Tag::InterfaceType>(&result_opt.value());
            if (result) {
                return *result;
            }

            return nullptr;
        }

    private:
        virtual std::optional<std::any> createImpl(const std::string &id) = 0;
    };

} // namespace Factory
