#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            // TODO ...

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::v_mirror() { //espelhar a imagem verticalmente
        Image image = *this->image;
        int w = image.width();
        int h = image.height();
        for (int y = 0; y < h / 2; y++) { //percorre a metade vertical da imagem, sendo isto suficiente para espelhar toda a imagem
            for (int x = 0; x < w; x++) {
                swap(image.at(x, y), image.at(x, h - 1 - y)); //troca os pixeis em (x,y) com (x,h-1-y), invertendo todos os pixeis ao percorrer metade
            }
        }
    }
    void Script::h_mirror() { //espelhar a imagem horizontalmente
        Image image = *this->image;
        int w = image.width();
        int h = image.height();
        for (int x = 0; x < w / 2; x++) { //percorre a metade horizontal da imagem, sendo isto suficiente para espelhar toda a imagem
            for (int y = 0; y < h; y++) {
                swap(image.at(x, y), image.at(w - 1 - x, y)); //troca os pixeis em (x,y) com (w-1-x,y) invertendo todos os pixeis ao percorrer metade
            }
        }
    }
}
