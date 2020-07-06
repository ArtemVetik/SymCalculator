#include "StringOperation.h"

void SymbolArithmetic::Detail::StringOperation::EqualizeLengthRight(std::string &first, std::string &second) {
    int difference = first.size() - second.size();
    if (difference < 0)
        first += std::string(-difference,'0');
    else
        second += std::string(difference,'0');
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