#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {

    queue<Coord> cQueue;

    //push starting coordinate and update maze
    cQueue.push(Coord(sr,sc));
    maze[sr][sc] = '#';

    while (!cQueue.empty()) {

        //look at front item of queue
        Coord current = cQueue.front();
        cQueue.pop();

        int row = current.r();
        int col = current.c();

        //if current coordinate is equal to ending coordinate, you've won
        if (row == er && col == ec) {
            return true;
        }

        //check each place you can move from the current cell
        if (maze[row + 1][col] == '.') {
            cQueue.push(Coord(row + 1, col));
            maze[row + 1][col] = '#';

        }
        if (maze[row][col + 1] == '.') {
            cQueue.push(Coord(row, col + 1));
            maze[row][col + 1] = '#';
        }
        if (maze[row - 1][col] == '.') {
            cQueue.push(Coord(row - 1, col));
            maze[row - 1][col] = '#';

        }
        if (maze[row][col - 1] == '.') {
            cQueue.push(Coord(row, col - 1));
            maze[row][col - 1] = '#';
        }

    }
    return false;
}

int main()
{

    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
