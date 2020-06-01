////
//// Created by asus on 6/1/2020.
////
//#include "iostream"
//
//using namespace std;
//
//class tst {
//public:
//    int a;
//    int b;
//    int c;
//
//    tst() : a(-1), b(-1), c(-1) {}
//
//    tst(int a, int b, int c) {
//        a = a;
//        b = b;
//        c = c;
//    }
//
//    void print() const {
//        cout << "a->" << a << "--b->" << b << "--c->" << c << endl;
//    }
//};
//
//
//class test {
//    tst *t;
//    int _t_width;
//    int _t_height;
//public:
//    test() : t(nullptr), _t_height(-2), _t_width(-2) {}
//
//    test(tst *t, int _t_width, int _t_height) {
//        t = t;
//        _t_width = _t_width;
//        _t_height = _t_height;
//    }
//
//    test(test &other) {
//        t = other.t;
//        _t_height = other._t_height;
//        _t_width = other._t_width;
//    }
//
//    ~test() {
//        delete[] t;
//    }
//
//    void set_tst(tst *val) {
//        this->t = val;
//    }
//
//    void print() {
//        if (t) {
//            cout << "pixl->";
//            t->print();
//        } else
//            cout << "t is a null pointer\n";
//        cout << "width->" << _t_width << "--height->" << _t_height << endl;
//    }
//};
//
//class Test {
//    test *_p_val;
//    Test **children;
//    int _height;
//    int _width;
//public:
//    Test() : children(new Test *[4]), _p_val(nullptr), _height(-3), _width(-3) {
//        for (int i = 0; i < 4; ++i)
//            children[i] = nullptr;
//    };
//
//    ~Test() {
//        delete _p_val;
//        // 当children还是null pointer 的时候，要判断，不然访问不到children[i]的值
//        if (children)
//            for (int i = 0; i < 4; ++i) {
//                delete children[i];
//            }
//        delete[] children;
//    }
//
//    void set_p_val(test *t) {
//        _p_val = t;
//    }
//
//    void set_children() {
//        _p_val = nullptr;
//        children = nullptr;
//    }
//
//    void set_width_and_height(int w, int h) {
//        _width = w;
//        _height = h;
//    }
//
//    Test(Test &other) {
//        _p_val = other._p_val;
//        _height = other._height;
//        _width = other._width;
//        children = other.children;
//    }
//
//    Test(Test &&other) noexcept {
//        _p_val = other._p_val;
//        other._p_val = nullptr;
//        children = other.children;
//        for (int i = 0; i < 4; i++) {
//            other.children[i] = nullptr;
//        }
//        _height = other._height;
//        _width = other._width;
//    }
//
//    void print() const {
//        if (_p_val)
//            _p_val->print();
//        else
//            cout << "_p_val is a null pointer.\n";
//        if (children) {
//            cout << "children is not a null pointer.\n";
//            for (int i = 0; i < 4; ++i) {
//                if (children[i])
//                    children[i]->print();
//                else
//                    cout << "children[" << i << "] is a null pointer\n";
//            }
//        } else
//            cout << "children is a null pointer.\n";
//        cout << "_height->" << _height << "--_width->" << _width << endl;
//    }
//};
//
//
//int main() {
//    tst t1;
//    t1.print();
//    test t2;
//    t2.print();
//    t2.set_tst(&t1);
//    t2.print();
//    Test t3;
//    t3.print();
//    t3.set_p_val(&t2);
//    t3.print();
//    t3.set_children();
//    Test t4 = t3;
//    t4.print();
//    t4.set_width_and_height(99,99);
//    t4.print();
//    t3.print();
//    cout << "set children\n";
//    t4.set_children();
//    cout << "after set children:";
//    t4.print();
//    cout << "t3:";
//    t3.print();
//    t4 = new Test();
//    return 0;
//}

#include "iostream"
#include "string.h"
#include "stdio.h"

using namespace std;

int main() {
    string str;
    strcpy((char *) str.c_str(), "wocaonima\0");
    cout << str.c_str() << "\n";
    str = "worinima";
    cout << str << "\n" << str.c_str();
    const char *p = str.c_str();
    cout << "\n" << &p;
}
