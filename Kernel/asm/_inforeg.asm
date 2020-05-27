GLOBAL getRegistersData


section .text


getRegistersData:
    push rbp
    mov rbp,rsp

    ; mov [rdi+8],rax
    ; lea rax,[rip]  ;workaround para conseguir el valor de rip
    ; mov [rdi],rax
    ; mov [rdi+16],rcx
    ; mov [rdi+24],rdx
    ; mov [rdi+32],rbx
    ; mov [rdi+40],rsi
    ; mov [rdi+48],rdi
    ; mov [rdi+56],rsp
    ; mov [rdi+64],rbp
    ; mov [rdi+72],r8
    ; mov [rdi+80],r9
    ; mov [rdi+88],r10
    ; mov [rdi+96],r11
    ; mov [rdi+104],r12
    ; mov [rdi+112],r13
    ; mov [rdi+120],r14
    ; mov [rdi+128],r15

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


