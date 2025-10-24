; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ; data segment
	; define your variables here
  
  array_A DWORD 3, 2, 3, 1, 7, 5, 0, 8, 9, 2; this is array A
  array_B DWORD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; this is array B
  array_C DWORD 1, 3, 2, 5, 4, 6, 0, 4, 5, 8; this is array C
  
.code ; code segment

main PROC ; main procedure
	; write your assembly code here
 

  
	INVOKE ExitProcess, 0 ; call exit function
  
main ENDP ; exit main procedure
END main  ; stop assembling
