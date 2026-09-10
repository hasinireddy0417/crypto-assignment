#include <stdio.h>
#include <string.h>
#include <ctype.h>

void column_encrypt(char *text, char *result, int key[], int n) {
    char matrix[100][20];
    int len = strlen(text);
    int rows = len / n;
    int pos = 0;
    int order, col, r, c;

    for (r = 0; r < rows; r++)
        for (c = 0; c < n; c++)
            matrix[r][c] = text[r * n + c];

    for (order = 1; order <= n; order++) {
        for (col = 0; col < n; col++) {
            if (key[col] == order) {
                for (r = 0; r < rows; r++)
                    result[pos++] = matrix[r][col];
            }
        }
    }

    result[pos] = '\0';
}

void column_decrypt(char *text, char *result, int key[], int n) {
    char matrix[100][20];
    int len = strlen(text);
    int rows = len / n;
    int pos = 0;
    int order, col, r, c;

    for (order = 1; order <= n; order++) {
        for (col = 0; col < n; col++) {
            if (key[col] == order) {
                for (r = 0; r < rows; r++)
                    matrix[r][col] = text[pos++];
            }
        }
    }

    pos = 0;

    for (r = 0; r < rows; r++)
        for (c = 0; c < n; c++)
            result[pos++] = matrix[r][c];

    result[pos] = '\0';
}

int valid_key(int key[], int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        if (key[i] < 1 || key[i] > n)
            return 0;

        for (j = i + 1; j < n; j++) {
            if (key[i] == key[j])
                return 0;
        }
    }

    return 1;
}

int main() {
    char message[500];
    char clean[500];
    char first[500];
    char encrypted[500];
    char second[500];
    char decrypted[500];
    int key1[20], key2[20];
    int n, i, j = 0;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i]))
            clean[j++] = toupper((unsigned char)message[i]);
    }

    clean[j] = '\0';

    printf("Enter number of columns: ");
    scanf("%d", &n);

    if (n < 2 || n > 20) {
        printf("Number of columns must be between 2 and 20.\n");
        return 0;
    }

    printf("Enter first key: ");
    for (i = 0; i < n; i++)
        scanf("%d", &key1[i]);

    printf("Enter second key: ");
    for (i = 0; i < n; i++)
        scanf("%d", &key2[i]);

    if (!valid_key(key1, n) || !valid_key(key2, n)) {
        printf("Invalid key. Use each number from 1 to %d exactly once.\n", n);
        return 0;
    }

    int len = strlen(clean);

    while (len % n != 0) {
        clean[len++] = 'X';
        clean[len] = '\0';
    }

    column_encrypt(clean, first, key1, n);
    column_encrypt(first, encrypted, key2, n);

    printf("Encrypted: %s\n", encrypted);

    column_decrypt(encrypted, second, key2, n);
    column_decrypt(second, decrypted, key1, n);

    printf("Decrypted: %s\n", decrypted);

    return 0;
}