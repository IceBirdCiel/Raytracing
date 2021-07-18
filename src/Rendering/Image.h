//
// Created by Antoine on 17/07/2021.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include "../Materials/Color.h"

class Image {
public:
    explicit Image(const std::string& name);
    Image(int width, int height);
    Image(int width, int height, Color baseColor);
    Image(const Image &img);
    ~Image();

    void save(const std::string& name) const;

    Color getColor(int x, int y) const;
    void setColor(int x, int y, const Color& color);

    int getWidth() const;
    int getHeight() const;
private:
    int m_width{};
    int m_height{};
    int m_nbChannels{};
    uint8_t* m_rgb_image;
    void fillImage(const Color& c);
};


#endif //IMAGE_H
