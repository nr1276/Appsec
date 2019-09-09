// Naresh Ramlogan, nr1276

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.c"

int hashsize = 0;

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[])
{

}


bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
  char row[LENGTH+1];
  FILE *wordlist = fopen(dictionary_file, "r");

  if(!wordlist)
  { 
    return false;
  }


  while (fgets(row, sizeof row, wordlist) != NULL)
  {
    char *word = row + strspn(row, "\t"); 
    word[strcspn(word, " \t\r\n")] = '\0';
    if (*word == '\0' || *word == '#' || *word == ';')
    {
      continue;
    }

    node *hashentry = malloc(sizeof(node));
    int hashval = hash_function(word);
    strcpy(hashentry->word, (word));
    hashentry->next = hashtable[hashval];
    hashtable[hashval] = hashentry;
    hashsize++; 
  }  

  fclose(wordlist);
  return true;


}


bool check_word(const char* word, hashmap_t hashtable[])
{

  int index = hash_function(word);
  if (strcmp(word, hashtable[index]->word) != 0)
  {
    printf ("%s, %s\n", word, hashtable[index]->word);

  }  

}


int main(int argc, char** argv)
{

  if (argc != 3)
  {
    return 3;
  }
	  
  if (!(load_dictionary(argv[1], hashtable)))
  {
    return 1;
  }

  printf("loaded %d words \n", hashsize);
  check_word(argv[2],hashtable);
  return 0;

}
