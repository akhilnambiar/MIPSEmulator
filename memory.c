#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

/* Pointer to simulator memory */
uint8_t *mem;

/* Called by program loader to initialize memory. */
uint8_t *init_mem() {
  assert (mem == NULL);
  mem = calloc(MEM_SIZE, sizeof(uint8_t)); // allocate zeroed memory
  return mem;
}

/* Returns 1 if memory access is ok, otherwise 0 */
int access_ok(uint32_t mipsaddr, mem_unit_t size) {
if (mipsaddr+size<MEM_SIZE && mipsaddr>0)   //Try changing this part first
switch(size)
  {
  case SIZE_WORD:
    if (mipsaddr % 4 == 0)
      return 1;
    break;
  case SIZE_HALF_WORD:
    if (mipsaddr % 2 == 0)
     return 1;
   break;
  case SIZE_BYTE:
    return 1;
  break;
  }
  return 0;



  
}

/* Writes size bytes of value into mips memory at mipsaddr */
void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value) {
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad write=%08x\n", __FUNCTION__, mipsaddr);
    exit(-1);
  }
  
  if(size==SIZE_WORD)

  {
    *(mem+mipsaddr) = value & 0x0000000FF;
    *(mem+mipsaddr+1) = (value>>8) & 0x0000000FF;
    *(mem+mipsaddr+2) = (value>>16) & 0x0000000FF;
    *(mem+mipsaddr+3) = (value>>24) & 0x0000000FF;

  }
  else if(size==SIZE_HALF_WORD)
  {
    *(mem+mipsaddr) = value & 0x0000000FF;
    *(mem+mipsaddr+1) = (value>>8) & 0x0000000FF;
  }
  else 
  {
    *(mem+mipsaddr) = value & 0x0000000FF;
  }

}

/* Returns zero-extended value from mips memory */
uint32_t load_mem(uint32_t mipsaddr, mem_unit_t size) {
  uint8_t byte_t;
  uint16_t halfword_t; 
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad read=%08x\n", __FUNCTION__, mipsaddr);
    exit(-1);
  }
  switch (size)
  {
    case SIZE_BYTE:
      byte_t = *(uint8_t*)(mem+mipsaddr);
      return (uint32_t) byte_t;
      break;
    case SIZE_HALF_WORD:
      halfword_t = *(uint16_t*)(mem + mipsaddr);
      return (uint32_t) halfword_t;
      break;
    case SIZE_WORD:
      return *(uint32_t*)(mem + mipsaddr);
  }

  /* TODO YOUR CODE HERE */

  // incomplete stub to let mipscode/simple execute
  // (only handles size == SIZE_WORD correctly)
  // feel free to delete and implement your own way
  return *(uint32_t*)(mem + mipsaddr);
}
