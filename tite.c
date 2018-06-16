#include <stdio.h>
#include<stdlib.h>
#include <math.h>


#define PARENT(i) ((i-1) / 2)
#define NUM_NODES 15
#define LINE_WIDTH 70

int main() {
    int tree[NUM_NODES]={46, 24, 62, 18, 26, 55, 74, 12, 0, 0, 0, 0, 58,0, 0};
    int print_pos[NUM_NODES];
    int i, j, k, pos, x=1, level=0;

    print_pos[0] = 0;
    for(i=0,j=1; i<NUM_NODES; i++,j++) {
        pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);

        for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':' ');
        
        if (tree[i]==0){
            printf("N");
        }
        else{
        printf("%d",tree[i]);
        }
        print_pos[i] = x = pos+1;
        if (j==pow(2,level)) {
            printf("\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    return 0;
}
