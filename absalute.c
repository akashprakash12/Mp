#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fiele1;
    int i, j, staraddr1;
    char line[50], name[50], staraddr[200];

    fiele1 = fopen("ab", "r");
    if (fiele1 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fiele1, "%s", line);

    // Extract name starting from position 2 until '^' is encountered
    for (i = 2, j = 0; line[i] != '^'; i++, j++) {
        name[j] = line[i];
    }
    name[j] = '\0';
    printf("Name from object file: %s\n", name);

    while (!feof(fiele1)) {
        fscanf(fiele1, "%s", line);

        if (line[0] == 'T') {
            // Extract start address from the line
            for (i = 2, j = 0; line[i] != '^'; i++, j++) {
                staraddr[j] = line[i];
            }
            staraddr[j] = '\0';
            staraddr1 = atoi(staraddr);
            i += 2;  // Move index past the starting address and length

            while (line[i] != '$') {
                if (line[i] != '^') {
                    printf("00%d\t%c%c\n", staraddr1, line[i], line[i + 1]);
                    staraddr1++;
                    i += 2;
                } else {
                    i++;
                }
            }
        } else if (line[0] == 'E') {
            break;
        }
    }

    fclose(fiele1);
    return 0;
}
