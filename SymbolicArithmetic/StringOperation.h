#ifndef SYMCALCULATOR_STRINGOPERATION_H
#define SYMCALCULATOR_STRINGOPERATION_H

#include <string>

namespace SymbolArithmetic {
    namespace Detail {
        class StringOperation {
        public:
            /// @brief Делает длину чисел одинаковой, добавляя у меньшего числа нули справа
            static void EqualizeLengthRight(std::string &first, std::string &second);
            /// @brief Удаляет у числа незначащие нули слева
            static std::string RemoveZerosLeft(std::string &number);
            /// @brief Удаляет у числа незначащие нули справа
            static std::string RemoveZerosRight(std::string &number);
        };
    }
}


#endif //SYMCALCULATOR_STRINGOPERATION_H
