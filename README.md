*This project has been created as part of the 42 curriculum by @albegar2.*

## Description

This project consists of solving the known computing problem of the dining philosophers.
In doing so, we use relevant new tools learned during the process: threads and mutexes.

The most important part is to work with threads and mutexes in a way that philosophers can 
use resources (variables) quickly without being interrupted or corrupted by other philosophers
(other threads) trying to access the same information pieces. Failing to do that would cause deadlocks, which would be a reason to fail this project. Another important part of the project is time management through functions as gettimeofday() or usleep().

## Instructions

To compile the program, follow these steps:

1. Download the repository, enter the /philo folder within the terminal, type `make` and press ENTER.
2. Within the terminal, type `./philo`.
3. Add the arguments you wish to check, each separated by a space.
4. Press ENTER.

This program accepts a minimum of 4 arguments and a maximum of 5 arguments (plus the name of the program). Any other number of arguments will result in the message "Error: invalid arguments" being displayed.

The arguments, in order, represent:
1. Number of philosophers.
2. Time to die (in milliseconds).
3. Time to eat (in milliseconds).
4. Time to sleep (in milliseconds).
5. Number of times each philosopher must eat (OPTIONAL).

## Resources

Here are a few links to online resources that explain the dining philosophers problem, and the theory behing threads and mutexes.

- "Dining Philosophers Problem", https://www.geeksforgeeks.org/operating-systems/dining-philosophers-problem/. 
- "Multithreading in C", https://www.geeksforgeeks.org/c/multithreading-in-c/. 
- "Mutexes and Condition Variables", https://www.gnu.org/software/guile/manual/html_node/Mutexes-and-Condition-Variables.html.
- "¿Qué es un mutex en C? (pthread_mutex)", https://www.youtube.com/watch?v=oq29KUy29iQ&t=187s&pp=ugMICgJlcxABGAHKBQhtdXRleCA0Mg%3D%3D.

**AI use**: AI has been used in this project for help in understanding some of its core concepts,
as well as for helpind understand errors or deadlocks and finding ways to search for them. 
