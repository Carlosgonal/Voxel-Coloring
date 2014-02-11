//
//  InterfrazGrafica.h
//  ProyectoVC
//
//  Created by Carlos González on 03/01/14.
//  Copyright (c) 2014 Carlos González. All rights reserved.
//

#ifndef __ProyectoVC__InterfrazGrafica__
#define __ProyectoVC__InterfrazGrafica__

#include <iostream>
#include <GLUI/GLUI.h>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <math.h>
#include <vector>
#include <stdio.h>
// yes, I know stdio.h is not good C++, but I like the *printf()
#include <stdlib.h>
#include <ctype.h>

#include "Voxel Coloring.h"

void	Animate( void );
void	Buttons( int );
void	Display( void );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( void );
void	InitGlui( void );
void	InitGraphics( void );
void	InitLists( void );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( void );
void	Resize( int, int );
void	Visibility( int );

void DibujarObjeto(int);

void	Arrow( float [3], float [3] );
void	Cross( float [3], float [3], float [3] );
float	Dot( float [3], float [3] );
float	Unit( float [3], float [3] );
void	Axes( float );
void	HsvRgb( float[3], float [3] );

#endif /* defined(__ProyectoVC__InterfrazGrafica__) */
