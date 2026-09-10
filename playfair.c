#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_matrix(char *key, char matrix[5][5]) {
    int used[26] = {0};
    int row = 0, col = 0;
    int i;
    char ch;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

void find_pos(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepare_playfairtext(char *input, char *output) {
    int i, j = 0;
    char ch;

    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha((unsigned char)input[i])) {
            ch = toupper(input[i]);

            if (ch == 'J')
                ch = 'I';

            output[j++] = ch;
        }
    }

    output[j] = '\0';

    j = 0;

    for (i = 0; output[i] != '\0'; i++) {
        if (output[i] == output[i + 1]) {
            memmove(&output[i + 1], &output[i], strlen(&output[i]) + 1);
            output[i + 1] = 'X';
        }
    }

    if (strlen(output) % 2 != 0)
        strcat(output, "X");
}

void process_playfairtext(char *text, char matrix[5][5], int decrypt) {
    int i;
    int r1, c1, r2, c2;
    char a, b;

    for (i = 0; text[i] != '\0'; i += 2) {
        a = text[i];
        b = text[i + 1];

        find_pos(matrix, a, &r1, &c1);
        find_pos(matrix, b, &r2, &c2);

        if (r1 == r2) {
            if (!decrypt) {
                text[i] = matrix[r1][(c1 + 1) % 5];
                text[i + 1] = matrix[r2][(c2 + 1) % 5];
            } else {
                text[i] = matrix[r1][(c1 + 4) % 5];
                text[i + 1] = matrix[r2][(c2 + 4) % 5];
            }
        }
        else if (c1 == c2) {
            if (!decrypt) {
                text[i] = matrix[(r1 + 1) % 5][c1];
                text[i + 1] = matrix[(r2 + 1) % 5][c2];
            } else {
                text[i] = matrix[(r1 + 4) % 5][c1];
                text[i + 1] = matrix[(r2 + 4) % 5][c2];
            }
        }
        else {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

int main() {
    char key[100];
    char message[256];
    char prepared[256];
    char encrypted[256];
    char matrix[5][5];
    int i, j;

    printf("Enter key: ");
    scanf("%s", key);

    getchar();

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    create_matrix(key, matrix);
    prepare_playfairtext(message, prepared);

    strcpy(encrypted, prepared);

    process_playfairtext(encrypted, matrix, 0);

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    printf("\nEncrypted: %s\n", encrypted);

    process_playfairtext(encrypted, matrix, 1);

    printf("Decrypted: %s\n", encrypted);

    return 0;
}