#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de función en ensamblador
extern int validar_comando(const char*);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s \"comando\"\n", argv[0]);
        return 1;
    }

    char* comando = argv[1];

    // Validar comando
    if (!validar_comando(comando)) {
        printf("Comando no permitido.\n");
        return 1;
    }

    // Construir y ejecutar el comando SSH
    char full_cmd[300];
    snprintf(
        full_cmd, sizeof(full_cmd),
        "ssh -i /home/andres/Descargas/keys/id_rsa.pem ubuntu@3.138.123.82 'cd ova-web && %s' 2>&1 > resultado_comando.txt",
        comando
    );

    int res = system(full_cmd);
    printf("Comando ejecutado con código: %d\n", res);

    return 0;
}
