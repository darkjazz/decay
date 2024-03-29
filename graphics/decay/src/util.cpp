/*
 *  util.cpp
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

#include "util.h"

//void initrand() 
//{ 
//    srand((unsigned)(time(0))); 
//} 

float map(float val, float lo, float hi)
{
	return val * (hi - lo) + lo;
}

int randint(int min, int max) 
{ 
    if (min>max) 
    { 
        return max+(int)((min-max+1)*rand()/(RAND_MAX+1.0)); 
    } 
    else 
    { 
        return min+(int)((max-min+1)*rand()/(RAND_MAX+1.0)); 
    } 
}

float randf() 
{ 
    return rand()/((float)(RAND_MAX)+1); 
} 

double randd() 
{ 
    return rand()/((double)(RAND_MAX)+1); 
} 

float randfloat(float min, float max) 
{ 
    if (min>max) 
    { 
        return randf()*(min-max)+max;     
    } 
    else 
    { 
        return randf()*(max-min)+min; 
    }     
} 

int xmod(int a, int n) {
	return a - (n * floor(a / (double)n));
}

int wrapi(int val, int lo, int hi) {
	int rtn;
	rtn = xmod((val - lo), (hi - lo + 1)) + lo;
	return rtn;
}

float wrapf(float val, float lo, float hi)
{
	return xmodf(val - lo, hi - lo) + lo;
}

double wrapd(double val, double lo, double hi)
{
	return xmodd(val - lo, hi - lo) + lo;
}

float xmodf(float value, float hi)
{
	return value - hi*floor(value/hi);
}

double xmodd(double value, double hi) 
{
	return value - hi*floor(value/hi);
}

int isEven(int number)
{
	return (int)(number % 2 == 0);
}

bool between(int aNumber, int a, int b) {
	if (aNumber >= a && aNumber <= b) {
		return true;
	}
	else {
		return false;
	}
}

float clipf(float val, float min, float max)
{
	if (val < min)
		val = min;
	if (val > max)
		val = max;
	return	val;
}

float linlin(float val, float inmin, float inmax, float outmin, float outmax) {
	
	if (val <= inmin) { return outmin; }
	if (val >= inmax) { return outmax; }
	
	return ((val-inmin)/(inmax-inmin) * ((outmax-outmin) + outmin));
}