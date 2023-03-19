#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ulong unsigned long
#define uint unsigned int
#define byte unsigned char
#define undefined8 unsigned long
#define undefined4 unsigned int
#define undefined2 unsigned short
#define undefined unsigned char

int u32(int *param_1) { return *param_1; }

short u16(short *param_1) { return *param_1; }

char u8(char *param_1) { return *param_1; }

void vm_add(uint *param_1) {
  uint uVar1;
  uint uVar2;
  byte bVar3;

  bVar3 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  uVar2 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 + uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_addi(uint *param_1) {
  uint uVar1;
  byte bVar2;
  byte bVar3;

  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 + bVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_cmp(uint *param_1) {
  exit(10);
  uint uVar1;
  byte bVar2;

  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  if (uVar1 == param_1[(long)(int)(uint)bVar2 + 2]) {
    *(undefined *)(param_1 + 0x22) = 1;
  }
  *param_1 = *param_1 + 6;
  return;
}

void vm_div(uint *param_1) {
  uint uVar1;
  uint uVar2;
  byte bVar3;

  bVar3 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  uVar2 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 / uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_exit(uint *param_1) {
  *(undefined *)(param_1 + 1) = 1;
  *param_1 = *param_1 + 6;
  return;
}

void vm_input(uint *param_1) {
  byte bVar1;
  uint uVar2;

  uVar2 = getchar();
  bVar1 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar1 + 2] = uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_inv(uint *param_1) {
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;

  bVar1 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  if (bVar2 == 0) {
    uVar3 = 0;
  } else {
    uVar3 = param_1[0x28];
    param_1[0x28] = uVar3 - 1;
    uVar3 = *(uint *)((ulong)(uVar3 - 1) * 4 + *(long *)(param_1 + 0x26));
  }
  if (bVar2 < 2) {
    uVar4 = 0;
  } else {
    uVar4 = param_1[0x28];
    param_1[0x28] = uVar4 - 1;
    uVar4 = *(uint *)((ulong)(uVar4 - 1) * 4 + *(long *)(param_1 + 0x26));
  }
  if (bVar2 < 3) {
    uVar5 = 0;
  } else {
    uVar5 = param_1[0x28];
    param_1[0x28] = uVar5 - 1;
    uVar5 = *(uint *)((ulong)(uVar5 - 1) * 4 + *(long *)(param_1 + 0x26));
  }
  if (bVar1 != 101) {
    printf("%d\b", bVar1);
    exit(69);
    lVar6 = syscall((ulong)bVar1, (ulong)uVar3, (ulong)uVar4, (ulong)uVar5);
  }
  param_1[0x21] = 0;
  *param_1 = *param_1 + 6;
  return;
}

void vm_je(uint *param_1) {
  uint uVar1;
  byte bVar2;
  unsigned short uVar3;

  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  // prints out the comparison
  printf("%d - %c - %c\n", *param_1, uVar1, param_1[(long)(int)(uint)bVar2 + 2]);
  if (uVar1 == param_1[(long)(int)(uint)bVar2 + 2]) {
    uVar3 = u16((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
    *param_1 = ((uint)uVar3 * 2 + (uint)uVar3) * 2;
  } else {
    *param_1 = *param_1 + 6;
  }
  // skip first check
  if (*param_1 == 360)
    *param_1 = 468;
  // skip second check
  if (*param_1 == 1158)
    *param_1 = 1206;
  return;
}

void vm_jge(uint *param_1) {
  uint uVar1;
  byte bVar2;
  unsigned short uVar3;

  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  if (uVar1 < param_1[(long)(int)(uint)bVar2 + 2]) {
    *param_1 = *param_1 + 6;
  } else {
    uVar3 = u16((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
    *param_1 = ((uint)uVar3 * 2 + (uint)uVar3) * 2;
  }
  return;
}

void vm_jle(uint *param_1) {
  uint uVar1;
  byte bVar2;
  unsigned short uVar3;

  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  if (param_1[(long)(int)(uint)bVar2 + 2] < uVar1) {
    *param_1 = *param_1 + 6;
  } else {
    uVar3 = u16((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
    *param_1 = ((uint)uVar3 * 2 + (uint)uVar3) * 2;
  }
  return;
}

void vm_jmp(uint *param_1) {
  byte bVar1;

  bVar1 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  *param_1 = *param_1 + param_1[(long)(int)(uint)bVar1 + 2];
  *param_1 = *param_1 + 6;
  return;
}

void vm_jne(uint *param_1) {
  uint uVar1;
  byte bVar2;
  unsigned short uVar3;

  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  if (uVar1 == param_1[(long)(int)(uint)bVar2 + 2]) {
    *param_1 = *param_1 + 6;
  } else {
    uVar3 = u16((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
    *param_1 = ((uint)uVar3 * 2 + (uint)uVar3) * 2;
  }
  return;
}

void vm_mov(uint *param_1) {
  long lVar1;
  byte bVar2;
  uint uVar3;

  lVar1 = *(long *)(param_1 + 0x24);
  uVar3 = *param_1;
  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  uVar3 = u32(lVar1 + (ulong)uVar3 + 2);
  param_1[(long)(int)(uint)bVar2 + 2] = uVar3;
  *param_1 = *param_1 + 6;
  return;
}

void vm_mul(uint *param_1) {
  uint uVar1;
  uint uVar2;
  byte bVar3;

  bVar3 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  uVar2 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 * uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_muli(uint *param_1) {
  uint uVar1;
  byte bVar2;
  byte bVar3;

  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 * bVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_nop(uint *param_1) {
  *param_1 = *param_1 + 6;
  return;
}

void vm_pop(uint *param_1) {
  uint uVar1;
  long lVar2;
  byte bVar3;

  lVar2 = *(long *)(param_1 + 0x26);
  uVar1 = param_1[0x28];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] =
      *(uint *)(lVar2 + (ulong)(uVar1 - 1) * 4);
  param_1[0x28] = param_1[0x28] - 1;
  *param_1 = *param_1 + 6;
  return;
}

void vm_print(uint *param_1) {
  byte bVar1;

  bVar1 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  printf("PRINT 0x%x\n", (ulong)param_1[(long)(int)(uint)bVar1 + 2]);
  *param_1 = *param_1 + 6;
  return;
}

void vm_push(uint *param_1) {
  byte bVar1;

  bVar1 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  *(uint *)(*(long *)(param_1 + 0x26) + (ulong)param_1[0x28] * 4) =
      param_1[(long)(int)(uint)bVar1 + 2];
  param_1[0x28] = param_1[0x28] + 1;
  *param_1 = *param_1 + 6;
  return;
}

void vm_putc(uint *param_1) {
  byte bVar1;

  bVar1 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  putchar((uint)bVar1);
  *param_1 = *param_1 + 6;
  return;
}

void vm_store(uint *param_1) {
  uint uVar1;
  byte bVar2;

  bVar2 = u8((ulong)(*param_1) + 1 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  *(char *)((ulong)uVar1 + *(long *)(param_1 + 0x24)) =
      (char)param_1[(long)(int)(uint)bVar2 + 2];
  *param_1 = *param_1 + 6;
  return;
}

void vm_sub(uint *param_1) {
  uint uVar1;
  uint uVar2;
  byte bVar3;

  bVar3 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  uVar2 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 - uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_subi(uint *param_1) {
  uint uVar1;
  byte bVar2;
  byte bVar3;

  bVar2 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar2 + 2];
  bVar2 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 - bVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_xor(uint *param_1) {
  uint uVar1;
  uint uVar2;
  byte bVar3;

  bVar3 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  uVar1 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 3 + *(long *)(param_1 + 0x24));
  uVar2 = param_1[(long)(int)(uint)bVar3 + 2];
  bVar3 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar3 + 2] = uVar1 ^ uVar2;
  *param_1 = *param_1 + 6;
  return;
}

void vm_load(uint *param_1) {
  byte bVar1;
  byte bVar2;

  bVar1 = u8((ulong)*param_1 + 2 + *(long *)(param_1 + 0x24));
  bVar1 = *(byte *)((ulong)param_1[(long)(int)(uint)bVar1 + 2] +
                    *(long *)(param_1 + 0x24));
  bVar2 = u8((ulong)*param_1 + 1 + *(long *)(param_1 + 0x24));
  param_1[(long)(int)(uint)bVar2 + 2] = (uint)bVar1;
  *param_1 = *param_1 + 6;
  return;
}

void (*functions[])(uint *) = {vm_add,   vm_addi, vm_sub,   vm_subi, vm_mul,
                               vm_muli,  vm_div,  vm_cmp,   vm_jmp,  vm_inv,
                               vm_push,  vm_pop,  vm_mov,   vm_nop,  vm_exit,
                               vm_print, vm_putc, vm_je,    vm_jne,  vm_jle,
                               vm_jge,   vm_xor,  vm_store, vm_load, vm_input};

char *names[] = {"vm_add",   "vm_addi", "vm_sub",   "vm_subi", "vm_mul",
                 "vm_muli",  "vm_div",  "vm_cmp",   "vm_jmp",  "vm_inv",
                 "vm_push",  "vm_pop",  "vm_mov",   "vm_nop",  "vm_exit",
                 "vm_print", "vm_putc", "vm_je",    "vm_jne",  "vm_jle",
                 "vm_jge",   "vm_xor",  "vm_store", "vm_load", "vm_input"};

void vm_step(uint *param_1) {
  if (0x19 < *(char *)((ulong)*param_1 + *(long *)(param_1 + 0x24))) {
    puts("dead");
    exit(0);
  }
  long id =
      (long)(int)(uint) * (byte *)((ulong)*param_1 + *(long *)(param_1 + 0x24));
  printf("%5d, %s\n", *param_1, names[id]);
  functions[id](param_1);
  return;
}

void vm_run(long param_1) {
  while (*(char *)(param_1 + 4) == '\0') {
    vm_step(param_1);
  }
  return;
}

int *vm_create(long param_1, long param_2) {
  undefined4 *puVar1;
  void *pvVar2;

  puVar1 = (undefined4 *)malloc(0xa8);
  *puVar1 = 0;
  *(undefined *)(puVar1 + 1) = 0;
  puVar1[0x28] = 0;
  memset(puVar1 + 2, 0, 0x80);
  pvVar2 = calloc(0x10000, 1);
  *(void **)(puVar1 + 0x24) = pvVar2;
  memcpy(*(void **)(puVar1 + 0x24), (void *)(param_1 + 3), param_2 - 3);
  pvVar2 = calloc(0x200, 4);
  *(void **)(puVar1 + 0x26) = pvVar2;
  return puVar1;
}

int main(int argc, char **argv) {
  FILE *__stream;
  long long __size;
  void *content;
  long vm;

  if (argc < 2) {
    printf("Usage: ./chall file");
    exit(1);
  }
  __stream = fopen(argv[1], "rb");
  fseek(__stream, 0, 2);
  __size = ftell(__stream);
  rewind(__stream);
  content = malloc(__size);
  fread(content, __size, 1, __stream);
  fclose(__stream);
  vm = vm_create(content, __size);
  vm_run(vm);
  return 0;
}
