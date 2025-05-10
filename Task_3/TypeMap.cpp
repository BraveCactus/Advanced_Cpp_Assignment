#include <iostream>
#include <tuple>
#include <string>
#include <type_traits>

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
    template <size_t Index, typename... Types>
    struct TypeAt; 
    
    // Специализация c TypeList
    template <size_t Index, typename... Types>
    struct TypeAt<Index, TypeList<Types...>>{
        using type = typename TypeAt<Index, Types...>::type;
    };

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

    //--------------------------------------------------------------
    // Структура для удаления элемента из TypeList
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

};   

template <typename... Types>
class TypeMap {
private:
    using KeyTypes = tl::TypeList<Types...>;
    std::tuple<Types...> values;
    
    // Вспомогательная структура для проверки наличия типа
    template <typename T>
    struct HasType {
        static constexpr bool value = tl::Contains<T, KeyTypes>::value;
    };
    
    // Вспомогательная структура для получения индекса типа
    template <typename T>
    struct TypeIndex {
        static constexpr size_t value = tl::IndexOf<T, KeyTypes>::index;
    };
    
public:
    // Добавление значения по типу ключа
    template <typename T>
    void AddValue(const T& value) {
        static_assert(HasType<T>::value, "Type not found in TypeMap");
        std::get<TypeIndex<T>::value>(values) = value;
    }   
    
    // Получение значения по типу ключа
    template <typename T>
    const T& GetValue() const {
        static_assert(HasType<T>::value, "Type not found in TypeMap");
        return std::get<TypeIndex<T>::value>(values);
    }      
    
    
    // Удаление значения по типу (устанавливает значение по умолчанию)
    template <typename T>
    void RemoveValue() {
        static_assert(HasType<T>::value, "Type not found in TypeMap");
        std::get<TypeIndex<T>::value>(values) = T{};
    }
};


int main() {
    TypeMap<int, double, std::string> myTypeMap;
    
    myTypeMap.AddValue<int>(42);
    myTypeMap.AddValue<double>(3.14);
    myTypeMap.AddValue<std::string>("Hello");
    
    std::cout << "Value for int: " << myTypeMap.GetValue<int>() << std::endl;
    std::cout << "Value for double: " << myTypeMap.GetValue<double>() << std::endl;
    std::cout << "Value for string: " << myTypeMap.GetValue<std::string>() << std::endl;

    using MyList = tl::TypeList<int, double, float>;
    using RemovedInt = tl::Remove<int, MyList>::type;    
    
    static_assert(std::is_same_v<RemovedInt, tl::TypeList<double, float>>, 
                 "Remove int failed");    
    
    static_assert(tl::IndexOf<int, MyList>::index == 0, 
                 "Wrong index for double");
    
    myTypeMap.RemoveValue<std::string>();
    std::cout << "After remove, string value: " << myTypeMap.GetValue<std::string>() << std::endl;

}