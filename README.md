
BGU Course Systems Programming, Assignment 1
Created by Tom and Nave
Grade: 100

Written in C++

The assignment: 
Create a console based application to manage a Studio.
This assignment tested our skills in C++, memory management (One of the requirements was not to use smart pointers), OOP, Rule of Five design pattern.

Our implementation:
We used vectors to store relevant information (I.E trainers, customers, workouts etc),
which we filled with information given to us by parsing a .txt file.
Later we filtered key words (commands) via standard input (cin) and processed them as 'actions' that the Studio is capable of doing,
based on requirements given in the assignment papers.

Libs:
* Standard library: IOStream, vector, algorithm