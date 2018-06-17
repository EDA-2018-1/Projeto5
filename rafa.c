#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>

typedef struct no
{
    int valor;
    struct no * esquerda;
    struct no * direita;
}No;
int AddToArray(No* node, int arr[], int i);
//Prototipos
int menu();
void LevelOrder(No*);

//Arvore
//Inserir
void insercao();
void inserir(struct no** , int);
No * adicionar(int);

void loadTreeFromFile();
//Excluir
void exclusao();
void excluir(No **, int);

//funcoes
int nivel(No*, int, int);
int altura(No*);
// int comparar(No*, No*);
int contarFolhas(No *);
int contarNos(No *);

//balancear
int perfeitamenteBalanceada(No*);
int balanceada(No*);
void balancear(No**);
//Imprecao
void preOrder(No *);
void postOrder(No* );
void inOrder(No* );
void preOrdem(No *);

bool isFull(No *);

struct no * arvore;
struct no * comp;

void searchValue();
void printTree(No* p, int);

int main ()
{
    int valor;
    arvore = NULL;
    comp = NULL;

    while(1)
    {
        switch(menu())
        {
            case 1:
                loadTreeFromFile();
                break;
            case 2:
                //showTree();
                // LevelOrder(arvore);
                PrintTree(arvore, 0);
                break;
            case 3:
                if (isFull(arvore))
                    printf("Está cheia!\n");
                 else
                    printf("Não está cheia!\n");
                break;
          case 4:
               // searchValue();
                break;
            case 5:
                printf("Altura da arvore: %d", altura(arvore));
                break;
            case 6:
                exclusao();
            case 7:
                inOrder(arvore);
            case 8:
                preOrder(arvore);
                break;
            case 9:
                postOrder(arvore);
                break;
            case 10:
                    balancear(&arvore);
            case 11:
//                return 0;
                break;
        }
    }
}

int menu ()
{
    int opcao;

    printf("\n\n1)loadTreeFromFile\n");
    printf("2)showTree\n");
    printf("3)isFull\n");
    printf("4)searchValue\n");
    printf("5)getHeight\n");
    printf("6)removeValue\n");
    printf("7)printInOrder\n");
    printf("8)printPreOrder\n");
    printf("9)printPostOrder\n");
    printf("10)balanceTree\n");
    printf("11)EXIT\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

void loadTreeFromFile()
{
    int numarquivo = 0;
    printf("\n\nInforme o arquivo entre 1 e 6: ");
    scanf("%d", &numarquivo);
    char filename[10];

    switch(numarquivo){
        case 1:
            strcpy(filename, "bst1.txt");
            break;
        case 2:
            strcpy(filename, "bst2.txt");
            break;
        case 3:
            strcpy(filename, "bst3.txt");
            break;
        case 4:
            strcpy(filename, "bst4.txt");
            break;
        case 5:
            strcpy(filename, "bst5.txt");
            break;
        case 6:
            strcpy(filename, "bst6.txt");
            break;
    }

    printf("\nArquivo escolhido: %s", filename);
    FILE *file;
    int valor;

    file = fopen(filename, "r");

    if (file == NULL){
        printf("erro no arquivo");
    return;
    }
    else{
        printf("\nDados do arquivo: ");
        while (fscanf(file, "%d", &valor) != EOF){
            inserir(&arvore, valor);
            printf(" %d", valor);
        }
    }
}

//Insere um VALOR na arvore
void inserir(No ** raiz, int valor)
{
    if(*raiz == NULL)
    {
        No * no = adicionar(valor);
        *raiz = no;
    }
    else
    {
        if(valor < (*raiz)->valor)
            inserir(&(*raiz)->esquerda, valor);
        else if(valor > (*raiz)->valor)
            inserir(&(*raiz)->direita, valor);
    }
}

No * adicionar(int valor)
{
    No * add = (No*)malloc(sizeof(No));

    add->valor = valor;
    add->esquerda = NULL;
    add->direita = NULL;

    return add;
}

//Insere um NO na arvore
void inserirNo(No ** no, No * add)
{
    if(*no == NULL)
    {
        *no = add;
    }
    else
    {
        if(add->valor < (*no)->valor)
            inserirNo(&(*no)->esquerda, add);
        else if(add->valor > (*no)->valor)
            inserirNo(&(*no)->direita, add);
    }
}


//Exclusao

void exclusao()
{
    int valor;
    printf("\nInforme valor para exlcuir: ");
    scanf("%d", &valor);

    excluir(&arvore, valor);
}

void excluir(No ** raiz, int valor)
{
    if(*raiz == NULL)
    {
        printf("\nNao foi possivel excluir.\n");
    }
    else if((*raiz)->valor == valor)
    {
        No * excluir = *raiz;
        No * auxAnt = *raiz;

        int esq = altura((*raiz)->esquerda);
        int dir = altura((*raiz)->direita);

        if(excluir->esquerda == NULL && excluir->direita == NULL)
        {
            *raiz = NULL;
        }
        else if(esq > dir)
        {
            *raiz = (*raiz)->esquerda;
            while((*raiz)->direita != NULL)
            {
                auxAnt = *raiz;
                *raiz = (*raiz)->direita;
            }
            auxAnt->direita = NULL;

            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->esquerda);
            if(excluir->direita != NULL)
                inserirNo(&(*raiz), excluir->direita);
        }
        else if( esq <= dir)
        {
            *raiz = (*raiz)->direita;
            while((*raiz)->esquerda != NULL)
            {
                auxAnt = *raiz;
                *raiz = (*raiz)->esquerda;
            }
            if(excluir != auxAnt)
                auxAnt->esquerda = NULL;

            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->esquerda);
            if(excluir->esquerda != NULL)
                inserirNo(&(*raiz), excluir->direita);
        }
        free(excluir);
    }
    else
    {
        if(valor < (*raiz)->valor)
            excluir( &(*raiz)->esquerda, valor);
        else if(valor > (*raiz)->valor)
            excluir( &(*raiz)->direita, valor);
    }

}

//Funcoes
//Altura
int altura(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        return 1 +(esq > dir ? esq : dir);
    }
}

//Nivel
int nivel(No * no, int niv, int valor)
{
    if(no == NULL)
        return 0;
    else
    {
        if(valor == no->valor)
            return niv;
        else
        {
            int n1 = nivel(no->esquerda, niv+1, valor);
            int n2 = nivel(no->direita, niv+1, valor);
            return  n1 > n2 ? n1 : n2;
        }
    }
}

//contarFolhas
int contarFolhas(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        if(no->esquerda == NULL && no->direita == NULL)
            return 1;
        else
        return 0 + contarFolhas(no->esquerda) + contarFolhas(no->direita);
    }
}

//ContarNos
int contarNos(No * no)
{
    if(no == NULL)
        return 0;
    else
    {
        return 1 + contarNos(no->esquerda) + contarNos(no->direita);
    }
}

//balancear
int perfeitamenteBalanceada(No * no)
{

    if(altura(no) == 0)
    {
        return 0;
    }
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if((esq - dir > 1) || (esq - dir < -1))
            return 1;
        else
        {
            int bEsq = perfeitamenteBalanceada(no->esquerda);
            int bDir = perfeitamenteBalanceada(no->direita);

            return 0 + bEsq + bDir;
        }
    }
}

int balanceada(No * no)
{
    if(altura(no) == 0)
    {
        return 1;
    }
    else
    {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if((esq - dir > 1) || (esq - dir < -1))
            return 0;
        else
            return 1;
    }

}

void balancear(No ** no)
{

    if(*no == NULL)
        return;

    balancear(&(*no)->esquerda);
    balancear(&(*no)->direita);

    while(!balanceada(*no))
    {
        preOrdem(arvore);
        printf("\n\nNO: %d\n", (*no)->valor);
        int esq = altura((*no)->esquerda);
        int dir = altura((*no)->direita);

        No * add = *no;

        if(esq > dir)
        {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->esquerda->valor);
            *no = (*no)->esquerda;
            add->esquerda = NULL;
            inserirNo(&(*no), add);
        }
        else if(esq < dir)
        {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->direita->valor);
            *no = (*no)->direita;
            add->direita = NULL;
            inserirNo(&(*no), add);
        }
    }
}

//Impressao

void preOrdem(No * aux)
{
    if(aux)
    {
        printf("%d ", aux->valor);
        preOrdem(aux->esquerda);
        preOrdem(aux->direita);
    }
    else
        printf("NULL ");

}

void preOrder(No* arvore) {
    if(arvore != NULL) {
        printf("%d ", arvore->valor);
        preOrdem(arvore->esquerda);
        preOrdem(arvore->direita);
    }
}

void inOrder(No* arvore){
    if(arvore != NULL){
        inOrder(arvore->esquerda);
        printf("%d ", arvore->valor);
        inOrder(arvore->direita);
    }
}

void postOrder(No* arvore){
    if(arvore != NULL){
        postOrder(arvore->esquerda);
        postOrder(arvore->direita);
        printf("%d ", arvore->valor);
    }
}

void extensao(No * aux, int nivel)
{
    if(aux)
    {
        if(altura(aux) == nivel)
        {
            printf("%d\t", aux->valor);
        }
        extensao(aux->esquerda, nivel);
        extensao(aux->direita, nivel);
    }
}

bool isFull (No* root)
{
    if (root == NULL)
        return true;

    if (root->esquerda == NULL && root->direita == NULL)
        return true;

    if ((root->esquerda) && (root->direita))
        return (isFull(root->esquerda) && isFull(root->direita));
    return false;
}

// #define LINE_WIDTH 70
// #define PARENT(i) ((i-1) / 2)

// void LevelOrder(No* root) {
//     int i = 0;
//     int* tree; // Here we just need to take an array of maximum size
//     int h = altura(arvore);
//     int aux;
//     int size = ((pow(2, h+1))-1);

//     tree = calloc(size, sizeof(int));

//     AddToArray(root, tree, i);

//     int print_pos[size];
//     int j, k, pos, x=1, level=0;

//     print_pos[0] = 0;
//     for(i=0,j=1; i<size; i++,j++) {
//         pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);

//         for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':' ');
        
//         if (tree[i]==0){
//             printf("N");
//         }
//         else{
//         printf("%d",tree[i]);
//         }
//         print_pos[i] = x = pos+1;
//         if (j==pow(2,level)) {
//             printf("\n");
//             level++;
//             x = 1;
//             j = 0;
//         }
//     }
//     printf("\n");
//     return;
// }

// int AddToArray(No* node, int arr[], int i)
// {
//      if(node == NULL){
//           return i;
//      }

//     arr[i] = node->valor;
//     node->esquerda != NULL ? (i = AddToArray(node->esquerda, arr, i+1)) : (i = AddToArray(0, arr, i+1)); 
//     node->direita != NULL ? (i = AddToArray(node->direita, arr, i+1)) : (i = AddToArray(0, arr, i+1)); 
//     return i++;
// }

#define PARENT(i) ((i-1) / 2)
#define LINE_WIDTH 70

void LevelOrder(No* arvore)
{
    int h = altura(arvore);
    int aux;
    int NUM_NODES = ((pow(2, h+1))-1);
    int tree[NUM_NODES];
    int print_pos[NUM_NODES];

    for (aux=1; aux<=h; aux++)
    {
        printGivenLevel(arvore, aux);
        printf("\n");
    }

    // int i, j, k, pos, x=1, level=0;

    // print_pos[0] = 0;
    // for(i=0,j=1; i<NUM_NODES; i++,j++) {
    //     pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);

    //     for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':' ');
        
    //     if (tree[i]==0){
    //         printf("N");
    //     }
    //     else{
    //     printf("%d",tree[i]);
    //     }
    //     print_pos[i] = x = pos+1;
    //     if (j==pow(2,level)) {
    //         printf("\n");
    //         level++;
    //         x = 1;
    //         j = 0;
    //     }
    // }

}
 
/* Print nodes at a given level */
void printGivenLevel(No* arvore, int level)
{
    int tabs;
    if (arvore == NULL)
        return;
    if (level == 1){
        tabs = 4*level;
        printf("%*d ", tabs, arvore->valor);
    }
        
    else if (level > 1)
    {
        printGivenLevel(arvore->esquerda, level-1);
        printGivenLevel(arvore->direita, level-1);
    }
}

void PrintTree(No * tp, int spaces) {
  int i;
  if (tp != NULL) {
    PrintTree(tp->direita, spaces + 4);
    for (i = 0; i < spaces; i++) {
      printf(" ");
    }
    printf("%d\n", tp-> valor);
    PrintTree(tp->esquerda, spaces + 4);
  }
  printf("\n");
}
