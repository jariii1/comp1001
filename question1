; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ; data segment
	; define your variables here
  array DWORD 10, 20, 30, 40 ; define an array of DWORDs
  
.code ; code segment

main PROC ; main procedure
	; write your assembly code here
  mov eax, [array + TYPE array * 3]; store the third element into eax
  mov ebx, 3; stores the multiplier into ebx
  mul ebx; multiply ebx and eax and store the result in eax
  mov ecx, 6; stores divider
  div ecx ; divides the product and stores it into eax
  mov [array + TYPE array * 3], eax; stores the result into the last element of the array
  
	INVOKE ExitProcess, 0 ; call exit function
  
main ENDP ; exit main procedure
END main  ; stop assembling
