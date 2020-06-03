GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _syscallHandler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL sys_changeProcess
GLOBAL sys_forceStart
GLOBAL _initialize_stack_frame

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysCallDispatcher
EXTERN schedule

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro pushStateNoRax 0
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

   
	
;rrsp rrbp rrip rrax rrcx rrdx rrbx rrsi rrdi rr8 rr9 rr10 rr11 rr12 rr13 rr14 rr15

%macro exceptionHandler 1
	push rsi
	push rdx

	mov [expRegisters+8*7],rsi ;save rsi

	lea rsi,[rsp+16]             ;get rsp in rsi (STACKFRAME)
	mov [expRegisters+8*0],rsi   ;save rsp

	mov [expRegisters+8*1],rbp  
	
	push rdx
	mov rdx,[rsi]				;get rdi value pushed from interruptFrame
	mov [expRegisters+8*2],rdx  ;save rdi
	pop rdx

	mov [expRegisters+8*3],rax
	mov [expRegisters+8*4],rcx
	mov [expRegisters+8*5],rdx
	mov [expRegisters+8*6],rbx
	mov [expRegisters+8*8],rdi
	mov [expRegisters+8*9],r8
	mov [expRegisters+8*10],r9
	mov [expRegisters+8*11],r10
	mov [expRegisters+8*12],r11
	mov [expRegisters+8*13],r12
	mov [expRegisters+8*14],r13
	mov [expRegisters+8*15],r14
	mov [expRegisters+8*16],r15

	mov rdx,expRegisters

	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

    popState

	pop rdx
	pop rsi

	iretq

%endmacro

sys_forceStart:
	mov rsi,1 ;force start
	call schedule
	mov rsp, rax
	iretq

sys_changeProcess:
	mov rdi,rsp
	mov rsi,0 ;start not forced
	call schedule
	mov rsp,rax
	iretq

_initialize_stack_frame:
	mov r8,rsp
	mov rsp, rdx
	mov rax,rsi
	push 0x0
	push rdx
	push 0x202
	push 0x08
	push rdi
	mov rdi, rsi
	mov rsi,rcx
	push 0x0
	pushStateNoRax
	mov rax, rsp
	mov rsp,r8
	ret

;se llenan
;%rdi, %rsi, %rdx, %rcx, %r8 y %r9 
;necesito
;%rax	%rdi	%rsi	%rdx	%r10	%r8	   %r9
;syscalls 

_syscallHandler:
	push rdi
	mov [sysRegisters+8*0],rax
	mov [sysRegisters+8*1],rdi
	mov [sysRegisters+8*2],rsi
	mov [sysRegisters+8*3],rdx
	mov [sysRegisters+8*4],r10
	mov [sysRegisters+8*5],r8
	mov [sysRegisters+8*6],r9

	mov rdi,sysRegisters
	call sysCallDispatcher

	pop rdi

	iretq

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn





;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1

	sysRegisters:
		rsrsp resq 1
		rsrax resq 1
		rsrdi resq 1
		rsrsi resq 1
		rsrdx resq 1
		rsr10 resq 1
		rsr8 resq 1
		rsr9 resq 1

	expRegisters:
	    rersp resq 1
	    rerbp resq 1
		rerip resq 1
		rerax resq 1
		rercx resq 1
		rerdx resq 1
		rerbx resq 1
		rersi resq 1
		rerdi resq 1
		rer8 resq 1
		rer9 resq 1
		rer10 resq 1
		rer11 resq 1
		rer12 resq 1
		rer13 resq 1
		rer14 resq 1
		rer15 resq 1

	