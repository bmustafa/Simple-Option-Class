// Exercise 9.B
// File: MeshArray.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish functions
// to generate a vector with a range
// of numbers

#ifndef MESHARRAY_H
#define MESHARRAY_H

#include <vector>
using namespace std;

vector<double> MeshArray(double first, double last, int elements)
{
	// Create a vector of double values evenly spaced between two provided numbers

	double distance = abs(first - last) / (elements - 1);
	// Create a variable for the increment between elements of the output vector

	vector<double> mesh(elements);
	if (first > last)
	{
		double temp = last;
		last = first;
		first = temp;
		// make sure that the first element if smaller than the last element, if not switch their values

	}
	mesh[0] = first;
	for (int i = 0; i < (elements - 1); i++)
	{
		mesh[i + 1] = mesh[i] + distance;
		// loop and place evenly spaced numbers in the output vector

	}
	return mesh;
}


#endif