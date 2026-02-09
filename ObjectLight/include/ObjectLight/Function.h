#pragma once
#include <cstddef> // nullptr_t Definition hinzufügen
#include <type_traits>
#include <memory>
#include <utility>

namespace OB {

    template <typename T> struct tag { using type = T; };
    template <typename Tag> using type_t = typename Tag::type;
	template <typename...> using void_t = void;
    

    namespace detail {
        template <class G, class... Args>
        using invoke_t = decltype(std::declval<G>()(std::declval<Args>()...));

        template <class Sig, class = void>
        struct res_of {};
        template <class G, class... Args>
        struct res_of<G(Args...), void_t<invoke_t<G, Args...>>> : tag<invoke_t<G, Args...>> {};
    }

    template <class Sig>
    using res_of = detail::res_of<Sig>;

    template <class Sig>
    using result_of = detail::res_of<Sig>;

    template <class Sig>
    using res_of_t = OB::type_t<detail::res_of<Sig>>;

    template <class Sig>
    using result_of_t = detail::res_of<Sig>;

    template <class Sig>
    class basic_function;

    template<size_t size, size_t align = alignof(void*)>
    struct aligned_storage {
        struct type { alignas(align) unsigned char data[size]; };
    };

    template<size_t size, size_t align = alignof(void*)>
    using aligned_storage_t = typename aligned_storage<size, align>::type;


    template <class R, class... Args>
    class basic_function<R(Args...)> {
        struct vtable_t {
            void (*mover)(void* src, void* dest);
            void (*destroyer)(void*);
            R(*invoke)(void const* t, Args &&...args);

            template <class T> static vtable_t const* get() {
                static const vtable_t m_vtable = {
                    [](void* src, void* dest) { new (dest) T(std::move(*static_cast<T*>(src))); },
                    [](void* t) { static_cast<T*>(t)->~T(); },
                    [](void const* t, Args &&...args) -> R {
                        return (*static_cast<T const*>(t))(std::forward<Args>(args)...);
                    }
                };
                return &m_vtable;
            }
        };
    public:
        using return_type = R;

        basic_function() noexcept : m_asdata() {}
        basic_function(const basic_function& o) noexcept
            : m_vtable(o.m_vtable), m_asdata(o.m_asdata) {
        }

        basic_function(basic_function&& o) noexcept
            : m_vtable(o.m_vtable) {
            if (m_vtable) m_vtable->mover(&o.m_asdata, &m_asdata);
        }

        template <class F, class dF = std::decay_t<F>, std::enable_if_t < !std::is_same<dF, basic_function>{} > * = nullptr,
            std::enable_if_t < std::is_convertible<OB::res_of_t <dF& (Args...)>, R>{} > * = nullptr >
        basic_function(F && f) : m_vtable(vtable_t::template get<dF>()) {
            static_assert(sizeof(dF) <= sizeof(void*) * 4, "object too large");
            static_assert(alignof(dF) <= alignof(void*), "object too aligned");
            new (&m_asdata) dF(std::forward<F>(f));
        }
        ~basic_function() {
            if (m_vtable) m_vtable->destroyer(&m_asdata);
        }


        basic_function& operator=(const basic_function& o) {
            this->~basic_function();
            new (this) basic_function(std::move(o));
            return *this;
        }

        basic_function& operator=(basic_function&& o) noexcept {
            this->~basic_function();
            new (this) basic_function(std::move(o));
            return *this;
        }

        explicit operator bool() const {
            return m_vtable;
        }

        return_type operator()(Args... args) const {
            return m_vtable->invoke(&m_asdata, std::forward<Args>(args)...);
        }
    private:
        vtable_t const* m_vtable = nullptr;
        OB::aligned_storage_t<sizeof(void*) * 4, alignof(void*)> m_asdata;
    };

    template <class R, class... Args>
    inline bool operator==(const basic_function<R(Args...)>& func, nullptr_t) {
        return !static_cast<bool>(func);
    }


    template <class R, class... Args>
    inline bool operator==(nullptr_t, const basic_function<R(Args...)>& func) {
        return !static_cast<bool>(func);
    }

    template <class R, class... Args>
    inline bool operator!=(const basic_function<R(Args...)>& func, nullptr_t) {
        return static_cast<bool>(func);
    }

    template <class R, class... Args>
    inline bool operator!=(nullptr_t, const basic_function<R(Args...)>& func) {
        return static_cast<bool>(func);
    }

    template <class R, class... Args>
    using function = basic_function<R(Args...)>;

}