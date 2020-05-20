GLOBAL sysWrite

section .text

sysWrite:
    push rbp
    mov rbp,rsp

    push rax
    push rdi
    push rsi
    push rdx

    mov rax,1
    mov rdi,2
    mov rsi,string
    mov rdx,8
    int 80h

    pop rdx
    pop rsi
    pop rdi
    pop rax

    leave
    ret


section .data
    string db "hola como estas bien?",0
    len equ $-string