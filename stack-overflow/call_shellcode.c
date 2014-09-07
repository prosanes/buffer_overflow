/* call_shellcode.c  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char code[] =
"\xeb\x16"      /* jmp string   */
"\x31\xdb"      /* xor ebx ebx */
"\x31\xd2"      /* xor edx edx */
"\x31\xc0"      /* xor eax eax */
"\x59"          /* pop ecx */
"\xbb\x01\x00\x00\x00"  /* mov $0x1, ebx */
"\xb2\x09"      /* mov 0x9 dl */
"\xb0\x04"      /* mov 0x04 al */
"\xcd\x80"      /* int 0x80 */
"\xb0\x01"      /* mov 0x1 al */
"\xcd\x80"      /* int 0x80 */
"\xe8\xe5\xff\xff\xff" /* call code */
"GOTCHA!\n"
;

int main(int argc, char **argv)
{
   char buf[sizeof(code)];
   strcpy(buf, code);
   printf("copiou\n");

    __asm__("call code");
    /*
   __asm__("jmp string");
   __asm__("code2: xor %EBX, %EBX");
   __asm__("xor %EDX, %EDX");
   __asm__("xor %EAX, %EAX");
   __asm__("popl %ECX");
   __asm__("movb $0x1, %bl");
   __asm__("movb $0x09, %dl");
   __asm__("movb $0x04, %al");
   __asm__("int $0x80");
   __asm__("movb $0x1, %al");
   __asm__("int $0x80");
   __asm__("string: call code2");
   "Fim\n";*/


   //((void(*)( ))buf)( );
    printf("Fim!\n");
} 
