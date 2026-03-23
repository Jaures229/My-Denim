#ifndef BOARD_HPP_
    #define BOARD_HPP_
    #include <iostream>
    #include "Cell.hpp"
    #include <cstdlib>
    #include <ctime>
    class Board {
        private:
            int width;
            int height;
            int mineCount;
            Cell** grid;

            void placeMines();
            void calculateNeighbors();
        public:
            Board(int w, int h, int m);
            ~Board();

            void initializeGrid();
            void revealCell(int x, int y);
            void toggleFlag(int x, int y);
            void initgame();

            bool isWithinBounds(int x, int y) const;
            void draw() const; 
            bool checkWin() const;
            bool checkLoss() const;
        };
#endif /* !BOARD_HPP_ */
