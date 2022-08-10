/*
 * Name: Ronney Sanchez
 * Date: November 27, 2018
 * Course: COMP2040 Computing 4
 * Assignment: Airport Simulation
*/

#include <iostream>
#include <thread>
#include <condition_variable>

#include "AirportServer.h"

//Comment out Lines 16, 32, 64, 80

/**
*  Called by an Airplane when it wishes to land on a runway
*/
void AirportServer::reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Acquire runway(s)
	{  // Begin critical region
		//unique_lock<mutex> runwaysLock(runwaysMutex);

		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is acquiring any needed runway(s) for landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}
		unique_lock<mutex> condition_lock(conditionLock);
		/**
		 *  ***** Add your synchronization here! *****
		 */
		
		AirportRunways::incNumLandingRequests();

		while(AirportRunways::getNumLandingRequests() > AirportRunways::MAX_LANDING_REQUESTS)
		{
			condition.wait(condition_lock);
		}

		switch(runway)
		{
		
			case AirportRunways::RunwayNumber::RUNWAY_4L:
				runway4L.lock();
				runway15L.lock();
				runway15R.lock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_4R:
				runway4R.lock();
				runway9.lock();
				runway15L.lock();
				runway15R.lock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_9:
				runway9.lock();
				runway4R.lock();
				runway15R.lock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_14:
				runway14.lock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_15L:
				runway15L.lock();
				runway4L.lock();
				runway4R.lock();
			break;

			default:
				runway15R.lock();
				runway4L.lock();
				runway4R.lock();
			break;
		}
		
		AirportRunways::checkAirportStatus(runway);

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Taxi for a random number of milliseconds
	std::uniform_int_distribution<int> taxiTimeDistribution(1, MAX_TAXI_TIME);
	int taxiTime = taxiTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is taxiing on Runway " << AirportRunways::runwayName(runway)
			 << " for " << taxiTime << " milliseconds\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(taxiTime));

} // end AirportServer::reserveRunway()


 /**
  *  Called by an Airplane when it is finished landing
  */
void AirportServer::releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Release the landing runway and any other needed runways
	{ // Begin critical region

		//unique_lock<mutex> runwaysLock(runwaysMutex);

		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is releasing any needed runway(s) after landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}

		/**
		*  ***** Add your synchronization here! *****
		*/

		AirportRunways::finishedWithRunway(runway);

                switch(runway)
		{
			case AirportRunways::RunwayNumber::RUNWAY_4L:
                        	runway4L.unlock();
				runway15L.unlock();
				runway15R.unlock();
                	break;

			case AirportRunways::RunwayNumber::RUNWAY_4R:
                        	runway4R.unlock();
				runway9.unlock();
				runway15L.unlock();
                        	runway15R.unlock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_9:
                        	runway9.unlock();
				runway4R.unlock();
				runway15R.unlock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_14:
                        	runway14.unlock();
			break;

			case AirportRunways::RunwayNumber::RUNWAY_15L:
                        	runway15L.unlock();
				runway4L.unlock();
				runway4R.unlock();
                	break;

			default:
                        	runway15R.unlock();
				runway4L.unlock();
                        	runway4R.unlock();
			break;
                }
		unique_lock<mutex> condition_lock(conditionLock);
		// Update the status of the airport to indicate that the landing is complete
		AirportRunways::decNumLandingRequests();
		//runwaysLock.unlock();

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Wait for a random number of milliseconds before requesting the next landing for this Airplane
	std::uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
	int waitTime = waitTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is waiting for " << waitTime << " milliseconds before landing again\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

} // end AirportServer::releaseRunway()
