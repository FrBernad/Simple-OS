GLOBAL cpuVendor
GLOBAL cpuModel
GLOBAL cpuTemp
GLOBAL getMem

section .text
	
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

	mov byte [rdi+13], 0

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

;shr dest, src	Intel Syntax
;Logical shift dest to the right by src bits.

cpuTemp:

	push rbp
	mov rbp, rsp

	push rcx

	mov rcx,0
	mov rcx, 0x1B1
	rdmsr
;	shr rax,15
;	and rax,0x7 ;0x0000000000000007   

	pop rcx

	mov rsp, rbp
	pop rbp
	ret

getMem:
	push rbp
	mov rbp, rsp

	push rcx
	push rdx

	mov rcx,0
	mov rdx,0
	mov rax,mem

.loopStart:
	cmp rcx,32
	je .loopEnd

	mov dl,[rdi]
	mov byte [rax], dl

	inc rcx
	inc rdi
	inc rax

	jmp  .loopStart
.loopEnd:
	
	pop rdx
	pop rcx

	mov rax,mem

	mov rsp, rbp
	pop rbp
	ret


section .bss
	mem resb 32