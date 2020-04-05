#include <iostream>

using namespace std;

class GoblinRabblemaster {
 public:
  long totalDamage(int T) {
    int gr = 0;
    int g = 0;
    long d = 0;
    for (int t = 0; t < T; ++t) {
      ++gr;
      g += gr;
      int oga = (gr - 2) + g;
      d += (gr - 1) * (2 + oga);
      d += g;
    }
    return d;
  }
};

int main(int argc, char** argv) {
  GoblinRabblemaster gr;

  cout << "1: " << gr.totalDamage(1) << endl;
  cout << "3: " << gr.totalDamage(3) << endl;
  cout << "6: " << gr.totalDamage(6) << endl;
  cout << "470: " << gr.totalDamage(470) << endl;

  return 0;
}