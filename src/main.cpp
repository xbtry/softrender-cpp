#include "tga_handler.hpp"
#include "timer.hpp"

int main(){
    TGAImage img(2560, 1440);
    img.set(1000, 1000, Color(0, 255, 0, 128));
    img(1003, 1003) = Color(255, 0, 0);
    for(int i = 0; i < 256; i++){
        img.set(0 + i, 0 + i, Color(0,0,255,255));
    }
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