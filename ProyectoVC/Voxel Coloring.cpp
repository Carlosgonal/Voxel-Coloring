//
//  Voxel Coloring.cpp
//  ProyectoVC
//
//  Created by Carlos González on 03/01/14.
//  Copyright (c) 2014 Carlos González. All rights reserved.
//

#include "Voxel Coloring.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Clase voxel
Voxel::Voxel(){
    size = 0;
}
Voxel::Voxel(int tamanio){
    voxel.resize(tamanio);
    for(int i = 0; i < tamanio; i++){
        voxel[i].resize(tamanio);
    }
    for(int i = 0; i < tamanio; i++){
        for(int j = 0; j < tamanio; j++){
            voxel[i][j].resize(tamanio);
        }
    }
    size = tamanio;
}
Voxel::~Voxel(){
    if(size != 0){
        for(int i = 0; i < voxel.size(); i++){
            for(int j = 0; j < voxel[0].size(); j++){
                voxel[i][j].clear();
            }
        }
        for(int i = 0; i < voxel.size(); i++){
            voxel[i].clear();
        }
        voxel.clear();
    }
}
float Voxel::Inicializar(int inicio){
    //Calculamos el tamaño uqe va ha tener cada voxel y su lugar en el espacio
    //Estos valores depenteran del tamaño de la malla y del lugare en el espacio
    //donde queramos empezar a construir la malla
    int n_cubos = size;
    int maxtam = inicio;
    float tam = ((float)maxtam+maxtam)/((float)n_cubos);

    for (float inicioX = -maxtam, i = 0; inicioX < maxtam and i < n_cubos; inicioX += tam, i++){
        for (float inicioY = -maxtam , j = 0; inicioY < maxtam and j < n_cubos; inicioY += tam, j++){
            for(float inicioZ = -maxtam, k = 0; inicioZ < maxtam and k < n_cubos; inicioZ += tam, k++){
                voxel[i][j][k].punto.x = inicioX;
                voxel[i][j][k].punto.y = inicioY;
                voxel[i][j][k].punto.z = inicioZ;
                voxel[i][j][k].pinta = 0;
            }
        }
    }
    return tam;
}
StructVoxel Voxel::Get(int x, int y , int z){
    return voxel[x][y][z];
    
}
cv::Point3f Voxel::GetPunto(int x , int y, int z){
    return voxel[x][y][z].punto;
}
void Voxel::Set(int x, int y , int z, StructVoxel valor){
    voxel[x][y][z] = valor;
}
void Voxel::Pinta(int x, int y, int z){
    voxel[x][y][z].pinta = 1;
}
int Voxel::Tamanio(){
    return size;
}
void Voxel::ModificarColor(int x, int y, int z,cv::Scalar col){
    //En el caso de que el voxel no ha sido pintado antes se pintara del color
    //de estrada, en caso contrario el color sera una media de todos los colores
    //que inciden en el voxel
    if(voxel[x][y][z].pinta == 0){
        voxel[x][y][z].color = col;
    }else{
        voxel[x][y][z].color[0] = (voxel[x][y][z].color[0]+col[0])/2;
        voxel[x][y][z].color[1] = (voxel[x][y][z].color[1]+col[1])/2;
        voxel[x][y][z].color[2] = (voxel[x][y][z].color[2]+col[2])/2;
    }
}
int Voxel::EstaPintado(int x, int y , int z ){
    return voxel[x][y][x].pinta;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pintaI(cv::Mat im){
    
    //Creamos la ventana
    cv::namedWindow("Ventana",1);
    //Introducimos la imagen en la ventana
    cv::imshow("Ventana",im);
    //Paramos al ejecucion
    cv::waitKey(0);
    //Destruimos la ventana
    cv::destroyWindow("ventana");
    
}
cv::Mat leeimagen(char* filename , int flagsColor){
    return cv::imread(filename, flagsColor);
}
void leerMatrices(int n_matrix, cv::Mat& K){
    std::fstream fs;
    char* filename;
    if(n_matrix <= 7){
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera0.m";
    }
    else if(n_matrix <= 15){
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera1.m";
    }
    else{
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera2.m";
    }
    fs.open (filename);
    std::string cadena;
    std::string::size_type sz;
    
    while (!fs.eof())
    {
        fs >> cadena;
        if(cadena == "fc"){
            for(int i = 0; i < 7;i++){
                fs>> cadena;
                if(i == 2){
                    cadena.pop_back();
                    //std::cout<<"Numero1 -->"<<cadena<< std::endl;
                    K.at<float>(0,0) = std::stof(cadena,&sz);
                }
                if(i == 3){
                    //std::cout<<"Numero1 -->"<<cadena<< std::endl;
                    K.at<float>(1,1) = std::stof(cadena,&sz);
                }
            }
        }
        if(cadena == "cc"){
            for(int i = 0; i < 7;i++){
                fs>> cadena;
                if(i == 2){
                    cadena.pop_back();
                    //std::cout<<"Numero2 -->"<<cadena<< std::endl;
                    K.at<float>(0,2) = std::stof(cadena,&sz);
                }
                if(i == 3){
                    //std::cout<<"Numero2 -->"<<cadena<< std::endl;
                    K.at<float>(1,2) = std::stof(cadena,&sz);
                }
            }
        }
    }
    K.at<float>(2,2) =1;
    fs.close();
}
void LeerMatrixdeProyeccion(int n_matrix,cv::Mat& P){
    std::fstream fs;
    char* filename;
    int cont = 0;
    if(n_matrix <= 7){
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera0.m";
        cont = 0;
    }
    else if(n_matrix <= 15){
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera1.m";
        cont = 8;
        //n_matrix = n_matrix +cont;
    }
    else{
        filename =(char*)"/Users/Carlos/Documents/Programas/ProyectoVC/ProyectoVC/Craneo/calib/camera2.m";
        cont = 16;
    }
    //std::cout << filename << std::endl;
    fs.open (filename);
    std::string cadena;
    std::string::size_type sz;
    int x = 0;
    int y = 0;
    //P.at<float>(0,0) = std::stof(cadena,&sz);
    while (!fs.eof())
    {
        fs >> cadena;
        cadena.pop_back();
        //std::cout << cadena <<  std::endl;
        if( cadena == "proj_"){
            if( cont == n_matrix){
                for(int i = 0; i < 14; i ++){
                    fs >> cadena;
                    if(i >= 2) {
                        if(i ==5)
                            cadena.pop_back();
                        if(i == 9)
                            cadena.pop_back();
                        if(i == 13){
                            cadena.pop_back();
                            cadena.pop_back();
                        }
                        P.at<float>(x,y) = std::stof(cadena,&sz);
                        y = (y+1)%4;
                        if(y == 0){
                            x = (x+1)%3;
                        }
                    }
                }
            }
            cont++;
        }
    }
    
}
void CalculaCentro (cv::Mat& proyeccion,cv::Mat& Centro){
    
    //cv::Mat Proj = cv::Mat::zeros(3,4,CV_32F);
    cv::Mat K = cv::Mat::zeros(3,3,CV_32F);
    cv::Mat UltimaColumnaP = cv::Mat::zeros(3, 1, CV_32F);
    
    leerMatrices(0, K);
    UltimaColumnaP.at<float>(0,0) = proyeccion.at<float>(0,3);
    UltimaColumnaP.at<float>(1,0) = proyeccion.at<float>(1,3);
    UltimaColumnaP.at<float>(2,0) = proyeccion.at<float>(2,3);
    cv::Mat K_1 = K.inv();
    
    Centro = K_1 * UltimaColumnaP;
}
float ConsistenciaCheck2(std::vector<cv::Scalar> pixel){
    
    //std::cout << pixel.size() << std::endl;
    long K = pixel.size();
    
    float expresion1 = 0;
    float expresion2 = 0;
    float expresion3 = 0;
    float expresion4 = 0;
    
    for(int i =0; i < K; i++){
        float b  = pixel[i][0];
        float g  = pixel[i][1];
        float r  = pixel[i][2];
        //std::cout << b <<  " "<< g << " "<<r << std::endl;
        
        expresion1 += (r*r)+(g*g)+(b*b);
        expresion2 += r;
        expresion3 += g;
        expresion4 += b;
        
        //std::cout << pixel[i] << std::endl;
        //std::cout << expresion1 << " "<< expresion2 << " "<<expresion3 << std::endl;
    }
    
    float valor1 = expresion1/K;
    float valor2 = (expresion2/K)*(expresion2/K);
    float valor3 = (expresion3/K)*(expresion3/K);
    float valor4 = (expresion4/K)*(expresion4/K);
    
    
    float desviacion = sqrt(valor1-valor2-valor3-valor4);
    //std::cout << valor1 << " "<<valor2<< " " << valor3 << " "<<valor4 << std::endl;
    //std::cout << desviacion<< std::endl;
    return desviacion;
}
void VoxelColoring(cv::Mat im1,cv::Mat im2, Voxel& v){
    
    cv::pyrDown(im1,im1,cv::Size(im1.cols/2, im1.rows/2 ));
    cv::pyrDown(im2,im2,cv::Size(im2.cols/2, im2.rows/2 ));
    
    std::vector<cv::Scalar> vectorColor;
    cv::Mat P1 = cv::Mat::zeros(3,4,CV_32F);
    cv::Mat P2 = cv::Mat::zeros(3,4,CV_32F);
    cv::Mat C1 = cv::Mat::zeros(3,1,CV_32F);
    cv::Mat C2 = cv::Mat::zeros(3,1,CV_32F);
    cv::Mat punto1 =  cv::Mat::zeros(3,1,CV_32F);
    cv::Mat punto2 =  cv::Mat::zeros(3,1,CV_32F);
    cv::Mat vector1;
    cv::Mat vector2;
    int tam = 1;
    
    LeerMatrixdeProyeccion(0, P1);
    LeerMatrixdeProyeccion(1, P2);
    CalculaCentro (P1,C1);
    CalculaCentro (P2,C2);
    
    std::cout << C1 << std::endl;
    std::cout << C2 << std::endl;
    C2 = C2 - C1;
    C1 = cv::Mat::zeros(C1.rows, C1.cols, C1.type());
    C1 = C1 +10;
    C2 = C2 +10;
    std::cout << C1 << std::endl;
    std::cout << C2 << std::endl;
    
    
    
    for(int i1 = 0; i1 < im1.rows/*-(im1.rows-40)*/; i1+= tam){
        for(int j1 = 0; j1 < im1.cols/*-(im1.cols -40)*/;j1+= tam){
            
            cv::Scalar color1;
            
            //RGB -> GBR
            color1[0] = im1.at<cv::Vec3b>(i1,j1)[0];
            color1[1] = im1.at<cv::Vec3b>(i1,j1)[1];
            color1[2] = im1.at<cv::Vec3b>(i1,j1)[2];
            
            punto1.at<float>(0,0) = i1;
            punto1.at<float>(0,1) = j1;
            punto1.at<float>(0,2) = 1;
            
            vector1 = (punto1 - C1);
        
            for(int i2 = i1; i2 < im2.rows/*-(im2.rows -40)*/; i2+= tam){
                for(int j2 = j1; j2 < im2.cols/*-(im2.cols-40)*/; j2+= tam){
                    
                    cv::Scalar color2;
                    
                    color2[0] = im2.at<cv::Vec3b>(i2,j2)[0];
                    color2[1] = im2.at<cv::Vec3b>(i2,j2)[1];
                    color2[2] = im2.at<cv::Vec3b>(i2,j2)[2];
                    
                    punto2.at<float>(0,0) = i2;
                    punto2.at<float>(0,1) = j2;
                    punto2.at<float>(0,2) = 1;
                    
                    vector2 = (punto2 - C2);
                    
                    vectorColor.push_back(color1);
                    vectorColor.push_back(color2);

                    double consistencia = ConsistenciaCheck2(vectorColor);
                    //std::cout << consistencia << std::endl;
                    bool encontrado = false;
                    if (consistencia < 1.4){
                        //std::cout << "Entramos"<< std::endl;
                        cv::Point3f punto;
                        float distancia;
                        float mindistancia = 1000000000.0;
                        
                        for(int i = 0; i < v.Tamanio(); i++){
                            for(int j = 0; j < v.Tamanio();j++){
                                for(int k= 0; k < v.Tamanio();k++){
                                    int lamda = 0;
                                    StructVoxel aux = v.Get(i, j, k);
                                    cv::Point3f punto3D = aux.punto;
                                    do{
                                        distancia = Distancia(lamda,vector1,C1,punto3D);
                                        distancia += Distancia(lamda,vector2,C2,punto3D);
                                        
                                        distancia = distancia/2;
                                        //std::cout << distancia << std::endl;
                                        if(distancia < mindistancia){
                                            mindistancia = distancia;
                                            punto.x = i;
                                            punto.y = j;
                                            punto.z = k;
                                            if(lamda > 0){
                                                encontrado = true;
                                            }
                                        }
                                        lamda++;
                                    }while(mindistancia >= distancia);
                                    //std::cout << "/////////////////////////////// "<< std::endl;
                                }
                            }
                                
                        }
                        if(encontrado){
                            //std::cout << "Encontrado " <<std::endl;
                            v.Pinta(punto.x, punto.y, punto.z);
                            v.ModificarColor(punto.x, punto.y, punto.z, color1);
                            i2 = im2.rows;
                            j2 = im2.cols;
                            encontrado = false;
                        }

                    }
                }
            }
        }
    }
}
void ProyectarPixel(cv::Point3f Punto3D, cv::Mat P,cv::Point2f& toReturn){
    
    /*Proyecta el voxel en las coordenadas de la imagen*/
    cv::Mat worldCoord = cv::Mat::zeros(4, 1,CV_32F);
    worldCoord.at<float>(0,0) = Punto3D.x;
    worldCoord.at<float>(1,0) = Punto3D.y;
    worldCoord.at<float>(2,0) = Punto3D.z;
    worldCoord.at<float>(3,0) = 1.0;
    
    cv::Mat projection = P * worldCoord;
    
    //Scale the result back down by the "w coordinate"
    //(since the scale of the projection matrix is arbitrary)
    projection = projection/projection.at<float>(2,0);
    
    toReturn.x = projection.at<float>(0,0);
    toReturn.y = projection.at<float>(1,0);
    
}
void VoxelColoring2(cv::Mat im1, int i, cv::Mat im2,int j,Voxel& v,cv::Mat silueta1,cv::Mat silueta2){
    
    cv::Mat P1 = cv::Mat::zeros(3,4,CV_32F);
    cv::Mat P2 = cv::Mat::zeros(3,4,CV_32F);
    std::vector<cv::Point2f> vp;
    LeerMatrixdeProyeccion(i, P1);
    LeerMatrixdeProyeccion(j, P2);
    
    std::vector<cv::Scalar> vectorColor;
    cv::Point2f Puntoim1;
    cv::Point2f Puntoim2;
    cv::Scalar Colorim1;
    cv::Scalar Colorim2;
    
    for(int i = 0; i < v.Tamanio(); i++){
        for(int j = 0; j < v.Tamanio();j++){
            for(int k= 0; k < v.Tamanio();k++){

                ProyectarPixel(v.GetPunto(i, j, k), P1,Puntoim1);
                ProyectarPixel(v.GetPunto(i, j, k), P2,Puntoim2);
                
                //std::cout << Puntoim1 << " "<<Puntoim2 << std::endl;
                
                if( (Puntoim1.x < im1.cols and Puntoim1.x >= 0)
                   and (Puntoim1.y < im1.rows and Puntoim1.y >= 0)
                   and (Puntoim2.x < im2.cols and Puntoim2.x >= 0)
                   and (Puntoim2.y < im2.rows and Puntoim2.y >= 0)){
                    
                    if(silueta1.at<cv::Vec3b>(Puntoim1.y,Puntoim1.x)[0] != 0 or silueta2.at<cv::Vec3b>(Puntoim2.y,Puntoim2.x)[0] != 0){
                        Colorim2[0] = im2.at<cv::Vec3b>(Puntoim2.y,Puntoim2.x)[0];
                        Colorim2[1] = im2.at<cv::Vec3b>(Puntoim2.y,Puntoim2.x)[1];
                        Colorim2[2] = im2.at<cv::Vec3b>(Puntoim2.y,Puntoim2.x)[2];
                    
                        Colorim1[0] = im1.at<cv::Vec3b>(Puntoim1.y,Puntoim1.x)[0];
                        Colorim1[1] = im1.at<cv::Vec3b>(Puntoim1.y,Puntoim1.x)[1];
                        Colorim1[2] = im1.at<cv::Vec3b>(Puntoim1.y,Puntoim1.x)[2];
                        
                        vectorColor.push_back(Colorim1);
                        vectorColor.push_back(Colorim2);
                        
                        double consistencia = ConsistenciaCheck2(vectorColor);
                        vectorColor.clear();
                        vectorColor.clear();
                        //std::cout << consistencia << std::endl;
                        if (consistencia > 0 and consistencia < 20){
                            v.ModificarColor(i, j, k,Colorim1);
                            v.Pinta(i, j, k);
                        }
                    }
                }
            }
        }
    }
}
float Distancia(int lamda,cv::Mat vector1,cv::Mat punto1, cv::Point3f p2){
    float distancia;
    cv::Point3f p1;
    
    //p2 = punto2 +(lamda*vector2);
    p1.x = (punto1.at<float>(0,0) + lamda*vector1.at<float>(0,0));
    p1.y = (punto1.at<float>(1,0) + lamda*vector1.at<float>(1,0));
    p1.z = (punto1.at<float>(2,0) + lamda*vector1.at<float>(2,0));
    
    distancia = sqrt(((p2.x-p1.x)*(p2.x-p1.x))
                    +((p2.y-p1.y)*(p2.y-p1.y))
                    +((p2.z-p1.z)*(p2.z-p1.z)));
    
    return distancia;
}
std::vector< cv::Mat > CrearSilhouttes(std::vector<cv::Mat> listaImagenes){
	std::vector<cv::Mat> salida;
	for (int i =0; i < listaImagenes.size();i++){
		
        /* calcular silhouette */
        cv::Mat silhouette;
        cv::cvtColor(listaImagenes.at(i), silhouette, CV_BGR2HSV);
        cv::inRange(silhouette, cv::Scalar(0,0,0), cv::Scalar(200,200,200), silhouette);
		salida.push_back(silhouette);
		
	}
	return salida;
}
