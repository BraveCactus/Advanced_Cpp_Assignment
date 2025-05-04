#include <iostream>
#include <vector>
#include <type_traits> //Для false_type и true_type


//std::true_type — тип, представляющий true (содержит статическое value = true).
//std::false_type — тип, представляющий false (содержит статическое value = false).

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
    // Вспомогательная структура для поиска типа по индексу
    template <size_t Index, typename... Types>
    struct TypeAt;    

    //Специализация когда Index = 0
    template <typename T, typename... Rest>
    struct TypeAt<0, T, Rest...>{
        using type = T;
    };

    //Рекурсивная специализация для индексов больших нуля
    template <size_t Index, typename T, typename... Rest>
    struct TypeAt<Index, T, Rest...>{
        using type = typename TypeAt<Index - 1, Rest...>::type;
    };
    //--------------------------------------------------------------

    //Структура для проверки наличия типа
    template <typename... Types>
    struct Contains;

    //Специализация для пустого списка (наследуем false_type)
    template<typename T>
    struct Contains<T>: std::false_type{};

    //Специализация, когда первый тип совпадает с искомым (наследуем true_type)
    template <typename T, typename... Rest>
    struct Contains<T, T, Rest...>: std::true_type{};

    //Специализация, когда первый тип НЕ совпадает с искомым 
    template <typename T1, typename T2, typename... Rest>
    struct Contains<T1, T2, Rest...>: Contains<T1, Rest...>{};     
    

}

int main(int argc, char* argv []){
    using list = tl::TypeList<int, float, char>;
    using t1 = tl::TypeAt<1, int, float, char>;
    using t2 = tl::Contains<int, int, float, char>;

    static_assert(std::is_same_v<typename t1::type, float>, "Несовпадение типов");
    static_assert(t2::value, "Тип не содержится в TypeList");
    std::cout << "Ок!" << std::endl;

    return 0;
}