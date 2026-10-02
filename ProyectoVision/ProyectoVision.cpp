#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include <experimental/filesystem>

using namespace std;
using namespace cv;


string nombreUsuario = "letrasAdrian";
string carpeta = "C://fotosvision//PROYECTO//";


void GuardarLetras(Mat imagen, string letra) {
    
    if (!std::experimental::filesystem::exists(carpeta + letra)) {
        std::experimental::filesystem::create_directories(carpeta + letra);
        cout << "carpeta no encontrada, se dispone a crear..."<<endl;
    }
    
    imwrite(carpeta + letra + "//" + nombreUsuario + letra + ".png", imagen);
}


int main() {

	Mat imagen;
	imagen = imread(carpeta + nombreUsuario + ".png", IMREAD_GRAYSCALE);

	Mat binarizada;
	threshold(imagen, binarizada, 128, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contornos;
	findContours(binarizada, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


    const int ANCHO = 160; 
    const int ALTO = 320; 
    const double TOLERANCIA = 0.8; 
    const int GROSOR = 14;
    

    for (size_t i = 0; i < contornos.size(); i++) {


        Rect boundingBox = boundingRect(contornos[i]);

        if (abs(boundingBox.width - ANCHO) <= ANCHO * TOLERANCIA &&
            abs(boundingBox.height - ALTO) <= ALTO * TOLERANCIA) {
      

            Rect innerBox(
                boundingBox.x + GROSOR,                          
                boundingBox.y + GROSOR,                          
                boundingBox.width - 2 * GROSOR,                  
                boundingBox.height - 2 * GROSOR                  
            );
            
            if (innerBox.x >= 0 && innerBox.y >= 0 &&
                innerBox.x + innerBox.width <= imagen.cols &&
                innerBox.y + innerBox.height <= imagen.rows) {



                vector<int> arrayTonalidades;
                Mat roi = imagen(innerBox);



                for (int y = 0; y < roi.rows; y++) {
                    for (int x = 0; x < roi.cols; x++) {
                        uchar valorGris = roi.at<uchar>(y, x);

                        arrayTonalidades.push_back(valorGris);
                    }
                }
            
                imshow("Contenido del cuadro", roi);
                waitKey(0);
                string letra;
                cout << "dime la letra: ";
                cin >> letra;
                cout << endl;
                GuardarLetras(roi, letra);
            }
        }
    }

    return 0;
}   