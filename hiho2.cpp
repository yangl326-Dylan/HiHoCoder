#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TREE_WIDTH 26
#define WORDLENMAX 10

struct trie_node_st {
	int cnt; //the count of the word
	int pass; //add a count for the part-include 
	struct trie_node_st *next[TREE_WIDTH];
};

static struct trie_node_st root={0,{NULL}};

static int insert(const char *word){
	int i;
	struct trie_node_st *curr, *newnode;

	if(word[0]=='\0')
		return 0;

	curr = &root;
	for(i=0; ;++i){
		if(word[i]=='\0')
			break;
		curr->pass++;//count;
		if(curr->next[word[i]-'a'] == NULL){
			newnode = (struct trie_node_st *)malloc(sizeof(struct trie_node_st));
			memset(newnode,0,sizeof(struct trie_node_st));
			//newnode->pass = 1; //initialized with 1
			curr->next[word[i]-'a'] = newnode;
		}
		curr = curr->next[word[i]-'a'];
	}
	curr->cnt++;
	return 0;
}
static int count(const char *word){
	int i,ret = 0;
	struct trie_node_st *curr;

    if(word[0] == '\0')
		return 0;

	curr = &root;

	for(i=0; ;i++){
		if(word[i] == '\0')
			return ret;
		if(curr->next[word[i]-'a'] == NULL) //no such prefix
			return 0;
		ret = curr->next[word[i]-'a']->pass+curr->next[word[i]-'a']->cnt;
		curr = curr->next[word[i]-'a'];
	}
}

int main(){
	char word[11];
	int ret;
    int N,M;
    int i=0;
	scanf("%d",&N);

	while(i<N){
		scanf("%s",word);
		insert(word);
		i++;
	}

	i=0;
	scanf("%d",&M);
	while(i<M){
		scanf("%s",word);
		printf("%d\n",count(word));
		i++;
	}
}
 	