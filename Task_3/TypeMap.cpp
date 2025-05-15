#include <iostream>
#include <tuple>
#include <string>
#include <type_traits>
#include "TypeList.h"

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