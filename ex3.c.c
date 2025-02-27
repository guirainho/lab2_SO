#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

void closeFiles(int src, int dest) {
    if (close(src) == -1) {
        perror("Erro ao fechar o arquivo de origem");
        exit(EXIT_FAILURE);
    }
    if (close(dest) == -1) {
        perror("Erro ao fechar o arquivo de destino");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int srcFile, destFile;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    srcFile = open("lab2_ex3_origem.txt", O_RDONLY);
    if (srcFile == -1) {
        perror("Erro ao abrir o arquivo de origem");
        exit(EXIT_FAILURE);
    }

    destFile = open("lab2_ex3_destino.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFile == -1) {
        perror("Erro ao abrir/criar o arquivo de destino");
        close(srcFile);
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = read(srcFile, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytesRemaining = bytesRead;
        char *bufferPtr = buffer;  

        while (bytesRemaining > 0) {
            bytesWritten = write(destFile, bufferPtr, bytesRemaining);
            if (bytesWritten == -1) {
                perror("Erro ao escrever no arquivo de destino");
                closeFiles(srcFile, destFile);
            }
            bytesRemaining -= bytesWritten;
            bufferPtr += bytesWritten;
        }
    }

    if (bytesRead == -1) {
        perror("Erro ao ler o arquivo de origem");
        closeFiles(srcFile, destFile);
    }

    closeFiles(srcFile, destFile);
    return 0;
}
