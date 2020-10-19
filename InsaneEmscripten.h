#pragma once
#include <emscripten/bind.h>
#include <InsanePreprocessor.h>
#include <type_traits>
#include <functional>

#define VAL_TYPE() emscripten::val
#define EMSCRIPTEN_EXPORT_FUNCTOR(arity, returnType, name, p3, p4, p5) emscripten::class_<std::function<returnType(INSANE_REPEAT_COMMA_##arity(VAL_TYPE(), 0))>>(STRINGIFY(name##arity)).constructor<>().function("opcall", &std::function<returnType(INSANE_REPEAT_COMMA_##arity(VAL_TYPE(), 0))>::operator());
#define EMSCRIPTEN_EXPORT_ALL_VOID_FUNCTORS(arity) INSANE_REPEAT_ADVANCED(EMSCRIPTEN_EXPORT_FUNCTOR, arity, VOID_TYPE(), VoidFunctor, 0, 0, 0)
#define EMSCRIPTEN_EXPORT_ALL_VAL_FUNCTORS(arity) INSANE_REPEAT_ADVANCED(EMSCRIPTEN_EXPORT_FUNCTOR, arity, VAL_TYPE(), ValFunctor, 0, 0, 0)
#define EMSCRIPTEN_EXPORT_ALL_FUNCTORS(arity) \
    EMSCRIPTEN_EXPORT_ALL_VAL_FUNCTORS(arity) \
    EMSCRIPTEN_EXPORT_ALL_VOID_FUNCTORS(arity)

#define EMSCRIPTEN_FUNCTOR_TYPE(arity, returnType) std::function<returnType(INSANE_REPEAT_COMMA_##arity(VAL_TYPE(), 0))>
#define EMSCRIPTEN_VOID_FUNCTOR_TYPE(arity) EMSCRIPTEN_FUNCTOR_TYPE(arity, VOID_TYPE())
#define EMSCRIPTEN_VAL_FUNCTOR_TYPE(arity) EMSCRIPTEN_FUNCTOR_TYPE(arity, VAL_TYPE())

#define USING_EMSCRIPTEN using namespace emscripten
#define USING_INSANE_EMSCRIPTEN using namespace Insane::Emscripten

typedef std::string String;
using namespace std::string_literals;

namespace Insane::Emscripten
{

    class Console
    {
    private:
        enum class ConsoleMessageType
        {
            LOG,
            INFO,
            WARN,
            ERROR
        };
        template <typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, String> ||
                                                                   std::is_same_v<ParamType, emscripten::val> ||
                                                                   std::is_floating_point_v<ParamType> ||
                                                                   std::is_integral_v<ParamType>>...>>
        static inline void Print(ConsoleMessageType type, const ParamType &... args)
        {
            USING_EMSCRIPTEN;
            String method = u8""s;
            switch (type)
            {
            case ConsoleMessageType::INFO:
                method = u8"info"s;
                break;
            case ConsoleMessageType::WARN:
                method = u8"warn"s;
                break;
            case ConsoleMessageType::ERROR:
                method = u8"error"s;
                break;
            default:
                method = u8"log";
                break;
            }
            val::global("console").call<void>(method.c_str(), args...);
        };

    public:
        Console() = default;
        ~Console() = default;
        template <typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, String> ||
                                                                   std::is_same_v<ParamType, emscripten::val> ||
                                                                   std::is_floating_point_v<ParamType> ||
                                                                   std::is_integral_v<ParamType>>...>>
        static inline void Log(const ParamType &... args)
        {
            USING_EMSCRIPTEN;
            Print(ConsoleMessageType::LOG, args...);
        };

        template <typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, String> ||
                                                                   std::is_same_v<ParamType, emscripten::val> ||
                                                                   std::is_floating_point_v<ParamType> ||
                                                                   std::is_integral_v<ParamType>>...>>
        static inline void Info(const ParamType &... args)
        {
            USING_EMSCRIPTEN;
            Print(ConsoleMessageType::INFO, args...);
        };

        template <typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, String> ||
                                                                   std::is_same_v<ParamType, emscripten::val> ||
                                                                   std::is_floating_point_v<ParamType> ||
                                                                   std::is_integral_v<ParamType>>...>>
        static inline void Warn(const ParamType &... args)
        {
            USING_EMSCRIPTEN;
            Print(ConsoleMessageType::WARN, args...);
        };

        template <typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, String> ||
                                                                   std::is_same_v<ParamType, emscripten::val> ||
                                                                   std::is_floating_point_v<ParamType> ||
                                                                   std::is_integral_v<ParamType>>...>>
        static inline void Error(const ParamType &... args)
        {
            USING_EMSCRIPTEN;
            Print(ConsoleMessageType::ERROR, args...);
        };
    };

    class Promise
    {
    private:
    public:
        static inline emscripten::val Resolve(const emscripten::val &value)
        {
            USING_EMSCRIPTEN;
            return val::global()[u8"Promise"].call<val>(u8"resolve", value);
        }
        static inline emscripten::val Reject(const emscripten::val &value)
        {
            USING_EMSCRIPTEN;
            return val::global()[u8"Promise"].call<val>(u8"reject", value);
        }
    };

    class Js
    {
    private:
        static inline emscripten::val Bind(const emscripten::val &fx)
        {
            USING_EMSCRIPTEN;
            return fx["opcall"].call<val>("bind", fx);
        }

    public:
        template <typename ReturnType,
                  typename... ParamType,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ReturnType, void> ||
                                                                   std::is_same_v<ReturnType, emscripten::val>>>,
                  typename = typename std::void_t<std::enable_if_t<std::is_same_v<ParamType, emscripten::val>>...>>
        static inline emscripten::val Bind(const std::function<ReturnType(ParamType...)> &fx)
        {
            USING_EMSCRIPTEN;
            return Bind(val(fx));
        }
    };
} // namespace Insane::Emscripten