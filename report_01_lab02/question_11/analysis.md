<!--
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-02-29 21:26:59
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-02-29 22:07:58
 -->
<!--please use markdown to get the best  Reading experience -->

首先,先将源代码放在这里,

``` c
#include<stdio.h>

int main(){
    int x = 0;
    x += 1;
    x += 1;
    x += 1;
    printf("%d\n",x);
    return 0;
}
```

之后,将使用的编译指令放置在这里

``` bash
gcc -S  opt.c -O0  -o opt0.s
gcc -S  opt.c -O1  -o opt1.s
```

然后,将汇编代码放在这里

# O0

``` asm
    .file    "opt.c"
    .text
    .section    .rodata
.LC0:
    .string    "%d\n"
    .text
    .globl    main
    .type    main, @function
main:
.LFB0:
    .cfi_startproc
    pushq    %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    subq    $16, %rsp
    movl    $0, -4(%rbp)
    addl    $1, -4(%rbp)
    addl    $1, -4(%rbp)
    addl    $1, -4(%rbp)
    movl    -4(%rbp), %eax
    movl    %eax, %esi
    leaq    .LC0(%rip), %rdi
    movl    $0, %eax
    call    printf@PLT
    movl    $0, %eax
    leave
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE0:
    .size    main, .-main
    .ident    "GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
    .section    .note.GNU-stack,"",@progbits

```

# O1

``` asm
    .file    "opt.c"
    .text
    .section    .rodata.str1.1,"aMS",@progbits,1
.LC0:
    .string    "%d\n"
    .text
    .globl    main
    .type    main, @function
main:
.LFB23:
    .cfi_startproc
    subq    $8, %rsp
    .cfi_def_cfa_offset 16
    movl    $3, %edx
    leaq    .LC0(%rip), %rsi
    movl    $1, %edi
    movl    $0, %eax
    call    __printf_chk@PLT
    movl    $0, %eax
    addq    $8, %rsp
    .cfi_def_cfa_offset 8
    ret
    .cfi_endproc
.LFE23:
    .size    main, .-main
    .ident    "GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
    .section    .note.GNU-stack,"",@progbits

```

## 分析O0等级的汇编代码:

1. 首先,不需要关注从".file \"opt.c\""到 "subq $16,%rsp"的代码
因为他们和函数的定义有关系,并不指代具体的指令
2. 其次,"movl    $0, -4(%rbp)",对应了将0赋值于rbp寄存器中的值-4位置的内存.
3. 接下来三条"addl    $1, -4(%rbp)",对应着将rbp寄存器中的值-4位置的内存中的值+1.
4. 接下来,
"movl    -4(%rbp), %eax
movl    %eax, %esi
leaq    .LC0(%rip), %rdi
movl    $0, %eax
call    printf@PLT"
指令涉及到了保存寄存器中的值,设定传入参数,调用函数的操作.
5. 最后"movl    $0, %eax"指令返回0.
6. 剩下的汇编代码与指令无关,不需要分析.
7. 
## 分析O1等级的汇编代码

1. 首先,不需要关注".file \"opt.c\""到 ".cfi_def_cfa_offset 16"的代码,他们只和函数的定义有关,不指代具体指令.
2. 其次,"movl    $3, %edx"指令直接相关edx寄存器中赋值 3.直接对应了int x = 0;与三条x+=1;指令,并且没有将其存入内存.
3. 然后,
"leaq    .LC0(%rip), %rsi
movl    $1, %edi
movl    $0, %eax
call    __printf_chk@PLT"这些指令设定传入参数,调用指令.
4. "movl    $0, %eax"返回0值.
5. 剩下的代码与指令无关,不需要返回值.

## 分析两个代码的区别

1. 首先,两种优化级别在开头,以及数据区并没有什么区别
2. 其次,在对应指令前和返回0后,有少许差别,O1优化等级删去了很多无用操作.
3. 重点在于对应语句的指令,O0优化等级只是简单的一步一步翻译,涉及变量就操作内存,并且比较严格的一步一步操作,每一步操作都对应语句.
4. 但是O1操作等级直接将没有使用到的变量存储在寄存器中,并且将一些操作合并到了一起,将运算在编译器完成.
5. 总之,O1优化级别会在编译器进行运算,并使用寄存器优化运算速度.


<!--please use markdown to get the best reading experience -->

First, put the source code here,

```c
#include <stdio.h>

int main () {
    int x = 0;
    x + = 1;
    x + = 1;
    x + = 1;
    printf ("% d \ n", x);
    return 0;
}
```

After that, place the pragma used here

```bash
gcc -S opt.c -O0 -o opt0.s
gcc -S opt.c -O1 -o opt1.s
```

Then, put the assembly code here

# O0

```asm
.file "opt.c"
.text
.section .rodata
.LC0:
.string "% d \ n"
.text
.globl main
.type main, @function
main:
.LFB0:
.cfi_startproc
pushq% rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq% rsp,% rbp
.cfi_def_cfa_register 6
subq $ 16,% rsp
movl $ 0, -4 (% rbp)
addl $ 1, -4 (% rbp)
addl $ 1, -4 (% rbp)
addl $ 1, -4 (% rbp)
movl -4 (% rbp),% eax
movl% eax,% esi
leaq .LC0 (% rip),% rdi
movl $ 0,% eax
call printf @ PLT
movl $ 0,% eax
leave
.cfi_def_cfa 7, 8
ret
.cfi_endproc
.LFE0:
.size main, .-main
.ident "GCC: (Ubuntu 7.5.0-3ubuntu1 ~ 18.04) 7.5.0"
.section .note.GNU-stack, "", @ progbits

```

# O1

```asm
.file "opt.c"
.text
.section .rodata.str1.1, "aMS", @ progbits, 1
.LC0:
.string "% d \ n"
.text
.globl main
.type main, @function
main:
.LFB23:
.cfi_startproc
subq $ 8,% rsp
.cfi_def_cfa_offset 16
movl $ 3,% edx
leaq .LC0 (% rip),% rsi
movl $ 1,% edi
movl $ 0,% eax
call __printf_chk @ PLT
movl $ 0,% eax
addq $ 8,% rsp
.cfi_def_cfa_offset 8
ret
.cfi_endproc
.LFE23:
.size main, .-main
.ident "GCC: (Ubuntu 7.5.0-3ubuntu1 ~ 18.04) 7.5.0"
.section .note.GNU-stack, "", @ progbits

```

## Analysis of O0 level assembly code:

1. First, you don't need to pay attention to the code from ".file \" opt.c \ "" to "subq $ 16,% rsp"
Because they are related to the definition of the function, they do not refer to specific instructions
2. Second, "movl $ 0, -4 (% rbp)" corresponds to the memory that assigns 0 to the value -4 in the rbp register.
3. The next three "addl $ 1, -4 (% rbp)" correspond to +1 in the memory at the -4 position in the rbp register.
4. Next,
"movl -4 (% rbp),% eax
movl% eax,% esi
leaq .LC0 (% rip),% rdi
movl $ 0,% eax
call printf @ PLT "
The instruction involves the operation of saving the value in the register, setting the incoming parameters, and calling the function.
5. Finally the "movl $ 0,% eax" instruction returns 0.
6. The rest of the assembly code has nothing to do with the instruction and does not need to be analyzed.

## Analyze O1 level assembly code

1. First of all, you don't need to pay attention to the code from ".file \" opt.c \ "" to ".cfi_def_cfa_offset 16", they are only related to the definition of the function, not referring to specific instructions.
2. Secondly, the "movl $ 3,% edx" instruction is directly related to the assignment in the edx register. 3. It directly corresponds to int x = 0; and three x + = 1; instructions, and it is not stored in memory.
3. Then,
"leaq .LC0 (% rip),% rsi
movl $ 1,% edi
movl $ 0,% eax
call __printf_chk @ PLT "These instructions set the incoming parameters and call the instruction.
4. "movl $ 0,% eax" returns 0.
5. The rest of the code has nothing to do with the instruction, no return value is required.

## Analyze the difference between the two codes

1. First, there is no difference between the two optimization levels at the beginning and the data area
2. Secondly, there is a slight difference before the corresponding instruction and after returning 0. The O1 optimization level deletes many useless operations.
3. The focus is on the instructions corresponding to the statement. The O0 optimization level is just a simple step-by-step translation. When variables are involved, the memory is manipulated, and the stricter step-by-step operation is performed.
4. But O1 operation level directly stores unused variables in registers, and merges some operations together to complete the operation in the compiler.
5. In short, the O1 optimization level will perform calculations in the compiler and use registers to optimize the operation speed.
