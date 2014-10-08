#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

char *progn;

void usage(void)
{
  fprintf(stderr,"Usage: %s pattern\n",progn);
}

int pattern_match(char *pattern, char *str)
{
	int str_len = strlen(str);
	int pattern_len = strlen(pattern);
	int i = 0;

	for (i =0; i <str_len, i++){
		int escape_count = 0;
		int j =0;

		for ( j = 0;j <pattern_len; j++){
			int escaped = 0;
			int optional = 0;

			if pattern[j] == '\\') {
				j++;
				escaped_count++;
				escaped == 1;
			}
			
			if (i +(j - escape_count) > str_len){
			break;
			}
			
			if (j+1 < pattern_len && pattern[j+1] == '?')
			{
				optional = 1;
				if (pattern_match(&pattern[j+2}, &str[i + (j-escape_count)]) ==0 )
				return i;
			}
			
			if (!(pattern[j] == '.' && !escaped)){
			if pattern[j] != str[i+(j-escape_count)])
				break;
			}

			if optional ==1)
				j++;
		}
		if (j>= pattern_len)
		return i;
	}
	return -1;
}	
				

int main(int argc, char **argv)
{
  char line[MAXLINE];
  char *pattern;
  progn = argv[0];
  
  if(argc!=2) {
    usage();
    return EXIT_FAILURE;
  }
  pattern = argv[1];
  
  while(!feof(stdin) && !ferror(stdin)) {
    if(!fgets(line,sizeof(line),stdin)) {
      break;
    }
    if(pattern_match(pattern,line)) {
      printf("%s",line);
    }
  }
  if(ferror(stdin)) {
    perror(progn);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
