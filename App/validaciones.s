.global validar_comando
.section .text


validar_comando:
    push %rbp
    mov %rsp, %rbp

    # Comparar los primeros 3 caracteres para "git"
    movzbl (%rdi), %eax
    cmp $'g', %al
    jne check_touch
    movzbl 1(%rdi), %eax
    cmp $'i', %al
    jne check_touch
    movzbl 2(%rdi), %eax
    cmp $'t', %al
    je valido

check_touch:
    movzbl (%rdi), %eax
    cmp $'t', %al
    jne check_nano
    movzbl 1(%rdi), %eax
    cmp $'o', %al
    jne check_nano
    movzbl 2(%rdi), %eax
    cmp $'u', %al
    jne check_nano
    movzbl 3(%rdi), %eax
    cmp $'c', %al
    jne check_nano
    movzbl 4(%rdi), %eax
    cmp $'h', %al
    je valido

check_nano:
    movzbl (%rdi), %eax
    cmp $'n', %al
    jne check_mkdir
    movzbl 1(%rdi), %eax
    cmp $'a', %al
    jne check_mkdir
    movzbl 2(%rdi), %eax
    cmp $'n', %al
    jne check_mkdir
    movzbl 3(%rdi), %eax
    cmp $'o', %al
    je valido

check_mkdir:
    movzbl (%rdi), %eax
    cmp $'m', %al
    jne invalido
    movzbl 1(%rdi), %eax
    cmp $'k', %al
    jne invalido
    movzbl 2(%rdi), %eax
    cmp $'d', %al
    jne invalido
    movzbl 3(%rdi), %eax
    cmp $'i', %al
    jne invalido
    movzbl 4(%rdi), %eax
    cmp $'r', %al
    je valido

invalido:
    movl $0, %eax
    pop %rbp
    ret

valido:
    movl $1, %eax
    pop %rbp
    ret


