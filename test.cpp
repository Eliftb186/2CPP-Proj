#include <iostream>
using namespace std;

int main() {
  cout << "\033[0;32;44m text \033[0m\n" << endl;
  return 0;
}

//          foreground background
// black        30         40
// red          31         41
// green        32         42
// yellow       33         43
// blue         34         44
// magenta      35         45
// cyan         36         46
// white        37         47

// reset             0  (everything back to normal)
// bold/bright       1  (often a brighter shade of the same colour)
// underline         4
// inverse           7  (swap foreground and background colours)
// bold/bright off  21
// underline off    24
// inverse off      27
