-----Project Introduction-----
-The goal of this project is to take an existing genetic algorithm and improve its speed.  Details on that are found in the project overview.

-The original genetic algorithm was borrowed from https://www.geeksforgeeks.org/genetic-algorithms/ (thanks).

-The program is given an input as a string.  Random genes (characters) are put together to create a chromosome (string). This builds an individual.
-The individual then evolves through crossover and mutation until it arrives at the target input string.


-----Instructions to Run-----
-Download the program and open the .sln file using Visual Studio.

-At the top of the Visual Studio window, select "Release" and run using the Local Windows Debugger. 

-Input 0 if you wish to compare the threaded and unthreaded speeds.  Input 1 if you just wish to turn the threaded program.  Input your target string.


-----Program Overview-----
-The program is built of four different files

--genetic_math.h
---This declares the functions relating to any mathematic operation in the program.

--individual.h
---This declares the functions relating to individuals (calculating fitness, getting chromosome, mating).


--class_implementation.cpp
---This is the implemenation for the functions declared in the previous two files

--driver.cpp
---Calls the functions to execute program and get user input


-----Project Overview-----
-The speed of the program was improved through the threading of two functions

--Threading the create_pop function
---The way the non threaded loop works is as follows:
----Vector for the population is initiated
----For the size of the initial population (1,000,000), an iterative loop creates an individual and adds that to the population
---The threaded loop simply creates two individuals at a time and adds them to the population

--Threading the next_Generation function
---The next_Generation function splits up the population creation
----In the one thread, the first half of the new population is created.  In another thread, the second is created.
----Once finished, the two halves are added together to create the next generation.


-----Results-----
-The following results were tested using best case scenario
--No background programs running
--Program is not outputting the current generation, is only outputting the time to arrive at the target
---Printing out each generation and chromosome added a noticible amount to the results

Target string: High Performance
Unthreaded execution time: 7450 milliseconds
Threaded execution time: 5768 milliseconds
Improvement: 22.58%

Target string: Mid-Hi-Test
Unthreaded execution time: 2769 milliseconds
Threaded execution time: 1623 milliseconds
Improvement: 41.39%

Target string: Mid-Test
Unthreaded execution time: 1805 milliseconds
Threaded execution time: 1145 milliseconds
Improvement: 36.57%

Target string: Tester
Unthreaded execution time: 2315 milliseconds
Threaded execution time: 1476 milliseconds
Improvement: 36.24%

Target string: Test
Unthreaded execution time: 920 milliseconds
Threaded execution time: 646 milliseconds
Improvement: 29.78%

Average improvement: 33.31%

-Overall, incredibly happy with the results.  Had a ton of fun working on this.