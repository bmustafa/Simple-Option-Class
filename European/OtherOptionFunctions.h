// Exercise 9.A
// File: OtherOptionFunctions.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish functions to
// be used with an option class


#ifndef OTHER_OPTION_FUNCTIONS_HPP
#define OTHER_OPTION_FUNCTIONS_HPP

#include "EuropeanOption.h"
#include "MeshArray.h"
#include <string>
#include "boost\variant.hpp"

using namespace std;

vector<double> OptionPrices(const EuropeanOption& option, vector<double> paramArray, char parameter)
{
// Function that takes a vector for a particular parameter (specified by user) and generates prices by applying the parameter values
// to a reference option

	EuropeanOption copy(option);
	// Create a copy of the reference option to manipulate

	vector<double> output(paramArray.size());
	// Initialize a vector to store prices
	
	for (int i = 0; i < (paramArray.size()); i++)
	{
		switch (parameter)
		{
		case 's': copy.spot(paramArray[i]); break;

		case 'v': copy.volatility(paramArray[i]); break;
			
		case 'k': copy.strike(paramArray[i]); break;
		
		case 't': copy.maturity(paramArray[i]); break;
		
		case 'r': copy.rfr(paramArray[i]); break;
		
		case 'q': copy.dividend(paramArray[i]); break;
		
		default: copy.spot(paramArray[i]); break;
		}
		// cycle through the values for the parameter specified by the user and modify the copy of the option

		output[i] = copy.Price();
		// and record the price in the price vector

	}
	return output;
}

vector<double> OptionInfo(const vector<vector<boost::variant<double, bool>>>& optArray, char info = 'p')
{
// Function that takes a matrix of parameters and return the price, delta or gamma of their corresponding options

	EuropeanOption temp(1,1,1,.3, .05, 1);
	// Create a temporary option

	vector<double> output(optArray.size());
	// create a vector for prices/deltas or gammas

	for (int j = 0; j < (optArray.size()); j++)
	{ 
		temp.strike(get<double>(optArray[j][0]));
		temp.spot(get<double>(optArray[j][1]));
		temp.maturity(get<double>(optArray[j][2]));
		temp.volatility(get<double>(optArray[j][3]));
		temp.rfr(get<double>(optArray[j][4]));
		// for each set of parameter, change the values for the temp option

		if (optArray[j].size() == 6)
		{
			temp.State(false);
			temp.type(get<bool>(optArray[j][5]));
		}
		else
		{
			temp.State(true);
			temp.dividend(get<double>(optArray[j][5]));
			temp.type(get<bool>(optArray[j][6]));
		}
		// Depending on whether or not an input for dividends was provided, set the dividend and type of the option
		
		if(info == 'g')
			output[j] = temp.Gamma();
		else if(info == 'd')
			output[j] = temp.Delta();
		else
			output[j] = temp.Price();
		// add to the output vector, the price, delta or gamma of the option

	}
	return output;
}

vector<double> OptionDeltas(const EuropeanOption& option, vector<double> paramArray, char parameter)
{
// Function that takes a vector for a particular parameter (specified by user) and generates deltas by applying the parameter values
// to a reference option	
	
	EuropeanOption copy(option);
	// Create a copy of the reference option to manipulate

	vector<double> output(paramArray.size());
	// Initialize a vector to store deltas

	for (int i = 0; i < (paramArray.size()); i++)
	{
		switch (parameter)
		{
		case 's': copy.spot(paramArray[i]); break;

		case 'v': copy.volatility(paramArray[i]); break;

		case 'k': copy.strike(paramArray[i]); break;

		case 't': copy.maturity(paramArray[i]); break;

		case 'r': copy.rfr(paramArray[i]); break;

		case 'q': copy.dividend(paramArray[i]); break;

		default: copy.spot(paramArray[i]); break;
		}
		// cycle through the values for the parameter specified by the user and modify the copy of the option

		output[i] = copy.Delta();
		// and record the delta in the output vector

	}
	return output;
}

vector<double> OptionGammas(const EuropeanOption& option, vector<double> paramArray, char parameter)
{
// Function that takes a vector for a particular parameter (specified by user) and generates gammas by applying the parameter values
// to a reference option	

	EuropeanOption copy(option);
	// Create a copy of the reference option to manipulate
	
	vector<double> output(paramArray.size());
	// Initialize a vector to store gammas

	for (int i = 0; i < (paramArray.size()); i++)
	{
		switch (parameter)
		{
		case 's': copy.spot(paramArray[i]); break;

		case 'v': copy.volatility(paramArray[i]); break;

		case 'k': copy.strike(paramArray[i]); break;

		case 't': copy.maturity(paramArray[i]); break;

		case 'r': copy.rfr(paramArray[i]); break;

		case 'q': copy.dividend(paramArray[i]); break;

		default: copy.spot(paramArray[i]); break;
		}
		// cycle through the values for the parameter specified by the user and modify the copy of the option

		output[i] = copy.Gamma();
		// and record the gamma in the output vector

	}
	return output;
}



#endif