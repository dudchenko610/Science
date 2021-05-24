#pragma once

namespace core
{

    template <typename... T>
    struct Tuple { };

    namespace tuple 
    {
        template<
            size_t idx,
            template <typename...> class Tuple,
            typename... Args
        >
            auto get(Tuple<Args...>& t);
    }

    // -------------------------------------------------------------------------
    // Tuple Implementation ----------------------------------------------------
    template<typename T, typename... Rest>
    struct Tuple<T, Rest...> {

        Tuple(const T& f, const Rest &... r)
            : first(f)
            , rest(r...) {
        }

        T                   first;
        Tuple<Rest...>  rest;

        template<size_t idx>
        auto get()
        {
            return tuple::get<idx>(*this);
        }
        
    };

    namespace tuple 
    {
        template<size_t idx, typename T>
        struct GetHelper { };

        // -------------------------------------------------------------------------
        // GetHelper ---------------------------------------------------------------
        template<typename T, typename... Rest >
        struct GetHelper<0, Tuple<T, Rest...>> { // Specialization for index 0
            static T get(Tuple<T, Rest...>& data) {
                return data.first;
            }
        };


        template<size_t idx, typename T, typename... Rest>
        struct GetHelper<idx, Tuple<T, Rest...>> { // GetHelper Implementation
            static auto get(Tuple<T, Rest...>& data) {
                return GetHelper<idx - 1, Tuple<Rest...>>::get(data.rest);
            }
        };


        // -------------------------------------------------------------------------
        // get Implementation ------------------------------------------------------
        template<
            size_t idx,
            template <typename...> class Tuple,
            typename... Args
        >
            auto get(Tuple<Args...>& t) {
            return GetHelper<idx, Tuple<Args...>>::get(t);
        }
    }
	
}