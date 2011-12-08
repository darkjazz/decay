/*
 *  rule.cpp
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

#include "rule.h"


Rule::Rule() {
	_numStates = 2;
	_states = new int[_numStates];
	_states[0] = 0;
	_states[1] = 1;
}

Rule::~Rule() {
	delete [] _states;
}

void Rule::setStates(int numStates) { 
	int i;
	_numStates = numStates;
	if (_states) { delete [] _states; }
	_states = new int[numStates];
	for (i = 0; i < numStates; i++)
	{
		_states[i] = i; 
	}
}

bool Rule::cellAlive(Cell* cell, int index) {
	return (cell->states[index] > 0);
}

void Faders::setBirths(int *births) {
	int i, size;
	for (i = 0; i < 26; i++) {
		_births[i] = 0;
	}
	if (births)
	{
		size = sizeof(births) / sizeof(int);
		for (i = 0; i < size; i++) {
			_births[births[i]] = 1;
		}
	}
}

void Faders::setSurvivals(int *survivals) {
	int i, size;
	for (i = 0; i < 26; i++) {
		_survivals[i] = 0;
	}
	if (survivals)
	{
		size = sizeof(survivals) / sizeof(int);	
		for (i = 0; i < size; i++) {
			_survivals[survivals[i]] = 1;
		}
	}
}

Faders::Faders(int *births, int *survivals, int states) : Rule() {
	setBirths(births);
	setSurvivals(survivals);
	setStates(states);
}

void Faders::next(Cell* current, int index) {
	int alive, state, nextIndex;
	
	nextIndex = wrapi(index + 1, 0, 2);
	
	alive = current->countAliveNeighbors(index);
	state = current->states[index];
	if (state > 1) {
		if (state < numStates()) {
			current->states[nextIndex] = state + 1;
		}
		else
		{
			current->states[nextIndex] = 0;
		}
	}
	else
	{
		if (state == 0)
		{
			current->states[nextIndex] = _births[alive];
		}
		else
		{
			if (_survivals[alive] == 0) {
				if (state < numStates()) {
					current->states[nextIndex] = state + 1;
				}
				else
				{
					current->states[nextIndex] = 0;
				}
			}
			else
			{
				current->states[nextIndex] = 1;
			}
		}
	}
		
}

void Life::setBirths(int *births) {
	int i, size;
	for (i = 0; i < 26; i++) {
		_births[i] = 0;
	}
	size = sizeof(births) / sizeof(int);
	for (i = 0; i < size; i++) {
		_births[births[i]] = 1;
	}
}

void Life::setSurvivals(int *survivals) {
	int i, size;
	for (i = 0; i < 26; i++) {
		_survivals[i] = 0;
	}
	size = sizeof(survivals) / sizeof(int);	
	for (i = 0; i < size; i++) {
		_survivals[survivals[i]] = 1;
	}
}

Life::Life(int *births, int *survivals) : Rule() {
	setBirths(births);
	setSurvivals(survivals);
}

void Life::next(Cell* current, int index) {
	int alive, state, nextIndex;
	
	nextIndex = wrapi(index + 1, 0, 2);
	
	alive = current->countAliveNeighbors(index);
	state = current->states[index];
	
	if (state == 1) {
		current->states[nextIndex] = _survivals[alive];
	}
	else
	{
		current->states[nextIndex] = _births[alive];
	}
	
}
