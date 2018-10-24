#include <string.h>
#include <stdio.h>
#include "Objects.h"

int main() {
    rock piedra;
    pick pico;
    int hardness;
    char name[20];
    char option[20];
    char type[20];
    while((scanf("%s", option)) && (strcmp(option, "exit") == 0)){
        if(strcmp(option, "create") == 0) {
            scanf("%s", type);
            if(strcmp(type, "rock") == 0) {
                scanf("%s %d", name, hardness);
                piedra.create(hardness, name);
            }
            
            if(strcmp(type, "pick") == 0) {
                scanf("%d", hardness);
                pico.create(hardness);
            }
        }
    }
    
    return 0;
}
