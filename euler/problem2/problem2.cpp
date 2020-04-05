#include <iostream>
#include <cstdint>

using namespace std;

int next_fib(uint32_t f1, uint32_t f2) {
  return f1 + f2;
}

class Problem2 {
 public:
  uint64_t sum(uint32_t limit) {
    uint64_t result = 2;
    uint32_t f1 = 1;
    uint32_t f2 = 2;
    while (f2 < limit) {
      uint32_t next = next_fib(f1, f2);
      f1 = f2;
      f2 = next;
      if (next % 2 == 0) {
        result += next;
      }
    }
    return result;
  }
};

int main() {
  Problem2 p2;

  cout << "10: " << p2.sum(10) << endl;
  cout << "4 million: " << p2.sum(4 * 1000 * 1000) << endl;

  return 0;
}