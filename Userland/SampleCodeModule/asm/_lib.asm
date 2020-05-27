GLOBAL sys_inforeg
GLOBAL sys_getMem
GLOBAL sys_RTCTime
GLOBAL sys_cpuInfo
GLOBAL sys_temp
GLOBAL sys_write
GLOBAL sys_staticwrite
GLOBAL sys_getchar
GLOBAL sys_deletechar
GLOBAL sys_clear
GLOBAL sys_ticksElapsed
GLOBAL sys_changeResources

section .text

sys_inforeg:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,0
    int 80h

    pop rax
    
    mov rsp, rbp
	pop rbp

    ret

sys_getMem:
push rbp
mov rbp, rsp

mov rax,1
int 80h

mov rsp, rbp
pop rbp

ret

sys_RTCTime:
push rbp
mov rbp, rsp

mov rax,2;POSIBLE FALLO PQ NO RECIBO PUNTERO
int 80h

mov rsp, rbp
pop rbp

ret

sys_cpuInfo:
push rbp
mov rbp, rsp

push rax

mov rax,3
int 80h

pop rax

mov rsp, rbp
pop rbp

ret

sys_temp:
push rbp
mov rbp, rsp

mov rax,4
int 80h

mov rsp, rbp
pop rbp

ret

sys_write:
push rbp
mov rbp, rsp

push rax

mov rax,5
int 80h

pop rax

mov rsp, rbp
pop rbp

ret

sys_staticwrite:
push rbp
mov rbp, rsp

push rax

mov rax,6
int 80h

pop rax

mov rsp, rbp
pop rbp

ret

sys_getchar:
push rbp
mov rbp, rsp

mov rax,7
int 80h

mov rsp, rbp
pop rbp

ret

sys_deletechar:
push rbp
mov rbp, rsp

push rax

mov rax,8
int 80h

pop rax

mov rsp, rbp
pop rbp

ret

sys_clear:
push rbp
mov rbp, rsp

push rax

mov rax,9
int 80h

pop rax

mov rsp, rbp
pop rbp

ret

sys_ticksElapsed:
push rbp
mov rbp, rsp

mov rax,10
int 80h

mov rsp, rbp
pop rbp

ret


sys_changeResources:
push rbp
mov rbp, rsp

push rax

mov rax,11
int 80h

pop rax

mov rsp, rbp
pop rbp

ret