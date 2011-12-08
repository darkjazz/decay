/*
 *  world.h
 *  mikro
 *
 *  Created by alo on 22/04/2011.
 *  
 *	This file is part of mikro.
 *
 *	mikro is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 
 *	mikro is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 
 *	You should have received a copy of the GNU General Public License
 *	along with mikro.  If not, see <http://www.gnu.org/licenses/>. 
 *
 */
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
#include <math.h>

#include "util.h"

using namespace std;

class Cell {
public:
	Cell() : x(0), y(0), z(0), pattern(0) {};
	~Cell() {};
	int x, y, z; 
	int states[3];
	int pattern;
	Cell* neighbors[26];
	
	int countAliveNeighbors(int);
};

class World {
	
public:
	World(int, int, int);
	~World();
	
	Cell*** cells;
	
	int index() { return _index; };
	int sizeX() { return _sizeX; };
	int sizeY() { return _sizeY; };
	int sizeZ() { return _sizeZ; };
	int alive() { return _alive; }
	double cellState(int, int, int);
	
	void nextIndex();
	void incrementAlive();
	void resetAlive();
	
	void initRandInArea(int, int, int, int, int, int, int, float, bool);
	void initWireCube(int, int, int, int, int, int);
	
private:
	void init();
	void clear();
	int _sizeX, _sizeY, _sizeZ, _index, _alive;
};


#endif