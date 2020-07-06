#ifndef SYMCALCULATOR_REALNUMBER_H
#define SYMCALCULATOR_REALNUMBER_H

#include "SymbolOperation.h"
#include "StringOperation.h"

namespace SymbolArithmetic {
    enum Sign : char {
        Plus = '+',
        Minus = '-',
    };

    class RealNumber {
    private:
        Sign sign;
        std::string wholePart;
        std::string fractionalPart;

        void SplitNumber(const std::string &number);
    public:
        explicit RealNumber(const std::string& number);

        virtual std::string ToString();

        friend RealNumber operator+(const RealNumber &number1, const RealNumber &number2);

        friend RealNumber operator-(const RealNumber &number1, const RealNumber &number2);
        friend RealNumber operator-(const RealNumber &number);

        friend bool operator>=(const RealNumber &number1, const RealNumber &number2);

        static RealNumber Abs(const RealNumber &number);
    };
}



#endif //SYMCALCULATOR_REALNUMBER_H
