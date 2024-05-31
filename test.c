# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <float.h>
# include <string.h>
# include <stdint.h>
# include <math.h>
# include <errno.h>
#include <time.h>
# include <stdio.h>

#define TEST(f,x) (*(f+(x)/16)&(1<<(((x)%16L)/2)))
#define SET(f,x) *(f+(x)/16)|=1<<(((x)%16L)/2)

#define MAX_RANGE              12000L    /* must be biger then 10000   org = 14010000     */
#define START_RANGE            70        /* must be biger then the lenght of AlpaNumericArry */
#define END_RANGE              MAX_RANGE-10000

static int test(unsigned char *f , unsigned long x){

	unsigned char c1 = (*(f+(x)/16));
	unsigned char c2 = 1<<(((x)%16L)/2);
	unsigned char c3 = c1 & c2;

	int i1 = c1;
	int i2 = c2;
	int i3 = c3;
	// printf("1.%c : %d\n", c1, i1);
	// printf("2.%c : %d\n", c2, i2);
	// printf("3.%c : %d\n", c3, i3);

	return i3;
}


static int set(unsigned char *f , unsigned long x){
	// *(f+(x)/16)|=1<<(((x)%16L)/2)
	unsigned char c1 = (*(f+(x)/16));
	unsigned char c2 = 1<<(((x)%16L)/2);
	unsigned char c3 = c1 |= c2;

	int i1 = c1;
	int i2 = c2;
	int i3 = c3;
	printf("1.%c : %d\n", c1, i1);
	printf("2.%c : %d\n", c2, i2);
	printf("3.%c : %d\n", c3, i3);

	int set = *(f+(x)/16)|=1<<(((x)%16L)/2);
	printf("set[%ld]:%d; f[%ld] = %d\n", x,set,x/16, f[x/16]);
	return *(f+(x)/16)|=1<<(((x)%16L)/2);
}

static unsigned long *Secsys_genPrimeNumbers()
{

/* Local Veriables *\
\* --------------- */

	unsigned char         *feld=NULL, *zzz;
	unsigned long         teste,maxSize ,mom, hits=1, count, allocSize, s=0, e=1;
	time_t                begin;
	static unsigned long  *pPrimeArray;
	int                   numInRange;

	maxSize = MAX_RANGE ;

	while (feld==NULL) {
		zzz = feld = (unsigned char*)malloc(allocSize=(((maxSize-=10000L)>>4)+1L));
	}

	//126 байт
  for (count=0; count<allocSize; count++) {
     *zzz++ = 0x00;
//	 printf("cnt[%ld]\n", count);
  }

	//returns the current calendar time (seconds since Jan 1, 1970)
	begin = time(NULL);
//	printf("begin:%ld\n", begin);

	int res = 0;
	teste = 1;
  while ((teste+=2) < maxSize) {
	test(feld, teste);

     if (!(res = TEST(feld, teste))) {
		//printf("[%ld] test:%d\n", teste, res);
		++hits;
		int i = 0;
		for (mom=3L*teste; mom<maxSize; mom+=teste<<1) {
			//printf("mom: %ld; teste:%ld\n", mom, teste);
			//set(feld, mom);
			SET (feld, mom);
			 //printf("feld[%ld] = %d\n", mom/16, feld[mom/16]);

		}

     }
	 else{
		//printf("EXCLDE[%ld] res:%d\n", teste, res);
	 }

	if(teste > 22)
		break;
  }

  	for(int i =0; i < allocSize; i++){
		//printf("feld[%d] = %d\n", i, feld[i]);
  	}

	s = START_RANGE ;
	e = END_RANGE ;
	//printf("hits:%ld\nstart range:%ld; end range:%ld\n", hits,s, e);
	count=s-2;
	 if (s%2==0)
	 	count++;

  pPrimeArray = (unsigned long *) malloc ( hits * sizeof(unsigned long));

  numInRange=0;

	//printf("count:%ld\n", count);
	while ((count+=2)<e) {
		res = test(feld, count);
		//printf("[%ld] mtest:%d\n", count, res);

		if (!(res=TEST(feld,count))){
			//printf("[%ld] test:%d\n", count, res);
			/* build an Arry of Primes */
			pPrimeArray[numInRange] = count ;
			//printf("pPrimeArray[%d] = %ld\n", numInRange, count);
			numInRange++;
		}
		if(numInRange > 10)
	 		break;

  }

	//printf("numInRange:%d\n", numInRange);
	free (feld);

  return(pPrimeArray);
}

static char SECAlpaNumericArry[]={ 'a','b','A','2','7','f','g','h','i','S','k','L','m','n','o','p','q','U','s','T','v','u','w','Z','y','Q',
                         'c','B','C','D','E','4','G','H','K','J','I','l','M','N','9','P','z','R','j','t','r','V','W','X','Y','x',
       '0','1','d','3','F','5','6','e','8','O','\0' };

static int Secsys_findCInAlphaNumAr(int  *cAlphaNumIndex, char c)
{
	int status=0, retIndex=0, alphaNumArLen=0;

	alphaNumArLen = strlen(SECAlpaNumericArry);


	while (retIndex < alphaNumArLen) {
		if (c == SECAlpaNumericArry[retIndex]) {
		 	break;
		}
     	retIndex++ ;
  	}

  if (retIndex == alphaNumArLen) {
     if (c == SECAlpaNumericArry[retIndex]) {
        *cAlphaNumIndex = retIndex;
 status = 1;
     } else {
 status = 0;
     }
  } else {
     *cAlphaNumIndex = retIndex;
     status = 1;
  }

  return (status);
}

static int SecShrinkArray( char *arr , int  len )
{
    len--;
    for(; len>=0 && arr[len] == ' '; len-- ) {
     ;
    }
	printf("len:%d\n", len);

    *(arr+len+1) = '\0';
	printf("arr new:%s\n", arr);

    return(1);
}

static int SecCheckArray( char *i_arr,
                   int   i_maxLen,
                int  *o_realLen )
{

 int status;

    if ( (int)strlen(i_arr) >= i_maxLen ) {
       if (i_arr[i_maxLen-1]==' ') {
          status = SecShrinkArray(i_arr, i_maxLen);
		  printf("CheckArray new i_arr: %s\n", i_arr);
          *o_realLen = strlen(i_arr);
       } else {
          *o_realLen = i_maxLen;
       }
    } else {
       *o_realLen = strlen(i_arr);
    }

    return(1);
}


static int SecDeCryptApi(char *i_String,
						char *o_String,
						int   i_varSize,
				unsigned long Key_Start_Index )
{

/* Local Veriables *\
\* --------------- */

  time_t        begin;
  unsigned long *pPrimeArray;
  char          *inputString;
  char         c,cryptInd[10];
  int status=0, primeIndex=0, inOutIndex=0, inputStringLen=0,
     newCAlphaNumIndex=0, cAlphaNumIndex=0, modeNum=0,
    rotateNum, randNum;

	if (status == 1) {
      strcpy(o_String , i_String);
   return(1);
  }

  pPrimeArray = Secsys_genPrimeNumbers();

  /* decrypr .... */
	i_varSize -- ;

	Secsys_findCInAlphaNumAr(&randNum , i_String[i_varSize ] );

	inputString = (char *)malloc((i_varSize+2)*sizeof(char));

	strcpy(inputString, i_String) ;
	status = SecCheckArray(inputString, i_varSize, &inputStringLen);

	memset(o_String,'\0', i_varSize);

	modeNum = strlen(SECAlpaNumericArry);

	primeIndex = Key_Start_Index ;

	primeIndex += randNum  ;

int test = 0;
	inOutIndex = 0;
	while (inOutIndex < inputStringLen) {
		c = inputString[inOutIndex];

		rotateNum = pPrimeArray[primeIndex];

		status = Secsys_findCInAlphaNumAr(&cAlphaNumIndex, c);

		if (status == 1) {
			test = rotateNum%modeNum;
			if (test <= cAlphaNumIndex) {
				newCAlphaNumIndex = cAlphaNumIndex - rotateNum%modeNum;
		} else {
			newCAlphaNumIndex = cAlphaNumIndex + modeNum - rotateNum%modeNum;
		}
		o_String[inOutIndex] = SECAlpaNumericArry[newCAlphaNumIndex];
	} else {
		o_String[inOutIndex] = c;
	}

     inOutIndex++;
     primeIndex++;
  }

  o_String[inOutIndex] = '\0' ;
/*
  printf("The decrypt was done in %ld secs.\n",time(NULL)-begin);
*/
	//free(inputString);
	free(pPrimeArray);
	return(1) ;

}


int		main(int ac, char **av)
{

	int		Key_Start_Index = 3;
	//char	*i_String = "d0xMrWU";
	char i_String[8] = "d0xMrWU";
	char *o_String;

	int i_varSize = strlen(i_String);

	o_String = (char*)malloc(i_varSize* sizeof(char));
	memset(o_String, 0, i_varSize);

	SecDeCryptApi(i_String, o_String, strlen(i_String), 1);

	//printf("decrypt:\n %s --> %s\n", i_String, o_String);





}
