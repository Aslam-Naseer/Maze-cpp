//N E S W 

#include<iostream>
#include<stack>
#include<vector>

using namespace std;

class Node {
    public:

    bool walls[4] = {false, false, true, true}, visited;
    Node() {
      visited = false;
    }

    void visit() {
      visited = true;
    }

    bool createOpening (int dir) {
      if(dir<4) walls[dir] = true;
      return walls[dir];
    }
};

class Maze{
  private:
    int row, col;
    vector<vector<Node>> maze;

    bool is_perp(int i,int j) {
      return i%3==0 && j%6==0;
    }

    bool is_horizontal(int i,int j) {
      if(i%3 != 0)
        return false;

      if(i==0 || i==3*row)
        return true;

      int x = i/3;
      int y = j/6;

      return maze[x][y].walls[0];
    }

    bool is_vertical(int i, int j) {
      if(j%6 != 0)
        return false;

      if(j==0 || j==6*col)
        return true;

      int x = i/3;
      int y = j/6;


      return maze[x][y].walls[1];
    }

  public:
    Maze(int r=25, int c=40) {
      row = r;
      col = c;

      for(int i=0; i<row; i++){
        vector<Node> row;
        for(int j=0; j<col; j++) {
          row.push_back(Node());
        }
        maze.push_back(row);
      }
    }

    void show_maze() {
      cout<<row<<col<<endl;
      for(int i=0; i<(3*row + 1); i++){
        cout<<endl;
        for(int j=0; j<(6*col + 1); j++) {
          if(is_perp(i,j))
            cout<<"+";
          else if ( is_horizontal(i,j))
            cout << "-"; 
          else if (is_vertical(i,j) )
            cout << "|";
          else 
            cout<<" ";
        }
      }
      cout<<"\n";
    }

    void show_visited() {
      for(int i=0;i<row;i++) {
        for(int j=0; j<col; j++) {
          cout<<maze[i][j].visited<<" ";
        }
        cout<<endl;
      }
    }
};

int main()
{
  int row, col;
  cout << "Row: ";
  cin >> row;
  cout << "Column: ";
  cin >> col;

  Maze m(row, col);
  m.show_maze();
  cout<<"done";
}