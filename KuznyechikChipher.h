#ifndef PRACTICALWORK2_KUZNYECHIKCHIPHER_H
#define PRACTICALWORK2_KUZNYECHIKCHIPHER_H

#include "GaloisFIeldWork.h"

#include <string>
#include <iostream>
#include <vector>

const std::vector<int> pi_substitution = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233,
                                          119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24,
                                          101,
                                          90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227,
                                          106, 143,
                                          160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171,
                                          242, 42,
                                          104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19,
                                          71, 156,
                                          183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157,
                                          158, 178,
                                          177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87,
                                          223,
                                          245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15,
                                          236,
                                          222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115,
                                          30, 0,
                                          98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47,
                                          140, 163,
                                          165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107,
                                          228, 136,
                                          217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202,
                                          216, 133,
                                          97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82,
                                          89, 166,
                                          116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

const std::vector<int> l_substitution = {148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148, 1};
const std::vector<char> hex_num ={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f',};


class KuznyechikChipher {

public:

    std::string k;

    unsigned long long formate_string(std::string s) {
        galois_num formated_string = 0;

        if(s.size()!=32){
            std::cout << "Error " << "\n";
            throw std::invalid_argument("Length of string is inappropriate!");
        }
        for (int i = 0; i < s.size(); ++i) {
            if (!(s[i]-'0'>=0 and s[i]-'0'<=9 or s[i]-'a'>=0 and s[i]-'a'<=5)) {
                std::cout << "Error on " << s[i] << "\n";
                throw std::invalid_argument("Is not a hex sequence!");
            } else {
                for (int j = 0; j < hex_num.size(); ++j) {
                    if(hex_num[j]==s[i]){
                        if (j!=0){
                            formated_string<<=4;
                        }
                        formated_string^=j;
                    }
                }
            }
        }
        return formated_string;
    }

    unsigned long long X_k_a(galois_num key, galois_num a) {
        return sum(key, a);
    }

    unsigned long long S(galois_num a) {
        galois_num temp = 0;
        for (int i = 15; i >= 0; i--) {
            galois_num byte = 0;
            for (int j = 0; j < 8; ++j) {
                if (1 << (i * 8 + j) & a) {
                    byte ^= 1 << j;
                }
            }
            temp ^= pi_substitution[byte] << (i * 8);
        }
        return temp;
    }

    unsigned long long S_reverse(galois_num a) {
        galois_num temp = 0;
        for (int i = 15; i >= 0; i--) {
            galois_num byte = 0;
            for (int j = 0; j < 8; ++j) {
                if (1 << (i * 8 + j) & a) {
                    byte ^= 1 << j;
                }
            }
            for (int j = 0; j < 256; ++j) {
                if (pi_substitution[j] == byte) {
                    temp ^= j << (i * 8);
                }
            }
        }
        return temp;
    }

    unsigned long long l(galois_num a) {
        galois_num temp = 0;
        for (int i = 15; i >= 0; i--) {
            galois_num byte = 0;
            for (int j = 0; j < 8; ++j) {
                if (1 << (i * 8 + j) & a) {
                    byte ^= 1 << j;
                }
            }
            temp ^= prod(l_substitution[i], byte);
        }
        return temp;
    }

    unsigned long long R(galois_num a) {
        galois_num temp = 0;
        temp ^= l(a) << 120;
        temp ^= a >> 8;
        return temp;
    }

    unsigned long long L(galois_num a) {
        for (int i = 0; i < 16; ++i) {
            a = R(a);
        }
        return a;
    }

    unsigned long long R_reverse(galois_num a) {
        galois_num temp = 0;
        for (int i = 14; i >= 0; i--) {
            galois_num byte = 0;
            for (int j = 0; j < 8; ++j) {
                if (1 << (i * 8 + j) & a) {
                    byte ^= 1 << j;
                }
            }
            temp ^= byte << (i * 8);
        }
        galois_num byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (1 << (15 * 8 + j) & a) {
                byte ^= 1 << j;
            }
        }
        temp = temp << 8;
        temp ^= l(temp ^ byte);
        return temp;
    }

    unsigned long long L_reverse(galois_num a) {
        for (int i = 0; i < 16; ++i) {
            a = R_reverse(a);
        }
        return a;
    }

    std::vector<galois_num> F_k(galois_num key, galois_num a1, galois_num a0) {
        galois_num temp = 0;
        temp = L(S(X_k_a(key, a1))) ^ a0;
        std::vector<galois_num> ans = {temp, a1};
        return ans;
    }

    std::vector<galois_num> C_i() {
        std::vector<galois_num> ans;
        for (int i = 1; i < 33; ++i) {
            ans.push_back(L(i << 120));
        }
        return ans;
    }

    std::vector<galois_num> iterative_keys() {
        std::vector<galois_num> ans;
        std::string temp = "";
        for (int j = 0; j < 32; ++j) {
            temp=k[j]+temp;
        }
        ans.push_back(formate_string(temp));
        temp = "";
        for (int j = 32; j < 64; ++j) {
            temp=k[j]+temp;
        }
        ans.push_back(formate_string(temp));

        std::vector<galois_num> it_const = C_i();
        for (int i = 1; i < 5; ++i) {
            std::vector<galois_num> temp_vec = F_k(it_const[8 * (i - 1) + 1], ans[2 * i - 2], ans[2 * i - 1]);
            for (int j = 2; j < 9; ++j) {
                temp_vec = F_k(it_const[8 * (i - 1) + j], temp_vec[0], temp_vec[1]);
            }
            ans.push_back(temp_vec[0]);
            ans.push_back(temp_vec[1]);
        }
        return ans;
    }

public:

    KuznyechikChipher(const std::string s) {
        k = s;
    }

    std::string encode(const std::string s) {
        galois_num open_text = formate_string(s);
        std::vector<galois_num> it_keys = iterative_keys();
        for (int i = 0; i < 9; ++i) {
            open_text = L(S(X_k_a(it_keys[i], open_text)));
        }
        open_text = X_k_a(it_keys[-1], open_text);
        std::string st = "";
        galois_num j = 0;
        while ((1 << j) <= open_text) {
            if ((1 << j) & open_text) {
                while (st.size() != j) {
                    st = "0" + st;
                }
                st = "1" + st;
            }
            j++;
        }
        return st;
    }

    std::string decode(std::string s){
        galois_num chipher_text = formate_string(s);
        std::vector<galois_num> it_keys = iterative_keys();
        for (int i = 9; i < 0; ++i) {
            chipher_text = S_reverse(L_reverse(X_k_a(it_keys[i], chipher_text)));
        }
        chipher_text = X_k_a(it_keys[0], chipher_text);
        std::string st = "";
        galois_num j = 0;
        while ((1 << j) <= chipher_text) {
            if ((1 << j) & chipher_text) {
                while (st.size() != j) {
                    st="0"+st;
                }
                st="1"+st;
            }
            j++;
        }
        return st;
    }


};

#endif
