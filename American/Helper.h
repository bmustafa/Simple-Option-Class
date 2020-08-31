// Exercise 9.B
// File: Helper.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish functions needed
// for the price calculation for 
// american options.


#ifndef HELPER_H
#define HELPER_H

using namespace std;


double y1(double vol, double r, double b)
{
// Calculates a component used in the calculation of the price of an american call option

	return(.5 - (b / pow(vol, 2)) + pow(pow((b / pow(vol, 2)) - .5, 2) + (2 * r / pow(vol, 2)), .5));
}



double y2(double vol, double r, double b)
{
// Calculates a component used in the calculation of the price of an american call option

	double y = (.5 - (b / pow(vol, 2)) - (pow(pow(((b / pow(vol, 2)) - .5), 2) + (2 * r / pow(vol, 2)), .5)));
	return y;
}

#endif