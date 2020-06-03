#include "tree.h"
#include <iostream>

Node::Node() {
    children = nullptr;
    p = nullptr;
    leaf = true; // 默认是叶子节点，当设置children时将不再是叶子节点
    // 默认全白色
    mean_r = mean_g = mean_b = 255;
    judgeNum = width = height = x = y = 0;
}

Node::Node(PNG *corner, int input_width, int input_height, int x, int y) {
    children = nullptr;
    leaf = true;
    p = corner;
    width = input_width;
    height = input_height;
    this->x = x;
    this->y = y;
	mean_r = mean_g = mean_b = 0;
    judgeNum = 0;
}

// 以下是4个相似并且我觉得非常冗余的代码，不过暂时没有想到好的优化方案，如果有，希望告知，万分感谢！！！
Node::Node(Node &other) {
    p = other.p;
    children = new Node *[4];
    if (other.children) {
        children = new Node *[4];
        for (int i = 0; i < 4; ++i) {
            if (other.children[i]) {
                if (leaf)
                    // 此时不再是叶子节点了
                    leaf = false;
                children[i] = new Node(*other.children[i]);
            }
        }
    } else
        children = nullptr;
    width = other.width;
    height = other.height;
    leaf = other.leaf;
    x = other.x;
    y = other.y;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    judgeNum = other.judgeNum;
}

Node::Node(Node &&other) {
    p = other.p;
    if (other.children) {
        children = new Node *[4];
        for (int i = 0; i < 4; ++i) {
            if (other.children[i]) {
                if (leaf)
                    // 此时不再是叶子节点了
                    leaf = false;
                children[i] = other.children[i];
                // must set null
                other.children[i] = nullptr;
            }
        }
    } else
        children = nullptr;
    width = other.width;
    height = other.height;
    leaf = other.leaf;
    x = other.x;
    y = other.y;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    judgeNum = other.judgeNum;
}


Node &Node::operator=(Node &other) {
    p = other.p;
    if (other.children) {
        children = new Node *[4];
        for (int i = 0; i < 4; ++i) {
            if (other.children[i]) {
                if (leaf)
                    // 此时不再是叶子节点了
                    leaf = false;
                children[i] = new Node(*other.children[i]);
            }
        }
    } else
        children = nullptr;
    width = other.width;
    height = other.height;
    leaf = other.leaf;
    x = other.x;
    y = other.y;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    judgeNum = other.judgeNum;
	return *this;
}

Node &Node::operator=(Node &&other) {
    p = other.p;
    if (other.children) {
        children = new Node *[4];
        for (int i = 0; i < 4; ++i) {
            if (other.children[i]) {
                if (leaf)
                    // 此时不再是叶子节点了
                    leaf = false;
                children[i] = other.children[i];
                // must set null
                other.children[i] = nullptr;
            }
        }
    } else
        children = nullptr;
    width = other.width;
    height = other.height;
    leaf = other.leaf;
    x = other.x;
    y = other.y;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    judgeNum = other.judgeNum;
	return *this;
}

void Tree::judge(int threshold) {
    root->judge_for_leaf(root, threshold);
}

void Tree::load_png(PNG *png) {
    if (png) {
        int with = png->get_width();
        int height = png->get_height();
        // 释放构造函数里为root申请的内存，一定要一个temp，不然root->creatTree会报错
        Node *temp = root;
        root = root->create_tree(png, with, height, 0, 0);
        // 现在才可以释放temp
        delete temp;
        temp = nullptr; // 置空
    }
}

/*
 ================================================
 ====DO NOT MODIFY ANY OF THE FUNCTIONS BELOW====
 ==============请不要修改以下任何函数==============
 ================================================
 */

Node::~Node() {
    if (children)
        for (int i = 0; i < 4; i++)
            //if (children[i]) 其实删不删除空指针没有影响的
            delete children[i];
    delete[] children;
}

void Node::print() {
    if (children)
        for (int i = 0; i < 4; ++i) {
            if (children[i])
                children[i]->print();
        }
    printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d\n", mean_r, mean_g, mean_b, width, height);
    //printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d,", p->red, p->green, p->blue, width, height);
    std::cout << "Leaf: " << leaf << std::endl;
}

pxl *Node::get_pxl() {
    return p->get_pxl(x, y);
}

Node *Node::create_tree(PNG *p, int width, int height, int x, int y) {
    // 传递5个参数，p是恒定的照片，with和height表示当前要处理的照片区块宽高，x和y存储相应的的像素点
    // 存储方式，均以顺时针方向，坐标记为x,y，高宽记为h,w，父节点在后面加一个p字母，孩子1的xy，hw记为x1、y1、h1、w1
    /*               ====坐标规律=======       ========高宽规律=========
     * children[0]: (xp, yp);                 (hp/2， wp/2)
     * children[1]: (xp + w1, yp)             (hp/2, wp - w1)
     * children[2]: (xp, yp+h1)               (hp - h1, wp/2)
     * children[3]: (xp + w1, y + h1)         (hp - h1, wp - w1)
     * */
    if (width == 1 && height == 1) {//说明是叶子节点
        Node *leaf_node = new Node(p, width, height, x, y);
		leaf_node->mean_r = p->get_pxl(x, y)->red;
		leaf_node->mean_g = p->get_pxl(x, y)->green;
		leaf_node->mean_b = p->get_pxl(x, y)->blue;
        return leaf_node;
    } else if (width == 1 && height > 1) {
        Node *parent_node = new Node(p, width, height, x, y);
        // 注意，这里必须要申请4个指针，并且后两个指针置空，后两个置空就行，因为只是申请了8字节的指针空间，还没有赋值
        // 所以不要去delete他们
        // 置空的原因是print()函数里面要用到判断，系统默认0x0是空指针，而野指针有可能不是0x0，造成段错误
        parent_node->children = new Node *[4];
        int child_height = height / 2;
        parent_node->children[0] = create_tree(p, 1, child_height, x, y);
        parent_node->children[1] = create_tree(p, 1, height - child_height, x, y + child_height);
        parent_node->children[2] = parent_node->children[3] = nullptr;
        parent_node->leaf = false;
        parent_node->mean_r = (parent_node->children[0]->mean_r + parent_node->children[1]->mean_r) / 2;
        parent_node->mean_g = (parent_node->children[0]->mean_g + parent_node->children[1]->mean_g) / 2;
        parent_node->mean_b = (parent_node->children[0]->mean_b + parent_node->children[1]->mean_b) / 2;
        return parent_node;
    } else if (width > 1 && height == 1) {
        Node *parent_node = new Node(p, width, height, x, y);
        parent_node->children = new Node *[4]();
        int child_width = width / 2;
        parent_node->children[0] = create_tree(p, child_width, 1, x, y);
        parent_node->children[1] = create_tree(p, width - child_width, 1, x + child_width, y);
        parent_node->children[2] = parent_node->children[3] = nullptr;
        parent_node->leaf = false;
        parent_node->mean_r = (parent_node->children[0]->mean_r + parent_node->children[1]->mean_r) / 2;
        parent_node->mean_g = (parent_node->children[0]->mean_g + parent_node->children[1]->mean_g) / 2;
        parent_node->mean_b = (parent_node->children[0]->mean_b + parent_node->children[1]->mean_b) / 2;
        return parent_node;
    } else {
        Node *parent_node = new Node(p, width, height, x, y);
        parent_node->children = new Node *[4];
        int child_width = width / 2;
        int child_height = height / 2;
        parent_node->children[0] = create_tree(p, child_width, child_height, x, y);
        parent_node->children[1] = create_tree(p, width - child_width, child_height, x + child_width, y);
        parent_node->children[2] = create_tree(p, child_width, height - child_height, x, y + child_height);
        parent_node->children[3] = create_tree(p, width - child_width, height - child_height, x + child_width,
                                               y + child_height);
        parent_node->leaf = false;
        parent_node->mean_r =
                (parent_node->children[0]->mean_r + parent_node->children[1]->mean_r + parent_node->children[2]->mean_r
                 + parent_node->children[3]->mean_r) / 4;
        parent_node->mean_g =
                (parent_node->children[0]->mean_g + parent_node->children[1]->mean_g + parent_node->children[2]->mean_g
                 + parent_node->children[3]->mean_g) / 4;
        parent_node->mean_b =
                (parent_node->children[0]->mean_b + parent_node->children[1]->mean_b + parent_node->children[2]->mean_b
                 + parent_node->children[3]->mean_b) / 4;
        return parent_node;
    }
}

Tree::Tree() {
    root = new Node();
}

Tree::~Tree() {
    delete root;
}

Tree::Tree(Tree &other) {
    if (other.root != NULL) {
        root = new Node(*other.root);
    }
}

Tree &Tree::operator=(Tree &other) {
    if (other.root != NULL && &other != this) {
        root = new Node(*(other.root));
    }
    return *this;
}

pxl *Tree::get_pxl() {
    return root->get_pxl();
}

void Tree::print() {
    root->print();
}

bool Node::is_repeat(Node *node) const {
    // 因为要用到&操作，所以要判断一个空指针，返回true
    if (!node)
        return false;
    if (node->leaf) // 如果是叶子节点
        return node->judgeNum > 2;
    else    // 有一个剪枝两次以上就行	
		return is_repeat(node->children[0]) || is_repeat(node->children[1])|| is_repeat(node->children[2]) || is_repeat(node->children[3]);
}

void Node::judge_for_leaf(Node *node, int threshold) {
    if (!node)  // 空指针return
        return;
    else {
		long long var = 0;
        // 孩子个数
        int n = 0;
        for (int i = 0; i < 4; ++i) {
			if (node->children[i]) {
				if (!node->children[i]->leaf) // 如果不是叶子节点，继续向下剪枝
					judge_for_leaf(node->children[i], threshold);
				 // 如果是叶子节点，开始计算阈值
				int red_value = (node->children[i]->mean_r - node->mean_r);
				int green_value = (node->children[i]->mean_g - node->mean_g);
				int blue_value = (node->children[i]->mean_b - node->mean_b);
				var += (red_value * red_value + green_value * green_value + blue_value * blue_value);
				n++;
			}
		}
        var /= (30 * n);    // 得到阈值
        if (var < threshold) { // 小于阈值进行剪枝
			if (!is_repeat(node)) { // 注意这里查找剪枝次数是从当前的节点开始判断，而不是每个子节点
			                        // 就是因为这个东西我调试了4个小时，用GDB调得我快吐了
				for (int i = 0; i < 4; ++i) {
					if (node->children[i])  // 如果没有重复并且不是空指针
						judging(node->children[i], node->mean_r, node->mean_g, node->mean_b);
				}
			}
		}
        return;
    }
}

void Node::judging(Node *node, int R, int G, int B) {
    if (!node)
        return;
    else if (node->leaf) { // 叶子节点开始剪枝
        node->mean_r = R;
        node->mean_g = G;
        node->mean_b = B;
        node->judgeNum++;
		node->get_pxl()->red = R;
		node->get_pxl()->green = G;
		node->get_pxl()->blue= B;
    } else {
        for (int i = 0; i < 4; ++i) {
            judging(node->children[i], R, G, B);
        }
    }
}
