#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdio>

int main() {
  auto sharedUserData = (BYTE*)0x7FFE0000;
  printf("Version: %d.%d.%d\n",
         *(ULONG*)(sharedUserData + 0x26c),   // major version offset
         *(ULONG*)(sharedUserData + 0x270),   // minor version offset
         *(ULONG*)(sharedUserData + 0x260));  // build number offset

  return 0;
}
