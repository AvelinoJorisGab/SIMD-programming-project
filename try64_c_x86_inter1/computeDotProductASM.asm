section .text
default rel
bits 64
global computeDotProductASM

computeDotProductASM:
	push rbp
	mov rbp, rsp
	sub rsp, 16

	mov r12, rdx
	mov r13, r8
	xor r15, r15

simpleLoop:
	cmp rcx, 0
	jle end

	movsd xmm0, qword [r12]
	mulsd xmm0, qword [r13]
	addsd xmm0, qword [rbp-16]
	movsd qword [rbp-16], xmm0

	add r12, 8
	add r13, 8

	sub rcx, 1
	jmp simpleLoop

end:
	movsd xmm0, qword [rbp-16]
	mov rax, xmm0
	add rsp, 16
	pop rbp
	ret