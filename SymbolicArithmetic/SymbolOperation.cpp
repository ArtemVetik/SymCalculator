#include "SymbolOperation.h"

std::string SymbolArithmetic::Detail::SymbolOperation::Add(const std::vector<std::string> &numberList) {
    std::string result;
    std::vector<std::string::const_iterator> numberPositions;
    std::string::iterator resultPosition;

    unsigned int maxSize = 0;
    for (const auto& number : numberList) {
        if (number.size() > maxSize)
            maxSize = number.size();
        numberPositions.emplace_back(number.cend());
    }
    result.resize(maxSize);
    resultPosition = result.end();

    unsigned int sum, mod = 0;
    bool hasSymbols;
    while (true) {
        sum = mod;

        hasSymbols = false;
        for (int i = 0; i < numberList.size(); ++i) {
            if (--numberPositions[i] >= numberList[i].cbegin()) {
                sum += *(numberPositions[i]) - '0';
                hasSymbols = true;
            }
        }
        if (!hasSymbols)
            break;

        mod = sum / 10;
        sum %= 10;

        *--resultPosition = '0' + sum;
    }

    if (mod != 0)
        result = std::to_string(mod) + result;

    return result;
}

std::string SymbolArithmetic::Detail::SymbolOperation::Sub(const std::string &first, const std::string &second) {
    std::string result = first;
    auto firstPosition = result.end();
    auto secondPosition = second.cend();

    unsigned char sub;
    while (--secondPosition >= second.cbegin()) {
        firstPosition--;
        sub = *firstPosition - *secondPosition;
        if (*secondPosition > *firstPosition) {
            sub += 10;
            auto tmpFirst = firstPosition;
            while (*--tmpFirst == '0')
                *tmpFirst = '9';
            *tmpFirst -= 1;
        }
        *firstPosition = '0' + sub;
    }

    return result;
}

std::string SymbolArithmetic::Detail::SymbolOperation::Mul(const std::string &first, const std::string &second) {
    std::vector<std::string> templateMults;

    int mul, mod;
    for (auto secondNumber = second.crbegin(); secondNumber != second.crend(); ++secondNumber) {
        mod = 0;
        templateMults.emplace_back(std::string());
        for (auto firstNumber = first.crbegin(); firstNumber != first.crend(); ++firstNumber) {
            mul = (*firstNumber - '0') * (*secondNumber - '0') + mod;
            mod = mul / 10;
            mul %= 10;
            templateMults.back().insert(0, std::to_string(mul));
        }
        if (mod != 0)
            templateMults.back().insert(0, std::to_string(mod));
        templateMults.back() += std::string(templateMults.size()-1,'0');
    }

    return Add(templateMults);
}

std::pair<std::string,std::string> SymbolArithmetic::Detail::SymbolOperation::Div(const std::string &first, const std::string &second) {
    std::vector<std::string> buffer;
    buffer.reserve(10);
    buffer.emplace_back("0");
    buffer.emplace_back(second);
    for (int i = 2; i < 10; ++i)
        buffer.emplace_back(Mul(std::to_string(i), second));

    unsigned int lastPos = 0;
    int div = 0;
    std::string result;
    std::string tempDiv;
    std::string mod;
    while (lastPos < first.size()) {
        tempDiv = StringOperation::GetBiggerOrEqualSubstringLeft(mod + first.substr(lastPos, std::string::npos), second);
        lastPos += tempDiv.size() - mod.size();
        result += std::string(tempDiv.size() - mod.size() - 1,'0');

        StringOperation::RemoveZerosLeft(tempDiv);
        if (tempDiv.empty())
            tempDiv = "0";
        for (div = 0; div < buffer.size(); ++div) {
            if (tempDiv.size() == buffer[div].size() && tempDiv.compare(buffer[div]) < 0 || tempDiv.size() < buffer[div].size())
                break;
        }
        div--;

        result += std::to_string(div);
        mod = Sub(tempDiv, buffer[div]);
        StringOperation::RemoveZerosLeft(mod);
    }

    return std::make_pair(result, mod);
}
