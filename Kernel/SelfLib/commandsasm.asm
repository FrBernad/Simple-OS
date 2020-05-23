GLOBAL getRTCsecs
GLOBAL getRTCmins
GLOBAL getRTChours

section .text

getRTCsecs:
	push rbp
    mov rbp, rsp		;armado de stackframe

	mov rax, 0			;limpio el registro por las dudas
	mov al, 0x00
	out 70h, al			;solicito lo que hay en al (segundos)
	in al, 71h			;meto en eax la rta

	mov rsp, rbp
    pop rbp
	ret

getRTCmins:
	push rbp
    mov rbp, rsp		;armado de stackframe

	mov rax, 0			;limpio el registro por las dudas
	mov al, 0x02
	out 70h, al			;solicito lo que hay en al (minutos)
	in al, 71h			;meto en eax la rta

	mov rsp, rbp
    pop rbp
	ret

getRTChours:
	push rbp
    mov rbp, rsp		;armado de stackframe

	mov rax, 0 			;limpio el registro por las dudas
	mov al, 0x04
	out 70h, al			;solicito lo que hay en al (horas)
	in al, 71h			;meto en eax la rta

	mov rsp, rbp
    pop rbp
	ret