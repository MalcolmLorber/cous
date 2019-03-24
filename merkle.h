#pragma once
#include "consts.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <blake2.h>

typedef struct hash_type{uint8_t x[32];} hash_type;

//using boost::multiprecision::uint256_t;

class MerkleStack {
  hash_type stack[64];
  uint64_t used = 0;
  uint8_t buffer [1 + SegmentSize];
 public:
  MerkleStack(){
    std::memset(buffer, 0,sizeof(buffer));
    for(auto&x: stack){
      std::memset(x.x, 0, sizeof(x));
    }
  }
  uint64_t LeafHash(hash_type* out, uint8_t leaf[]);
  uint64_t NodeHash(hash_type* out, hash_type left, hash_type right);
  void AppendLeafHash(hash_type hash);
  uint64_t NumLeaves() const{return used;}
  void Reset(){used = 0;}
  uint64_t ReadFrom(std::istream in);
  hash_type Root();
};
