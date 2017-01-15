//
// Created by StevensChew on 17/1/15.
//

#ifndef ASPECT_ASPECT_H
#define ASPECT_ASPECT_H

using namespace std;

namespace aspect {
#define HAS_MEMBER(member) \
    template<typename T, typename... Args> \
    struct has_member_##member \
    { \
       private: \
                template<typename U> static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type()); \
                template<typename U> static std::false_type Check(...); \
       public: \
                enum {value = std::is_same<decltype(Check<T>(0)), std::true_type>::value}; \
}; \


    HAS_MEMBER(Foo)std

    HAS_MEMBER(Before)std

    HAS_MEMBER(After)std

    template<typename Func, typename... Args>
    struct Aspect {
        Aspect(Func &&func) : m_func(std::forward<Func>(func)) {

        }

        template<typename T>
        typename std::enable_if<has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type
        Invoke(Args... args, T &&aspect) {
            aspect.Before(std::forward<Args>(args)...);
            m_func(std::forward<Args>(args)...);
            aspect.After(std::forward<Args>(args)...);
        };

        template<typename T>
        typename std::enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type
        Invoke(Args &&... args, T &&aspect) {
            m_func(std::forward<Args>(args)...);
            aspect.After(std::forward<Args>(args)...);
        }

        template<typename Head, typename... Tail>
        void Invoke(Args &&... args, Head &&headAspect, Tail &&... tailAspect) {
            headAspect.Before(std::forward<Args>(args)...);
            Invoke(std::forward<Args>(args...), std::forward<Tail>(tailAspect)...);
            headAspect.After(std::forward<Args>(args)...);
        };

    private:
        Func m_func;
    };

    template<typename T> using identity_t = T;

    template<typename... AP, typename... Args, typename Func>
    void Invoke(Func &&func, Args &&... args) {
        Aspect<Func, Args...> asp(std::forward<Func>(func));
        asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
    }
}

#endif //ASPECT_ASPECT_H
