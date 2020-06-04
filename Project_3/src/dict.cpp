#include "dict.h"

int Dict::insert(const char *str) {
    if (!str)
        return 1;
    //string cstr = convertToString(str);
    string cstr = str;
    if (!isAlpha(cstr))
        return 1;
    toLowerCase(cstr);
    int len = cstr.size();
    int first_of;
    while (!cstr.empty()) {
        // remove the leading and trailing spaces
        stringTrim(cstr);
        if (cstr.empty())
            return 1;
        first_of = cstr.find_first_of(' ', 0);
        if (first_of == string::npos) {
            if (isAlpha(cstr)) {
                Node n(cstr);
                h.insert(n);
                size++;
            }
            cstr = "";
        } else {
            string temp = cstr.substr(0, first_of);
            if (isAlpha(temp)) {
                Node n(temp);
                h.insert(n);
                size++;
            }
            cstr = cstr.substr(first_of, len);
        }
    }
    return 0;
}

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Dict::Dict() {
    size = 0;
}

void Dict::print() const {
    for (int i = 0; i < h.get_size(); i++) {
        if (h.get_pair(i)->first.compare("#")) {
            std::cout << "[" << h.get_pair(i)->first << "]:[" << h.get_pair(i)->second << "]\n";
        }
    }
    std::cout << "\nTotal: " << size << " words.\n";
}

bool Dict::isAlpha(string &word) {
    // filter word fill of spaces
    int space_nums = 0;
    if (word.empty())
        return false;
    else {
        for (char c : word) {
            // mainly for filtering nums 0~9
            // record space char nums
            if (48 <= c && c <= 57)
                return false;
            if (c == ' ')
                space_nums++;
        }
    }
    // space_nums must don't equal to is's lengths
    return space_nums != word.size();
}

string Dict::convertToString(char *str) {
    string cstr;
    if (!str)
        return cstr;
    else {
        int i = 0;
        while (str[i] != '\0') {
            // filter special chars, and convert them to space
            if (str[i] < 48 || str[i] > 122 || (91 <= str[i] && str[i] <= 96) || (58 <= str[i] && str[i] <= 64)) {
                if (str[i] == '-')
                    str[i] = '\0';
                else
                    str[i] = ' ';
            }
            cstr += str[i];
            i++;
        }
    }
    return cstr;
}

void Dict::toLowerCase(string &word) {
    if (word.empty())
        return;
    for (char &c : word) {
        c |= convertCode;
    }
}

void Dict::stringTrim(string &word) {
    // use java's algorithm
    int len = word.size();

    int st;
    for (st = 0; st < len && (word[st] & 255) <= 32; ++st);
    while (st < len && (word[len - 1] & 255) <= 32)
        len--;
    if (st <= 0 && len >= word.size())
        return; // will do nothing for word
    else
        word = word.substr(st, len - st);
}
