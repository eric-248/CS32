#include <iostream>
#include <string>
#include <stack>

using namespace std;

class coord
{
public:
    coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

// return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathexists(char maze[][10], int sr, int sc, int er, int ec) {

    stack<coord> coordstack;

    //push starting coordinate and update maze
    coord start(sr, sc);
    coordstack.push(start);
    maze[sr][sc] = '#';

    while (!coordstack.empty()) {

        //pop top coordinate off stack
        coord current = coordstack.top();
        coordstack.pop();

        int row = current.r();
        int col = current.c();


        //if current coordinate is equal to ending coordinate, you've won
        if (row == er && col == ec) {
            return true;
        }

        //check each place you can move from the current cell
        //south
        if (maze[row+1][col] == '.') {
            coord move(row + 1, col);
            coordstack.push(move);
            maze[row + 1][col] = '#';

        }
        //east
        if(maze[row][col + 1] == '.') {
            coord move(row, col+1);
            coordstack.push(move);
            maze[row][col+1] = '#';
        }
        //north
        if(maze[row - 1][col] == '.') {
            coord move(row - 1, col);
            coordstack.push(move);
            maze[row - 1][col] = '#';

        }
        //west
        if(maze[row][col-1] == '.') {
            coord move(row, col - 1);
            coordstack.push(move);
            maze[row][col - 1] = '#';
        }
   
    }
    return false;
}

int main()
{

    char maze[10][10] = {
        { 'x','x','x','x','x','x','x','x','x','x' },
        { 'x','.','.','.','x','.','.','.','.','x' },
        { 'x','.','.','x','x','.','x','x','.','x' },
        { 'x','.','x','.','.','.','.','x','x','x' },
        { 'x','x','x','x','.','x','x','x','.','x' },
        { 'x','.','.','x','.','.','.','x','.','x' },
        { 'x','.','.','x','.','x','.','.','.','x' },
        { 'x','x','.','x','.','x','x','x','x','x' },
        { 'x','.','.','.','.','.','.','.','.','x' },
        { 'x','x','x','x','x','x','x','x','x','x' }
    };

    if (pathexists(maze, 3, 4, 8, 1))
        cout << "solvable!" << endl;
    else
        cout << "out of luck!" << endl;
}
