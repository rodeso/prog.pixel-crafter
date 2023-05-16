#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include <algorithm>

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
            }/* 
            // TODO ...
            if(command=="invert"){
                invert();
                continue;
            }
            if(command=="to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if(command=="replace"){
                Color c1,c2;
                input>>c1;
                input>>c2;
                replace(c1,c2);
                continue;
            }
            if(command=="fill"){
                int x,y,w,h;
                input >> x>>y>>w>>h;
                Color c3;
                input >>c3;
                fill(x,y,w,h,c3);
                continue;
            }*/
            if(command=="h_mirror"){
                h_mirror();
                continue;
            }
            if(command=="v_mirror"){
                v_mirror();
                continue;
            }
            if(command=="add"){
                
                
                add();
                continue;
            }
            if(command=="crop"){
                int x,y,w,h;
                input >> x >>y >>w>>h;
                crop(x,y,w,h);
                continue;
            }
            
            if(command=="rotate_left"){
                rotate_left();
                continue;
            }
            
            if(command=="rotate_right"){
                rotate_right();
                continue;
            }
            if(command=="median_filter"){
                median_filter();
                continue;
            }
            if(command=="xpm2_open") {
                clear_image_if_any();
                string xpm2_filename;
                input >> xpm2_filename;
                loadFromXPM2(xpm2_filename);
                continue;
            }


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
        *this->image=image;
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
        *this->image=image;
    }
    void Script::add() {
        string filename;
        Color neutral;
        int x,y;
        input >> filename >>neutral>> x>>y;
        Image *png=loadFromPNG(filename); //carrega a imagem
        int pngW = png->width(); //largura da imagem
        int pngH = png->height(); //altura da imagem
        
        
        for (int i = 0; i < pngW; i++) {
            for (int j = 0; j < pngH; j++) { //percorre a imagem para ter a cor dos pixeis
                Color pngC = png->at(i, j); //guarda a cor em pngC            
                if (pngC.red()==neutral.red() && pngC.green()==neutral.green() && pngC.blue()==neutral.blue()) { //copia apenas os diferentes ao neutro
                    continue;
                    
                }
                else{
                    int currentX = x + i; //x atual
                    int currentY = y + j; //y atual
                    image->at(currentX, currentY) = pngC;
                }
            }
        }
        delete png;
    }
    
    void Script::rotate_right(){
        // 90 graus para a direita
        vector<vector<Color>> temp;//vetor para reorganizar a imagem
        //novas dimensões
        int w = image->height();
        int h = image->width();
        for(int i = w-1; i >= 0; i--){//escolhe uma linha a começar do fim
            vector<Color> new_colum;
            for(int j = 0; j < h; j++){//escolhe uma coluna
                new_colum.push_back(image->at(j,i));//preenche coluna de v
            }
            temp.push_back(new_colum);//junta coluna à nova imagem
        }
        //atualiza a imagem
        Image v(w, h, temp);
        *image = v;
        

    }
    void Script::rotate_left(){
        //90 graus para a esquerda
        int w=image->height();
        int h=image->width();
        vector<vector<Color>> temp;
        
       for(int i=0; i < image->height(); i++){//fixa uma linha
            vector<Color> new_line;
            for(int j = image->width()-1; j >= 0; j--){//anda de coluna em coluna
                new_line.push_back(image->at(j,i));//preenche coluna de v
            }
            temp.push_back(new_line);
            
        }
        //atualiza imagem
        Image v(w, h, temp);
        *image = v;
    }
    void Script::crop(int x, int y, int w, int h){
        Image v(w, h);//nova imagem
        vector<vector<Color>> temp;
        for(int i = x; i < w+x; i++){//escolhe uma coluna
            vector<Color> new_colum;
            for(int j = y ;j < h+y; j++){//escolhe linha
                new_colum.push_back(image->at(i,j));
            }
            temp.push_back(new_colum);
        }
        //coloca cores na nova imagem
        for(int x = 0;x < w; x++){
            for(int y = 0; y<h; y++){
                v.at(x, y) = temp[x][y];
            }
        }
        *image = v;//atualiza a imagem
        
        
    }
    void Script::median_filter(){
        int ws;
        input >> ws;
        int dim=ws/2;//distancia a percorrer a partir do centro da janela
        Image v(image->width(),image->height());
        for(int x=0; x<image->width();x++){
            for(int y=0;y<image->height();y++){
                //vetores para os valores de cada cor
                vector<rgb_value> v_mr;
                vector<rgb_value> v_mg;
                vector<rgb_value> v_mb;
                for(int i=max(0,x-dim);i<=min(image->width()-1,x+dim);i++){//percorre a janela garantindo que nunca sai do limite
                    for(int j=max(0,y-dim);j<=min(image->height()-1,y+dim);j++){
                        //guarda os valores de cada cor
                        v_mr.push_back(image->at(i,j).red());
                        v_mg.push_back(image->at(i,j).green());
                        v_mb.push_back(image->at(i,j).blue());
                    }
                    
                }
                //ordena valores
                sort(v_mr.begin(),v_mr.end());
                sort(v_mg.begin(),v_mg.end());
                sort(v_mb.begin(),v_mb.end());
                rgb_value r,g,b;
                unsigned long int size=v_mb.size();
                //calcula a mediana de cada valor
                if(size%2==0){
                    r= ((v_mr[ size / 2 - 1] + v_mr[ size / 2]))/2;
                    g=((v_mg[ size / 2 - 1] + v_mg[ size / 2]))/2;
                    b=((v_mb[ size / 2 - 1] + v_mb[ size / 2]))/2;
                }
                else{
                    r=v_mr[size/2];
                    g=v_mg[size/2];
                    b=v_mb[size/2];
                }
                Color temp(r,g,b);//nova cor com as medianas
                v.at(x,y)=temp;//coloca na nova imagem
            }
        }
        *image=v;//atualiza a imagem 
    }
}
