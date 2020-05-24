GLOBAL putchar
GLOBAL printString
GLOBAL printNum
GLOBAL deletechar
GLOBAL getchar
GLOBAL clear
GLOBAL clearLine
GLOBAL newLine
GLOBAL stringcmp
GLOBAL help
GLOBAL inforeg
GLOBAL printmem
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
    
    mov rsp, rbp
	pop rbp

    ret

printString:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,1
    int 80h

    pop rax
    
    mov rsp, rbp
	pop rbp
    
    ret
    
printNum:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,2
    int 80h

    pop rax
    
    mov rsp, rbp
	pop rbp
    
    ret


deletechar:
	push rbp
	mov rbp, rsp

	push rax
	mov rax, 3
	int 80h
	pop rax

	mov rsp, rbp
	pop rbp

	ret


getchar:
	push rbp
	mov rbp, rsp

	mov rax, 4
	int 80h

	mov rsp, rbp
	pop rbp

	ret

clear:
	push rbp
	mov rbp, rsp

	push rax
	mov rax, 5
	int 80h
	pop rax

	mov rsp, rbp
	pop rbp

	ret

clearLine:
	push rbp
	mov rbp, rsp

	push rax
	mov rax, 6
	int 80h
	pop rax
	
	mov rsp, rbp
	pop rbp

	ret

newLine:
	push rbp
	mov rbp, rsp

	push rax
	mov rax, 7
	int 80h
	pop rax

	mov rsp, rbp
	pop rbp

	ret

stringcmp:
    push rbp
    mov rbp, rsp

    mov rax,8
    int 80h

    mov rsp, rbp
	pop rbp
    
    ret

help:
    push rbp
    mov rbp, rsp
 
    push rax
 
    mov rax, 9
    int 80h
 
    pop rax
 
    mov rsp, rbp
	pop rbp

    ret
 
inforeg:
    push rbp
    mov rbp, rsp
 
    push rax
 
    mov rax, 10
    int 80h
 
    pop rax
 
    
    mov rsp, rbp
	pop rbp

    ret

printmem:
    push rbp
    mov rbp, rsp

    push rax

    mov rax,11
    int 80h

    pop rax
    
    mov rsp, rbp
	pop rbp
    
    ret
 
time:
    push rbp
    mov rbp, rsp
 
    push rax
 
    mov rax, 12
    int 80h
 
    pop rax
    
    mov rsp, rbp
	pop rbp

    ret
 
cpuInfo:
    push rbp
    mov rbp, rsp
 
    push rax
 
    mov rax, 13
    int 80h
 
    pop rax
 
    mov rsp, rbp
	pop rbp
    ret
 
temp:
    push rbp
    mov rbp, rsp
 
    push rax
 
    mov rax, 14
    int 80h
 
    pop rax
    
    mov rsp, rbp
	pop rbp
    
    ret
    
    