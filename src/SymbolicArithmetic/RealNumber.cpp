#include "RealNumber.h"

SymbolArithmetic::RealNumber::RealNumber(const std::string& number) : sign(Sign::Plus) {
    SplitNumber(number);
    Detail::StringOperation::RemoveZerosLeft(wholePart);
    Detail::StringOperation::RemoveZerosRight(fractionalPart);

    if (wholePart.empty()) wholePart = "0";
    if (fractionalPart.empty()) fractionalPart = "0";
}

std::string SymbolArithmetic::RealNumber::ToString() {
    std::string signString = (sign != Sign::Plus) ? std::string(1,sign) : "";
    return signString + wholePart + "." + fractionalPart;
}

std::ostream &SymbolArithmetic::operator<<(std::ostream &out, const SymbolArithmetic::RealNumber &number) {
    if (number.sign != Sign::Plus)
        out << std::string(1, number.sign);
    out << number.wholePart;
    if (number.fractionalPart != "0")
        out << std::string(".") << number.fractionalPart;

    return out;
}

SymbolArithmetic::RealNumber SymbolArithmetic::operator-(const SymbolArithmetic::RealNumber &number) {
    if (number.sign == Sign::Plus)
        return RealNumber("-" + number.wholePart + "." + number.fractionalPart);
    else
        return RealNumber("+" + number.wholePart + "." + number.fractionalPart);
}

void SymbolArithmetic::RealNumber::SplitNumber(const std::string &number) {
    wholePart = number;

    int dotPos = number.find('.');
    if (dotPos != std::string::npos) {
        wholePart = number.substr(0, dotPos);
        fractionalPart = number.substr(dotPos+1, std::string::npos);
    }

    if (wholePart[0] == Sign::Plus || wholePart[0] == Sign::Minus) {
        sign = (Sign)wholePart[0];
        wholePart = wholePart.substr(1, std::string::npos);
    }
}

SymbolArithmetic::RealNumber SymbolArithmetic::operator+(const SymbolArithmetic::RealNumber &number1, const SymbolArithmetic::RealNumber &number2) {
    if (number1.sign != number2.sign) {
        if (number1.sign == Sign::Plus)
            return number1 - RealNumber::Abs(number2);
        else
            return number2 - RealNumber::Abs(number1);
    }
    
    std::string newFractionalPart;
    std::string fractionalOverflow;
    std::string firstFraction = number1.fractionalPart;
    std::string secondFraction = number2.fractionalPart;

    Detail::StringOperation::EqualizeLengthRight(firstFraction, secondFraction);
    newFractionalPart = Detail::SymbolOperation::Add(firstFraction, secondFraction);

    if (newFractionalPart.size() > firstFraction.size()) {
        fractionalOverflow = newFractionalPart.substr(0, newFractionalPart.size() - firstFraction.size());
        newFractionalPart = newFractionalPart.substr(fractionalOverflow.size(), std::string::npos);
    }
    std::string newWholePart = Detail::SymbolOperation::Add(number1.wholePart, number2.wholePart, fractionalOverflow);

    return RealNumber(std::string(1, number1.sign) + newWholePart + "." + newFractionalPart);
}

SymbolArithmetic::RealNumber SymbolArithmetic::operator-(const SymbolArithmetic::RealNumber &number1, const SymbolArithmetic::RealNumber &number2) {
    if (number2.sign == Sign::Minus)
        return number1 + RealNumber::Abs(number2);
    if (number1.sign == Sign::Minus)
        return number1 + -number2;

    bool firstBigger = number1 >= number2;
    RealNumber bigger = firstBigger ? number1 : number2;
    RealNumber less = firstBigger ? number2 : number1;

    Detail::StringOperation::EqualizeLengthRight(bigger.fractionalPart, less.fractionalPart);
    int dotPos = bigger.wholePart.size();

    std::string sub = Detail::SymbolOperation::Sub(bigger.wholePart + bigger.fractionalPart, less.wholePart + less.fractionalPart);

    return RealNumber((firstBigger ? "+" : "-") + sub.substr(0,  dotPos) + "." + sub.substr(dotPos, std::string::npos));
}

SymbolArithmetic::RealNumber SymbolArithmetic::operator*(const SymbolArithmetic::RealNumber &number1, const SymbolArithmetic::RealNumber &number2) {
    Sign resultSign = (number1.sign == number2.sign) ? Sign::Plus : Sign::Minus;

    std::string firstNumber = number1.wholePart + number1.fractionalPart;
    std::string secondNumber = number2.wholePart + number2.fractionalPart;

    unsigned int dotPosRight = number1.fractionalPart.size() + number2.fractionalPart.size();

    std::string result = Detail::SymbolOperation::Mul(firstNumber, secondNumber);
    return RealNumber(std::string(1, resultSign) + result.substr(0, result.size()-dotPosRight) + "." +
                      result.substr(result.size()-dotPosRight, std::string::npos));
}

SymbolArithmetic::RealNumber SymbolArithmetic::operator/(const SymbolArithmetic::RealNumber &number1, const SymbolArithmetic::RealNumber &number2) {
    std::string first = number1.wholePart + number1.fractionalPart;
    std::string second = number2.wholePart + number2.fractionalPart;
    unsigned int maxFractionalSize = number1.fractionalPart.size() > number2.fractionalPart.size() ?
            number1.fractionalPart.size() : number2.fractionalPart.size();
    unsigned int eps = 16;

    if (number1.fractionalPart.size() <= maxFractionalSize) first += std::string(maxFractionalSize - number1.fractionalPart.size(), '0');
    else if (number2.fractionalPart.size() <= maxFractionalSize) second += std::string(maxFractionalSize - number2.fractionalPart.size(), '0');

    first += std::string(eps, '0');

    auto result = Detail::SymbolOperation::Div(first, second);
    if (result.first.size() < eps) result.first.insert(0, std::string(eps - result.first.size(),'0'));

    std::string sign = number1.sign == number2.sign ? std::string(1, Sign::Plus) : std::string(1,Sign::Minus);
    unsigned int dotPos = result.first.size() - eps;
    return RealNumber(sign + result.first.substr(0,dotPos) + "." + result.first.substr(dotPos, std::string::npos));
}

bool SymbolArithmetic::operator>=(const SymbolArithmetic::RealNumber &number1, const SymbolArithmetic::RealNumber &number2) {
    if (number1.wholePart.size() != number2.wholePart.size())
        return number1.wholePart.size() > number2.wholePart.size();

    int compValue = number1.wholePart.compare(number2.wholePart);
    if (compValue != 0)
        return compValue > 0;

    std::string firstFractional = number1.fractionalPart;
    std::string secondFractional = number2.fractionalPart;
    Detail::StringOperation::EqualizeLengthRight(firstFractional, secondFractional);

    return firstFractional.compare(secondFractional) >= 0;
}

SymbolArithmetic::RealNumber SymbolArithmetic::RealNumber::Abs(const RealNumber &number) {
    return RealNumber(number.wholePart + "." + number.fractionalPart);
}
