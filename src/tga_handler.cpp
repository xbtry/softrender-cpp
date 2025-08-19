#include "tga_handler.hpp"

TGAImage::TGAImage(int width, int height)
    : m_width(width), m_height(height), m_pixels(width * height) {}

void TGAImage::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_pixels.resize(width * height);
}

void TGAImage::set(int x, int y, const Color& color) {
    if (x < 0 || y < 0 || x >= m_width || y >= m_height)
        throw std::out_of_range("set: pixel out of bounds");
    m_pixels[index(x, y)] = color;
}

Color TGAImage::get(int x, int y) const {
    if (x < 0 || y < 0 || x >= m_width || y >= m_height)
        throw std::out_of_range("get: pixel out of bounds");
    return m_pixels[index(x, y)];
}

Color& TGAImage::operator()(int x, int y) {
    return m_pixels[index(x, y)];
}

const Color& TGAImage::operator()(int x, int y) const {
    return m_pixels[index(x, y)];
}

bool TGAImage::write(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false;

    uint8_t header[18] = {};
    header[2] = 2; // Uncompressed true-color
    header[12] = m_width & 0xFF;
    header[13] = (m_width >> 8) & 0xFF;
    header[14] = m_height & 0xFF;
    header[15] = (m_height >> 8) & 0xFF;
    header[16] = 32; // bits per pixel
    header[17] = 8;  // alpha bits, origin bottom-left

    out.write(reinterpret_cast<char*>(header), sizeof(header));
    out.write(reinterpret_cast<const char*>(m_pixels.data()), m_pixels.size() * sizeof(Color));

    return out.good();
}