/**********************************************************************
 *  Airport-readme template                                                   
 *  Airport Simulation (C++11 Concurrency)                       
 **********************************************************************/

Your name: Ronney Sanchez

Operating system you're using (Linux, OS X, or Windows):

I am using Windows.

If Windows, which solution?:

I am using VirtualBox and doing my program in a text editor.

Text editor or IDE you're using: VI Text Editor

Hours to complete assignment: 

18 hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
The assignment is an airport simulation which requests up to a total of
six planes to land and uses a mutual lock to handle each landing requests.
The program specifies a certain plane to land at a certain path or specifies
more than one plane to land at non-conflicting paths. The program uses mutual
locks and condition variables to handle the landing request.

 /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
One key algorithm that was central to this assignment is concurrency. This
assignment is related to the Operating System course. This assignment
has a lot of Operating System knowledge involved. This assignment also has
deadlocks and starvation problem with the airplane landing.

Another key algorithm that is central is mutual exclusion. If we want more
than one plane to land then we need to tell the program to find non-conflicting
paths for these two planes to land other-wise, one plane must wait while the
other plane finish landing to clear the runway for the next plane to land.
Then when more request comes, those plane request must be put to sleep
until the other requests has been resolved.
/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
I added more mutual lock and condition variables to the program to handle
the landing requests to avoid crashes. I also modified the landing request
and release functions to handle any conflicting landing paths. Each mutex
variables are for each runway paths. I used switch statements to handle the
locks and unlocks of each runways.


 /**********************************************************************
 *  Briefly explain what you learned in the assignment.
 **********************************************************************/
I learned a little more about Operating System with this assignment because
this assignment uses a lot of concurrency knowledge which involves mutual
exclusion, locks, unlocks, condition variables, deadlocks, and starvation.
I learned that we can control variables using the mutual lock variables.


/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I recieved help from the instructor (Dr. Tom Wilkes) and Patrick Fuller
with this assignment. Even though I received help, I was still struggling
to get this assignment working in which I even worked on this over the
Thanskgiving break. Finally I achieved where the program was going wrong and
it is fixed. My program finally works for 15+ minutes as required with
no more than six landing requests and more than one plane landing at
non-conflicting paths.

/**********************************************************************
 *  Describe any serious problems you encountered.  
 *  If you didn't complete any part of any assignment, 
 *  the things that you didn't do, or didn't get working.                  
 **********************************************************************/
I was encountering crashes in my airport simulation. I kept debugging and got 
the program to run for a couple of seconds more before another crash happens. I was playing around with the mutual exclusion variables to note which spots
in the program it needs to be in. I noticed that when the number of landing
requests reach more than 1 the more likely the program will crash. I used
switch statements to lock and unlock the mutex variables for each paths being
occupied and paths that intersect the occupied paths. Finally my program is
stable enough to control the landing request safely for each airplanes.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
This program is probably not difficult but we need to know the right method
of controlling the lock and unlock variables with the condition variables.
