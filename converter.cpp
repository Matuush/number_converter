#include <iostream>
#include <string>
#include <map>

namespace Converter{
    std::map<const char*, std::map<std::string, int>> charsets = {
        {"romanPre", {
            {"IV", 4},
            {"IX", 9},
            {"XL", 40},
            {"XC", 90},
            {"CD", 400},
            {"CM", 900}
        }},
        {"roman", {
            {"I", 1},
            {"V", 5},
            {"X", 10},
            {"L", 50},
            {"C", 100},
            {"D", 500},
            {"M", 1000},
        }}
    };

    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    std::map<const char*, std::map<int, std::string>> rCharsets = {
        {"roman", {
            {values[0], "M"},
            {values[1], "CM"},
            {values[2], "D"},
            {values[3], "CD"},
            {values[4], "C"},
            {values[5], "XC"},
            {values[6], "L"},
            {values[7], "XL"},
            {values[8], "X"},
            {values[9], "IX"},
            {values[10], "V"},
            {values[11], "IV"},
            {values[12], "I"}
        }}
    };

    int fromRoman(std::string roman) {
        for (unsigned int i = 0; i < roman.size(); i++) roman[i] = toupper(roman[i]);
        unsigned long result = 0;
        for (int i = 0; i < roman.size(); i++) {
            std::string u{roman[i], roman[i + 1]};
            if (charsets["romanPre"].count(u) != 0) {
                result += charsets["romanPre"][u];
                roman.erase(i, 2);
                i--;
            }
        }
        for (; roman.size() > 0; roman.erase(0, 1)) result += charsets["roman"][{roman[0]}];
        return result;
    }

    std::string toRoman(int number) {
        std::string result = "";
        for(unsigned int i = 0; i < rCharsets["roman"].size(); i++) {
            while(number - values[i] >= 0) {
                result += rCharsets["roman"][values[i]];
                number -= values[i];
            }
        }
        return result;
    }

    std::string baseCharset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string toBase(unsigned int value, unsigned int p_base) {
        std::string result = "", reversed = "";
        for(unsigned int base = 1; value > 0; value -= value % (base * p_base), base *= p_base) result += baseCharset[value % (base * p_base) / base];
        for(int i = result.length() - 1; i >= 0; i--) reversed += result[i];
        return reversed;
    }

    int fromBase(std::string value, unsigned int p_base) {
        unsigned int result = 0, base = 1;
        for(int i = value.length() - 1; i >= 0; i--, base *= p_base)
            result += baseCharset.find(value[i]) * base;
        return result;
    }
}

int e(int m, int n){
    if(m % n == 0) return n;
    else return e(n, m % n);
}

int main(){
    std::cout << e(63, 14);
    return 0;
}