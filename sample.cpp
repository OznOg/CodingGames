
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

std::string doit(int size, std::vector<unsigned int> a) {

  std::vector<unsigned int> b(size / 16); // <- output tab
 
  for (int i = 0; i < size; i++) {
      std::div_t di = std::div(i, 32);
      auto bi = (a[di.quot] >> di.rem) & 1;

      for (int j = 0; j < size; j++) {
          std::div_t dj = std::div(j, 32);
          auto bj = (a[dj.quot + size / 32] >> dj.rem) & 1;

          std::div_t dij = std::div(i + j, 32);
          b[dij.quot] ^= ( bi & bj) << dij.rem;   // Magic centaurian operation
      }
  }

//  876543210
//  XXXXXX000
//  0XXXXXX00
//  00XXXXXX0
//  000XXXXXX


  std::stringstream out;
  for(int i = 0; i < size / 16; i++) {
    if (i > 0) {
      out << ' ';
    }
    out << setfill('0') << setw(8) << hex << b[i];       // print result
  }
  return out.str();
}

int main()
{
  //cin >> size;

  //std::vector<unsigned int> a(size / 16); // <- input tab to encrypt
  //for (auto &e : a) {   // Read size / 16 integers to a
  //  cin >> hex >> e;
  //}
  std::vector<unsigned int> a{0xb0c152f9, 0xebf2831f};

  
//32
//b0c152f9 ebf2831f
//46508fb7 6677e201

auto r =  doit(32, a);

auto s = r == "46508fb7 6677e201";

cout << (s ? "success" : "failure") << " " << r << endl;
 /* 
    Good luck humans     
 */
  return 0;
}
