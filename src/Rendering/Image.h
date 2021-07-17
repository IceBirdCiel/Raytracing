//
// Created by Antoine on 17/07/2021.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "../Materials/Color.h"

class Image {
public:
    Image(std::string name);
    ~Image();
    const Color operator()(int i, int j) const;
private:
    int m_width;
    int m_height;
    int m_pixelDataSize;
    uint8_t* m_rgb_image;
};


#endif //IMAGE_H
