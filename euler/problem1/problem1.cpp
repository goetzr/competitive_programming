#include <iostream>

using namespace std;

class Problem1 {
 public:
  long sum(int n) {
    long result = 0;
    for (int i = 1; i < n; ++i) {
      if (i % 3 == 0 || i % 5 == 0) {
        result += i;
      }
    }
    return result;
  }
};

int main() {
  Problem1 p1;

  cout << "10: " << p1.sum(10) << endl;
  cout << "1000: " << p1.sum(1000) << endl;

  return 0;
}