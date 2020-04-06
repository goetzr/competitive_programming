#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

template <typename T>
bool contains(vector<T> vec, T val) {
  return find(begin(vec), end(vec), val) != end(vec);
}

template <typename T>
void print(vector<T> vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i];
    if (i < vec.size() - 1) {
      cout << ", ";
    }
  }
}

/*
vector<uint64_t> factors(uint64_t n) {
  vector<uint64_t> result;

  result.push_back(n);
  for (auto i = n / 2; i >= 2; --i) {
    if (n % i == 0) {
      result.push_back(i);
    }  
  }
  result.push_back(1);

  return result;
}
*/

vector<uint64_t> primes(uint64_t n) {
  std::vector<uint64_t> result;
  if (n < 2) {
    return result;
  }
  result.push_back(2);

  for (uint64_t i = 3; i <= n; ++i) {
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
  uint64_t lpf(uint64_t n) {
    uint64_t result = 0;

    auto pm = primes((uint64_t)sqrt(n));
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