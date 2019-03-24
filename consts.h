#pragma once
#include <cstdint>
using std::uint32_t;
//size of hashes, set by sia at 256 bits or 32 bytes
const uint32_t HashSize = 32;
//bytes per segment, equivalent to twice the hash size
const uint32_t SegmentSize = 64;
//number of bytes per sector
const uint32_t SectorSize = 1<<22;
//convenience const, number of segments per sector
const uint32_t SegmentsPerSector = SectorSize / SegmentSize;

const uint8_t leafHashPrefix = 1;
const uint8_t nodeHashPrefix = 1;
