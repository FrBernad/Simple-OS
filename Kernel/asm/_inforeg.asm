GLOBAL getRegistersData


section .text


getRegistersData:
    push rbp
    mov rbp,rsp

    mov [rdi],rax
    mov [rdi+8],rcx
    mov [rdi+16],rdx
    mov [rdi+24],rbx
    mov [rdi+32],rsi
    mov [rdi+40],rdi
    mov [rdi+48],rsp
    mov [rdi+56],rbp
    mov [rdi+64],r8
    mov [rdi+72],r9
    mov [rdi+80],r10
    mov [rdi+88],r11
    mov [rdi+96],r12
    mov [rdi+104],r13
    mov [rdi+112],r14
    mov [rdi+120],r15

    mov rax,rdi

    leave
    ret


