#include <iostream>
using namespace std;

class LuckyElevator {
 public:
  int actualFloor(int buttonPressed) {
    int count = 0;
    for (int i = 1; i <= buttonPressed; ++i) {
      auto contains4 = false;
      int j = i;
      while (j != 0) {
        if (j % 10 == 4) {
          contains4 = true;
          break;
        }
        j /= 10;
      }
      if (!contains4) {
        ++count;
      } 
    }
    return count;
  }    
};

int main(int argc, char** argv) {
  LuckyElevator le;
  cout << "3: " << le.actualFloor(3) << endl;  
  cout << "5: " << le.actualFloor(5) << endl;  
  cout << "18: " << le.actualFloor(18) << endl;  
  cout << "50: " << le.actualFloor(50) << endl;  
  cout << "100000: " << le.actualFloor(100000) << endl;  
}
