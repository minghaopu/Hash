#include <iostream>
#include <ctime>

using namespace std;

double array[10000][10000];

int main(){
  int val = 0;
  clock_t timeBegin, timeEnd;
  double totalTime = 0.0;

  timeBegin = clock();
  // code between timeBegin and timeEnd is the code you are "timing"
  // perform some slow task for an example
  for(int i = 0; i<10000;i++)
    for(int j = 0; j<10000;j++)
     array[i][j] = i+5*1000/1.1 ;

  timeEnd =clock();
  //cout<<timeEnd<<endl;
  totalTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;

  cout << "Total (approx) runtime is " << totalTime << endl; 

  return 0;

}
