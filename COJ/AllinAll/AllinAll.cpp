#include <stdio.h>
#include <stdlib.h>

int getSize(char A[]) {
    int cont = 0;
    for(int i = 0; A[i] != '\0'; i++) {
        cont++;
    }      
    return cont;
}

bool isEncoded(char O[], char E[]) {
    bool value = false;
    int cont = 0, i = 0, j = 0, temp = 0;
    for(i; O[i] != '\0'; i++) {       
        for(j = temp; E[j] != '\0'; j++) {            
            if (E[j] == O[i]) {
                temp = j+1;
                cont++;               
                break;
            }
        }

    }

    if (cont == getSize(O)) {
        value = true;
    }
    
    return value;
}

int main() {
    char original[100], encoded[100];
    while(scanf("%s%s", original, encoded) != EOF) {
        if (isEncoded(original, encoded)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }      
    }
    return 0;
}
