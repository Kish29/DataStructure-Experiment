//
// Created by asus on 6/1/2020.
//
#include "iostream"

using namespace std;

class tst {
public:
    int a;
    int b;
    int c;

    tst() : a(-1), b(-1), c(-1) {}

    tst(int a, int b, int c) {
        a = a;
        b = b;
        c = c;
    }

    void print() const {
        cout << "a->" << a << "--b->" << b << "--c->" << c << endl;
    }
};


class test {
    tst *t;
    int _t_width;
    int _t_height;
public:
    test() : t(nullptr), _t_height(-2), _t_width(-2) {}

    test(tst *t, int _t_width, int _t_height) {
        t = t;
        _t_width = _t_width;
        _t_height = _t_height;
    }

    test(test &other) {
        t = other.t;
        _t_height = other._t_height;
        _t_width = other._t_width;
    }

    ~test() {
        delete[] t;
    }

    void set_tst(tst *val) {
        this->t = val;
    }

    void print() {
        if (t) {
            for (int i = 0; i < 4; ++i) {
                cout << "pixl->";
                t[i].print();
            }
        } else
            cout << "t is a null pointer\n";
        cout << "width->" << _t_width << "--height->" << _t_height << endl;
    }
};

class Test {
    test *_p_val;
    Test **children;
    int _height;
    int _width;
public:
    Test() : children(nullptr), _p_val(nullptr), _height(-3), _width(-3) {};

    ~Test() {
        delete _p_val;
        // 当children还是null pointer 的时候，要判断，不然访问不到children[i]的值
        if (children)
            for (int i = 0; i < 4; ++i)
                delete children[i];
        delete[] children;
    }

    void set_p_val(test *t) {
        _p_val = t;
    }

    void set_children(Test *input_children) {
        if (input_children) {
            children = new Test *[4];
            for (int i = 0; i < 4; ++i) {
                children[i] = &input_children[i];
            }
        }
    }

    void set_width_and_height(int w, int h) {
        _width = w;
        _height = h;
    }

    void deletePval() {
        delete _p_val;
    }

    Test(Test &other) {
        _p_val = other._p_val;
        _height = other._height;
        _width = other._width;
        children = other.children;
    }

    Test(Test &&other)
    noexcept {
        _p_val = other._p_val;
        other._p_val = nullptr;
        children = other.children;
        for (int i = 0; i < 4; i++) {
            other.children[i] = nullptr;
        }
        _height = other._height;
        _width = other._width;
    }

    void print() const {
        if (_p_val)
            _p_val->print();
        else
            cout << "_p_val is a null pointer.\n";
        if (children) {
            cout << "children is not a null pointer.\n";
            for (int i = 0; i < 4; ++i) {
                if (children[i])
                    children[i]->print();
                else
                    cout << "children[" << i << "] is a null pointer\n";
            }
        } else
            cout << "children is a null pointer.\n";
        cout << "_height->" << _height << "--_width->" << _width << endl;
    }
};

#include "tree.h"
int main() {
    Node n1, n2, n3, n4;
    n1.print();
    n2.print();
    n3.print();
    n4.print();
    return 0;
}

