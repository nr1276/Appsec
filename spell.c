// Naresh Ramlogan, nr1276

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
//#include "dictionary.c"

int hashsize = 0;



int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[])
{
  int num_misspelled = 0; // track the number of misspelled items
  int wordlength = 0; // track wordlength
  int newlength = 0; // track new length of word after stripping chars
  char c = '\0';  // row read in from file
  char *word = malloc(sizeof(char)*(LENGTH+1));
  char *tempword;
  int i = 0;
  int source = 0; // used to strip charcters before and after word
  int destination = 0; // used to strip characters before and after word

  // Read Row

  while (c != EOF)
  {  
     while (EOF!=(c=getc(fp)) && ( (c == '\n') || (c == ' ')));
     if ( c == EOF ) return num_misspelled;
     i = 0;
     do {
        if(i <= LENGTH)
	{
	   word[i++] = c;
        }
	else
	{
           i++;
	}

     } while(EOF!=(c=fgetc(fp)) && (c != ' ') && (c != '\n'));


     if(i > (LENGTH+1))
     {
       word[LENGTH+1] = '\0';
     }
     else
     {     
       word[i] = '\0';
       // printf(" %s \n", word);
     }      

       wordlength = strlen(word);
       newlength = wordlength;
       source = 0;
       destination = 0;

       while (word[source] != '\0') 
       {
          // Strip spcial chars in word
	  if ((source == 0 || source == (wordlength -1)) && !isalpha(word[source]))
          {  
     
            ++source;
            --newlength;
          }
          else
          {
            word[destination] = word[source];
            ++source;
            ++destination;
          }

  
       }   
       word[newlength] = '\0';   

       //printf("%s\n ", word); 
       // Check the word against hashtable    
       if (!check_word(word, hashtable))
       {
        //printf("%s %d \n", word, num_misspelled;
	tempword = malloc(sizeof(char)*(LENGTH+1));
	strcpy(tempword,word);
        misspelled[num_misspelled] = tempword;
//	printf("%s \n", misspelled[num_misspelled]);
	num_misspelled++;	
        

        }
     

  }
 
   free(word);
  //printf("%d :blahah", num_misspelled);
  return num_misspelled;
}




bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
  char row[LENGTH+1];
  FILE *wordlist = fopen(dictionary_file, "r");


  
  if(!wordlist)
  { 
    return false;
  }
 
  // Read line
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

    // If not collision, add it to the hashtable
    if (hashtable[hashval] == NULL)
    {
      hashentry->next = NULL;
      hashtable[hashval] = hashentry;
      hashsize++;   
    }
    else
    {
      // if collision, add new node
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
  if (wordlength > LENGTH+1)
  {
    return 1;
  }


  //check to ensure word is not number
  for (int i = 0; i < wordlength; i++)
  {
    if ('0' <= word[i] && word[i] <= '9')
    {
      return 1;
    }	    
  }	  


  //printf("word: %s ", word);
  // check word against hash table 
  int index = hash_function(word);
  node *tempnode = hashtable[index]; 
  while ( (tempnode != NULL)) //Check hastable to see if it is not null
  {

    //printf("%s ", tempnode->word); 
    if (strcmp(word, tempnode->word) == 0)
    {
       //printf("%s ", word); 
       return 1; 
      
    }
  
    else
    {
   
  
      tempnode = tempnode->next; 
    }
  } 

  
  // Non Caps Word
  char word2[LENGTH+1];

  //find lowercase word 
  for (int i = 0; i < wordlength; i++)
  {
    if ('A' <= word[i] && word[i] <= 'Z')
    {
      word2[i] = word[i] + 32;
    }
    else
    {
      word2[i] = word[i];
    }

  }
  word2[wordlength] = '\0';
  
  //printf("word2: %s ", word2);
  // check lowercase word against hash table
  index = hash_function(word2);
  tempnode = hashtable[index]; 
  while ( (tempnode != NULL)) //Check hastable to see if it is not null
  {
    
    if (strcmp(word2, tempnode->word) == 0)
    {
  
       //printf("%s ", word2); 
       return 1; 
      
    }
  
    else
    {
   
      tempnode = tempnode->next; 
    }
  } 


  return 0;
}

