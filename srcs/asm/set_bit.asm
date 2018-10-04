section .text

global _set_bit

;rdi - value, rsi - bit number
_set_bit:
	mov rbx, 1

;next:
	shl	rbx, 1
	;mov cl, si
	;dec rsi
	;jnz next
	or	rdi, rbx
	ret