#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (10)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'0')

// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    int prefixes;
    trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};

// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
    trie_node_t *pNode = NULL;

    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));

    if( pNode )
    {
        int i;

        pNode->value = 0;
        pNode->prefixes=0;

        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }

    return pNode;
}

// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *pCrawl;

    pTrie->count++;
    pCrawl = pTrie->root;

    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
        if( !pCrawl->children[index] )
        {
            pCrawl->children[index] = getNode();
        }
        pCrawl = pCrawl->children[index];
        ++(pCrawl->prefixes);
    }

    // mark last node as leaf
    pCrawl->value = pTrie->count;
}
int countPrefixes(trie_t *pTrie, char key[]){
    trie_node_t *pCrawl;
    pCrawl=pTrie->root;
    int index,i,len;
    len=strlen(key);
    for(i=0;i<len;++i){
        int index=CHAR_TO_INDEX(key[i]);
        if(pCrawl->children[index]==NULL) return 0;
        pCrawl=pCrawl->children[index];
    }
    return pCrawl->prefixes;
}
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    int i,t,n;
    scanf("%d",&t);
    while(t--){
    trie_t trie;
    scanf("%d",&n);
    char keys[n][11];

    initialize(&trie);

    // Construct trie
    for(i = 0; i < n; i++)
    {
        scanf("%s", keys[i]);
        insert(&trie, keys[i]);
    }
    int valid=1;
    for(i=0;i<n&&valid;++i)
    {
        if(countPrefixes(&trie, keys[i])>1) valid=0;
    }
    if(!valid) printf("NO\n");
    else printf("YES\n");
    }
    return 0;
}

