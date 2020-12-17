#include <stdio.h>

void prod(int prot[3][2], int deft[2][2]) {
    int i, j, tel[3][2];

    tel[0][0] = prot[0][0] * deft[0][0] + prot[0][1] * deft[1][0];
    tel[0][1] = prot[0][0] * deft[0][1] + prot[0][1] * deft[1][1];
    tel[1][0] = prot[1][0] * deft[0][0] + prot[1][1] * deft[1][0];
    tel[1][1] = prot[1][0] * deft[0][1] + prot[1][1] * deft[1][1];
    tel[2][0] = prot[2][0] * deft[0][0] + prot[2][1] * deft[1][0];
    tel[2][1] = prot[2][0] * deft[0][1] + prot[2][1] * deft[1][1];

    for (i=0; i<3; i++){
		printf("%d %d", tel[i][0], tel[i][1]);

        if (i<2) printf("\n");
    }
}

int main() {
    int prot[3][2], deft[2][2], i, j;

    for (i=0; i<3; i++) {
        for (j=0; j<2; j++) {
            scanf("%d", &prot[i][j]);
        }
    }

    for (i=0; i<2; i++) {
        for (j=0; j<2; j++) {
            scanf("%d", &deft[i][j]);
        }
    }

    prod(prot,deft);

    return 0;
}
