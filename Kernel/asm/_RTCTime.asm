GLOBAL getBSDTimeInfo

section .text

getBSDTimeInfo:
    push rbp
    mov rbp,rsp

    mov rax, rdi
    out 70h, al
    mov rax,0
    in al, 71h

    leave
    ret

