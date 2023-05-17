#include "XPM2.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


namespace prog {

    Color getColor(const std::string& str) { //hex para rgb
        
        rgb_value r = std::stoi(str.substr(1, 2), nullptr, 16);
        rgb_value g = std::stoi(str.substr(3, 2), nullptr, 16);
        rgb_value b = std::stoi(str.substr(5, 2), nullptr, 16);

        return Color(r, g, b);
    }

    Image* loadFromXPM2(const std::string& file) {

        std::ifstream fileStream(file); //load do ficheiro

        if (!fileStream.is_open()) { //verifica se foi possivel abrir o ficheiro
            throw std::runtime_error("Failed to open XPM file");
            return nullptr;
        }

        std::string line;
        getline(fileStream, line);
        if (line != "! XPM2") { //primeira linha
            throw std::runtime_error("Invalid XPM file format");
            return nullptr;
        }

        getline(fileStream, line);
        std::istringstream iss(line);
        int width, height, num_colors, chars_per_pixel;
        if (!(iss >> width >> height >> num_colors >> chars_per_pixel)) { //segunda linha
            throw std::runtime_error("Invalid XPM header format");
            return nullptr;
        }

        std::unordered_map<char, Color> colorMap;
        //percorre as linhas codificadas para adiquirir as cores em função dos simbolos/chaves
        for (int i = 0; i < num_colors; i++) { 
            getline(fileStream, line);
            std::istringstream colorIss(line);
            char symbol; //chave para o map e cores no XMP
            char letter; //neste caso apenas c
            std::string hex; //hex que será convertido para rgb
            if (!(colorIss >> symbol >> letter >> hex)) {
                throw std::runtime_error("Invalid color definition in XPM file");
                return nullptr;
            }
            Color color = getColor(hex); //converte hex para rgb
            colorMap[symbol] = color; //adiciona a chave e cores no map
        }
            
        Image* image = new Image(width, height); //cria a nossa salvação
        //percorre a imagem em caracteres para atribuir uma cor a cada pixel
        for (int i = 0; i < height; i++) {
            getline(fileStream, line);
            for (int j = 0; j < width; j++) {
                char symbol = line[j];
                std::cout << symbol;
                auto colorIter = colorMap.find(symbol);
                if (colorIter == colorMap.end()) {
                    throw std::runtime_error("Invalid pixel color in XPM file");
                    return nullptr;
                }
                image->at(j, i) = colorIter->second;
            }
            std::cout << std::endl;
        }
        
        return image; //retorna o que é pedido
    }


    void saveToXPM2(const std::string& file, const Image* image) {
        std::ofstream fileStream(file); //load do ficheiro
        fileStream << "! XPM2" << std::endl;
        = image->num_color
        fileStream << image->width() << " " << image->height() << std::endl; << image->/*num_color*/() << " 1" << std:endl;
        for (int c = 0, c < numberOfcolors; c++) {
            fileStream << c << " c #" << image->at().toHex() << std::endl;

            for (int i = 0; i < image->height(); i++) {
                for (int j = 0; j < image->width(); j++) {
                    fileStream << simbolo da cor em image->at(j, i) << " " << simbolo da cor em image->at(j, i) << " " << simbolo da image->at(j, i);
                }
                fileStream << std::endl;
            }
    }
        
}

