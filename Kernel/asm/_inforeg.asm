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

    mov [rdi+8],rax
    mov rax,[rbp+8]      ; cargo RIP
    mov [rdi],rax        
    mov [rdi+8*2],rcx
    mov [rdi+8*3],rdx
    mov [rdi+8*4],rbx
    mov [rdi+8*5],rsi
    mov [rdi+8*6],rdi
    mov [rdi+8*7],rsp
    mov [rdi+8*8],rbp
    mov [rdi+8*9],r8
    mov [rdi+8*10],r9
    mov [rdi+8*11],r10
    mov [rdi+8*12],r11
    mov [rdi+8*13],r12
    mov [rdi+8*14],r13
    mov [rdi+8*15],r14
    mov [rdi+8*16],r15

    mov rax,rdi

    leave
    ret


