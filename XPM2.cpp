#include "XPM2.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


namespace prog {

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
                auto colorIter = colorMap.find(symbol);
                if (colorIter == colorMap.end()) {
                    throw std::runtime_error("Invalid pixel color in XPM file");
                    return nullptr;
                }
                image->at(j, i) = colorIter->second;
            }
        }
        
        return image; //retorna o que é pedido
    }
    void saveToXPM2(const std::string& file, const Image* image) {

        char symbol = '!'; // chave para o map e cores no XPM (penso que o '!' é o primeiro símbolo em ASCII)
        
        //colorMap para fazer a equivalência certa
        std::unordered_map<char, Color> colorMap;
        for (int i = 0; i < image->height(); i++) {
            for (int j = 0; j < image->width(); j++) {
                Color color = image->at(j, i); //cor atual
                if (colorMap.find(symbol) == colorMap.end() && !hasColor(colorMap, color)) { //verifica se a cor não existe no map
                    colorMap[symbol] = color; //adiciona a chave e cores no map
                    symbol++; //próximo símbolo
                }
            }
        }

        int numberOfColors = colorMap.size(); //tamanho do map para saber o número de cores

        std::ofstream fileStream(file); //cria o ficheiro
        fileStream << "! XPM2" << std::endl; //primeira linha
        fileStream << image->width() << " " << image->height() << " " << numberOfColors << " 1" << std::endl; //segunda linha

        // chaves e cores
        for (const auto& entry : colorMap) {
            char key = entry.first;
            Color color = entry.second;
            fileStream << key << " c " << color.toHex() << std::endl; //chama a função que converte a cor em hex para preencher as linhas
        }

        // criar a imagem com as chaves e cores
        for (int i = 0; i < image->height(); i++) {
            for (int j = 0; j < image->width(); j++) {
                Color currentColor = image->at(j, i); //obtem a cor atual
                char symbol = colorToSymbol(colorMap, currentColor); //chama a função auxiliar como se fosse colorMap[color]
                fileStream << symbol; //preenche a linha
            }
            fileStream << std::endl; //muda de linha para fazer em altura
        }
    }
    //função auxiliar para obter a cor a partir de hex
    Color getColor(const std::string& str) {        
        rgb_value r = std::stoi(str.substr(1, 2), nullptr, 16);
        rgb_value g = std::stoi(str.substr(3, 2), nullptr, 16);
        rgb_value b = std::stoi(str.substr(5, 2), nullptr, 16);
        return Color(r, g, b);
    }
    //função auxiliar para verificar se uma cor existe no map para evitar preencher o map com todos os pixeis
    bool hasColor(const std::unordered_map<char, Color>& colorMap, const Color& color) {
        for (const auto& pair : colorMap) {
            if (pair.second.red() == color.red() && pair.second.green() == color.green() && pair.second.blue() == color.blue()) {
                return true;
            }
        }
        return false;
    }
    
    //função auxiliar para obter o símbolo a partir da cor para passar para o XPM, um inverso do colorMap[symbol]
    char colorToSymbol(const std::unordered_map<char, Color>& colorMap, const Color& currentColor) {
        for (const auto& pair : colorMap) {
            if (pair.second.red() == currentColor.red() && pair.second.green() == currentColor.green() && pair.second.blue() == currentColor.blue()) {
                return pair.first;
            }
        }
        return '\0';
    }

}

