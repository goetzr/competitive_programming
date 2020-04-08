#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Find the prime numbers up to and including the specified number.
 * The algorithm used is based on the Sieve of Eratosthenes.
 * Instead of generating a list of consecutive integers in which non-primes are marked,
 * which uses too much memory for large n, each number if checked against a list of
 * primes already found. If it's evenly divisible by any of the primes arelady found,
 * it's not a prime.
 * 
 * @param n   Find primes up to (and including) this number.
 * 
 * @return A list of the primes up to (and including) the specified number.
 **/ 
vector<uint64_t> primes(uint64_t n) {
  std::vector<uint64_t> result;
  if (n < 2) {
    return result;
  }
  // 2 is the only even number that's prime.
  result.push_back(2);

  // i += 2 ==> Skip over all other even numbers, which are never prime.
  for (uint64_t i = 3; i <= n; i += 2) {
    // Assume the current number is prime.
    // If it's evenly divisible by any of the primes already found, then it's not a prime.
    bool is_prime = true;
    for (auto prime : result) {
      if (i % prime == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      result.push_back(i);
    }
  }

  return result;
}

class Problem3 {
 public:
 /**
  * Find the largest prime factor (lpf) of the specified number.
  * 
  * @param n    The number whose largest prime factor should be found.
  * 
  * @return The largest prime factor of the specified number.
  **/
  uint64_t lpf(uint64_t n) {
    uint64_t result = 0;

    // Only need to generate primes up to sqrt(n), as factors of n can't be larger than sqrt(n).
    // This is dramatically faster when n is large.
    auto pm = primes((uint64_t)sqrt(n));

    // Sort the primes from largest to smallest, then test them in order.
    // The first factor of n found is its largest prime factor.
    sort(begin(pm), end(pm), [](auto a, auto b) { return a > b; });
    for (auto prime : pm) {
      if (n % prime == 0) {
        result = prime;
        break;
      }
    }

    return result;
  } 
};

int main() {
  Problem3 p3;

  cout << "21: " << p3.lpf(21) << endl;
  cout << "43: " << p3.lpf(43) << endl;
  cout << "91: " << p3.lpf(91) << endl;
  cout << "33: " << p3.lpf(33) << endl;
  cout << "13195: " << p3.lpf(13195) << endl;
  cout << "600851475143: " << p3.lpf(600851475143) << endl;

  return 0;
}