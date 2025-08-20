#include "tga_handler.hpp"
#include "timer.hpp"
#include <cassert>

void line(int x0, int y0, int x1, int y1, TGAImage &image, Color color) { 
    assert(x0 >= 0 && x0 < image.width());
    assert(x1 >= 0 && x1 < image.width());
    assert(y0 >= 0 && y0 < image.height());
    assert(y1 >= 0 && y1 < image.height());
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 

int main(){
    TGAImage img(2560, 1440);
    img.set(1000, 1000, Color(0, 255, 0, 128));
    img(1003, 1003) = Color(255, 0, 0);
    
    Timer::start();
    line(100,100,1000,1300,img,Color(255,0,0,0));
    Timer::stop(std::string{"Draw Line"});

    Timer::start();
    if(img.write("output.tga")){
        Logger::print(Logger::Color::Green, "File save success..");
    }
    else{
        throw std::exception{"File save error."};
    }
    Timer::stop(std::string{"Write TGA"});
    
    return 0;
}