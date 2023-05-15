#include "XPM2.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


namespace prog {

    Color getColor(const std::string& str) { //hex para rgb
        
        int r = std::stoi(str.substr(1, 2), nullptr, 16);
        int g = std::stoi(str.substr(3, 2), nullptr, 16);
        int b = std::stoi(str.substr(5, 2), nullptr, 16);

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
        for (int i = 0; i < num_colors; ++i) { 
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
            //W.I.P.
        std::vector<std::vector<Color>> data(height, std::vector<Color>(width));
        //percorre a imagem em caracteres para atribuir uma cor a cada pixel
        for (int i = 0; i < height; i++) {
            getline(fileStream, line);
            for (int j = 0; j < width; j++) {
                char symbol = line[j];
                auto colorIter = colorMap.find(symbol);
                if (colorIter == colorMap.end()) {
                    throw std::runtime_error("Invalid pixel color in XPM file");
                    return nullptr;
                }
                data[i][j] = colorIter->second;
            }
        }
        
        Image* image = new Image(width, height, data); //cria a imagem 
        return image; //retorna o que é pedido
    }


    void saveToXPM2(const std::string& file, const Image* image) {
        //TODO
    }

}

