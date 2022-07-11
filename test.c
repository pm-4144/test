
#include "mk_file.h"
//#include "perm.h"
//#include "cycle_shape.h"


#define NUM 0
#define SIZE 1000






//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
static void putFileLine(FILE* fp)
{
    char buf[80];
    long pos = ftell( fp ); 
    printf("%ld : ",pos);

    if( fgets( buf, sizeof(buf), fp ) == NULL ){
        fputs( "ファイルからの読み込みに失敗しました。\n", stderr );
        exit( EXIT_FAILURE );
    }

    // 末尾の改行文字を取り除く
    char* p = strchr( buf, '\n' );
    if( p != NULL ){
        *p = '\0';
    }

    puts( buf );
}

int main(int argc,char **argv){

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mk_array_num_cc();
MALLOC_ALL();

*fact = 1;
for(int i = 1; i <= n_prime; i++ )
        *(fact + i) = i*(*(fact + i - 1));



int *b = NULL;
if ((b = MALLOC_ARRAY(n_prime, int)) == NULL)
	exit( EXIT_FAILURE );

printf("%d\n",term);

int **a;
PP_MALLOC(a, term, int);

for(int i=0;i<10;i++)
for(int j=0;j<10;j++)
*(*(a+i)+j)=i*j;
for(int i=0;i<10;i++){
for(int j=0;j<10;j++)
printf("%3d",*(*(a+i)+j));
printf("\n");}

PP_FREE(a, term);

free(b);
FREE_ALL();

return 0;}



/*
%%%     #include<stdio.h>
%%%     #include <stdlib.h>
%%%     #include <errno.h>
%%%     #include <string.h>
%%%
%%%     #define SIZE 100
%%%
%%%     typedef enum { Jan, Feb, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC} month;
%%%
%%%     typedef struct {
%%%         unsigned char dd;
%%%         month mm;
%%%         unsigned yy;
%%%     } date;
%%%
%%%     #define MALLOC_ARRAY(number, type) \
%%%         ((type *)malloc((number) * sizeof(type)))
%%%
%%%     int main() {
%%%         date *d = NULL;
%%%
%%%         errno = 0;
%%%         d = MALLOC_ARRAY(SIZE, date);
%%%         if (!d) {
%%%             perror("malloc");
%%%             exit(EXIT_FAILURE);
%%%         }
%%%
%%%         free(d);
%%%         exit(EXIT_SUCCESS);
%%%     }
*/
