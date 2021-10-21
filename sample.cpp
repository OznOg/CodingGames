
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>

using namespace std;

std::string doit(int size, std::vector<unsigned int> a) {

 
 uint64_t B = 0;

 uint64_t A = a[1];
 A <<= 32;
 A += a[0];

 std::vector<uint64_t> ai(size);
 std::vector<uint64_t> aj(size);

  for (int i = 0; i < size; i++) {
      ai[i] = (A >> i) & 1;
      aj[i] = (A >> (i + 32)) & 1;
  }

  for (int z = 0; z < 32; z++) {
      uint64_t r = 0;
      for (int i = 0; i < z + 1; i++) {
          for (int j = 0; j + i < z + 1 ; j++) {
              r ^= (ai[i] & aj[j]) << i + j;   // Magic centaurian operation
              r ^= (ai[31 - i] & aj[31 - j]) << (62 - (i + j));   // Magic centaurian operation
          }
      }
      cout << setw(32) << hex <<  r << endl;
      B |= r;
  }

#if 0

B0 = A0 & X0
B1 = A0 & X1 + A1 & X0
B2 = A0 & X2 + A1 & X1 + A2 & X0
B3 = A0 & X3 + A1 & X2 + A2 & X1 + A3 & X0
...

B61 = A29 & X31 + A30 & X30 + A31 & X29
B62 = A30 & X31 + A31 & X30
B63 = A31 & X31

si A1 & X1 == 1 =>    A1 == X1 == 1 => B1 = X2 + A2
              0 => si A1 == X1 == 0 => B1 = 0
                   si A1 == 0; X1 == 1 => B1 = A2
                   si A1 == 1; X1 == 0 => B1 = X2


B1 + B0 => (A0 & X0) + (A0 & X1) + (A1 & X0) => A0 & (X0 + X1) + A1 & X0


A & B ^ A & C == A & (B + C)
0   1   0   0    0
0   0   0   1    0     
0   1   0   1    0     
1   0   1   0    0     
1   1   1   0    1     
1   0   1   1    1 

  BC
A 00 01 11 01   
0 0  0  0  0
1 0  1  0  1



A1 A2 A3 00 00 00
B1 B2 B3 00 00 00
00 B1 B2 B3 00 00
00 00 B1 B2 B3 00
00 00 00 B1 B2 B3

#endif

//  876543210
//  XXXXXX000
//  0XXXXXX00
//  00XXXXXX0
//  000XXXXXX


  std::vector<unsigned int> b(2);
  b[0] = B & 0xFFFFFFFF;
  b[1] = (B>>32) & 0xFFFFFFFF;
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

if (!s)
    cout << "expect' " << "46508fb7 6677e201" << endl;
 /* 
    Good luck humans     
 */
  return 0;
}
