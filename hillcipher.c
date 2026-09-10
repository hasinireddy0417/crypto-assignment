#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a) {
    int i;
    a = (a % 26 + 26) % 26;

    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

void encrypt_hilltext(char *text, int key[2][2]) {
    int i, x, y;
    int len = strlen(text);

    for (i = 0; i < len; i += 2) {
        x = toupper(text[i]) - 'A';

        if (i + 1 < len)
            y = toupper(text[i + 1]) - 'A';
        else
            y = 'X' - 'A';

        text[i] = (key[0][0] * x + key[0][1] * y) % 26 + 'A';
        text[i + 1] = (key[1][0] * x + key[1][1] * y) % 26 + 'A';
    }
}

void decrypt_hilltext(char *text, int key[2][2]) {
    int i, x, y;
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int inverse = mod_inverse(det);
    int a = key[1][1] * inverse % 26;
    int b = -key[0][1] * inverse % 26;
    int c = -key[1][0] * inverse % 26;
    int d = key[0][0] * inverse % 26;
    int len = strlen(text);

    b = (b + 26) % 26;
    c = (c + 26) % 26;

    for (i = 0; i < len; i += 2) {
        x = text[i] - 'A';
        y = text[i + 1] - 'A';

        text[i] = (a * x + b * y) % 26 + 'A';
        text[i + 1] = (c * x + d * y) % 26 + 'A';
    }
}

int main() {
    char message[256];

    int key[2][2] = {
        {3, 3},
        {2, 5}
    };

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] == ' ')
            memmove(&message[i], &message[i + 1], strlen(&message[i]));
    }

    if (strlen(message) % 2 != 0)
        strcat(message, "X");

    encrypt_hilltext(message, key);
    printf("Encrypted: %s\n", message);

    decrypt_hilltext(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}