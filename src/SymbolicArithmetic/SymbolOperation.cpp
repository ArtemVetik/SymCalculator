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

void SymbolArithmetic::Detail::SymbolOperation::FastFourierTransform(std::vector<std::complex<double>> &coefficients, bool invert) {
    unsigned int coefSize = coefficients.size();

    for (unsigned int i = 1, j = 0; i < coefSize; ++i) {
        unsigned int bit = coefSize >> 1u;
        for (; j>=bit; bit >>= 1u)
            j -= bit;
        j += bit;
        if (i < j)
            swap(coefficients[i], coefficients[j]);
    }

    for (unsigned int length = 2; length <= coefSize; length <<= 1u) {
        double ang = 2 * M_PI / length * (invert ? -1 : 1);
        std::complex<double> wLength (cos(ang), sin(ang));
        for (unsigned int i = 0; i < coefSize; i += length) {
            std::complex<double> w(1);
            for (int j = 0; j < length / 2; ++j) {
                std::complex<double> firstPart = coefficients[i + j];
                std::complex<double> secondPart = coefficients[i + j + length / 2] * w;
                coefficients[i+j] = firstPart + secondPart;
                coefficients[i + j + length / 2] = firstPart - secondPart;
                w *= wLength;
            }
        }
    }
    if (invert)
        for (int i = 0; i < coefSize; ++i)
            coefficients[i] /= coefSize;
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
    std::string result;

    std::vector<std::complex<double>> dftA,  dftB;
    for (const auto elem : first)
        dftA.emplace_back(elem - '0');
    for (const auto elem : second)
        dftB.emplace_back(elem - '0');

    unsigned int size = 1;
    while (size < std::max(first.size(), second.size())) size <<= 1u;
    size <<= 1u;
    dftA.resize (size);
    dftB.resize (size);

    FastFourierTransform(dftA, false), FastFourierTransform(dftB, false);
    for (int i = 0; i < size; ++i)
        dftA[i] = dftA[i] * dftB[i];
    FastFourierTransform(dftA, true);

    result.resize (size);

    int carry = 0, whole;
    for (int i = size - 1; i >= 0; --i) {
        whole = (int)floor(dftA[i].real() + 0.5) + carry;
        carry = whole / 10;
        whole = whole % 10;
        result[i] = '0' + whole;
    }

    result = result.substr(0, first.size() + second.size() - 1);
    if (carry != 0)
        result = std::to_string(carry) + result;

    return result;
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