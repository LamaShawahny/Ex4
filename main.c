#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>


#define NUM_LETTERS ((int)26)
typedef struct node{
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    int isEndOfWord;
} node;

void insert(node* root, char* key)
{
    node* p = root;
    int i = 0;
    int lengh = strlen(key);
    int j = 0;
    for (i = 0; i < lengh; i++)
    {
        j = (int)key[i] - 97;
        if (p->children[i] == NULL)
        {
            node* newP = NULL;
            newP = (node*)malloc(sizeof(node));
            if (newP == NULL)
            {
                int k = 0;
                newP->isEndOfWord = 0;
                newP->count = 0;
                for (k = 0; k < NUM_LETTERS; k++)
                {
                    newP->children[k] = NULL;
                }
                p->children[j] = newP;
                p->children[j]->letter = key[i];
            }
            p = p->children[j];
        }
        p->count = p->count + 1;
        p->isEndOfWord = 1;
    }


}


void print(node* root, char* key, int level)
{
    node* p = root;
    int i = 0;
    if (p == NULL)
    {
        return;
    }
    if (p->isEndOfWord == 1)
    {
        *(key + level) = '\0';
        printf("%s\t%ld \n", key, p->count);
    }
    for (i = 0; i < NUM_LETTERS; i++)
    {
        if (p->children[i] != NULL)
        {
            *(key + level) = p->children[i]->letter;
            print((p->children[i]), key, level + 1);
        }
    }
}
void freeAllTrie(node* root)
{
    node* p = root;
    int i = 0;
    for (i = 0; i < NUM_LETTERS; i++)
    {
        if (p->children[i] != NULL)
        {
            freeAllTrie((p->children[i]));  //The recursion
        }
    }
    free(p);
}


void bulidTrie(int maxlen, char* text) {
    node* root = NULL;
    root = (node*)malloc(sizeof(node));
    if (root)  //pNode!=NULL i.e the malloc Succeeded
    {
        int i = 0;
        root->isEndOfWord = 0;
        root->count = 0;
        for (i = 0; i < NUM_LETTERS; i++) {
           root->children[i] = NULL;
        }
    }
    int i = 0;
    char ch = text[i];
    while (ch != '\0')
    {
        char* word = (char*)malloc(sizeof(char) * maxlen);
        while (ch != ' ' && ch != '\0')
        {
            word = word + ch;
            ch = text[i];
            i++;
        }
        insert(root, word);
        i++;     free(word);
    }
    i = 0;
    ch = text[i];
    while (ch != '\0')
    {
        char* word = (char*)malloc(sizeof(char) * maxlen);
        while (ch != ' ' && ch != '\0')
        {
            word = word + ch;
            ch = text[i];
            i++;
        }
        print(root, word, 0);
        i++;
        free(word);
    }
    freeAllTrie(root);
}

char CToS(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        ch = (int)ch + 32;
    return ch;
}

int main(int argc, char* argv[]) {
    int maxlen = 1;
    char* mytext = "";
    char ch = getchar();
    while (ch != EOF)
    {
        int c = 1;
        while (ch != '\n' && ch != '\0' && ch != ' ' && ch != '\t')
        {
            ch = CToS(ch);
            mytext = mytext + ch;
            ch = getchar();
            c++;
        }
        if (c > maxlen)
            maxlen = c;
        mytext = mytext +' ' ;
        ch = getchar();
    }
    mytext = mytext + '\0';
    bulidTrie(maxlen,mytext);


    return 0;
}



