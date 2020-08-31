// Exercise 9.B
// File: OtherOptionFunctions.h
// By Bilal Mustafa
// Date: 12/4/2019
// Objective: Establish functions that
// operate with American Option class


#ifndef OTHER_OPTION_FUNCTIONS_H
#define OTHER_OPTION_FUNCTIONS_H

#include "AmericanOption.h"
#include "MeshArray.h"
#include "boost\variant.hpp"
#include <string>

using namespace std;

vector<double> OptionPrices(const AmericanOption& option, vector<double> paramArray, char parameter)
{
// Function that takes a vector for a particular parameter (specified by user) and generates prices by applying the parameter values
// to a reference option

	AmericanOption copy(option);
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


vector<double> OptionPrices(const vector<vector<boost::variant<double, bool>>>& optArray)
{
// Function that takes a matrix of parameters and return the price of their corresponding options

	AmericanOption temp(1, 1, 1, .3, .05, 1);
	// Create a temporary option

	vector<double> output(optArray.size());
	// create a vector for prices
	
	for (int j = 0; j < (optArray.size()); j++)
	{
		temp.strike(get<double>(optArray[j][0]));
		temp.spot(get<double>(optArray[j][1]));
		temp.volatility(get<double>(optArray[j][2]));
		temp.rfr(get<double>(optArray[j][3]));
		// for each set of parameter, change the values for the temp option

		if (optArray[j].size() == 5)
		{
			temp.State(false);
			temp.type(get<bool>(optArray[j][4]));
		}
		else
		{
			temp.State(true);
			temp.dividend(get<double>(optArray[j][4]));
			temp.type(get<bool>(optArray[j][5]));
		}
		// Depending on whether or not an input for dividends was provided, set the dividend and type of the option

		output[j] = temp.Price();
		// add the option price to the output vector

	}
	return output;
}

#endif