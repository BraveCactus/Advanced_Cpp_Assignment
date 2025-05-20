#include <iostream>
#include <vector>
#include <type_traits> //Для false_type и true_type

//std::true_type — тип, представляющий true (содержит статическое value = true).
//std::false_type — тип, представляющий false (содержит статическое value = false).

//Проблема: возникает ошибка если в TypeAt добавить структуру TypeList
//static_assert(std::is_same_v<typename tl::TypeAt<3, myList>::type, double>, "...");

namespace tl{
    // Базовая структура
    template <typename... Types>
    struct TypeList{
        // Получение размера списка
        static constexpr int size(){
            return sizeof...(Types);
        }
    };

    //--------------------------------------------------------------
    //Cтруктура для поиска типа по индексу
    // Базовый шаблон TypeAtSup
    template <size_t Index, typename... Types>
    struct TypeAtSup;
    
    // Специализация для Index == 0
    template <typename T, typename... Rest>
    struct TypeAtSup<0, T, Rest...> {
        using type = T;
    };
    
    // Рекурсивный случай
    template <size_t Index, typename T, typename... Rest>
    struct TypeAtSup<Index, T, Rest...> {
        using type = typename TypeAtSup<Index - 1, Rest...>::type;
    };    

    // Теперь интерфейс TypeAt
    template <size_t Index, typename TList>
    struct TypeAt;
    
    // Специализация для TypeList
    template <size_t Index, typename... Types>
    struct TypeAt<Index, TypeList<Types...>> {
        using type = typename TypeAtSup<Index, Types...>::type;
    };
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    //Структура для проверки наличия типа
    template <typename... Types>
    struct Contains;

    // Специализация c TypeList
    template <typename T, typename... Types>
    struct Contains<T, TypeList<Types...>> : Contains<T, Types...> {};

    //Специализация для пустого списка (наследуем false_type)
    template<typename T>
    struct Contains<T>: std::false_type{};

    //Специализация, когда первый тип совпадает с искомым (наследуем true_type)
    template <typename T, typename... Rest>
    struct Contains<T, T, Rest...>: std::true_type{};

    //Специализация, когда первый тип НЕ совпадает с искомым 
    template <typename T1, typename T2, typename... Rest>
    struct Contains<T1, T2, Rest...>: Contains<T1, Rest...>{};     
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    //Структура для нахождения индекса конкретного типа
    template<typename... Types>
    struct IndexOf;

    // Специализация c TypeList
    template <typename T, typename... Types>
    struct IndexOf<T, TypeList<Types...>> : IndexOf<T, Types...>{};

    //Специализация, когда искомый индекс следующий
    template<typename T, typename... Rest>
    struct IndexOf<T, T, Rest...>{
        static constexpr size_t index = 0; 
    };

    //Специализация, когда искомый индекс НЕ следующий
    template<typename T1, typename T2, typename... Rest>
    struct IndexOf<T1, T2, Rest...>{
        static constexpr size_t index = 1 + IndexOf<T1, Rest...>::index; 
    };

    // Специализация для случая, когда тип не найден (вызовет ошибку компиляции)
    template <typename T>
    struct IndexOf<T> {
        static_assert(sizeof(T) == 0, "Тип не найден в TypeList");
    };   
    //--------------------------------------------------------------

    //--------------------------------------------------------------
    // Структура для добавления типа в конец
    template<typename... Types>
    struct PushBack;

    template<typename NT, typename... Types>
    struct PushBack<NT, TypeList<Types...>>{
        using type = TypeList<Types..., NT>;
    };

    // Структура для добавления типа в начало
    template<typename... Types>
    struct PushFront;

    template<typename NT, typename... Types>
    struct PushFront<NT, TypeList<Types...>>{
        using type = TypeList<NT, Types...>;
    };
    //--------------------------------------------------------------
};   



int main(int argc, char* argv []){
    using myList = tl::TypeList<int, float, char>;
    using t1 = tl::TypeAt<1, myList>; // можно using t1 = tl::TypeAt<1, int, float, char>;
    using t2 = tl::Contains<int, myList>; // можно using t2 = tl::Contains<int, int, float, char>;
    using ind1 = tl::IndexOf<float, myList>; // можно using ind1 = tl::IndexOf<float, int, float, char>;

    static_assert(std::is_same_v<typename t1::type, float>, "Несовпадение типов");
    static_assert(t2::value, "Тип не содержится в TypeList");
    static_assert(ind1::index == 1, "Тип не найден");
    
    static_assert(std::is_same_v<typename tl::TypeAt<2, myList>::type, char>, "TypeAt не работает!");   

    std::cout << "Ок!" << std::endl;

    return 0;
}