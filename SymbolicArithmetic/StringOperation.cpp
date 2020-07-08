#include "StringOperation.h"

std::string SymbolArithmetic::Detail::StringOperation::GetBiggerOrEqualSubstringLeft(const std::string &number, const std::string &equivalent) {
    if (number.size() < equivalent.size())
        return number;

    const std::string &result = number.substr(0, equivalent.size());
    if (result.compare(equivalent) < 0)
        return number.substr(0, equivalent.size()+1);
    return result;
}

void SymbolArithmetic::Detail::StringOperation::EqualizeLengthRight(std::string &first, std::string &second) {
    int difference = first.size() - second.size();
    if (difference < 0)
        first += std::string(-difference,'0');
    else
        second += std::string(difference,'0');
}

void SymbolArithmetic::Detail::StringOperation::EqualizeLengthLeft(std::string &first, std::string &second) {
    int difference = first.size() - second.size();
    if (difference < 0)
        first = std::string(-difference,'0') + first;
    else
        second = std::string(difference,'0') + second;
}

std::string SymbolArithmetic::Detail::StringOperation::RemoveZerosLeft(std::string &number) {
    int rank = number.find_first_not_of('0');
    if (rank > 0 && number[rank] != '.')
        number = number.substr(rank, std::string::npos);
    else if (rank == std::string::npos)
        number.clear();

    return number;
}

std::string SymbolArithmetic::Detail::StringOperation::RemoveZerosRight(std::string &number) {
    int rank = number.find_last_not_of('0');
    if (rank < number.size() - 1 && number[rank] != '.')
        number = number.substr(0, rank+1);
    else if (rank == std::string::npos)
        number.clear();

    return number;
}