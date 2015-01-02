
#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include "../list_mtm1.h"

//********************* MACROS **********************************************

#define TEST_RESULT_IS(flag, funcToRun, result) \
									if(flag && (funcToRun != result)) { \
													flag = false; \
												}
#define CHECK_IF_NOT_GOOD(flag, stringToPrint)  if(flag == false) { \
							printf("problems in the block: %s\n", stringToPrint);\
													flag = true; \
												}
//*****************************************************************************

static ListElement copyString(ListElement str) {
  char* copy = malloc(strlen(str) + 1);
  return copy ? strcpy(copy, str) : NULL;
}

static void freeListElement(ListElement str) {
	if(!str) {
		return;
	}
	free(str);
}

static int stringCompare(ListElement strg1, ListElement strg2) {
	int delta = strcmp((char*)strg1, (char*)strg2);
	if(delta > 0) {
		return 1;
	}
	if(delta < 0) {
		return -1;
	}
   return 0;
 }

static bool isLongerThan(ListElement string, ListFilterKey filterKey) {
	int len = strlen(string);
	int key = *(int*)filterKey;
	return len > key;
}

//*****************************************************************************

int main() {
	int filterKey = 5;
	char* iceCream = "Vanilla";
	char* movie = "InterStellar";
	char* favoriteCity = "New York City";
	char* emptyString1 = "A";
	char* emptyString2 = "nela";
	char* shortString1 = "yo";
	char* shortString2 = "lol";

	bool flag = true;

	//***************** test list create
	List newList = listCreate(copyString, freeListElement);
	List check = listCreate(NULL, freeListElement);
	TEST_RESULT_IS(flag,check, NULL);

	CHECK_IF_NOT_GOOD(flag, "listCreate")

	//**************** test list insert first

	TEST_RESULT_IS(flag,listGetSize(newList), 0);

	TEST_RESULT_IS(flag, listInsertFirst(newList, NULL), LIST_NULL_ARGUMENT);

	TEST_RESULT_IS(flag, listInsertFirst(newList, iceCream), LIST_SUCCESS);

	TEST_RESULT_IS(flag,listGetSize(newList), 1);

	// check case with one Node
	List cpy = listCopy(newList);
	TEST_RESULT_IS(flag,listGetSize(cpy), 1);

	ListElement el1 = listGetFirst(cpy);
	TEST_RESULT_IS(flag, strcmp(el1,iceCream), 0);

	TEST_RESULT_IS(flag, listRemoveCurrent(cpy), LIST_SUCCESS);
	TEST_RESULT_IS(flag,listGetSize(cpy), 0);

	TEST_RESULT_IS(flag, listInsertFirst(newList, movie), LIST_SUCCESS);

	TEST_RESULT_IS(flag, listInsertFirst(newList, NULL), LIST_NULL_ARGUMENT);

	CHECK_IF_NOT_GOOD(flag, "listInsertFirst")

	//**************** test list insert last

	TEST_RESULT_IS(flag, listInsertLast(newList, emptyString1), LIST_SUCCESS);

	TEST_RESULT_IS(flag, listInsertLast(newList, emptyString2), LIST_SUCCESS);

	// check the iterator
	TEST_RESULT_IS(flag,listGetCurrent(newList), NULL);

	CHECK_IF_NOT_GOOD(flag, "listInsertLast")

	//**************** more test for list get size

	TEST_RESULT_IS(flag,listGetSize(newList), 4);

	CHECK_IF_NOT_GOOD(flag, "listGetSize")

	//**************** test list insert before and after current

	TEST_RESULT_IS(flag, listInsertBeforeCurrent(newList, favoriteCity), LIST_INVALID_CURRENT);

	char* stringToTest = listGetFirst(newList);
	TEST_RESULT_IS(flag, strcmp(stringToTest,movie), 0);

	char* stringToTest2 = listGetNext(newList);
	TEST_RESULT_IS(flag, strcmp(stringToTest2,iceCream), 0);

	TEST_RESULT_IS(flag, listInsertBeforeCurrent(newList, favoriteCity), LIST_SUCCESS);

	TEST_RESULT_IS(flag, listInsertAfterCurrent(newList, shortString2), LIST_SUCCESS);

	char* stringToTest3 = listGetCurrent(newList);
	TEST_RESULT_IS(flag, strcmp(stringToTest3, iceCream), 0);

	TEST_RESULT_IS(flag, listGetSize(newList), 6);

	CHECK_IF_NOT_GOOD(flag, "insert before and after current")

	//**************** test list copy

	List copiedList = listCopy(newList);

	TEST_RESULT_IS(flag, listGetSize(copiedList), 6);

	TEST_RESULT_IS(flag, listRemoveCurrent(copiedList), LIST_SUCCESS);

	CHECK_IF_NOT_GOOD(flag, "listCopy")

	//**************** test list sort

	TEST_RESULT_IS(flag, listSort(newList, stringCompare), LIST_SUCCESS);

	stringToTest = listGetFirst(newList);
	TEST_RESULT_IS(flag, strcmp(stringToTest,emptyString1), 0);

	stringToTest = listGetNext(newList);
	TEST_RESULT_IS(flag, strcmp(stringToTest,movie), 0);

	CHECK_IF_NOT_GOOD(flag, "listSort")

	//**************** test list clear

	TEST_RESULT_IS(flag, listClear(copiedList), LIST_SUCCESS);

	CHECK_IF_NOT_GOOD(flag, "listClear")

	//**************** more test for list

	TEST_RESULT_IS(flag, listRemoveCurrent(newList), LIST_SUCCESS);

	TEST_RESULT_IS(flag, listInsertLast(newList,shortString1), LIST_SUCCESS);

	CHECK_IF_NOT_GOOD(flag, "more test for list")

	//**************** test list filter

	List filteredList = listFilter(newList, isLongerThan, &filterKey);
	TEST_RESULT_IS(flag, listGetSize(filteredList), 2);

	CHECK_IF_NOT_GOOD(flag, "listFilter")

	//**************** test list destroy

	listDestroy(cpy);
	listDestroy(newList);
	listDestroy(copiedList);
	listDestroy(filteredList);
	if(flag) {
		printf("Great Success\n");
	} else {
		printf("failed..\n");
	}

	return 0;
}

