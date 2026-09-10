#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void my_encrypt(const char *msg, const char key[ALPHABET_SIZE], char *out) {
    int i;
    for (i = 0; msg[i] != '\0'; i++) {
        if (isalpha((unsigned char)msg[i])) {
            int is_upper = isupper((unsigned char)msg[i]);
            int idx = tolower((unsigned char)msg[i]) - 'a';
            char enc_char = key[idx];
            out[i] = is_upper ? toupper((unsigned char)enc_char) : tolower((unsigned char)enc_char);
        } else {
            out[i] = msg[i];
        }
    }
    out[i] = '\0';
}

void my_decrypt(const char *msg, const char key[ALPHABET_SIZE], char *out) {
    int i, j;
    for (i = 0; msg[i] != '\0'; i++) {
        if (isalpha((unsigned char)msg[i])) {
            int is_upper = isupper((unsigned char)msg[i]);
            char c = tolower((unsigned char)msg[i]);
            int idx = -1;
            for (j = 0; j < ALPHABET_SIZE; j++) {
                if (tolower((unsigned char)key[j]) == c) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                out[i] = msg[i];
            } else {
                char dec_char = 'a' + idx;
                out[i] = is_upper ? toupper((unsigned char)dec_char) : tolower((unsigned char)dec_char);
            }
        } else {
            out[i] = msg[i];
        }
    }
    out[i] = '\0';
}

int main() {
    char message[256];
    char encrypted[256], decrypted[256];
    char key[ALPHABET_SIZE] = "qwertyuiopasdfghjklzxcvbnm";

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    my_encrypt(message, key, encrypted);
    my_decrypt(encrypted, key, decrypted);

    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}