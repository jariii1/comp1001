.global _start
.text
_start:
    // write(1, message, 14)
    mov x0, #1              // stdout
    ldr x1, =message        // pointer to string
    mov x2, #14             // length of string
    mov x16, #4             // syscall number for write
    svc #0x80               // make the system call

    // exit(0)
    mov x0, #0
    mov x16, #1             // syscall number for exit
    svc #0x80

.data
message:
    .ascii "Hello, world!\n"
