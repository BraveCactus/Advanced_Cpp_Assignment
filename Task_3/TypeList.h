#pragma once
#include <type_traits>

namespace tl {
    // Базовая структура TypeList
    template <typename... Types>
    struct TypeList {
        // Получение размера списка
        static constexpr int size() {
            return sizeof...(Types);
        }
    };

    //--------------------------------------------------------------
    // Поиск типа по индексу (TypeAt)
    template <size_t Index, typename... Types>
    struct TypeAt;

    // Специализация для TypeList
    template <size_t Index, typename... Types>
    struct TypeAt<Index, TypeList<Types...>> {
        using type = typename TypeAt<Index, Types...>::type;
    };

    // Базовый случай: Index = 0 (возвращаем первый тип)
    template <typename T, typename... Rest>
    struct TypeAt<0, T, Rest...> {
        using type = T;
    };

    // Рекурсивный случай: Index > 0 (продолжаем поиск)
    template <size_t Index, typename T, typename... Rest>
    struct TypeAt<Index, T, Rest...> {
        using type = typename TypeAt<Index - 1, Rest...>::type;
    };
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    // Проверка наличия типа (Contains)
    template <typename... Types>
    struct Contains;

    // Специализация для TypeList
    template <typename T, typename... Types>
    struct Contains<T, TypeList<Types...>> : Contains<T, Types...> {};

    // Базовый случай: пустой список (false)
    template<typename T>
    struct Contains<T> : std::false_type {};

    // Совпадение типа (true)
    template <typename T, typename... Rest>
    struct Contains<T, T, Rest...> : std::true_type {};

    // Несовпадение (продолжаем поиск)
    template <typename T1, typename T2, typename... Rest>
    struct Contains<T1, T2, Rest...> : Contains<T1, Rest...> {};
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    // Поиск индекса типа (IndexOf)
    template<typename... Types>
    struct IndexOf;

    // Специализация для TypeList
    template <typename T, typename... Types>
    struct IndexOf<T, TypeList<Types...>> : IndexOf<T, Types...> {};

    // Найден нужный тип (возвращаем 0)
    template<typename T, typename... Rest>
    struct IndexOf<T, T, Rest...> {
        static constexpr size_t index = 0;
    };

    // Не найден (продолжаем поиск и увеличиваем индекс)
    template<typename T1, typename T2, typename... Rest>
    struct IndexOf<T1, T2, Rest...> {
        static constexpr size_t index = 1 + IndexOf<T1, Rest...>::index;
    };

    // Тип не найден (ошибка компиляции)
    template <typename T>
    struct IndexOf<T> {
        static_assert(sizeof(T) == 0, "Тип не найден в TypeList");
    };
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    // Добавление типа в конец (PushBack)
    template<typename... Types>
    struct PushBack;

    template<typename NT, typename... Types>
    struct PushBack<NT, TypeList<Types...>> {
        using type = TypeList<Types..., NT>;
    };

    // Добавление типа в начало (PushFront)
    template<typename... Types>
    struct PushFront;

    template<typename NT, typename... Types>
    struct PushFront<NT, TypeList<Types...>> {
        using type = TypeList<NT, Types...>;
    };
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    // Удаление типа из TypeList (Remove)
    template<typename T, typename... Types>
    struct Remove;

    // Специализация для TypeList
    template<typename T, typename... Types>
    struct Remove<T, TypeList<Types...>> {
        using type = typename Remove<T, Types...>::type;
    };

    // Базовый случай - пустой список
    template<typename T>
    struct Remove<T, TypeList<>> {
        using type = TypeList<>;
    };

    // Если тип совпадает - пропускаем его (удаляем)
    template<typename T, typename... Rest>
    struct Remove<T, TypeList<T, Rest...>> {
        using type = typename Remove<T, TypeList<Rest...>>::type;
    };

    // Если тип не совпадает - сохраняем его и продолжаем
    template<typename T, typename Other, typename... Rest>
    struct Remove<T, TypeList<Other, Rest...>> {
        using type = typename PushFront<
            Other,
            typename Remove<T, TypeList<Rest...>>::type
        >::type;
    };
    //--------------------------------------------------------------
}