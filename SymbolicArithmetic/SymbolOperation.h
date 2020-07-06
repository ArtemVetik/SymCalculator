#ifndef SYMCALCULATOR_SYMBOLOPERATION_H
#define SYMCALCULATOR_SYMBOLOPERATION_H

#include <string>
#include <algorithm>
#include <vector>

namespace SymbolArithmetic {
    namespace Detail {
        class SymbolOperation {
        private:
            static std::string Add(const std::vector<std::string> &numbers);
        public:
            /// @brief Сложение n целых чисел
            /// @param numbers список целых чисел в строковом представлении
            template<typename... T>
            static std::string Add(const T& ... numbers);
            /// @brief Вычитание целых чисел
            /// @note Первое чило должно быть больше второго, иначе функция отработает с ошибкой
            static std::string Sub(const std::string &first, const std::string &second);
            static std::string Mul(const std::string &first, const std::string &second);
        };

        template<typename... T>
        std::string SymbolArithmetic::Detail::SymbolOperation::Add(const T& ... numbers) {
            auto numberList = std::vector<std::string>{numbers...};
            return Add(numberList);
        }
    }
}

#endif //SYMCALCULATOR_SYMBOLOPERATION_H
