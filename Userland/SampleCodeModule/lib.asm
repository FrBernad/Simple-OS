GLOBAL putchar
GLOBAL printString
GLOBAL printNum
GLOBAL stringcmp
GLOBAL printmem
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

putchar:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,0
    int 80h

    pop rax
    leave

    ret

printString:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,1
    int 80h

    pop rax
    leave
    
    ret
    
printNum:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,2
    int 80h

    pop rax
    leave
    
    ret
    
stringcmp:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,8
    int 80h

    pop rax
    leave
    
    ret
    
printmem:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,0
    int 80h

    pop rax
    leave
    
    ret
    
    