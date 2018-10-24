#include <string.h>
#include <stdio.h>
class rock {
    public:char typeName[20];
    public:bool exist = true;
    int hardness;
    
    public:int destroy() {
        if(hardness <= 0) {
            delete(this);
            return 0;
        } else {
            return 1;
        }
    }

    public:int mine(int value) {
        if(hardness > 0) {
            hardness = hardness - value;
        } else {
            destroy();
        }
    }

    public:void create(int hardnessInput, char typeNameInput[]) {
        strcpy(typeName, typeNameInput);
        hardness = hardnessInput;
    }

    public:void listValues() {
        if(hardness > 0) {
            printf("%s: %d\n", typeName, hardness);
        } else {
            printf("La piedra ya esta destruida.\n");
        }
    }

};

class pick {
    int hardness;

    public:void create(int hardnessInput) {
        hardness = hardnessInput;
    }

    public:void mine(rock toMine) {
        if(toMine.exist) {
            toMine.mine(hardness);
        } else {
            printf("La roca esta destruida.");
        }
    }
};