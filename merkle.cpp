#include "merkle.h"

uint64_t MerkleStack::LeafHash(hash_type* out, uint8_t leaf[]){
  buffer[0] = leafHashPrefix;
  std::memcpy(&buffer[1], leaf, 32);
  return blake2b(out->x, buffer, NULL, sizeof(out->x), sizeof(buffer), 0);
};

uint64_t MerkleStack::NodeHash(hash_type* out, hash_type left, hash_type right){
  buffer[0] = nodeHashPrefix;
  std::memcpy(&buffer[1], left.x, 32);
  std::memcpy(&buffer[1+sizeof(left)], right.x, 32);
  return blake2b(out->x, buffer, NULL, sizeof(out->x), sizeof(buffer), 0);
};

void MerkleStack::AppendLeafHash(hash_type hash){
  uint64_t i=0;
  for(; (used&(1<<i)) != 0; i++){
    NodeHash(&hash, stack[i], hash);
  }
  stack[i] = hash;
  used++;
};

uint64_t MerkleStack::ReadFrom(std::istream in){

};

hash_type MerkleStack::Root(){
  hash_type root;
  uint64_t i = __builtin_ctz(used);
  if(i==64){
    std::memset(&root, 0, sizeof(root));
  }
  root = stack[i];
  for(i++;i<64;i++){
    if((used&(1<<i))!=0){
      NodeHash(&root, stack[i], root);
    }
  }
  return root;
};

////////
int main(){
  MerkleStack a;
  for(int i=0;i<256; i++){
    hash_type b;
    blake2b(b.x, &i, NULL, sizeof(b.x), sizeof(i), 0);
    a.AppendLeafHash(b);
  }
  hash_type b = a.Root();
}
