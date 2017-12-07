#ifndef TYPES_H_
#define TYPES_H_

using LogicalAddress = unsigned int;
using PhyscialAddress = LogicalAddress;
using BitMask = LogicalAddress;
using AddressOffset = LogicalAddress;

using PageNumber = int;
using FrameNumber = PageNumber;

using Byte = unsigned char;
using Size = unsigned int;
using SizePow2 = unsigned int;
using Count = unsigned int;

#define TLB_REPLACE_FIFO '1'
#define TLB_REPLACE_LRU '2'


#endif