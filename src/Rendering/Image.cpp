//
// Created by Antoine on 17/07/2021.
//

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

Image::Image(const std::string& name) {
    m_rgb_image = stbi_load(("resources/"+name).c_str(), &m_width, &m_height, &m_nbChannels, 0);
    std::cout << "Image loaded. Width : " << m_width << ", height : " << m_height << ", pixel data size : " << m_nbChannels << std::endl;
    std::cout << "Image data size : " << sizeof(m_rgb_image)/sizeof(*m_rgb_image) << std::endl;
}

Image::Image(const Image& img) {

}
Image::Image(int width, int height): m_width(width), m_height(height) {
    m_nbChannels = 3;
    m_rgb_image = new uint8_t[m_width * m_height * m_nbChannels];
    Color defaultColor = Color(1,1,1);

    fillImage(defaultColor);
}

Image::Image(int width, int height, Color baseColor): m_width(width), m_height(height) {
    m_nbChannels = 3;
    m_rgb_image = new uint8_t[m_width * m_height * m_nbChannels];

    fillImage(baseColor);
}

Image::~Image() {
    stbi_image_free(m_rgb_image);
}

void Image::fillImage(const Color& c) {
    for(int y = 0; y < m_height; ++y){
        for(int x = 0; x < m_width; ++x){
            setColor(x,y,c);
        }
    }
}

void Image::save(const std::string& name) const {
    stbi_write_png((name + ".png").c_str(), m_width, m_height, m_nbChannels, m_rgb_image, m_width * m_nbChannels);
}

Color Image::getColor(int x, int y) const {
    int dataPos = (y*m_width+x) * m_nbChannels;
    uint8_t r = m_rgb_image[dataPos];
    uint8_t g = m_rgb_image[dataPos+1];
    uint8_t b = m_rgb_image[dataPos+2];
    //std::cout << "getColor (" << (int)r << ", " << (int)g << ", " << (int)b << ")" << std::endl;
    return Color(r/256.0f, g/256.0f, b/256.0f);
}

void Image::setColor(int x, int y, const Color& color) {
    int dataPos = (y*m_width+x) * m_nbChannels;
    m_rgb_image[dataPos] = (uint8_t)(color.r*255.999f);
    m_rgb_image[dataPos+1] = (uint8_t)(color.g*255.999f);
    m_rgb_image[dataPos+2] = (uint8_t)(color.b*255.999f);
}

int Image::getWidth() const {
    return m_width;
}
int Image::getHeight() const {
    return m_height;
}



