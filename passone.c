#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr, start, length;
    FILE *fiel1, *fiel2, *fiel3, *fiel4;
    fiel1 = fopen("input", "r");
    fiel2 = fopen("optab", "r");
    fiel3 = fopen("symtab", "w");
    fiel4 = fopen("intermediate", "w");

    if (fiel1 == NULL || fiel2 == NULL || fiel3 == NULL || fiel4 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(fiel1, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fiel4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fiel1, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }
    while (strcmp(opcode, "END") != 0) {
        fprintf(fiel4, "%d\t", locctr);
        if (strcmp(label, " ") != 0) {
            fprintf(fiel3, "%s\t%d\n", label, locctr);
        }

        rewind(fiel2); // Reset optab file pointer to beginning
        fscanf(fiel2, "%s\t%s", code, mnemonic);

        while (!feof(fiel2)) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                break;
            }
            fscanf(fiel2, "%s\t%s", code, mnemonic);
        }

        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operand) - 3; // Assuming BYTE uses 'C' or 'X' format
        }

        fprintf(fiel4, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fiel1, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(fiel4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;
    printf("Length of the code: %d\n", length);

    fclose(fiel1);
    fclose(fiel2);
    fclose(fiel3);
    fclose(fiel4);
    return 0;
}
