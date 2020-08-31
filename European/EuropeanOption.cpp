// Exercise 9.A
// File: EuropeanOption.cpp
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish methods and
// attributes for an option class

#include <boost/math/distributions/exponential.hpp>
#include <boost/math/distributions/poisson.hpp>
#include <boost/math/distributions.hpp> 
#include <vector>
#include <iostream>
#include "EuropeanOption.h"
#include "NormalDist.h"
#define M_PI acos(-1.0)

using namespace std;

double EuropeanOption::Price() const
{
// Return the price of the option as given by the Black Scholes formula

	if (call)
	{
		return -1 * k * exp(-1 * r * t) * cum_norm(d2(vol, s, k, t, b)) + s * exp((b - r) * t) * cum_norm(d1(vol, s, k, t, b));
		// if option is a call option, return the price given by this formula

	}
	else
	{
		return k * exp(-1 * r * t) * cum_norm(-1 * d2(vol, s, k, t, b)) - s * exp((b - r) * t) * cum_norm(-1 * d1(vol, s, k, t, b));
		// else if it is a put option, return the price given by this formula
	
	}
}


double EuropeanOption::ParityPrice() const
{
// Return the price of the corresponding put or call option as given by the Put-Call partiy

	if (call)
	{
		return this->Price() - s + (k * exp(-1 * r * t));
		// If option is a call option, return the price of the corresponding put option

	}
	else
	{
		return this->Price() + s - (k * exp(-1 * r * t));
		// If option is a put option, return the price of the corresponding call option

	}
}


bool EuropeanOption::ParityPrice(double price) const
{
// Take the value of the corresponding put or call option and return whether it satisfies put-call parity (within a margin of error)

	if (call)
	{
		return abs((this->Price() - s + (k * exp(-1 * r * t))) - price) < pow(10,-6);
		// if option is a call option, check if the price given equals that of the corresponding put option
	
	}
	else
	{
		return ((this->Price() + s - (k * exp(-1 * r * t))) - price) < pow(10,-6);
		// if option is a put option, check if the price given equals that of the corresponding call option

	}
}

void EuropeanOption::rfr(double R)
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

void EuropeanOption::dividend(double Q)
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

void EuropeanOption::toggleB()
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

void EuropeanOption::State(bool one)
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

double EuropeanOption::Gamma() const
{
// Returns the gamma of the option

	return (1 / pow(2 * M_PI, 0.5)) * exp(-1 * pow(d1(vol, s, k, t, b), 2) / 2) * (1 / (s * vol * pow(t, 0.5))) * exp((b - r) * t);
}


double EuropeanOption::Delta() const
{
// Returns the delta of the option

	if(call)
		return cum_norm(d1(vol, s, k, t, b)) * exp((b-r) * t);
		// if option is a call option, calculate delta using this formula and return

	else
		return  (cum_norm(d1(vol, s, k, t, b)) - 1) * exp((b-r) * t);
		// if option is a put option, calculate delta using this formula and return

}

double EuropeanOption::DeltaApprox(double h) const
{
// Returns the approximate delta

	EuropeanOption temp1(k, s+h, t, vol, r, q, call);
	EuropeanOption temp2(k, s-h, t, vol, r, q, call);
	// Creating temporary options to check price

	return (temp1.Price() - temp2.Price()) / (2 * h);
}

double EuropeanOption::GammaApprox(double h) const
{
// Returns the approximate gamma

	EuropeanOption temp1(k, s + h, t, vol, r, q, call);
	EuropeanOption temp2(k, s, t, vol, r, q, call);
	EuropeanOption temp3(k, s-h, t, vol, r, q, call);
	// Creating temporary options to check the price

	return (temp1.Price() -(2*temp2.Price()) +  temp3.Price()) / pow(h,2);
}