#pragma once
#include <functional>
#include <variant>
#include <optional>

namespace oinkoinkrun::events {
    class Events final {
    public:
        struct Event {
            template<class Data>
            Event(Data&& t): data(std::move(t)) {}

            struct Key {
                enum class Type {
                    Press, Unknown
                };
                enum class Code {
                    Escape, Unknown
                };

                Type type = Type::Unknown;
                Code code = Code::Unknown;
            };

            std::variant<Key> data;
        };

        Events();
        ~Events();

        void poll(const std::function<void(const Event&)>& callback);
    };
}