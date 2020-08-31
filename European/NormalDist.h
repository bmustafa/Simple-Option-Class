// Exercise 9.A
// File: NormalDist.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish functions needed
// for the probability calculation for 
// options.


#ifndef NORMALDIST_HPP
#define NORMALDIST_HPP

using namespace std;
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>


double cum_norm(double parameter)
{
// CDF function for normal distribution

	boost::math::normal_distribution<> norm(0, 1);
	return boost::math::cdf(norm, parameter);
}

double d1(double vol, double spot, double strike, double t, double b)
{
// Calculates parameter d1 in Black Scholes formula for b or b=r

	return (log(spot / strike) + (b + pow(vol, 2) / 2) * t) / (vol * pow(t, 0.5));
}

double d2(double vol, double spot, double strike, double t, double b)
{
// Calculates parameter d2 in Black Scholes formula for b or b=r

	return (log(spot / strike) + (b - pow(vol, 2) / 2) * t) / (vol * pow(t, 0.5));
}


double d1(double vol, double spot, double strike, double t, double r, double q)
{
// Calculates parameter d1 in Black Scholes formula for r and q
	return (log(spot / strike) + (r + - q +pow(vol, 2) / 2) * t) / (vol * pow(t, 0.5));
}



double d2(double vol, double spot, double strike, double t, double r, double q)
{
// Calculates parameter d2 in Black Scholes formula for r and q

	return (log(spot / strike) + (r - q - pow(vol, 2) / 2) * t) / (vol * pow(t, 0.5));
}

#endif