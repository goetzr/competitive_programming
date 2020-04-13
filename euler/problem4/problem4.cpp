#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

/**
 * Computes the number of digits in the specified number
 * 
 * @param n The number whose number of digits should be found.
 * 
 * @return The number of digits in the specified number.
 */
int num_digits(int n) {
  // Ignore the special case where n = 0.
  int nd = 0;
  while (n > 0) {
    ++nd;
    n /= 10;
  }
  return nd;
}

/**
 * Calculates 10 to the specified power.
 * 
 * @param n The power to raise 10 to.
 * 
 * @return 10 ^ n.
 */
int pow10(int n) {
  int result = 1;
  for (int i = 0; i < n; ++i) {
    result *= 10;
  }
  return result;
}

/**
 * Returns the desired number of digits from the right side of the specified number.
 * 
 * @param n       The number whose right-side digits should be returned.
 * @param ndigits The number of right-side digits to return.
 * 
 * @return The ndigits digits from the specified number.
 */
int right_digits(int n, int ndigits) {
  auto scale = pow10(ndigits);
  return n - (n / scale * scale);
}

/**
 * Returns the right-most digit of the specified number.
 * 
 * @param n The number whose right-most digits should be returned.
 * 
 * @return The right-most digit of the specified number.
 */
int right_digit(int n) {
  return right_digits(n, 1);
}

/**
 * Returns the digits of the specified number reversed.
 * 
 * @param n The number whose digits should be returned in a reverse order.
 * 
 * @return The digits of the specified number in reverse order.
 */
int reversed_digits(int n) {
  int reversed = 0;
  while (n > 0) {
    reversed *= 10;
    reversed += right_digit(n);
    n /= 10;
  }
  return reversed;
}

/**
 * Represents a Palindromic number.
 * 
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
  /**
   * Represents the specified palindromic number. If the number is not a palindrome,
   * the nearest palindrome to the number is represented.
   * 
   * @param n The number to represent.
   */
  Palindrome(int n) {
    nd_ = num_digits(n);
    // Remove the right half of the number's digits to form the core.
    // NOTE: This also works for numbers with an odd number of digits,
    //       because it does not remove the middle digit, as desired.
    core_ = n / pow10(nd_ / 2);
    mirror_ = get_mirror();
  }

  /**
   * Returns the value of the palindrome.
   *
   * @return The value of the palindrome.
   */
  int value() const {
    return core_ * pow10(nd_ / 2) + reversed_digits(mirror_);
  }

  /**
   * Increments the palindrome to the next largest palindrome.
   */
  void increment() {
    auto nd_last_core = num_digits(core_);
    ++core_;
    if (num_digits(core_) != nd_last_core) {
      ++nd_;
      core_ /= 10;
    }
    mirror_ = get_mirror();
  }

  /**
   * Decrements the palindrome to the next smallest palindrome.
   */
  void decrement() {
    auto nd_last_core = num_digits(core_);
    --core_;
    if (num_digits(core_) != nd_last_core) {
      --nd_;
    }
    mirror_ = get_mirror();
  }

 private:
  /**
   * Gets the mirror from the core and the number of digits.
   */
  int get_mirror() {
    // When forming the mirror, remove the number's middle digit from the right side of the core
    // for numbers with an odd number of digits.
    return (nd_ % 2 == 0) ? core_ : core_ / 10;
  }

  /**
   * The number of digits in the palindrome.
   */
  int nd_;

  /**
   * The palindrome's core.
   */
  int core_;

  /**
   * The palindrome's mirror.
   */
  int mirror_; 
};

class Problem4 {
 public:
  /**
   * Computes the largest palindrome that's a product of two numbers having the specified number of digits.
   * 
   * @param ndigits   The number of digits in each number.
   * @param factors   [out] Returns the two factors whose product is equal to the palindrome returned.
   * 
   * @return The largest palindrome that's a product of two numbers having the specified number of digits.
   */
  int lpp(int ndigits, pair<int, int>& factors) {
    auto sp = find_starting_palindrome(ndigits);
    while (!has_factor_pair_with_ndigits(sp.value(), ndigits, factors)) {
      sp.decrement();
    }
    return sp.value();
  }

 private:
  /**
   * Finds the starting palindrome. This is the largest palindrome that's not greater than the largest
   * product formed by multiplying two numbers with the specified number of digits.
   * 
   * @param ndigits The number of digits in the two numbers that are being multiplied.
   * 
   * @return The starting palindrome.
   */
  Palindrome find_starting_palindrome(int ndigits) {
    // Find the largest number with the specified number of digits.
    auto n = pow10(ndigits) - 1;

    // Square this number to find the largest product.
    int largest_product = n * n;

    // Find the largest palindrome that is <= the largest product.
    Palindrome starting_palindrome(largest_product);
    if (starting_palindrome.value() > largest_product) {
      starting_palindrome.decrement();
    }
    
    return starting_palindrome;
  }

  /**
   * Returns whether specified palindrome has two factors with the specified number of digits.
   * 
   * @param n         The palindrome being tested.
   * @param ndigits   The number of digits in the two factors.
   * @param factors   [out] If found, returns the two factors used to form the palindrome.
   * 
   * @return Returns whether the specified palindrome has two factors with the specified number of digits.
   */
  bool has_factor_pair_with_ndigits(int n, int ndigits, pair<int, int>& factors) {
    // Start looking for factors from the smallest number with the specified number of digits.
    auto starting_factor = pow10(ndigits - 1); 
    // Only look for factors having the specified number of digits up to the square root of the number.
    for (auto i = starting_factor; num_digits(i) == ndigits && i < sqrt(n); ++i) {
      // If the current number is a factor, and its associated factor also has the specified number of digits,
      // return true.
      if (n % i == 0 && num_digits(n / i) == ndigits) {
        factors.first = i;
        factors.second = n / i;
        return true;
      }
    }
    return false;
  }
};

int main() {
  Problem4 p4;

  pair<int, int> factors;
  cout << "Largest palindrome made from product of two 2-digit numbers: " << p4.lpp(2, factors) << " = " << factors.first << " * " << factors.second << endl;
  cout << "Largest palindrome made from product of two 3-digit numbers: " << p4.lpp(3, factors) << " = " << factors.first << " * " << factors.second << endl;

  return 0;
}