#include <iostream>
#include <vector>

namespace tl{
    // Базовая структура
    template <typename... Types>
    struct TypeList{
        // Получение размера списка
        static constexpr int size(){
            return sizeof...(Types);
        }
    };

    // Вспомогательная структура для поиска типа по индексу
    template <size_t Index, typename... Types>
    struct TypeAt;    

    //Структура, которая возвращает тип по указанному индексу
    template<size_t Index, typename... Types>
    struct TypeAt;

    //Случай когда Index = 0
    template <typename T, typename... Rest>
    struct TypeAt<0, T, Rest...>{
        using type = T;
    };

    //Рекурсивная специализация для индексов больших нуля
    template <size_t Index, typename T, typename... Rest>
    struct TypeAt<Index, T, Rest...>{
        using type = typename TypeAt<Index - 1, Rest...>::type;
    };

}

int main(int argc, char* argv []){
    using list = tl::TypeList<int, float, char>;

    return 0;
}