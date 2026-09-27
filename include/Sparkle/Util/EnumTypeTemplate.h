#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
//
// Created by z3r0_ on 18/09/2026.
//

#ifndef SPARKLEINPUT_ENUMTYPETEMPLATE_H
#define SPARKLEINPUT_ENUMTYPETEMPLATE_H

#include <cstddef>
#include <string>
#include <cassert>

namespace Sparkle
{
    template<typename Enum, typename EnumTraits>
    class EnumType
    {
    private:
        Enum Value { };

    public:
        constexpr EnumType() = default;
        constexpr EnumType(Enum value) : Value(value) { }
        constexpr explicit EnumType(int value) : Value(static_cast<Enum>(value))
        {
            assert(value >= 0 && value < static_cast<int>(Enum::Count) && "EnumType Template >> out-of-range index");
        }
        constexpr explicit EnumType(unsigned int value) : Value(static_cast<Enum>(value))
        {
            assert(value < static_cast<unsigned int>(Enum::Count) && "EnumType Template >> out-of-range index");
        }
        constexpr explicit EnumType(std::size_t value) : Value(static_cast<Enum>(value))
        {
            assert(value < static_cast<size_t>(Enum::Count) && "EnumType Template >> out-of-range index");
        }

        void* operator new(std::size_t) = delete;
        void* operator new[](std::size_t) = delete;
        void operator delete(void*) = delete;
        explicit operator bool() = delete;

        constexpr operator Enum() const { return Value; }

        const char* c_str() { return EnumTraits::Name(Value); }
        operator std::string() const { return c_str(); }

        explicit operator int() const { return static_cast<int>(Value); }
        explicit operator unsigned int() const { return static_cast<unsigned int>(Value); }

        friend constexpr bool operator==(EnumType a, Enum b) { return a.Value == b; }
        friend constexpr bool operator==(Enum a, EnumType b) { return b.Value == a; }
        friend constexpr bool operator==(EnumType a, EnumType b) { return a.Value == b.Value; }
        friend constexpr bool operator<(EnumType a, Enum b)  { return a.Value < b;  }
        friend constexpr bool operator<(Enum a, EnumType b)  { return a < b.Value;  }
        friend constexpr bool operator<(EnumType a, EnumType b)  { return a.Value < b.Value;  }

    };
}

#define SPARKLE_DEFINE_ENUM_TYPE(ClassName, LIST)                                   \
enum class ClassName##Enum { LIST(SPARKLE_DETAIL_ENUMERATOR) };                     \
struct ClassName##Traits {                                                          \
    static constexpr const char * Names[] = { LIST(SPARKLE_DETAIL_NAME) };          \
    static constexpr const char * Name(ClassName##Enum value) {                     \
        auto index = static_cast<std::size_t>(value);                               \
        if (index >= std::size(Names)) { return "Unknown " #ClassName; }            \
        return Names[index];                                                        \
    }                                                                               \
};                                                                                  \
class ClassName : public EnumType<ClassName##Enum, ClassName##Traits>               \
{                                                                                   \
public:                                                                             \
    using EnumType::EnumType;                                                       \
    using enum ClassName##Enum;                                                     \
};

#define SPARKLE_DETAIL_ENUMERATOR(name) name,
#define SPARKLE_DETAIL_NAME(name) #name,


#endif //SPARKLEINPUT_ENUMTYPETEMPLATE_H

#pragma clang diagnostic pop