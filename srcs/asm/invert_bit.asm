section .text

global _invert_bit

;rdi - value, rsi - bit number
_invert_bit:
	mov al, 1
	mov cx, si
	shl al, cl
	xor ax, di
	ret