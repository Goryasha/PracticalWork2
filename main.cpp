#include <iostream>
#include "KuznyechikChipher.h"
#include "GaloisFIeldWork.h"


int main() {
    KuznyechikChipher c("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    std::cout<<"Plaintext: "<<"7f679d90bebc24305a468d42b9d4edcd"<<"\n";
    std::cout<<"Ciphertext: "<<c.encode("7f679d90bebc24305a468d42b9d4edcd")<<"\n";
    std::cout<<"Decrypted text: "<<c.decode(c.encode("7f679d90bebc24305a468d42b9d4edcd"))<<"\n";
    return 0;
}
