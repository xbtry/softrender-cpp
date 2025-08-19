#ifndef TGAHANDLER_H
#define TGAHANDLER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <fstream>
#include <iostream>

struct Color {
    uint8_t b, g, r, a;
    Color(uint8_t red=0, uint8_t green=0, uint8_t blue=0, uint8_t alpha=255)
        : b(blue), g(green), r(red), a(alpha) {}
};

class TGAImage {
public:
    TGAImage(int width, int height);
    TGAImage() = default;

    void resize(int width, int height);
    void set(int x, int y, const Color& color);
    Color get(int x, int y) const;

    Color& operator()(int x, int y);
    const Color& operator()(int x, int y) const;

    bool write(const std::string& filename) const;

    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    int m_width = 0;
    int m_height = 0;
    std::vector<Color> m_pixels;

    inline int index(int x, int y) const {
        return y * m_width + x;
    }
};

#endif
