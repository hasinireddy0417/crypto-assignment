#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encode_message(char *text, char *key) {
    int i, j = 0;
    int key_len = strlen(key);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (isupper((unsigned char)text[i]))
                text[i] = ((text[i] - 'A') + (tolower(key[j % key_len]) - 'a')) % 26 + 'A';
            else
                text[i] = ((text[i] - 'a') + (tolower(key[j % key_len]) - 'a')) % 26 + 'a';

            j++;
        }
    }
}

void decode_message(char *text, char *key) {
    int i, j = 0;
    int key_len = strlen(key);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (isupper((unsigned char)text[i]))
                text[i] = ((text[i] - 'A') - (tolower(key[j % key_len]) - 'a') + 26) % 26 + 'A';
            else
                text[i] = ((text[i] - 'a') - (tolower(key[j % key_len]) - 'a') + 26) % 26 + 'a';

            j++;
        }
    }
}

int main() {
    char message[256];
    char key[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter key: ");
    scanf("%s", key);

    encode_message(message, key);
    printf("Encrypted: %s\n", message);

    decode_message(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}