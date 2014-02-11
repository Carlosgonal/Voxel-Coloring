//
//  Voxel Coloring.h
//  ProyectoVC
//
//  Created by Carlos González on 03/01/14.
//  Copyright (c) 2014 Carlos González. All rights reserved.
//

#ifndef __ProyectoVC__Voxel_Coloring__
#define __ProyectoVC__Voxel_Coloring__


#include <iostream>

#ifdef _WIN64

#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\nonfree\features2d.hpp>

#define MAC 1

#elif _WIN32

#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\nonfree\features2d.hpp>

#define MAC 1

#elif __APPLE__

#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

#define MAC 2

#endif

#include <vector>
#include <set>
#include <fstream>
#include <string>
//Struct que usarems para el Clase Voxel
struct StructVoxel{
    cv::Point3f punto;      //Punto en el espacio
    cv::Scalar color;       //Color del Voxel
    int pinta;              //Valor que nos indicara si es pintado o no
};
///////////////////////////////////////////////////////////////////////////////////////////////////
//Clase voxel, la clase voxel costrulle una malla tridimensional la c ual nos aporta el punto en el espacio
//de cada voxel de la malla, ademas de eso tambien guardamos el tamaño de la malla que siempre será cuadrada
class Voxel{
private:
    std::vector<std::vector<std::vector<StructVoxel> > > voxel;
    int size;
public:
    //Constructor por defecto
    Voxel();
    //Constructor
    Voxel(int tam);
    //Destrucctor
    ~Voxel();
    //Medotod que inicializa el espacio 3D
    float Inicializar(int inicio);
    //Metodo que devuelve el valor de una voxel de la malla
    StructVoxel Get(int x, int y , int z);
    //Metodo que devuelve unicamente el punto en 3D del voxel
    cv::Point3f GetPunto(int x , int y, int z);
    //Medtodo que hace que un voxel se valla a puntar
    void Pinta(int x, int y, int z);
    //MEdtodo para modificar el valor de un voxel
    void Set(int x, int y , int z, StructVoxel valor);
    //Medtodo que devuelte si un voxel será pintado
    int EstaPintado(int x, int y , int z );
    //Metodo que devuelve el tamaño del la malla de voxels
    int Tamanio();
    //Metodo que modifica el color de un voxel
    void ModificarColor(int x, int y, int z,cv::Scalar col);
};
///////////////////////////////////////////////////////////////////////////////////////////////////


//Funcion que pinta una imagen
void pintaI(cv::Mat im);
//Funcion que lee una imagen
cv::Mat leeimagen(char* filename , int flagsColor);
//Funcion que lee la matriz K
void leerMatrices(int n_matrix, cv::Mat& K);
//Funcion que obtine la matriz de proyeccion desde fichero
void LeerMatrixdeProyeccion(int n_matrix,cv::Mat& P);
//Funcion qeu calcula en centro de una camara
void CalculaCentro (cv::Mat& proyeccion,cv::Mat& Centro);
//Funcion que implementa el Algoritmo Voxel Coloring (Funcion Erronea), diferente implementacion
void VoxelColoring(cv::Mat im1,cv::Mat im2, Voxel& v);
//Funcion que implementa el Algoritmo Voxel Coloring, implementacion usada y explicada
void VoxelColoring2(cv::Mat im1,int i, cv::Mat im2,int j,Voxel& v,cv::Mat silueta1,cv::Mat silueta2);
//Funcion que calcula la consistencia del color
float ConsistenciaCheck2(std::vector<cv::Scalar> pixel);
//Funcion que proyecta puntos en el espacio en los pixeles de las imagenes
void ProyectarPixel(cv::Point3f Punto3D, cv::Mat P,cv::Point2f& toReturn);
//Funcion que calcula la distancia entre un punto y una recta
float Distancia(int lamda,cv::Mat vector1,cv::Mat punto1, cv::Point3f p2);
//Funcion que crea la silueta de una imagen
std::vector< cv::Mat > CrearSilhouttes(std::vector<cv::Mat> listaImagenes);

#endif /* defined(__ProyectoVC__Voxel_Coloring__) */
