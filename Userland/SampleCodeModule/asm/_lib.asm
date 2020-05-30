GLOBAL sys_inforeg
GLOBAL sys_getMem
GLOBAL sys_RTCTime
GLOBAL sys_temp
GLOBAL sys_write
GLOBAL sys_staticwrite
GLOBAL sys_getchar
GLOBAL sys_clear
GLOBAL sys_ticksElapsed
GLOBAL sys_changeApp
GLOBAL sys_loadApp
GLOBAL sys_run
GLOBAL halt
GLOBAL cpuVendor
GLOBAL cpuModel
GLOBAL getRegistersData

section .text

sys_getMem:
    push rbp
    mov rbp, rsp

    mov rax,0
    int 80h

    mov rsp, rbp
    pop rbp

    ret

sys_RTCTime:
    push rbp
    mov rbp, rsp

    mov rax,1;POSIBLE FALLO PQ NO RECIBO PUNTERO
    int 80h

    mov rsp, rbp
    pop rbp

    ret

sys_temp:
    push rbp
    mov rbp, rsp

    mov rax,2
    int 80h

    mov rsp, rbp
    pop rbp

    ret

sys_write:
    push rbp
    mov rbp, rsp

    push rax
    push r10

    mov r10,rcx
    mov rax,3
    int 80h

    pop r10
    pop rax

    mov rsp, rbp
    pop rbp

    ret

sys_staticwrite:
    push rbp
    mov rbp, rsp

    push rax
    push r10

    mov r10,rcx
    mov rax,4
    int 80h

    pop r10
    pop rax

    mov rsp, rbp
    pop rbp

    ret

sys_getchar:
    push rbp
    mov rbp, rsp

    mov rax,5
    int 80h

    mov rsp, rbp
    pop rbp

    ret

sys_clear:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,6
    int 80h

    pop rax

    mov rsp, rbp
    pop rbp

    ret

sys_ticksElapsed:
    push rbp
    mov rbp, rsp

    mov rax,7
    int 80h

    mov rsp, rbp
    pop rbp

    ret


sys_changeApp:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,8
    int 80h

    pop rax

    mov rsp, rbp
    pop rbp

    ret

sys_loadApp:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,9
    int 80h

    pop rax

    mov rsp, rbp
    pop rbp

    ret

sys_run:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,10
    int 80h

    pop rax

    mov rsp, rbp
    pop rbp

    ret

halt:
    hlt
    ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx
	push rcx
	push rdx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+12], 0

	mov rax,rdi

	pop rdx
	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp
	ret

cpuModel:
	push rbp
	mov rbp, rsp

	mov rax,0
	mov rax,1
	cpuid

	shr rax,4
	and rax,0xF ;0x000000000000000F
	
	mov rsp, rbp
	pop rbp
	ret

 getRegistersData:
    push rbp
    mov rbp,rsp

    push rax

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

    pop rax
    
    leave
    ret
