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

    unsigned char sum, mod = 0;
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
