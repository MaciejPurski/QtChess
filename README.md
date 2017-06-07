# QtChess

## Description
This is my first attempt to chess programming done for myself. It is written in Qt/C++. The gui is very basic. At the moment it is 
possible to play with two players on a one machine. Playing against a computer is still under development. 
The game engine is implemented using Bitboards concept which is an advanced technique used in modern chess programms. Bitboards allow
moves generation using bit operations which is very effective in terms of AI algorithms. In my programm I have implemented move generation
for all pieces and checking checks and mat based on all generated moves. 

## Build and run
### Requierments 
* Qt5 libs 

### Building procedure
1. Create Makefile by executing `qmake`
2. execute `make`
3. Run app `./filtr`

## Using app
To start a game you have to choose "new game" in a menu bar, choose time and game side. Game engine should find out if the game 
should be finished. All the possible moves are implemented except for rochedes, en passent and promotion. It will be added in newer versions.






