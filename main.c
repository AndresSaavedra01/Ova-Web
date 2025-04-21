#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de función en ensamblador
extern int validar_comando(const char*);

int main(int argc, char* argv[]) {
    const char* rutaKey = "ruta de la llavae de la maquina aws";
    const char* rutaDirectorio = "directorio de la maquina aws donde se va ejecutar los comandos";
    const char* ipAWS = "ip publica de la maquina";

    if (argc < 2) {
        printf("Uso: %s \"comando\"\n", argv[0]);
        return 1;
    }

    const char* comando = argv[1];

    // Validar comando
    if (!validar_comando(comando)) {
        printf("Comando no permitido.\n");
        return 1;
    }

    // Construir y ejecutar el comando SSH
    char full_cmd[512];
    snprintf(full_cmd, sizeof(full_cmd),
             "ssh -i %s ubuntu@%s 'cd %s && %s' > resultado_comando.txt 2>&1",
             rutaKey, ipAWS, rutaDirectorio, comando);

    int res = system(full_cmd);
    printf("Comando ejecutado con código: %d\n", res);

    return 0;
}
