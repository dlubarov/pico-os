#include "util/blob.h"
#include "util/hashmap.h"

typedef struct tar_header
{
  char path[100];
  char mode[8];
  char uid[8];
  char gid[8];
  char size[12];
  char mtime[12];
  char chksum[8];
  char typeflag[1];
} tar_header_t;

uint32 parse_ascii_number(const char *in)
{
  unsigned int size = 0;
  unsigned int j;
  unsigned int count = 1;
  for (j = 11; j > 0; j--, count *= 8)
    size += ((in[j - 1] - '0') * count);
  return size;
}

void parse_tar(Blob tar, StringHashMap<Blob> &result)
{
  uint32 offset = 0;
  while (tar[offset])
  {
    tar_header *header = (tar_header *) (tar.buf_start() + offset);
    offset += 512;
    uint32 size = parse_ascii_number(header->size);
    uint32 size_padded = (size + 512) / 512 * 512;
    Blob file_content((uint8 *) tar.buf_start() + offset, size);
    result[header->path] = file_content;
    offset += size_padded;
  }
}
