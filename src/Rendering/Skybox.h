#pragma once

#include <string>
#include "Image.h"
#include "../Math/Ray.h"

class Skybox {
public:
    Skybox(const std::string& image);
    Color getColor(Ray ray);

private:
    Image m_image;
};

