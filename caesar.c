#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt_text(char *text, int shift) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        }
        else if (islower((unsigned char)text[i])) {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
    }
}

void decrypt_text(char *text, int shift) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) {
            text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
        }
        else if (islower((unsigned char)text[i])) {
            text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
        }
    }
}

int main() {
    char message[256];
    int shift;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter shift value: ");
    scanf("%d", &shift);

    encrypt_text(message, shift);
    printf("Encrypted: %s\n", message);

    decrypt_text(message, shift);
    printf("Decrypted: %s\n", message);

    return 0;
}