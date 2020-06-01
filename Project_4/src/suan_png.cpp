#include "suan_png.h"

PNG::PNG() {
    width_ = 0;
    height_ = 0;
    image = nullptr;
}

PNG::~PNG() {
    delete[] image;
}

int PNG::load(std::string &file_name) {
    // 先用标准文件流打开文件
    FILE *fp = fopen(file_name.c_str(), "rb");
    if (!fp) {  // 打开失败
        perror("Fopen failed: ");
        return 1;
    }
    // 检查图片前八个字节的签名是否是png图像，返回0说明是png图像，反之当反
    // 检查文件的签名头不要超过文件的前8个字节
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        perror("Not a valid PNG file: ");
        return 1;
    }


    // 如果文件打开成功并且是png图片开始初始化
    // 创建png图片的读取指针，用于和打开的文件进行指针绑定
    // 初始化libpng的时候，用户可以指定自定义错误处理函数，
    // 如果不需要指定自定义错误处理函数，则传NULL即可。
    // png_create_read_struct函数返回一个png_structp变量，该变量不应该被用户访问，应该在以后调用 libpng的函数时传递给libpng库。
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    // 创建图像信息，传入png指针，通过png_infop变量来获得图片的信息，设置图片解码参数等
    // png_infop创建失败返回一个null
    png_infop info_ptr = png_create_info_struct(png_ptr);
    // 让libpng会设置一个png_jmpbuf并且返回非0，说明错误发生，如果设置的时候返回0.说明没有错误
    // 但是当后面libpng中有错误发生时，会跳到你设置错误的这个地方继续执行
    // 只有用户在初始化libpng的时候未指定用户自定义的错误处理函数情况下，才需要设置错误返回点。
    // 如果设置了用户自定义的错误处理函数，libpng将会调用用户自定义错误处理函数，而不会返回到这个调用点。
    if (setjmp(png_jmpbuf(png_ptr))) {
        // 释放掉内存
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    // 创建png读取的io流，和打开的实例文件进行绑定
    png_init_io(png_ptr, fp);
    // 如果您以前曾打开文件并从头开始读取一些字节来查看签名，以查看它是否为PNG文件，则需要让libpng知道文件开头缺少一些字节
    png_set_sig_bytes(png_ptr, 8);
    // 将png_ptr指向的文件的信息读入到info_ptr的结构体中
    png_read_info(png_ptr, info_ptr);


    // 得到位深度，就是一个像素有多少位的通道组成，比如24位深的位图就是Red（8位）、Green（8位）、Blue（8位）
    // 或者再加一个alpha通道（8位）就变成了png通道的32位深的图像格式
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    if (bit_depth == 16) {
        // 如果图片的位深度是16位，设置pnglib的颜色存储格式是16位格式
        png_set_strip_16(png_ptr);
    }

    // 得到颜色的类型
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    // 如果颜色类型既不是RGB也不是RGBA
    if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA) {
        // 如果是灰度图或者是包含alpha通道的灰度图
        if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
            // 低位深度灰度图像位深度小于8，则必须始终转换为至少8位格式
            if (bit_depth < 8) {
                png_set_expand(png_ptr);
            }
            // 灰度图必须转变为rgb通道图格式
            png_set_gray_to_rgb(png_ptr);
        }
        // 调色板图像设置成RGB格式
        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png_ptr);
        }
    }

    // 检查获取的图片是否含有alpha通道（透明信息），有的话则要向png_ptr添加完整的alpha通道，以便获取alpha通道的信息
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }

    // 读取图片的以像素为单位计算的宽度和高度，最大2^31次方，比如1920x1080的格式
    size_t width = png_get_image_width(png_ptr, info_ptr);
    size_t height = png_get_image_height(png_ptr, info_ptr);

    // 创建像素存储对象
    pxl *new_pixs = nullptr;
    png_byte *row = nullptr;

    // 先将上面的所有设置更新一遍
    png_read_update_info(png_ptr, info_ptr);
    // 重新设置错误回调点
    if (setjmp(png_jmpbuf(png_ptr))) {
        delete[] new_pixs;
        delete[] row;
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        perror("png_jmpbuf failed: ");
        return 1;
    }

    // 获取图片一行的字节数，记住8位为一个字节
    int bpr = png_get_rowbytes(png_ptr, info_ptr);

    // 设置像素的总个数，比如1920x1080（1080p）就是2073600个像素
    new_pixs = new pxl[height * width];

    // 一行的png_byte个数
    row = new png_byte[bpr];

    // 这个是颜色类型的通道数，值为 1~n ，一个通道通常为8位（一个字节）
    /* 1->就是一个通道的颜色（8位），比如灰度图（GRAY）和调色板（PALETTE）
     * 2->两个通道的颜色（16位），灰度+透明度（GRAY_ALPHA）
     * 3->三个通道的颜色（24位真彩色），RGB
     * 4->四个通道的颜色（32位），RGB_ALPHA或者RGB+填充字节*/
    int numchannels = png_get_channels(png_ptr, info_ptr);

    // 相当于二维矩阵的读取方式：根据行数，读取每一列的数据
    for (size_t y = 0; y < height; y++) {
        // 读取每一行的字节数据
        png_read_row(png_ptr, row, nullptr);
        png_byte *pix = (png_byte *) row;
        // 读取每一列的数据
        for (size_t x = 0; x < width; x++) {
            pxl &px = new_pixs[width * y + x];
            // 8位或16位深度图，一列读取一个或两个字节的数据即可
            if (numchannels == 1 || numchannels == 2) {
                // unsigned char是8位一个字节的数据
                unsigned char color = (unsigned char) *pix++;
                px.red = color;
                px.green = color;
                px.blue = color;
                if (numchannels == 2) {
                    px.alpha = (unsigned char) *pix++;
                } else {
                    // 不透明
                    px.alpha = 255;
                }
                // 24位或32位深度图，一列读取3个或四个自己的数据
            } else if (numchannels == 3 || numchannels == 4) {
                px.red = (unsigned char) *pix++;
                px.green = (unsigned char) *pix++;
                px.blue = (unsigned char) *pix++;
                if (numchannels == 4) {
                    px.alpha = (unsigned char) *pix++;
                } else {
                    // 不透明
                    px.alpha = 255;
                }
            }
        }
    }
    // 释放image之前指向的数据（虽然我感觉好像没必要做这步。。。）
    delete[] image;

    // 赋值为实例的图片
    image = new_pixs;
    width_ = width;
    height_ = height;
    delete[] row;
    // 读取结束
    png_read_end(png_ptr, nullptr);
    // 正常结束，释放内存
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);
    return 0;
}

int PNG::save(std::string &file_name) {
    // 使用file_name.c_str()因为比较安全
    FILE *fp = fopen(file_name.c_str(), "wb");
    if (!fp) {
        perror("fopen Failed: ");
        return 1;
    }
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    png_init_io(png_ptr, fp);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png jmpBuf Failed: ");
        return 1;
    }
    // 设置要生成的图片的png结构，第五个参数是位深度，第六个是颜色类型
    png_set_IHDR(png_ptr, info_ptr, width_, height_, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // 改变原始的图片信息，设置写入数据流，指向的就是图片实例
    png_write_info(png_ptr, info_ptr);
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        perror("png_jmpbuf failed: ");
        return 1;
    }
    int bpr = png_get_rowbytes(png_ptr, info_ptr);
    png_byte *row = new png_byte[bpr];

    // 改变图片的数据格式
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {

            // 改变每一行的每一个像素为已经被剪枝（judge）好的数据形式（计蒜客上说是求平均值）
            png_byte *blah = row + (x * 4);
            blah[0] = image[width_ * y + x].red;
            blah[1] = image[width_ * y + x].green;
            blah[2] = image[width_ * y + x].blue;
            blah[3] = image[width_ * y + x].alpha;
        }
        png_write_row(png_ptr, row);
    }
    png_write_end(png_ptr, nullptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    delete[] row;
    fclose(fp);
    return 0;
}

pxl *PNG::get_pxl(int x, int y) {
    if (x >= width_ || y >= height_) {
        return NULL;
    }
    return &image[width_ * y + x];
}

int PNG::get_width() const {
    return width_;
}

int PNG::get_height() const {
    return height_;
}
