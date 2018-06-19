#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>

typedef struct no {
    int valor;
    struct no * esquerda;
    struct no * direita;
} No;

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
No* excluir(No*, int);

//funcoes
int nivel(No*, int, int);
bool imprimePai(No*, int);
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

void searchValue(No*, int);
void printLevelOrder(No*);
void printGivenLevel(No*, int);

int main (){
    int valorPesquisa;
    int valor;
    arvore = NULL;
    comp = NULL;

    while(1){
        switch(menu()){
            case 1:
                system("clear");
                loadTreeFromFile();
                break;
            case 2:
                system("clear");
                printTree(arvore, 0);
                break;
            case 3:
                system("clear");
                if (isFull(arvore))
                    printf("Está cheia!\n");
                 else
                    printf("Não está cheia!\n");
                break;
            case 4:
                system("clear");
                printf("Digite o numero que deseja pesquisar: ");
                scanf("%d", &valorPesquisa);
                searchValue(arvore, valorPesquisa);
                break;
            case 5:
                system("clear");
                printf("Altura da arvore: %d", altura(arvore));
                break;
            case 6:
                system("clear");
                exclusao();
                break;
            case 7:
                system("clear");
                inOrder(arvore);
                break;
            case 8:
                system("clear");
                preOrder(arvore);
                break;
            case 9:
                system("clear");
                postOrder(arvore);
                break;
            case 10:
                system("clear");
                if(balanceada(arvore))
                    printf("\na arvore esta balanceada\n\n");
                 else
                    balancear(&arvore);
                break;
            case 11:
                system("clear");
                return 0;
                break;
        }
    }
}

int menu (){
    int opcao;

    printf("\n\n1) loadTreeFromFile\n");
    printf("2) showTree\n");
    printf("3) isFull\n");
    printf("4) searchValue\n");
    printf("5) getHeight\n");
    printf("6) removeValue\n");
    printf("7) printInOrder\n");
    printf("8) printPreOrder\n");
    printf("9) printPostOrder\n");
    printf("10) balanceTree\n");
    printf("11) EXIT\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

void loadTreeFromFile(){
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
    arvore = NULL;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("erro no arquivo");
    return;
    } else {
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
    if (*raiz == NULL) {
        No * no = adicionar(valor);
        *raiz = no;
    } else {
        if (valor < (*raiz)->valor)
            inserir(&(*raiz)->esquerda, valor);
        else if (valor > (*raiz)->valor)
            inserir(&(*raiz)->direita, valor);
    }
}

No * adicionar(int valor){
    No * add = (No*)malloc(sizeof(No));

    add->valor = valor;
    add->esquerda = NULL;
    add->direita = NULL;

    return add;
}

//Insere um NO na arvore
void inserirNo(No ** no, No * add) {
    if (*no == NULL) {
        *no = add;
    } else {
        if(add->valor < (*no)->valor)
            inserirNo(&(*no)->esquerda, add);
        else if(add->valor > (*no)->valor)
            inserirNo(&(*no)->direita, add);
    }
}


//Exclusao

void exclusao() {
    int valor;
    printf("\nInforme valor para exlcuir: ");
    scanf("%d", &valor);

    arvore = excluir(arvore, valor);
}

No* minValueNode(No* node) {
    No* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->esquerda != NULL)
        current = current->esquerda;

    return current;
}

No* excluir(No* root, int key) {
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->valor)
        root->esquerda = excluir(root->esquerda, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->valor)
        root->direita = excluir(root->direita, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->esquerda == NULL) {
            No *temp = root->direita;
            free(root);
            return temp;
        } else if (root->direita == NULL) {
            No *temp = root->esquerda;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        No* temp = minValueNode(root->direita);
 
        // Copy the inorder successor's content to this node
        root->valor = temp->valor;
 
        // Delete the inorder successor
        root->direita = excluir(root->direita, temp->valor);
    }
    return root;
}

//Funcoes
//Altura
int altura(No * no) {
    if (no == NULL)
        return 0;
    else { 
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);
        return 1 +(esq > dir ? esq : dir);
    }
}

//Nivel
int nivel(No * no, int niv, int valor) {
    if (no == NULL)
        return 0;
    else {
        if (valor == no->valor)
            return niv;
        else {
            int n1 = nivel(no->esquerda, niv+1, valor);
            int n2 = nivel(no->direita, niv+1, valor);
            return  n1 > n2 ? n1 : n2;
        }
    }
}

void searchValue(No* root, int num) {
    int nivel = 1;
    No *pai = NULL, *irmao = NULL;
  
    if (root == NULL) {
        printf("\nValor nao encontrado.\n\n");
    }

    while (root != NULL) {
        if (root->valor == num)
            break;

        nivel++;
        pai = root;

        if (root->valor > num){
            irmao = root->direita;
            root = pai->esquerda;
        } else {
            irmao = root->esquerda;
            root = pai->direita;
        }
    }

    printf("Nivel: %d\n", nivel);
    if (pai != NULL) {
        printf("O pai eh: %d\n", pai->valor);
    }
    if (irmao != NULL) {
        printf("O irmao eh: %d\n", irmao->valor);
    } else {
        printf("Nao tem irmao\n");
    }
}

//contarFolhas
int contarFolhas(No * no) {
    if (no == NULL)
        return 0;
    else {
        if (no->esquerda == NULL && no->direita == NULL)
            return 1;
        else
            return 0 + contarFolhas(no->esquerda) + contarFolhas(no->direita);
    }
}

//ContarNos
int contarNos(No * no) {
    if (no == NULL)
        return 0;
    else
        return 1 + contarNos(no->esquerda) + contarNos(no->direita);
}

//balancear
int perfeitamenteBalanceada(No * no) {
    if (altura(no) == 0) {
        return 0;
    } else {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if ((esq - dir > 1) || (esq - dir < -1))
            return 1;
        else {
            int bEsq = perfeitamenteBalanceada(no->esquerda);
            int bDir = perfeitamenteBalanceada(no->direita);
            return 0 + bEsq + bDir;
        }
    }
}

int balanceada(No * no) {
    if(altura(no) == 0)
        return 1;
    else {
        int esq = altura(no->esquerda);
        int dir = altura(no->direita);

        if((esq - dir > 1) || (esq - dir < -1))
            return 0;
        else
            return 1;
    }
}

void balancear(No ** no) {
    if (*no == NULL)
        return;

    balancear(&(*no)->esquerda);
    balancear(&(*no)->direita);

    while(!balanceada(*no)) {
        preOrdem(arvore);
        printf("\n\nNO: %d\n", (*no)->valor);
        int esq = altura((*no)->esquerda);
        int dir = altura((*no)->direita);

        No * add = *no;

        if (esq > dir) {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->esquerda->valor);
            *no = (*no)->esquerda;
            add->esquerda = NULL;
            inserirNo(&(*no), add);
        } else if (esq < dir) {
            printf("TROCANDO NO: %d pelo NO: %d\n", (*no)->valor, (*no)->direita->valor);
            *no = (*no)->direita;
            add->direita = NULL;
            inserirNo(&(*no), add);
        }
    }
}

//Impressao
void preOrdem(No * aux) {
    if (aux) {
        printf("%d ", aux->valor);
        preOrdem(aux->esquerda);
        preOrdem(aux->direita);
    } else
        printf("NULL ");
}

void preOrder(No* arvore) {
    if (arvore != NULL) {
        printf("%d ", arvore->valor);
        preOrder(arvore->esquerda);
        preOrder(arvore->direita);
    }
}

/* Print in-order */
void inOrder(No* arvore) {
    if (arvore != NULL) {
        inOrder(arvore->esquerda);
        printf("%d ", arvore->valor);
        inOrder(arvore->direita);
    }
}
void postOrder(No* arvore) {
    if (arvore != NULL){
        postOrder(arvore->esquerda);
        postOrder(arvore->direita);
        printf("%d ", arvore->valor);
    }
}

void extensao(No * aux, int nivel) {
    if (aux) {
        if (altura(aux) == nivel)
            printf("%d\t", aux->valor);
        extensao(aux->esquerda, nivel);
        extensao(aux->direita, nivel);
    }
}

bool isFull (No* root) {
    if (root == NULL)
        return true;
    if (root->esquerda == NULL && root->direita == NULL)
        return true;
    if ((root->esquerda) && (root->direita))
        return (isFull(root->esquerda) && isFull(root->direita));
    return false;
}

int rec[1000006];
void printTree(No* curr,int depth) {
    int i;
    
    if (curr==NULL) {
        return;
    }
    
    printf("\t");
    for(i=0; i<depth; i++) {
        if (i==depth-1)
            printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
        else
            printf("%s   ",rec[i]?"\u23B8":"  ");
    }
    
    printf("%d\n",curr->valor);
    rec[depth]=1;
    printTree(curr->esquerda,depth+1);
    rec[depth]=0;
    printTree(curr->direita,depth+1);
}