Description.

Implementation in the C of the famous cellular automaton Game Of Life
(https://en.wikipedia.org/wiki/Conway's_Game_of_Life).
To run the game, download the files from the repository and enter the make command.
The action takes place on the surface of the torus, a plane of dimensions is chosen for observation.
Field for life 80x25. You can change it by setting the size of the MAX_Y MAX_X.
For random filling, use the 'r' key (./life r).
To use ready-made tables, set one of the files located in the directory (for example./life < 1.txt).
Importantly, the program uses the ncurses library. If you don't have it installed, you can do it 
(if you have Debian and Ubuntu $sudo apt-get install ncurses-dev).
To control the speed, use '+' and '-', to exit enter 'q'.

Observing the creation and destruction, we return again and again to the laws of Nature.
