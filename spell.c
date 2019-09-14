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
  int num_misspelled = 0;

  char word[LENGTH+1];
  while( fscanf(fp, "%s", word) != EOF)
  {
    if(!check_word(word, hashtable))
    {
      misspelled[num_misspelled] = word;
      num_misspelled++;
    }	    
  }


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
    // Read word from line and strip spaces
    char *word = row + strspn(row, "\t"); 
    word[strcspn(word, " \t\r\n")] = '\0';
    if (*word == '\0' || *word == '#' || *word == ';')
    {
      continue;
    }
  
    node *hashentry = malloc(sizeof(node));
    int hashval = hash_function(word);
    strcpy(hashentry->word, (word));


    if (hashtable[hashval] == NULL)
    {
      hashentry->next = NULL;
      hashtable[hashval] = hashentry;
      hashsize++;   
    }
    else
    {
      
	    
      hashentry->next = hashtable[hashval];
      hashtable[hashval] = hashentry;
      hashsize++;
	  
    }	
       
      
  }
  fclose(wordlist);
  return 1;
}


bool check_word(const char* word, hashmap_t hashtable[])
{
  int wordlength = strlen(word);
  //check to ensure word is not number
  for (int i = 0; i < wordlength; i++)
  {
    if ('0' <= word[i] && word[i] <= '9')
    {
      printf("Not a string");
      return 0;
    }	    
  }	  

  char word2[LENGTH + 1];
  //convert string to lowercase
  for (int i = 0; i < wordlength; i++)
  {
     if ('A' <= word[i] && word[i] <= 'Z')
     {
       
        word2[i] = (word[i]) + 32;

     }
     else
     {
       word2[i] = word[i];
     }

  }



  int index = hash_function(word2);
  node *tempnode = hashtable[index]; 
  printf("%s", tempnode->word);
  int found = 0;
  while ((found == 0) && (tempnode != NULL)) //Check hastable to see if it is not null
  {
    if (strcmp(word2, tempnode->word) == 0)
    {
      printf ("%s", word2);
      found = 1; 
    }
    else
    {
      tempnode = tempnode->next; 
    }
  }  

  return found;
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

  check_word(argv[2], hashtable);

}
