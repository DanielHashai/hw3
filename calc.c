#include "calc.h"

int getGematriaCnt(char* str, int start, int end) {
	int curCnt = 0;
	int i;
	for (i = start; i <= end; i++) {
		int inc = (int)(((str[i] >= a) ? (str[i] - a) : (str[i] - A)) + 1);
		if (!IS_VALID(str[i])) continue;
		curCnt += inc;
	}
	return curCnt;
}

int getAtbashCnt(char* str, int start, int end) {
	int curCnt = 0;
	int i;
	for (i = start; i <= end; i++) {
		int inc = (int)(((str[i] >= a) ? (z-str[i]+1) : (Z-str[i]+1)));
		if (!IS_VALID(str[i])) continue;
		curCnt += inc;
	}
	return curCnt;
}

void getInput() {

	int termSet = 0, i;

	scanf("%s", word);
	wordGematriaCnt = getGematriaCnt(word, 0, strlen(word)-1);
	wordAtbashCnt = getAtbashCnt(word, 0, strlen(word)-1);
	for(i = 0; i < (strlen(word)); i++) {
		wordAtbash[i] = (word[i] == '\0') ? '\0' : ((word[i] >= a) ? (char)((z-word[i])+a) : (char)((Z-word[i]))+A);
		//printf("i %d word %c atbash %c (z-word[i])+a  %d\n", i,word[i], wordAtbash[i],(z-word[i])+a );
	}

	for(i = 0; i < (strlen(word)); i++) {
		if ((word[i] >= A) && (word[i] <= Z)) upperCnt[word[i]-A]++;
		if ((word[i] >= a) && (word[i] <= z)) lowerCnt[word[i]-a]++;
		if ((wordAtbash[i] >= A) && (wordAtbash[i] <= Z)) upperAtbCnt[wordAtbash[i]-A]++;
		if ((wordAtbash[i] >= a) && (wordAtbash[i] <= z)) lowerAtbCnt[wordAtbash[i]-a]++;
	}
	for(i = 0; i < (26); i++) {
	//	printf("\nupperCnt[%d] %d lowerCnt[%d] %d upperAtbCnt %d lowerAtbCnt %d",i, upperCnt[i],i, lowerCnt[i], upperAtbCnt[i], lowerAtbCnt[i]);
	}
//	printf("\n");
    
    while(~TEXT_OVERFLOW(0) && !termSet) {
        char in[WORD];
		char *termIndex = NULL;
		int textSize = 0;
		int i;

		//scanf("%s", in);
		fgets(in, TEXT, stdin);
		//printf("\n%s\n",in);

		textSize = strlen(in);

		termIndex = strchr(in, '~');
		if (termIndex != NULL) {
			termSet = 1;
			textSize = termIndex - in;
//	printf("termIndex %p ", termIndex);
		}

		if (~TEXT_OVERFLOW(textSize) && (textSize > 0)) {
			for(i = 0; i < textSize; i++) {
				text[textWrPtr+i] = in[i];
			}
			textWrPtr += textSize;
		//	printf("\ntextWrPtr %d textSize%d\n",textWrPtr,textSize);
		}
		else 
			break;

    }

	//printf("\ntext %s\n", text);
	//printf("\nword %s\n",word);
	//printf("\nwordAtbash %s\n",wordAtbash);
	//printf("\nwordGematria %d\n",wordGematriaCnt);
	//printf("\nwordAtbashCnt %d\n",wordAtbashCnt);
	//printf("\ntextWrPtr %d\n",textWrPtr);

	return;

}

void printGematria() {
	char *source = NULL;
	char *dest = NULL;
	int i, j;
	int firstPrintDone = 0;

	printf("Gematria Sequences: ");
	for(i = 0; i < textWrPtr; i++) {
		if (!IS_VALID(text[i])) continue;

		for(j = i; j < textWrPtr; j++) {
			int curGematria = getGematriaCnt(text, i,j);
			int size = (j-i)+1;
			if (curGematria < wordGematriaCnt)
				continue;

			if (curGematria > wordGematriaCnt)
				break;

			dest = (char *)(malloc((size + 1) * sizeof(char)));
			dest[size] = '\0'; 
			source = text + i;
			strncpy(dest, source, size);
			if (firstPrintDone) printf("~");
			printf("%s",dest);
			firstPrintDone = 1;
			break;
		}
	}

}

void printAtbash() {
	char *source = NULL;
	char *dest = NULL;
	int i, j, k;
	int firstPrintDone = 0;

	printf("Antbash Sequences: ");
	for(i = 0; i < textWrPtr; i++) {
		if (!IS_VALID(text[i])) continue;

		for(j = i; j < textWrPtr; j++) {
			char curAtbUpperCnt[26] = {0};
			char curAtbLowerCnt[26] = {0};
			int isAtbash = 1;
			int size = (j-i)+1;
			if (!IS_VALID(text[j])) break;
			for(k = i; k <= j; k++) {
				if ((text[k] >= A) && (text[k] <= Z)) curAtbUpperCnt[text[k]-A]++;
				if ((text[k] >= a) && (text[k] <= z)) curAtbLowerCnt[text[k]-a]++;
				//printf("i %d j %d k %d text %c", i,j,k,text[k]);
			}

			for(k = 0; k < 26; k++) {
				if ((curAtbUpperCnt[k] != upperAtbCnt[k]) || (curAtbLowerCnt[k] != lowerAtbCnt[k])) {
					isAtbash = 0;
				}
			}

			if (isAtbash) {		
				dest = (char *)(malloc((size + 1) * sizeof(char)));
				dest[size] = '\0'; 
				source = text + i;
				strncpy(dest, source, size);
				if (firstPrintDone) printf("~");
				printf("%s",dest);
				firstPrintDone = 1;
				break;
			}
		}
	}

}

void printAnagram() {
	int i, j, k;
	int firstPrintDone = 0;
	char *source = NULL;
	char *dest = NULL;

	printf("Anagram Sequences: ");
	for(i = 0; i < textWrPtr; i++) {
		if (!IS_VALID(text[i])) continue;


			//printf("\ni %d\n", i);
		for(j = i; j < textWrPtr; j++) {
			char curUpperCnt[26] = {0};
			char curLowerCnt[26] = {0};
			int isAnagram = 1;
			int size = (j-i)+1;
			if (!IS_VALID(text[j])) break;
			for(k = i; k <= j; k++) {
				if ((text[k] >= A) && (text[k] <= Z)) curUpperCnt[text[k]-A]++;
				if ((text[k] >= a) && (text[k] <= z)) curLowerCnt[text[k]-a]++;
				//printf("i %d j %d k %d text %c", i,j,k,text[k]);
			}
			for(k = 0; k < 26; k++) {
				if ((curUpperCnt[k] != upperCnt[k]) || (curLowerCnt[k] != lowerCnt[k])) {
					isAnagram = 0;
				}
			}
			//printf("\nj %d\n", j);
	//for(k = 0; k < 26; k++) {
	//		if (curUpperCnt[k] != 0 || curLowerCnt[k] != 0)
	//		printf("\nisAnagram %d curUpperCnt[%d] %d curLowerCnt[%d] %d upperCnt %d lowerCnt %d",isAnagram,k, curUpperCnt[k],k, curLowerCnt[k], upperCnt[k], lowerCnt[k]);
	//		if ((curUpperCnt[k] != upperCnt[k]) || (curLowerCnt[k] != lowerCnt[k])) {
	//				isAnagram = 0;
	//			}
	//	}
			if (isAnagram) {

	//printf("i %d j %d: ",i,j);
				dest = (char *)(malloc((size + 1) * sizeof(char)));
				dest[size] = '\0'; 
				source = text + i;
				strncpy(dest, source, size);
				if (firstPrintDone) printf("~");
				printf("%s",dest);
				firstPrintDone = 1;
				break;
			}
		}
	}

}
