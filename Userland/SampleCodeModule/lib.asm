GLOBAL
GLOBAL
GLOBAL
GLOBAL
GLOBAL
GLOBAL
GLOBAL
GLOBAL
GLOBAL help
GLOBAL inforeg
GLOBAL 
GLOBAL time
GLOBAL cpuInfo
GLOBAL temp

section .text

help:
    push rbp
    mov rbp, rsp

    push rax

    mov rax, 9
    int 80h

    pop rax

    leave
    ret

inforeg:
    push rbp
    mov rbp, rsp

    push rax

    mov rax, 10
    int 80h

    pop rax

    leave
    ret

time:
    push rbp
    mov rbp, rsp

    push rax

    mov rax, 12
    int 80h

    pop rax

    leave
    ret

cpuInfo:
    push rbp
    mov rbp, rsp

    push rax

    mov rax, 13
    int 80h

    pop rax

    leave
    ret

temp:
    push rbp
    mov rbp, rsp

    push rax

    mov rax, 14
    int 80h

    pop rax

    leave
    ret

