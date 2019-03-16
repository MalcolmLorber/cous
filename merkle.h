#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include "consts.h"
#include <iostream>

using boost::multiprecision::uint256_t;

class MerkleStack {
  uint256_t stack[64];
  uint64_t used;
  uint8_t buffer [1 + SegmentSize];
 public:
  
  uint256_t LeafHash(uint8_t leaf[]);
  uint256_t Nodehash(uint256_t left, uint256_t right);
  void AppendLeafHash(uint256_t hash);
  uint64_t NumLeaves() const{return used;}
  void Reset(){used = 0;}
  uint64_t ReadFrom(std::istream in);
  uint256_t Root() const;
};
