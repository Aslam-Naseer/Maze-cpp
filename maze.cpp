//N E S W 

#include <random> 
#include <iostream> 
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

class Node {
    public:

    bool walls[4] = {true, true, true, true}, visited;
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


    // node related methods

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


    // maze generation methods

    vector<pair<int,int>> find_neigbours(int x, int y){
      random_device rd;
      mt19937 gen(rd());

      vector<pair<int,int>> list;
      if(x != 0) list.push_back(pair<int,int>(x-1,y));
      if(y != 0) list.push_back(pair<int,int>(x,y-1));
      if(x != row-1) list.push_back(pair<int,int>(x+1,y));
      if(y != col-1) list.push_back(pair<int,int>(x,y+1));
      
      shuffle(list.begin(), list.end(), gen);
      return list;
    }

    //Main maze generation method
    bool generate_maze() {
    stack<pair<int,int>> stk;
    stk.push(pair<int,int>(0,0));
    int nodes_visited = 0;

    while(!stk.empty() && nodes_visited < row*col) {
      pair<int,int> curr = stk.top();
      int x = curr.first,y = curr.second;
      maze[x][y].visited = true;

      bool is_gen = false; 
      vector<pair<int,int>> list = find_neigbours(x,y);

      for(pair<int,int> next: list) {
        int x_new = next.first, y_new = next.second;
        if(!maze[x_new][y_new].visited) {
          if(x_new == x+1) maze[x+1][y].walls[0]=false;
          if(x_new == x-1) maze[x][y].walls[0]=false;
          if(y_new == y+1) maze[x][y+1].walls[1]=false;
          if(y_new == y-1) maze[x][y].walls[1]=false;

          is_gen = true;
          nodes_visited++;
          stk.push(pair<int,int>(x_new,y_new));
          break;
        }
      }

      if(!is_gen) 
        stk.pop();
    }
    

    return true;
    }

  public:
    Maze(int r=5, int c=7) {
      row = r;
      col = c;

      for(int i=0; i<row; i++){
        vector<Node> row;
        for(int j=0; j<col; j++) {
          row.push_back(Node());
        }
        maze.push_back(row);
      }

      generate_maze();
    }

    void show_maze(vector<pair<int,int>> v = vector<pair<int,int>>()) {

      for(int i=0; i<(3*row + 1); i++){
        cout<<endl;
        for(int j=0; j<(6*col + 1); j++) {
          if(is_perp(i,j))
            cout<<"+";
          else if ( is_horizontal(i,j))
            cout << "-"; 
          else if (is_vertical(i,j) )
            cout << "|";
          else if(find(v.begin(),v.end(), pair<int,int>(i/3, j/6)) != v.end())
            cout<<".";
          else
            cout<<" ";
        }
      }
      cout<<"\n";
    }

    void show_visited() {
      cout<<endl;
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
  Maze m(10,16);

  m.show_maze();
  cout<<"done";
}