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
    mov esi, OFFSET array_A      ; base A
    mov edi, OFFSET array_B      ; base B
    mov ebp, OFFSET array_C      ; base C
    xor ecx, ecx                 ; i = 0

  ;for (i=0; i<10; i++){
    ;B[i] = (A[i]*2+1) + (C[i]*3+1) + (A[i]+C[i])/3;

    
  loop_start:
    cmp ecx, 10 ; start loop for i<10
    jpe loop_end

    ;a[i] + c[i] /3
    mov eax, [esi + ecx*4]       ; EAX = A[i]
    add eax, [ebp + ecx*4]       ; EAX = A[i] + C[i]
    xor edx, edx                 ; EDX:EAX is dividend for division
    mov ebx, 3
    div ebx                      ; EAX = (A+C)/3, EDX = remainder
    mov ebx, eax                 ; EBX = term3

    ;2*a[i] +1
    mov eax, [esi + ecx*4]       ; EAX = A[i]
    shl eax, 1                   ; EAX = A[i]*2
    add eax, 1                   ; EAX = 2*A[i] + 1

    ;3*c[i] +1  
    mov edx, [ebp + ecx*4]       ; EDX = C[i]
    lea edx, [edx*2 + edx + 1]   ; EDX = 3*C + 1

  ; store the results
    add eax, edx                 ; EAX = term1 + term2
    add eax, ebx                 ; EAX = term1 + term2 + term3
    mov [edi + ecx*4], eax       ; B[i] = result

    inc ecx                      ; i++
    jmp loop_start               ; repeat loop
  loop_end:
  
	INVOKE ExitProcess, 0 ; call exit function
  
main ENDP ; exit main procedure
END main  ; stop assembling
