GLOBAL cpuVendor
GLOBAL cpuModel
GLOBAL cpuTemp
GLOBAL sys_getMem

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

	mov rax,0
	mov rcx,0
	mov ecx, 0x19C ;codigo que corresponde a THERMAL STATUS
	rdmsr  ;me deja en eax la parte baja del msr solicitado, que en este caso es la unica que me interesa

;	shr rax,15                         ;shifteo que usaria para quedarme con los bits que me importan
;	and rax,0x7 ;0x0000000000000007   

	pop rcx
							
	mov rsp, rbp
	pop rbp
	ret             ;se devuelve en eax el valor cargado por rdmsr

sys_getMem:
	push rbp
	mov rbp, rsp

	mov rax,0
	mov al,[rdi]

	mov rsp, rbp
	pop rbp
	ret