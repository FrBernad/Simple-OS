GLOBAL getRegistersData


section .text


getRegistersData:
    push rbp
    mov rbp,rsp

    mov [registers],rax
    mov [registers+8],rcx
    mov [registers+16],rdx
    mov [registers+24],rbx
    mov [registers+32],rsi
    mov [registers+40],rdi
    mov [registers+48],rsp
    mov [registers+56],rbp
    mov [registers+64],r8
    mov [registers+72],r9
    mov [registers+80],r10
    mov [registers+88],r11
    mov [registers+96],r12
    mov [registers+104],r13
    mov [registers+112],r14
    mov [registers+120],r15

    mov rax,registers

    leave
    ret


section .bss

registers:
    rrax resq 1
    rrcx resq 1
    rrdx resq 1
    rrbx resq 1
    rrsi resq 1
    rrdi resq 1
    rrsp resq 1
    rrbp resq 1
    rr8 resq 1
    rr9 resq 1
    rr10 resq 1
    rr11 resq 1
    rr12 resq 1
    rr13 resq 1
    rr14 resq 1
    rr15 resq 1
	