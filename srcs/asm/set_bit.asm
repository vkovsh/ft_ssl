section .text

global _set_bit

;rdi - value, rsi - bit number
_set_bit:
	mov rax, 1
	mov cx, si
	shl rax, cl
	or rax, rdi
	ret