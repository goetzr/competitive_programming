#include <iostream>

using namespace std;

#define ASSERT(condition)                           \
if (!(condition)) {                                 \
  cerr << "ASSERT FAILED: " << #condition << endl;  \
}

int num_digits(int n) {
  // Ignore the special case where n = 0.
  int nd = 0;
  while (n > 0) {
    ++nd;
    n /= 10;
  }
  return nd;
}

int pow10(int n) {
  int result = 1;
  for (int i = 0; i < n; ++i) {
    result *= 10;
  }
  return result;
}

int right_digits(int n, int nd) {
  // TODO: Implement this
}

int right_digit(int n) {
  return n - (n / 10 * 10);
}

int reversed_digits(int n) {
  int reversed = 0;
  while (n > 0) {
    reversed *= 10;
    reversed += right_digit(n);
    n /= 10;
  }
}

class NotPalindromeException {};

/**
 * A number's core is used to determine whether the number is a palindrome, or, if the number is a palindrome,
 * to increment/decrement it to the next higher/lower palindrome.
 * 
 * A number's core is formed by taking the appropriate number of digits from the front of the number.
 * The number of digits taken is determined by the mirror axis of the number.
 * For numbers with an even number of digits, this is the front half of the digits.
 * For numbers with an odd number of digits, this is the front half of the digits and the middle digit.
 * 
 * A number's mirror is the front digits of a number that must be mirrored on the back side for the
 * number to be a palindrome.
 * A number's mirror is simply its core when the number has an even number of digits.
 * If the number has an odd number of digits, its middle digit must be removed from the right side of its core
 * to form its mirror. 
 *
 * Examples:
 * n = 11,      core = 1,     mirror = 1
 * n = 101,     core = 10,    mirror = 1
 * n = 1001,    core = 10,    mirror = 10
 * n = 10001,   core = 100,   mirror = 10
 * n = 100001,  core = 100,   mirror = 100
 * n = 1000001, core = 1000,  mirror = 100
 */
class Palindrome {
 public:
  Palindrome(int n) {
    nd_ = num_digits(n);
    // Remove the right half of the number's digits to form the core.
    // NOTE: This also works for numbers with an odd number of digits,
    //       because it does not remove the middle digit, as desired.
    core_ = n / pow10(nd_ / 2);
    mirror_ = get_mirror();

    if (right_digits(n, num_digits(mirror_)) != reversed_digits(mirror_)) {
      throw NotPalindromeException();
    }
  }

  int value() const {    
    return core_ * pow10(nd_ / 2) + reversed_digits(mirror_);
  }

  void increment() {
    auto nd_last_core = num_digits(core_);
    ++core_;
    if (num_digits(core_) != nd_last_core) {
      ++nd_;
      core_ /= 10;
    }
    mirror_ = get_mirror();
  }

 private:
  int get_mirror() {
    // When forming the mirror, remove the number's middle digit from the right side of the core
    // for numbers with an odd number of digits.
    return (nd_ % 2 == 0) ? core_ : core_ / 10;
  }

  int nd_;
  int core_;
  int mirror_; 
};

class Problem4 {
 public:
  int lpp(int n1, int n2) {
    return 0;
  }

  void run_tests() {
    ASSERT(num_digits(101) == 3)
    ASSERT(num_digits(10001) == 5)
    ASSERT(num_digits(100001) == 6)

    ASSERT(get_core(101) == 10)
    ASSERT(get_core(10001) == 100)
    ASSERT(get_core(100001) == 100)
    ASSERT(get_core(1000001) == 1000)
    
    cout << "TESTS DONE" << endl;
  }

 private:


  /**
   * Gets the core of the specified number.
   * 
   * A number's core is used to determine whether the number is a palindrome, or, if the number is a palindrome,
   * to increment/decrement it to the next higher/lower palindrome.
   * 
   * A number's core is formed by taking the appropriate number of digits from the front of the number.
   * The number of digits taken is determined by the mirror axis of the number.
   * For numbers with an even number of digits, this is the front half of the digits.
   * For numbers with an odd number of digits, this is the front half of the digits and the middle digit.
   *
   * The numbe specified is assumed to have at least 2 digits.
   * 
   * Examples:
   * n = 11,      core = 1,     mirror = 1
   * n = 101,     core = 10,    mirror = 1
   * n = 1001,    core = 10,    mirror = 10
   * n = 10001,   core = 100,   mirror = 10
   * n = 100001,  core = 100,   mirror = 100
   * n = 1000001, core = 1000,  mirror = 100
   * 
   * @param n   The number whose core should be found.
   * 
   * @return The specified number's core.
   */
  int get_core(int n) {
    // Remove the right half of the number's digits.
    // NOTE: This also works for numbers with an odd number of digits,
    //       because it does not remove the middle digit, as desired.
    return n / pow10(num_digits(n) / 2);
  }

  bool is_palindrome(int n) {
    auto core = get_core(n);
  }

  int find_starting_palindrome(int num_digits) {
    // Find the largest number with the specified number of digits.
    int n = 1;
    for (int i = 0; i < num_digits; ++i) {
      n *= 10;
    }
    --n;

    // Square this number to find the largest product.
    int largest_product = n * n;

  }
};

int main() {
  Problem4 p4;

  p4.run_tests();

  return 0;
}