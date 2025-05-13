#include "App_Aplicacion.h"
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validar_comando(const char *cmd) {
    const char *permitidos[] = {"git", "touch", "mkdir", "ls", "cat", "cd", "rm"};
    int num_comandos = sizeof(permitidos) / sizeof(permitidos[0]);

    for (int i = 0; i < num_comandos; ++i) {
        if (strncmp(cmd, permitidos[i], strlen(permitidos[i])) == 0) {
            if (strncmp(cmd, "cd", 2) == 0) {
                if (strstr(cmd, "..") != NULL || strchr(cmd, '/') != NULL) {
                    return 0; // cd .. o cd /no/permitido no son válidos
                }
            }
            return 1;
        }
    }

    return 0;
}

JNIEXPORT jstring JNICALL Java_App_Aplicacion_ejecutarComandosGit
  (JNIEnv *env, jobject obj, jstring ip, jstring rutaKey, jstring comando) {

    const char *ipStr = (*env)->GetStringUTFChars(env, ip, NULL);
    const char *keyStr = (*env)->GetStringUTFChars(env, rutaKey, NULL);
    const char *cmdStr = (*env)->GetStringUTFChars(env, comando, NULL);

    const char *rutaDir = "ova-web";  // Carpeta fija

    if (!validar_comando(cmdStr)) {
        (*env)->ReleaseStringUTFChars(env, ip, ipStr);
        (*env)->ReleaseStringUTFChars(env, rutaKey, keyStr);
        (*env)->ReleaseStringUTFChars(env, comando, cmdStr);
        return (*env)->NewStringUTF(env, "Comando no permitido");
    }

    char full_cmd[2048];
    snprintf(full_cmd, sizeof(full_cmd),
             "ssh -i %s ubuntu@%s 'cd %s && %s' 2>&1",
             keyStr, ipStr, rutaDir, cmdStr);

    FILE *fp = popen(full_cmd, "r");
    if (!fp) {
        (*env)->ReleaseStringUTFChars(env, ip, ipStr);
        (*env)->ReleaseStringUTFChars(env, rutaKey, keyStr);
        (*env)->ReleaseStringUTFChars(env, comando, cmdStr);
        return (*env)->NewStringUTF(env, "Error al ejecutar el comando");
    }

    char resultado[4096];
    size_t total = 0;
    while (fgets(resultado + total, sizeof(resultado) - total, fp) != NULL) {
        total = strlen(resultado);
        if (total >= sizeof(resultado) - 1) break;
    }
    pclose(fp);

    (*env)->ReleaseStringUTFChars(env, ip, ipStr);
    (*env)->ReleaseStringUTFChars(env, rutaKey, keyStr);
    (*env)->ReleaseStringUTFChars(env, comando, cmdStr);

    return (*env)->NewStringUTF(env, resultado);
}
