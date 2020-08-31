// Exercise 9.B
// File: AmericanOption.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish methods and
// attributes for an option class

#ifndef AMERICANOPTIONS_H
#define AMERICANOPTIONS_H

#include <vector>
#include <iostream>
using namespace std;

class AmericanOption
{
private:
	double b;							// cost of carry
	double r;							// risk free rate
	double q;							// dividend rate
	double vol;							// volatility
	double k;							// strike price
	bool call;							// call or put
	int b_state;						// if 0 b=r		if 1 b= r - q
	double s;							// spot price

public:
	AmericanOption() : k(10.0), s(10), vol(0.1), r(0.0), q(0.0), b(0.0), b_state(0), call(true) {};
	// Default contructor

	AmericanOption(double K, double S, double Vol, double R, bool Call) :k(K), s(S), vol(Vol), r(R), q(0.0), b(R), b_state(0), call(Call) {};
	// Constructor with parameters without q

	AmericanOption(double K, double S, double Vol, double R, double Q, bool Call) :k(K), s(S), vol(Vol), r(R), q(Q), b(R - Q), b_state(1), call(Call) {};
	// Constructor with parameters with q

	AmericanOption(const AmericanOption& other) : k(other.k), s(other.s), vol(other.vol), r(other.r), q(other.q), b(other.b), b_state(other.b_state), call(other.call) {};
	// Copy constructor

	virtual ~AmericanOption() {};
	// Destructor

	double Price() const;							// returns price
	double B() const { return b; }					// returns cost of carry					

	void spot(double S) { s = S; }					// modifies spot price
	void volatility(double Vol) { vol = Vol; }		// modifies volatility
	void strike(double K) { k = K; }				// modifies strike price
	void rfr(double R);								// modifies risk free rate
	void dividend(double Q);						// modifies dividend rate
	void type(bool Call) { call = Call; }			// modifies option type (call/put)
	void toggleB();									// changes the state of the cost of carry
	void State(bool one);							// change the state of cost of carry to one specified by user
};

#endif
