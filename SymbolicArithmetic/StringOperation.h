#ifndef SYMCALCULATOR_STRINGOPERATION_H
#define SYMCALCULATOR_STRINGOPERATION_H

#include <string>

namespace SymbolArithmetic {
    namespace Detail {
        class StringOperation {
        public:
            /// @brief Сравнивает числа и возвращает минимальную часть первого числа слева, большую чем второе число
            /// @param number число, из которое надо преобразовать
            /// @param equivalent число, с которым происходит сравнение
            static std::string GetBiggerOrEqualSubstringLeft(const std::string &number, const std::string &equivalent);
            /// @brief Делает длину чисел одинаковой, добавляя у меньшего числа нули справа
            static void EqualizeLengthRight(std::string &first, std::string &second);
            /// @brief Делает длину чисел одинаковой, добавляя у меньшего числа нули слева
            static void EqualizeLengthLeft(std::string &first, std::string &second);
            /// @brief Удаляет у числа незначащие нули слева
            static std::string RemoveZerosLeft(std::string &number);
            /// @brief Удаляет у числа незначащие нули справа
            static std::string RemoveZerosRight(std::string &number);
        };
    }
}


#endif //SYMCALCULATOR_STRINGOPERATION_H
