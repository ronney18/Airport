/*
 * Name: Ronney Sanchez
 * Date: November 27, 2018
 * Course: COMP2040 Computing 4
 * Assignment: Airport Simulation
*/

/**
*  AirportServer.h
*  This class defines the methods called by the Airplanes
*/

#ifndef AIRPORT_SERVER_H
#define AIRPORT_SERVER_H

#include <mutex>
#include <random>
#include <condition_variable>

#include "AirportRunways.h"



class AirportServer
{
public:

	/**
	*  Default constructor for AirportServer class
	*/
	AirportServer()
	{
		// ***** Initialize any Locks and/or Condition Variables here as necessary *****

	} // end AirportServer default constructor


	  /**
	  *  Called by an Airplane when it wishes to land on a runway
	  */
	void reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway);

	/**
	*  Called by an Airplane when it is finished landing
	*/
	void releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway);


private:

	// Constants and Random number generator for use in Thread sleep calls
	static const int MAX_TAXI_TIME = 10; // Maximum time the airplane will occupy the requested runway after landing, in milliseconds
	static const int MAX_WAIT_TIME = 100; // Maximum time between landings, in milliseconds

	/**
	*  Declarations of mutexes and condition variables
	*/
	 // Used to enforce mutual exclusion for acquiring & releasing runways

	/**
	 *  ***** Add declarations of your own Locks and Condition Variables here *****
	 */
	mutex conditionLock;
	mutex runway4L;
	mutex runway4R;
	mutex runway9;
	mutex runway14;
	mutex runway15L;
	mutex runway15R;
	condition_variable condition;

}; // end class AirportServer

#endif
