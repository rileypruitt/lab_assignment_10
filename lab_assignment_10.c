#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* children[26];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* tree = (struct Trie*)malloc(sizeof(struct Trie));
    if (tree) {
        tree->count = 0;
        for(int i = 0 ; i < 26; i++)
        {
            tree->children[i] = NULL;
        }
    }
    return tree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* temp = pTrie;
    int len = strlen(word);

    for(int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!temp->children[index]) 
        {
            temp->children[index] = createTrie();
        }
        temp = temp->children[index];
    }
    temp->count++;
}

// computes the number of occurrences of the word
int numberOfOccurrences(struct Trie *pTrie, char *word)
{
    struct Trie* temp = pTrie;
    int len = strlen(word);

    for(int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL)
            return 0;
        temp = temp->children[index];
    }

    return temp->count;
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++) 
    {
        if (pTrie->children[i] != NULL) 
        {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// This function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int numOfWords;
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &numOfWords);
    for(int i = 0; i < numOfWords; i++)
    {
        pInWords[i] = (char*)malloc(256 *sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return numOfWords;
}

int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n",inWords[i]);
    }
    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
