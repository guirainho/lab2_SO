#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fileDescriptor;
    char buffer[128];
    ssize_t bytesRead;
    int lineCount = 0;
    char *currentChar;

    fileDescriptor = open("lab2_ex2.txt", O_RDONLY);
    if (fileDescriptor < 0) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        currentChar = buffer;
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                lineCount++;
            }
        }
    }

    if (bytesRead < 0) {
        perror("Erro ao ler o arquivo");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }

    printf("Número total de linhas: %d\n", lineCount);

    if (close(fileDescriptor) < 0) {
        perror("Erro ao fechar o arquivo");
        exit(EXIT_FAILURE);
    }

    return 0;
}
