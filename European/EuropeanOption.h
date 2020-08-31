// Exercise 9.A
// File: EuropeanOption.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish methods and
// attributes for an option class

#ifndef EUROPEANOPTIONS_HPP
#define EUROPEANOPTIONS_HPP

#include <boost/math/distributions/exponential.hpp>
#include <boost/math/distributions/poisson.hpp>
#include <boost/math/distributions.hpp> 
#include <vector>
#include <iostream>
using namespace std;

class EuropeanOption
{
private:
	double b;				// cost of carry
	double r;				// risk free rate
	double q;				// dividend rate
	double t;				// time in year
	double vol;				// volatility
	double k;				// strike price
	bool call;				// call or put
	int b_state;			// if 0 b=r		if 1 b= r - q
	double s;				// spot price

public:
	EuropeanOption() : k(10.0),s(10), t(1), vol(0.1), r(0.0), q(0.0), b(0.0), b_state(0), call(true) {};
	// Default contructor

	EuropeanOption(double K, double S, double T, double Vol, double R, bool Call) :k(K), s(S), t(T), vol(Vol), r(R), q(0.0), b(R), b_state(0), call(Call) {};
	// Constructor with parameters without q

	EuropeanOption(double K, double S, double T, double Vol, double R, double Q, bool Call) :k(K), s(S), t(T), vol(Vol), r(R), q(Q), b(R - Q), b_state(1), call(Call) {};
	// Constructor with parameters with q

	EuropeanOption(const EuropeanOption& other) : k(other.k), s(other.s), t(other.t), vol(other.vol), r(other.r), q(other.q), b(other.b), b_state(other.b_state), call(other.call) {};
	// Copy constructor

	virtual ~EuropeanOption() {};
	// Destructor

	double Price() const;							// returns price
	double Gamma() const;							// returns gamma
	double Delta() const;							// returns delta
	double B() const { return b; }					// returns cost of carry

	bool ParityPrice(double price) const;			// returns if pull call parity is satisfied for given price for option of the opposite type
	double ParityPrice() const;						// returns the price for option of the opposite type that would satisfy put call parity
	
	void spot(double S) { s = S; }					// modifies spot price
	void maturity(double T) { t = T; }				// modifies time to maturity
	void volatility(double Vol) { vol = Vol; }		// modifies volatility
	void strike(double K) { k = K; }				// modifies strike price
	void rfr(double R);								// modifies risk free rate
	void dividend(double Q);						// modifies dividend rate
	void type(bool Call) { call = Call; }			// modifies option type (call/put)
	void toggleB();									// changes the state of the cost of carry
	void State(bool one);							// change the state of cost of carry to one specified by user
	
	double DeltaApprox(double h) const;				// returns the delta value approximation
	double GammaApprox(double h) const;				// returns gamma value approximation
};

#endif
