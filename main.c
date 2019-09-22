#include "spell.c"
#include "dictionary.h"
#include "dictionary.c"


int main(int argc, char* argv[])
{

	if (argc!= 3) return 0;

	hashmap_t hashtable[HASH_SIZE];

	load_dictionary(argv[1], hashtable);

         char*misspelled[MAX_MISSPELLED];
	 FILE *fp = fopen(argv[2], "r");
	 int num_misspelled = check_words(fp, hashtable, misspelled);

	 for (int i = 0; i < num_misspelled; i++)
	 {
             printf("%s \n", misspelled[i]);
          
	 }
		 
         return 1;
}
