#include <iostream>
using namespace std;

main() {
  string kata[3] = {"efbey", "cdf", "okoj"};

  for(int i=0; i<3; i++) {
    cout << kata[i] << endl;
  }

  for(int i=0; i<3-1; i++) {
    for(int j=i+1; j<3; j++) {
      if(kata[i] > kata[j]) {
        string tampung;

        tampung = kata[i];
        kata[i] = kata[j];
        kata[j] = tampung;
      }
    }
  }

  cout << "========================" << endl;

  for(int i=0; i<3; i++) {
    cout << kata[i] << endl;
  }
}