/*
 *  ogl.h
 *  pime
 *
 *  Created by alo on 11/07/2011.
 *  
 *	This file is part of pime.
 *
 *	pime is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 
 *	pime is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 
 *	You should have received a copy of the GNU General Public License
 *	along with pime.  If not, see <http://www.gnu.org/licenses/>. 
 *
 */

#ifndef OGL_H
#define OGL_H

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "world.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GraphicsRenderer : public AppBasic {
	
public:
	GraphicsRenderer() {};
	
	~GraphicsRenderer() {};
		
	void setupOgl (int, int, int, int, int);
	
	void setupFrame(int, int);
			
	void drawFragment(Cell*);
	
	int currentPattern() { return _currentPattern; }
	
	void setCurrentPattern(int pattern) { _currentPattern = pattern; }
	
private:
	
	float _red, _green, _blue, _alpha, _rAng;
	
	float _left, _bottom, _front, _width, _height, _depth;
	
	float _size, _halfscreen;
	
	int _worldIndex, _maxState, _sx, _sy, _sz, _currentPattern;
		
	Cell* _currentCell;
	
	// *** patterns *** //
	
	void pattern00();
	
	void pattern01();
	
	void pattern02();

	void pattern03();
	
	void pattern04();
	
	void pattern05();
	
	void pattern06();

	void pattern07();

	void pattern08();

	void pattern09();

	void pattern10();

	// *** basic drawing functions *** //
	
	void strokeCube();
	
	void fillCube();
	
	void drawPoint (float, float, float, float);
	
	void drawLine (float, float, float, float, float, float, float);	
};


#endif