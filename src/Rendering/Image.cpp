//
// Created by Antoine on 17/07/2021.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../Materials/Color.h"
#include <iostream>

Image::Image(std::string name) {
    m_rgb_image = stbi_load(("resources/"+name).c_str(), &m_width, &m_height, &m_pixelDataSize, 0);
    std::cout << "Image loaded. Width : " << m_width << ", height : " << m_height << ", pixel data size : " << m_pixelDataSize << std::endl;
    std::cout << "Image data size : " << sizeof(m_rgb_image)/sizeof(*m_rgb_image) << std::endl;
}

Image::~Image() {
    stbi_image_free(m_rgb_image);
}

const Color Image::operator()(int i, int j) const {
    int dataPos = (i*m_width+j)*m_pixelDataSize;

    uint8_t r = m_rgb_image[dataPos];
    uint8_t g = m_rgb_image[dataPos+1];
    uint8_t b = m_rgb_image[dataPos+2];

    //std::cout << "(" << (float)r << ", " << (float)g << ", " << (float)b << ")" << std::endl;
    return Color(((float) r)/(float)256, ((float) g)/256, ((float) b)/256);
}
