#ifndef SUAN_PNG_H_
#define SUAN_PNG_H_

#include <string>
#include <png.h>
#include "pxl.h"

class PNG {
private:
    pxl *image;
    int width_;
    int height_;
public:
    PNG();
    ~PNG();
    // load函数会将整个png文件的所有像素存放在一维的image像素结构数组里
    int load(std::string &file_name);
    // save函数将image保存的像素数据放到一张新的图片中
    int save(std::string &file_name);
    pxl *get_pxl(int x, int y);
    int get_width() const;
    int get_height() const;
};

#endif
