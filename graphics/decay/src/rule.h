/*
 *  rule.h
 *  decay
 *
 *  Created by alo on 11/07/2011.
 *  
 *	This file is part of decay.
 *
 *	decay is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 
 *	decay is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 
 *	You should have received a copy of the GNU General Public License
 *	along with decay.  If not, see <http://www.gnu.org/licenses/>. 
 *
 */

#ifndef RULE_H
#define RULE_H

#include "world.h"

class Rule {
public: 
	Rule();
	~Rule();
	
	int* states() { return _states; };
	void setStates(int);
	int numStates() { return _numStates; };
	bool cellAlive(Cell*, int);
	
	virtual void next(Cell*, int) {};
	virtual void setBirths(int*) {};
	virtual void setSurvivals(int*) {};
	
private:
	int *_states;
	int _numStates;
};

class Faders : public Rule {
public:
	Faders(int*, int*, int);
	~Faders() {};
	
	void setBirths(int*);
	void setSurvivals(int*);
	
	void next(Cell*, int);
		
private:
	int _births[26]; 
	int _survivals[26];
};

class Life : public Rule {
public:
	Life(int*, int*);
	~Life() {};
	
	void setBirths(int*);
	void setSurvivals(int*);

	void next(Cell*, int);
	
private:
	int _births[26]; 
	int _survivals[26];	
};

#endif