/*
 * Name: Ronney Sanchez
 * Date: November 27, 2018
 * Course: COMP2040 Computing 4
 * Assignment: Airport Simulation
*/

/**
*  Airport driver program
*/

#include <iostream>
#include <thread>
#include <vector>

#include "AirportServer.h"
#include "AirportRunways.h"
#include "Airplane.h"

using namespace std;

int main(void)
{
	AirportServer as;

	vector<thread> apths; // Airplane threads

	// Create and launch the individual Airplane threads
	for (int i = 1; i <= AirportRunways::NUM_AIRPLANES; i++)
	{
		Airplane* ap = new Airplane(i, &as);

		apths.push_back(thread([=]{ap->land();}));
	}

	// Wait for all Airplane threads to terminate (shouldn't happen!)
	for (auto& th : apths)
	{
		th.join();
	}

	return 0;

} // end main
