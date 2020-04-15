#include <iostream>

using namespace std;

class Problem5 {
 public:
  /**
   * Smallest Possible Number Evenly Divisible By (SPNEDB) by the numbers from 1 through the specified upper limit.
   * 
   * @param range_upper The upper limit.
   * 
   * @return The result.
   */
  int spnedb(int range_upper) {
    int result = 1;

    // i holds the number in the range 1 through the specified upper limit.
    for (int i = 2; i <= range_upper; ++i) {
      // If the result is already evenly divisble by the current number, move on to the next number.
      if (result % i == 0) {
        continue;
      }

      // If the result is not evenly divisible by the current number,
      // try multiplying the result by each of the existing factors (< i),
      // one at a time, starting with the smallest factor and working up,
      // until the product is evenly divisible by the current number.
      // The worst case is the result must be multiplied by the current number.
      int j = 2;
      while (j <= i && (result * j) % i != 0) {
        ++j;
      }
      result *= j;
    }
    return result;
  }
};

int main() {
  Problem5 p5;

  cout << "Smallest possible number evenly divisible by 1 through 10: " << p5.spnedb(10) << endl;
  cout << "Smallest possible number evenly divisible by 1 through 20: " << p5.spnedb(20) << endl;

  return 0;
}