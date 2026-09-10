#include <stdio.h>
#include <string.h>

void encode_railfence(char *text, char *result, int rails) {
    int len = strlen(text);
    int row = 0;
    int direction = 1;
    int index = 0;
    int i;

    for (i = 0; i < len; i++) {
        result[index++] = text[i];

        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;

        row += direction;
    }

    result[index] = '\0';
}

void decode_railfence(char *text, char *result, int rails) {
    int len = strlen(text);
    int pattern[256];
    int count[256] = {0};
    int pos[256];
    int row = 0;
    int direction = 1;
    int i, j, index = 0;

    for (i = 0; i < len; i++) {
        pattern[i] = row;
        count[row]++;

        if (row == 0)
            direction = 1;
        else if (row == rails - 1)
            direction = -1;

        row += direction;
    }

    pos[0] = 0;

    for (i = 1; i < rails; i++)
        pos[i] = pos[i - 1] + count[i - 1];

    for (i = 0; i < len; i++) {
        result[i] = text[pos[pattern[i]]++];
    }

    result[len] = '\0';
}

int main() {
    char message[256];
    char encrypted[256];
    char decrypted[256];
    int rails;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    if (rails < 2) {
        printf("Number of rails must be at least 2.\n");
        return 0;
    }

    encode_railfence(message, encrypted, rails);
    printf("Encrypted: %s\n", encrypted);

    decode_railfence(encrypted, decrypted, rails);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}