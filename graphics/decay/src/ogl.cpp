/*
 *  ogl.cpp
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

#include "ogl.h"

const double pi = 3.1415926535;

GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };
GLfloat mat_emission[]		= { 0.0, 0.1, 0.3, 0.0 };
GLfloat mat_shininess[]		= { 128.0 };

void GraphicsRenderer::setupOgl (int w, int h, int sx, int sy, int sz) {
		
	_rAng = 0;
	
	_sx = sx; _sy = sy; _sz = sz;

	/*
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);	
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);	
	
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)1, 0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	 */
}

void GraphicsRenderer::setupFrame (int index, int state) {
	_worldIndex = wrapi(index + 1, 0, 2);
	_maxState = state;
}


void GraphicsRenderer::drawFragment (Cell* cell) {
	
	_currentCell = cell;
	
	if (_currentCell->states[_worldIndex] > 0 && _currentCell->pattern != _currentPattern) {
		_currentCell->pattern = _currentPattern;
	}
	
	switch (_currentCell->pattern) {
		case 1:
			pattern01();
			break;
		case 2:
			pattern02();
			break;
		case 3:
			pattern03();
			break;
		case 4:
			pattern04();
			break;
		case 5:
			pattern05();
			break;
		case 6:
			pattern06();
			break;
		case 7:
			pattern07();
			break;
		case 8:
			pattern08();
			break;
		case 9:
			pattern09();
			break;
		case 10:
			pattern10();
			break;
		default:
			break;
	}
	
}

void GraphicsRenderer::pattern00() {

	// this pattern shows the order of ogl 3D drawing: 1. back (-) to front (+) 2. bottom (-) to top (+) 3. left (-) to right (+)
	
	int p, q, r, i, j;
		
	if (_currentCell->x == 14 && _currentCell->y == 14 && _currentCell->z==14)
	{
		_size = 1.2;
		_halfscreen = 20.0;
		
		i = 0;
		
		for (i = 0; i < 26; i++)
		{
			p = (_currentCell->neighbors[i]->x - _currentCell->x) + 1;
			q = (_currentCell->neighbors[i]->y - _currentCell->y) + 1;
			r = (_currentCell->neighbors[i]->z - _currentCell->z) + 1;
			j = (p*8+p) + (q*2+q) + r;
			_red = _green = _blue = (float)(j + 1) / 26.0;
			
			_left = (float)(_currentCell->x + (_currentCell->neighbors[i]->x - _currentCell->x)) * _size - _halfscreen;
			_bottom = (float)(_currentCell->y + (_currentCell->neighbors[i]->y - _currentCell->y)) * _size - _halfscreen;
			_front = (float)(_currentCell->z + (_currentCell->neighbors[i]->z - _currentCell->z)) * _size - _halfscreen;			

			_width = _height = _depth = _size * 0.5;
			_alpha = 1.0;

			strokeCube();
			
		}
		
	}
	
}

void GraphicsRenderer::pattern01() {
	
	float state;
	
	if (_currentCell->states[_worldIndex] > 0)
	{
	
		_size = 1.0;
		_halfscreen = _size * 15;
		state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);
		
		_left = (float)_currentCell->x * _size - _halfscreen + _size - (_size * (1 - state));
		_bottom = (float)_currentCell->y * _size - _halfscreen + _size - (_size * (1 - state));
		_front = (float)_currentCell->z * _size - _halfscreen + _size - (_size * (1 - state));
		
		_width = _height = _depth = _size * (1 - state) * 0.5f;

		_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.5);
		_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.5);
		_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.5, 0.1);
		_alpha = state * 0.5f;
		
		gl::color(_red, _green, _blue, _alpha);
		gl::drawCube(Vec3f(_left + 0.5f, _bottom + 0.5f, _front + 0.5f), Vec3f( _width, _height, _depth ));
		
//		fillCube();
				
	}	
}

void GraphicsRenderer::pattern02() {
	
	float state;
	
	if (_currentCell->z == (int)(_sz / 2 - 1) || _currentCell->z == (int)(_sz / 2) || 
		_currentCell->x == (int)(_sx / 2 - 1) || _currentCell->x == (int)(_sx / 2)
	)
	{
	
		if ((_currentCell->states[_worldIndex]) > 0)
		{
			
			_size = 1.0;
			_halfscreen = _size * 15;
			state = (_maxState - _currentCell->states[_worldIndex]) * (2.0 / _maxState);
			
			_left = (float)_currentCell->x * _size - _halfscreen + _size - (_size * state);
			_bottom = (float)_currentCell->y * _size - _halfscreen + _size - (_size * state);
			_front = (float)_currentCell->z * _size - _halfscreen + _size - (_size * state);
			
			_width = _height = _depth = _size * state;
			
			_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.5, 0.0);
			_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.1, 0.9);
			_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.0, 0.8);
			_alpha = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.4, 1.0); 
			
			if (_currentCell->states[_worldIndex] == 1)
			{
				fillCube();
			}
			{
				strokeCube();
			}
			
		}	
	}
}

void GraphicsRenderer::pattern03() {
	
	float state;
	
	if ((_currentCell->states[_worldIndex]) > 0)
	{
		
		_size = 1.0;
		_halfscreen = _size * 15;
		state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);
		
		_left = (float)_currentCell->x * _size - _halfscreen + _size - sin(state * 2 * pi);
		_bottom = (float)_currentCell->y * _size - _halfscreen + _size - sin(state * 2 * pi);
		_front = (float)_currentCell->z * _size - _halfscreen + _size - sin(state * 2 * pi);
		
		_width = _height = _depth = _size * state;
		
		_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.1, 1.0);
		_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.1, 1.0);
		_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.1, 1.0);
		_alpha = 1.0;
		
		drawPoint(_left, _bottom, _front, 1.0);
		
	}	
}

void GraphicsRenderer::pattern04() {
	
	if (_currentCell->x == (int)(_sx / 2) || _currentCell->y == (int)(_sy / 2) || _currentCell->z == (int)(_sz / 2))
	{
		
		_size = 1.0;
		_halfscreen = _size * 15;
		
		_left = (float)_currentCell->x * _size - _halfscreen;
		_bottom = (float)_currentCell->y * _size - _halfscreen;
		_front = (float)_currentCell->z * _size - _halfscreen;
		
		_width = _height = _depth = _size * (1.0 / _currentCell->states[_worldIndex]);
		
		_red = 0.4;
		_green = 0.4;
		_blue = 1.0;
		_alpha = 0.2;

//		ci::ColorA col(CM_RGB, _red, _green, _blue, _alpha);
//		
//		glMaterialfv( GL_FRONT, GL_DIFFUSE, col);
//		glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
//		glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
		
		gl::drawCube(Vec3f(_left + 0.5f, _bottom + 0.5f, _front + 0.5f), Vec3f( _width, _height, _depth ));
			
	}	
}

void GraphicsRenderer::pattern05() {
	
	int i;
	float ex, ey, ez;
	
	if (
		(_currentCell->x != 0 && _currentCell->y != 0 && _currentCell->z != 0 && 
		_currentCell->x != _sx - 1 && _currentCell->y != _sy - 1 && _currentCell->z != _sz - 1) && 
		(
		 _currentCell->x == (int)(_sx / 3) || _currentCell->x == (int)(_sx * 2 / 3) ||
		 _currentCell->z == (int)(_sz / 3) || _currentCell->z == (int)(_sz * 2 / 3)	
		)
	)
	{
		if (_currentCell->states[_worldIndex] > 0) {
			
			_size = 1.0f;
			_halfscreen = _size * 15;
			
			_left = (float)_currentCell->x * _size - _halfscreen + (_size * 0.5);
			_bottom = (float)_currentCell->y * _size - _halfscreen + (_size * 0.5);
			_front = (float)_currentCell->z * _size - _halfscreen + (_size * 0.5);
			
			for (i = 0; i < 26; i++) {
				if (_currentCell->neighbors[i]->states[_worldIndex] > 0 && _currentCell->neighbors[i]->states[_worldIndex] < 13)
				{
					ex = _currentCell->neighbors[i]->x * _size - _halfscreen + (_size * 0.5);
					ey = _currentCell->neighbors[i]->y * _size - _halfscreen + (_size * 0.5);
					ez = _currentCell->neighbors[i]->z * _size - _halfscreen + (_size * 0.5);

					_red = 0.0;
					_green = 0.5;
					_blue = 1.0 - linlin(_currentCell->neighbors[i]->states[_worldIndex], 1, 12, 0.0, 0.7);
					_alpha = 1.0 - linlin(_currentCell->neighbors[i]->states[_worldIndex], 1, 12, 0.2, 0.8);
					_alpha *= 0.5f;

					gl::color(_red, _green, _blue, _alpha);				
					gl::drawLine( Vec3f(_left, _bottom, _front), Vec3f(ex, ey, ez) );
				}
			}
		}
	}
}

void GraphicsRenderer::pattern06() {
	float state;
	
	if (
		between(_currentCell->x, _sx / 3, _sx * 2 / 3 ) &&
		between(_currentCell->y, _sy / 3, _sy * 2 / 3 ) &&
		between(_currentCell->z, _sz / 3, _sz * 2 / 3 ) &&
		(isEven(_currentCell->x) && !isEven(_currentCell->y))
	)
	{
		
		if ((_currentCell->states[_worldIndex]) > 0)
		{
						
			_size = 2.0;
			_halfscreen = 5;
			state = (_maxState - _currentCell->states[_worldIndex]) * (1.0 / _maxState);
			
			_left = (float)_currentCell->x - _halfscreen + 1.0 - (_size * (1-state));
			_bottom = (float)_currentCell->y - _halfscreen + 1.0 - (_size * (1-state));
			_front = (float)_currentCell->z - _halfscreen + 1.0 - (_size * (1-state));
			
			_width = _height = _depth = _size;
			
			_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.5, 0.0);
			_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.1, 0.9);
			_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.0, 0.8);
			_alpha = 1; //1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.4, 1.0); 
			
//			ci::ColorA col(CM_HSV,  
//				(float)_currentCell->x/(float)(_sx - 1),
//				(float)_currentCell->y/(float)(_sy - 1),
//				(float)_currentCell->z/(float)(_sz - 1),
//				1.0f
//			);

			ci::ColorA col(CM_RGB, _red, _green, _blue, _alpha);
			
//			gl::color(_red, _green, _blue, _alpha);
			glMaterialfv( GL_FRONT, GL_DIFFUSE, col);
			glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
//			glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
			gl::drawSphere( Vec3f(_left, _bottom, _front), _width, 24);
			
		}	
	}	
}

void GraphicsRenderer::pattern07() {
	
	float state;
	
	if (_currentCell->states[_worldIndex] > 0)
	{
		
		_size = 1.0;
		_halfscreen = _size * 15;
		state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);
		
		_left = (float)_currentCell->x * _size - _halfscreen + _size - sin(_size * (1 - state) * 2 * pi);
		_bottom = (float)_currentCell->y * _size - _halfscreen + _size - sin(_size * (1 - state) * 2 * pi);
		_front = (float)_currentCell->z * _size - _halfscreen + _size - sin(_size * (1 - state) * 2 * pi);
		
		_width = _height = _depth = _size * (1 - state) * 0.5f;
		
		_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.8);
		_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.75, 0.25);
		_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.5, 0.1);
		_alpha = state * 0.5f;
		
		gl::color(_red, _green, _blue, _alpha);
		gl::drawCube(Vec3f(_left, _bottom, _front), Vec3f( _width, _height, _depth ));
		
		//		fillCube();
		
	}	
}

void GraphicsRenderer::pattern08() {
	
	float state;
	
	if (
		between(_currentCell->x, _sx / 3, _sx * 2 / 3 ) &&
		between(_currentCell->y, _sy / 3, _sy * 2 / 3 ) &&
		between(_currentCell->z, _sz / 3, _sz * 2 / 3 )
	)
	{
		if (_currentCell->states[_worldIndex] > 0) {
			
			_size = 1.0f;
			_halfscreen = _size * 15;
			
			state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);			
			
			_left = (float)_currentCell->x * _size - _halfscreen + (_size * 0.5);
			_bottom = (float)_currentCell->y * _size - _halfscreen + (_size * 0.5);
			_front = (float)_currentCell->z * _size - _halfscreen + (_size * 0.5);
			
			_width = _height = _depth = _size;

			_red = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.5);
			_green = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.25);
			_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 1.0, 0.25);
			_alpha = 1.0 - state;
			
			gl::color(_red, _green, _blue, _alpha);
			gl::drawCube(Vec3f(_left, _bottom, _front), Vec3f( _width, _height, _depth ));
			
		}
	}
}

void GraphicsRenderer::pattern09() {
	
	int i;
	float ex, ey, ez, state;
	
	if (
		(_currentCell->x != 0 && _currentCell->y != 0 && _currentCell->z != 0 && 
		 _currentCell->x != _sx - 1 && _currentCell->y != _sy - 1 && _currentCell->z != _sz - 1) && 
		(
		 _currentCell->x == (int)(_sx / 3) || _currentCell->x == (int)(_sx * 2 / 3) ||
		 _currentCell->z == (int)(_sz / 3) || _currentCell->z == (int)(_sz * 2 / 3)	
		 )
		)
	{
		if (_currentCell->states[_worldIndex] > 0) {
			
			_size = 1.0f;
			_halfscreen = _size * 15;
			
			state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);
			
			_left = (float)_currentCell->x - _halfscreen + 1.0 - (sin((1 - state) * pi));
			_bottom = (float)_currentCell->y - _halfscreen + 1.0 - (sin((1 - state) * pi));
			_front = (float)_currentCell->z - _halfscreen + 1.0 - (sin((1 - state) * pi));
			
			for (i = 0; i < 26; i++) {
				if (_currentCell->neighbors[i]->states[_worldIndex] > 0 && _currentCell->neighbors[i]->states[_worldIndex] < 9)
				{

					state = (_maxState - _currentCell->neighbors[i]->states[_worldIndex]) * (_size / _maxState);

					ex = _currentCell->neighbors[i]->x - _halfscreen + 1.0 - (sin(_size * (1 - state) * 2 * pi));
					ey = _currentCell->neighbors[i]->y - _halfscreen + 1.0 - (sin(_size * (1 - state) * 2 * pi));
					ez = _currentCell->neighbors[i]->z - _halfscreen + 1.0 - (sin(_size * (1 - state) * 2 * pi));
					
					_red = 0.0;
					_green = 0.5;
					_blue = 1.0 - linlin(_currentCell->neighbors[i]->states[_worldIndex], 1, 8, 0.0, 0.7);
					_alpha = 1.0 - linlin(_currentCell->neighbors[i]->states[_worldIndex], 1, 8, 0.2, 0.8);
					_alpha *= 0.5f;
					
					gl::color(_red, _green, _blue, _alpha);				
					gl::drawLine( Vec3f(_left, _bottom, _front), Vec3f(ex, ey, ez) );
				}
			}
		}
	}
}

void GraphicsRenderer::pattern10() {
	
	if (_currentCell->states[_worldIndex] > 0) {
		float state;
		_size = 1.0;
		_halfscreen = 15;
		state = (_maxState - _currentCell->states[_worldIndex]) * (_size / _maxState);
		
		_left = (float)_currentCell->x * _size - _halfscreen + _size - (_size * state);
		_bottom = (float)_currentCell->y * _size - _halfscreen + _size - (_size * state);
		_front = (float)_currentCell->z * _size - _halfscreen + _size - (_size * state);
		
		_width = (_size * 2 * state);
		_height = (_size * 2 * state);
		_depth = (_size * 2 * state);
		
		_red = 0.0;
		_green = 0.2;
		_blue = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.0, 0.7);
		_alpha = 1.0 - linlin(_currentCell->states[_worldIndex], 1, _maxState, 0.2, 0.8);
	
		gl::color(_red, _green, _blue, _alpha);
		gl::drawCube( Vec3f(_left, _bottom, _front), Vec3f(_width, _height, _depth) );
//		gl::drawSolidRect(Rectf(_left, _bottom, _width, _height));
//		gl::drawCylinder();
		
	}
	
}

void GraphicsRenderer::strokeCube() {
	glColor4f(_red, _green, _blue, _alpha);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	
	
	glVertex3f (_left, _bottom, _front);
	glVertex3f (_left + _width, _bottom, _front);
	
	glVertex3f (_left + _width, _bottom, _front);
	glVertex3f (_left + _width, _bottom + _height, _front);
	
	glVertex3f (_left + _width, _bottom + _height, _front);
	glVertex3f (_left, _bottom + _height, _front);
	
	glVertex3f (_left, _bottom + _height, _front);
	glVertex3f (_left, _bottom, _front);	
	
	glVertex3f (_left, _bottom, _front);
	glVertex3f (_left, _bottom, _front + _depth);
	
	glVertex3f (_left, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom, _front + _depth);
	
	glVertex3f (_left + _width, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom, _front);
	
	glVertex3f (_left, _bottom + _height, _front);
	glVertex3f (_left, _bottom + _height, _front + _depth);
	
	glVertex3f (_left, _bottom + _height, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front);
	
	glVertex3f (_left, _bottom, _front + _depth);
	glVertex3f (_left, _bottom + _height, _front + _depth);
	
	glVertex3f (_left + _width, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	
}

void GraphicsRenderer::fillCube() {
	glColor4f(_red, _green, _blue, _alpha);
	glEnable(GL_POLYGON_SMOOTH);
	glBegin(GL_POLYGON);
	
	glVertex3f (_left, _bottom, _front);
	glVertex3f (_left + _width, _bottom, _front);
	
	glVertex3f (_left + _width, _bottom, _front);
	glVertex3f (_left + _width, _bottom + _height, _front);
	
	glVertex3f (_left + _width, _bottom + _height, _front);
	glVertex3f (_left, _bottom + _height, _front);
	
	glVertex3f (_left, _bottom + _height, _front);
	glVertex3f (_left, _bottom, _front);	
	
	glVertex3f (_left, _bottom, _front);
	glVertex3f (_left, _bottom, _front + _depth);
	
	glVertex3f (_left, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom, _front + _depth);
	
	glVertex3f (_left + _width, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom, _front);
	
	glVertex3f (_left, _bottom + _height, _front);
	glVertex3f (_left, _bottom + _height, _front + _depth);
	
	glVertex3f (_left, _bottom + _height, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front);
	
	glVertex3f (_left, _bottom, _front + _depth);
	glVertex3f (_left, _bottom + _height, _front + _depth);
	
	glVertex3f (_left + _width, _bottom, _front + _depth);
	glVertex3f (_left + _width, _bottom + _height, _front + _depth);
	
	glEnd();
	glDisable(GL_POLYGON_SMOOTH);
	
}

void GraphicsRenderer::drawPoint (float x, float y, float z, float sz) {
	glColor4f(_red, _green, _blue, _alpha);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(sz);
	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
}

void GraphicsRenderer::drawLine (float startx, float starty, float startz, float endx, float endy, float endz, float lineWidth) {
	glColor4f(_red, _green, _blue, _alpha);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	
	glVertex3f(startx, starty, startz);
	glVertex3f(endx, endy, endz);
	
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}


