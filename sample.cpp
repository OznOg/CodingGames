
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
  int size;

  cin >> size;

  std::vector<unsigned int> a(size / 16); // <- input tab to encrypt
  std::vector<unsigned int> b(size / 16); // <- output tab
 
  for (auto &e : a) {   // Read size / 16 integers to a
    cin >> hex >> e;
  }

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
      std::div_t dij = std::div(i + j, 32);
      std::div_t di = std::div(i, 32);
      std::div_t dj = std::div(j, 32);
      
      b[dij.quot] ^= ( (a[di.quot] >> (di.rem)) & (a[dj.quot + size / 32] >> (dj.rem)) & 1 ) << dij.rem;   // Magic centaurian operation
  }
 
  for(int i = 0; i < size / 16; i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << setfill('0') << setw(8) << hex << b[i];       // print result
  }
  cout << endl;

 /* 
    Good luck humans     
 */
  return 0;
}
