#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char buffer[128];
    int fd = open("lab2_ex1.txt", O_RDONLY);
    
    if (fd == -1) {
        printf("Erro de abertura\n");
        return 1;
    }

    ssize_t bytesLidos = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesLidos == -1) {
        printf("Erro de leitura\n");
        close(fd);
        return 1;
    }

    buffer[bytesLidos] = '\0';
    printf("Conteúdo:\n%s\n", buffer);

    close(fd);
    return 0;
}
