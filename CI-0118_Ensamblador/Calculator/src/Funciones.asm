; Funciones.asm - MASM x64 Version
.CODE                   ; Code segment

; Declare functions as public
PUBLIC suma
PUBLIC resta
PUBLIC multiplicacion
PUBLIC division

; int suma(int a, int b)
suma PROC
    mov rax, rcx    ; First parameter in RCX (Windows x64 calling convention)
    add rax, rdx    ; Second parameter in RDX
    ret
suma ENDP

; int resta(int a, int b)
resta PROC
    mov rax, rcx    ; First parameter in RCX
    sub rax, rdx    ; Subtract second parameter (RDX) from first (RCX)
    ret
resta ENDP

; int multiplicacion(int a, int b)
multiplicacion PROC
    mov rax, rcx    ; First parameter in RCX
    imul rax, rdx   ; RAX = RCX * RDX (signed multiplication)
    ret
multiplicacion ENDP

; int division(int a, int b)
division PROC
    mov rax, rcx    ; Dividend in RAX (first parameter)
    mov r8, rdx     ; Divisor in R8 (avoid conflict with RDX)
    cqo             ; Sign-extend RAX into RDX:RAX
    idiv r8         ; Divide RDX:RAX by R8 (signed division)
    ret
division ENDP

END
