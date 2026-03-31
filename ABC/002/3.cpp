#include<bits/stdc++.h>
using namespace std;

int main(){
  double x[3], y[3];
  for(int i = 0; i < 3; i++) cin >> x[i] >> y[i];
  
  double S = fabs((x[0] - x[2]) * (y[1] - y[2]) - (x[1] - x[2]) * (y[0] - y[2])) / 2.0;
  
  cout << fixed << setprecision(10) << S << endl; // 精度を10桁に設定
  
  return 0;
}