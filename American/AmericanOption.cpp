// Exercise 9.B
// File: AmericanOption.cpp
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish methods and
// attributes for an option class

#include <vector>
#include <iostream>
#include "AmericanOption.h"
#include "Helper.h"
#define M_PI acos(-1.0)

using namespace std;

double AmericanOption::Price() const
{
// Return the price of an american option

	if (call)
	{
		return (k/(y1(vol, r, b) - 1)) * (pow((((y1(vol,r,b) - 1)*s)/ (y1(vol, r, b) * k)), y1(vol,r,b)));
		// if option is a call option, return the price given by this formula

	}
	else
	{
		return (k / (1 - y2(vol, r, b))) * (pow((((y2(vol, r, b) -1 ) * s) / (y2(vol, r, b) * k)), y2(vol, r, b)));
		// else if it is a put option, return the price given by this formula

	}
}



void AmericanOption::rfr(double R)
{
// Modify the risk free rate to the value passed

	if (b_state == 0)
	{
		r = R;
		b = r;
		// if b = r, change r and b

	}
	else if (b_state == 1)
	{
		r = R;
		b = r - q;
		// if b = r-q, change r and b

	}
}

void AmericanOption::dividend(double Q)
{
// Modify the dividend rate to that passed by the user

	if (b_state == 0)
	{
		q = Q;
		// if b= r, just change q

	}
	else if (b_state == 1)
	{
		q = Q;
		b = r - q;
		// if b = r-q, change both q and b

	}
}

void AmericanOption::toggleB()
{
// Change the value of b_state and make the appropriate changes to b (cost of carry)

	if (b_state == 0)
	{
		b = r - q;
		b_state = 1;
		// if b_state is 0 (b=r), change b_state to 1 and change b to b = r-q

	}
	else if (b_state == 1)
	{
		b = r;
		b_state = 0;
		// if b_state is 1 (b=r-q), change b_state to 0 and change b to b = r

	}
}

void AmericanOption::State(bool one)
{
//  Change the value of b_state to the state passed by parameter and make the appropriate changes to b (cost of carry)

	if (one == true)
	{
		b = r - q;
		b_state = 1;
		// if true is passed, change b_state to 1 and set b to r-q

	}
	else
	{
		b = r;
		b_state = 0;
		// if false is passed, change b_state to 0 and set b to r

	}
}
