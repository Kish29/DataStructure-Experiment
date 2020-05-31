#include "hashtable.h"
#include "cstdlib"
#include "ctime"

string result;
// 生成随机的长度小于10的string
void getRandomString() {
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890~!#$%^&*()-+=_/?.,\\[]{}";
    int len = charset.size();
    result = "";
    int len2 = rand() % 10;
    for (int i = 0; i < len2; i++) {
        result += charset[rand() % len];
    }
}

int main() {
    HashTable *h = new HashTable();
    for (int i = 0; i < 10; i++) {
        h->insert("test");
        /*if (i != 0 && a != 2) {
            break;
        }*/
    }

    // 两个for循环娱乐用，测一下随机生成10000个字母它的出现次，排除'#'
    for (int j = 0; j < 10000; ++j) {
        getRandomString();
        //std::cout << result << "---->";
        Node n(result);
        h->insert(n);
    }
    for (int k = 0; k < 10000; ++k) {
        getRandomString();
        int testhash = h->hash(result);
        if (testhash != -1 && h->get_pair(testhash)->first != "#") {
            if (h->get_pair(testhash)->second > 20)
                std::cout << "[" << h->get_pair(testhash)->first << "]:[" << h->get_pair(testhash)->second << "]\n";
        }
    }
//    for (int i = 0; i < h->get_size(); i++) {
//        if (h->get_pair(i)->first.compare("#")) {
//            std::cout << "[" << h->get_pair(i)->first << "]:[" << h->get_pair(i)->second << "]\n";
//        }
//    }
    delete h;
    return 0;
}
