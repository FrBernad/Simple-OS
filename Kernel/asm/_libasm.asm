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

;shr dest, src	Intel Syntax
;Logical shift dest to the right by src bits.

cpuTemp:
	push rbp
	mov rbp, rsp

	push rcx
	push rdi

	mov rax,0
	mov rcx,0
	mov ecx, 0x19C ;codigo que corresponde a THERMAL STATUS
	rdmsr          ;me deja en eax la parte baja del msr solicitado, que en este caso es la unica que me interesa

	shr rax,16                         ;shifteo que usaria para quedarme con los bits que me importan
	and rax,0x7 ;0x0000000000000007    ;set in rax last 7 bytes digital readout

	mov rdi,rax							;backup digital readout

	mov rcx,0
	mov rax,0
	mov ecx,0xEE
	rdmsr          ;acces Tj_Max rdmsr
	and rax,0x40000000  ;get bit 30, if turned on tjMax = 100 else tjMax=85
	cmp rax,0
	jne .tjhundred
	mov rax,85
	jmp .finish
.tjhundred:
	mov rax,100
.finish:
	sub rax,rdi

	pop rdi
	pop rcx
							
	mov rsp, rbp
	pop rbp
	ret             ;se devuelve en eax el valor de la temp en C

sys_getMem:
	push rbp
	mov rbp, rsp

	push rdx
	push r10

	mov rax,rsi

	mov rdx,0
.loopStart:
	cmp rdx,32
	jle .loopEnd
	dec rdx
	mov r10,[rdi]
	mov [rsi],r10
	inc rdi
	inc rsi
	jmp .loopStart
.loopEnd:
	pop r10
	pop rdx

	mov rsp, rbp
	pop rbp
	ret