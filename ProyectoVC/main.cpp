//
//  main.cpp
//  ProyectoVC
//
//  Created by Carlos González on 03/01/14.
//  Copyright (c) 2014 Carlos González. All rights reserved.
//


#include "InterfrazGrafica.h"
#include "Voxel Coloring.h"

using namespace std;

//
// main program:
//

int main( int argc, char *argv[] )
{
    
    //Iniciamos OpenGl y su interfaz de usuario
	glutInit( &argc, argv );
	InitGraphics();
	InitLists();
	Reset();
	InitGlui();
	glutMainLoop();
	////////////////////////////////////////////
    
	return 0;
}
