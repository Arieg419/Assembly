#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "match.h"
#include "mtm_ex3.h"
#define BUFFER_SIZE 121
#define ARRAYLENGTH 7
#define FATAL_ERROR false
#define INVALID_REQ true
#define VALID_REQ true
#define EXIT_PROG return 0;
#define EXIT_WITH_ERR(error)\
	mtmPrintErrorMessage(stderr,error);\
	EXIT_PROG
#define CLOSE_FILES_AND_EXIT_WITH_ERR(input,output,error)\
	CLOSE_FILES(input,output)\
	mtmPrintErrorMessage(stderr,error);\
	EXIT_PROG
#define CLOSE_FILES(input,output)\
	if(input!=stdin && input!= NULL){\
		fclose(input);\
	}\
	if(output!=stdout && output != NULL){\
		fclose(output);\
	}

#define CHECK_CANNOT_OPEN_AND_RETURN(ptr)\
	if(ptr == NULL){\
		return MATCH_CANNOT_OPEN_FILE;\
	}
#define CHECK_NULL_AND_CLOSE(arg,filePointer)\
		if(arg == NULL){\
			fclose(*filePointer);\
			return MATCH_CANNOT_OPEN_FILE;\
		}
#define CHECK_NULL(arg)\
		if(arg == NULL){\
			return MATCH_NULL_ARGUMENT;\
	    }

static int turnStringToInt(char* string) {
	int lengthOfString = strlen(string);
	int value = 0 ;
	int whereToStart = 0;
	bool isNegative = false;
	 if(string[0] == '-') {
        isNegative = true;
        whereToStart = 1;
    }

	for(int i = whereToStart; i < lengthOfString ; i++) {
		int currentDigit = string[i] - '0';
		value += currentDigit;
		if(i != lengthOfString - 1) {
		value *= 10;
		}
	}
	if(isNegative) {
	    value *= -1;
	}
	return value;
}

sexualOrientation determineGender(List list) {
	sexualOrientation gender;
	char* gen = listGetNext(list);
	if(!strcmp(gen,"M")){
			gender = M;
		}
	if(!strcmp(gen,"F")) {
		gender = F;
	}
	return gender;// what if its not M or F
}

sexualOrientation determinePref(List list) {
	sexualOrientation prefRtn;
	char* pref = listGetNext(list);
	if(!strcmp(pref, "M")) {
		prefRtn = M;
	}
	if(!strcmp(pref, "F")) {
			prefRtn = F;
		}
	if(!strcmp(pref, "B")) {
			prefRtn = B;
		}
	return prefRtn;// same here
}

sexualOrientation determineChoice(List list) {
	choice userChoice;
	char* choice = listGetNext(list);
	if(!strcmp(choice, "accept")){
		userChoice = accept;
	}
	if(!strcmp(choice, "deny")){
		userChoice = deny;
	}
	return userChoice;// same here
}

static bool processMatchResult(MatchResult res, Match match, List list) {
	switch(res) {
		case MATCH_OUT_OF_MEMORY:
		mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
		return FATAL_ERROR;
		case MATCH_CANNOT_OPEN_FILE:
		mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
		return FATAL_ERROR;
		case MATCH_INVALID_COMMAND_LINE_PARAMETERS:
		mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return INVALID_REQ;
		case MATCH_NULL_ARGUMENT:
		mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return INVALID_REQ;
		case MATCH_NO_USERS:
		mtmPrintErrorMessage(stderr, MTM_NO_USERS);
		return INVALID_REQ;
		case MATCH_USER_ALREADY_EXISTS:
		mtmPrintErrorMessage(stderr, MTM_USER_ALREADY_EXISTS);
		return INVALID_REQ;
		case MATCH_USER_DOES_NOT_EXIST:
		mtmPrintErrorMessage(stderr,MTM_USER_DOES_NOT_EXIST);
		return INVALID_REQ;
		case MATCH_HOBBY_DOES_NOT_EXIST:
		mtmPrintErrorMessage(stderr,MTM_HOBBY_DOES_NOT_EXIST);
		return INVALID_REQ;
		case MATCH_NO_HOBBIES:
		mtmPrintErrorMessage(stderr,MTM_NO_HOBBIES);
		return INVALID_REQ;
		case MATCH_HOBBY_ALREADY_EXISTS:
		mtmPrintErrorMessage(stderr,MTM_HOBBY_ALREADY_EXISTS);
		return INVALID_REQ;
		case MATCH_USER_DOESNT_PARTICIPATE_HOBBY:
		mtmPrintErrorMessage(stderr,MTM_USER_DOESNT_PARTICIPATE_HOBBY);
		return INVALID_REQ;
		case MATCH_USER_ALREADY_PARTICIPATES_HOBBY:
		mtmPrintErrorMessage(stderr,MTM_USER_ALREADY_PARTICIPATES_HOBBY);
		return INVALID_REQ;
		case MATCH_USER_NOT_FRIEND:
		mtmPrintErrorMessage(stderr,MTM_USER_NOT_FRIEND);
		return INVALID_REQ;
		case MATCH_USER_ALREADY_FRIEND:
		mtmPrintErrorMessage(stderr,MTM_USER_ALREADY_FRIEND);
		return INVALID_REQ;
		case MATCH_USER_NO_IN_USER_REQUEST:
		mtmPrintErrorMessage(stderr,MTM_NO_USER_REQUEST);
		return INVALID_REQ;
		case MATCH_INVALID_PARAMETERS:
		mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETERS);
		return INVALID_REQ;
		case MATCH_SUCCESS:
		return VALID_REQ;
    }
	return true;  //TODO what do i return here?
}

static MatchResult callHobbyAdd(Match match, List list) {
	char* hobbyName = (char*)listGetNext(list); //first two args are hobby and add third is string name
	MatchResult matchResult = hobbyAdd(match, hobbyName);
	return matchResult;
}

static MatchResult callHobbyRemove(Match match, List list) {
	char* hobbyName = listGetNext(list);
	MatchResult matchResult = hobbyRemove(match, hobbyName);
	return matchResult;
}

static MatchResult callReportHobbies(Match match, List list, FILE* outputFile) {
	int count =  turnStringToInt(listGetNext(list)); //won't this be a problem getting integers into this array?
	MatchResult matchResult = hobbyReport(match, count, outputFile);
	return matchResult;
}

static MatchResult callUserAdd(Match match, List list) {
	int id =  turnStringToInt(listGetNext(list));
	char* name = (char*)listGetNext(list);
	int birthYear = turnStringToInt(listGetNext(list));
	sexualOrientation gender = determineGender(list);
	sexualOrientation pref = determinePref(list);
	MatchResult matchResult = userAdd(match, id, name, birthYear, gender, pref);
	return matchResult;
}

static MatchResult callUserRemove(Match match, List list) {
	int id =  turnStringToInt(listGetNext(list));
	MatchResult matchResult = userRemove(match, id);
	return matchResult;
}

static MatchResult callReportUsers(Match match, List list, FILE* outputFile) {
	MatchResult matchResult = reportUsers(match, outputFile);
	return matchResult;
}

static MatchResult callHobbyJoin(Match match, List list) {
	MatchResult matchResult;
	char* name =listGetNext(list);
	int id =  turnStringToInt(listGetNext(list));
	matchResult = hobbyJoin(match, name, id);
	return matchResult;
}

static MatchResult callHobbyLeave(Match match , List list) {
	MatchResult matchResult;
	char* name = listGetNext(list);
	int id =  turnStringToInt(listGetNext(list));
	matchResult = hobbyLeave(match, name, id);
	return matchResult;
}

static MatchResult callReportHobbiesByAge(Match match, List list, FILE* outputFile) {
	MatchResult matchResult;
	matchResult = reportHobbiesByAge(match, outputFile);
	return matchResult;
}

static MatchResult callFriendRequest(Match match, List list) {
	MatchResult matchResult;
	int requesting_id = turnStringToInt(listGetNext(list));
	int requested_id = turnStringToInt(listGetNext(list));
	matchResult = friendRequest(requesting_id, requested_id, match);
 	return matchResult;
}

static MatchResult callUserHandleRequest(Match match, List list) {
	MatchResult matchResult;
	int requesting_id = turnStringToInt(listGetNext(list));
	int requested_id = turnStringToInt(listGetNext(list));
	choice userChoice = determineChoice(list);
	matchResult = handleRequest(requesting_id, requested_id, userChoice, match);
	return matchResult;
}


static MatchResult callUserUnfriend(Match match, List list) {
	MatchResult matchResult;
	int requesting_id = turnStringToInt(listGetNext(list));
	int requested_id = turnStringToInt(listGetNext(list));
	matchResult = userUnFriend(requesting_id, requested_id, match);
	return matchResult;
}

static MatchResult callWhoCanIDate(Match match, List list, FILE* outputFile) {
	MatchResult matchResult;
	int id = turnStringToInt(listGetNext(list));
	int count = turnStringToInt(listGetNext(list));
	matchResult = userWhoCanIDate(id, count, match, outputFile);
	return matchResult;
}

static MatchResult readCommandCall(Match match, char* command, char* command2, List list, FILE* outputFile) {
	    if(strcmp(command,"#")== 0){
			MatchResult result = MATCH_SUCCESS;
			return result;
        }
		if(strcmp(command,"hobby")== 0){
			if(strcmp(command2, "add") == 0) {
			MatchResult result = callHobbyAdd(match,list);
			return result;
			}
		}
		if(strcmp(command,"hobby")== 0){
			if(strcmp(command2, "remove") == 0) {
			MatchResult result = callHobbyRemove(match,list);
			return result;
			}
		}
		if(strcmp(command,"report")== 0){
			if(strcmp(command2, "hobbies") == 0) {
			MatchResult result = callReportHobbies(match,list,outputFile);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "add") == 0) {
			MatchResult result = callUserAdd(match,list);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "remove") == 0) {
			MatchResult result = callUserRemove(match,list);
			return result;
			}
		}
		if(strcmp(command,"report")== 0){
			if(strcmp(command2, "users") == 0) {
			MatchResult result = callReportUsers(match,list,outputFile);
			return result;
			}
		}
		if(strcmp(command,"hobby")== 0){
			if(strcmp(command2, "join") == 0) {
			MatchResult result = callHobbyJoin(match,list);
			return result;
			}
		}
		if(strcmp(command,"hobby")== 0){
			if(strcmp(command2, "leave") == 0) {
			MatchResult result = callHobbyLeave(match,list);
			return result;
			}
		}
		if(strcmp(command,"report")== 0){
			if(strcmp(command2, "hobbies_by_age") == 0) {
			MatchResult result = callReportHobbiesByAge(match,list, outputFile);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "friend_request") == 0) {
			MatchResult result =  callFriendRequest(match,list);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "handle_request") == 0) {
			MatchResult result = callUserHandleRequest(match,list);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "unfriend") == 0) {
			MatchResult result = callUserUnfriend(match,list);
			return result;
			}
		}
		if(strcmp(command,"user")== 0){
			if(strcmp(command2, "who_can_i_date") == 0) {
			MatchResult result = callWhoCanIDate(match,list, outputFile);
			return result;
			}
		}
		return MATCH_INVALID_PARAMETERS;
}

static bool argumentCounter(int argc) {
	if(argc != 1 && argc != 3 && argc != 5) {
		return false;
	}
	return true;
}

static bool delimiters(char arg){
		if((arg == '\t') || (arg == '\n') || (arg == '\r') || (arg == '\0') || (arg == ' ')){
			return true;
		}
		return false;
}


static MatchResult analyzeCommandLineArgs(int argc, char** argv, FILE** inputFilePointer, FILE** outputFilePointer) {
	if(argc == 1) {
		*inputFilePointer = stdin;
		*outputFilePointer = stdout;
		return MATCH_SUCCESS;
	}
	if(argc == 3) {
		if(!strcmp(argv[1],"-i")) {
			*inputFilePointer = fopen(argv[2], "r");
			CHECK_CANNOT_OPEN_AND_RETURN(*inputFilePointer)
			*outputFilePointer = stdout;
			return MATCH_SUCCESS;
		}
        if(!strcmp(argv[1],"-o")) {
			*outputFilePointer = fopen(argv[2], "w");
			CHECK_CANNOT_OPEN_AND_RETURN(*outputFilePointer)
			*inputFilePointer = stdin;
			return MATCH_SUCCESS;
		}
		return MATCH_INVALID_COMMAND_LINE_PARAMETERS;
	}
	if(argc == 5) {
		if(!strcmp(argv[1],"-i")) {
			*inputFilePointer = fopen(argv[2], "r");
			CHECK_CANNOT_OPEN_AND_RETURN(*inputFilePointer)
			if(!strcmp(argv[3],"-o")) {
				*outputFilePointer = fopen(argv[4], "w");
				CHECK_NULL_AND_CLOSE(outputFilePointer, inputFilePointer)
				return MATCH_SUCCESS;
			}
			return MATCH_INVALID_COMMAND_LINE_PARAMETERS;
		}
		if(!strcmp(argv[1],"-o")) {
			*outputFilePointer = fopen(argv[2], "w");
			CHECK_CANNOT_OPEN_AND_RETURN(*outputFilePointer)
			if(!strcmp(argv[3],"-i")) {
				*inputFilePointer = fopen(argv[4], "r");
				CHECK_NULL_AND_CLOSE(inputFilePointer, outputFilePointer)
				return MATCH_SUCCESS;
		    }
			return MATCH_INVALID_COMMAND_LINE_PARAMETERS;
		}
		return MATCH_INVALID_COMMAND_LINE_PARAMETERS;
	}
	return MATCH_INVALID_COMMAND_LINE_PARAMETERS;
}


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

static bool readCurrentLine(char* buffer, Match match, FILE* outputFile, FILE* inputFile) {
	char* pointer = buffer;
	bool isWord = false;
	List argList = listCreate(copyString, freeListElement);
    if(argList == NULL) {
    	processMatchResult(MATCH_OUT_OF_MEMORY, match, argList);
    	return FATAL_ERROR;
    }
	int wordLength = 0;
	while(*pointer != '\0') {
		if(*pointer == '\n' && listGetSize(argList)==0) { //hitting an empty line
			listDestroy(argList);
			return true;
		}
		if(*pointer == '\r' && listGetSize(argList)==0) { //hitting an empty line
			listDestroy(argList);
			return true;
		}
		if(delimiters(*pointer)) {
			if(isWord) {
				char stringToPlace[wordLength + 1];  //declaring a string the length of the word
				char* ptr2 = pointer; //this pointer will point to the beginning of the word
				for(int i = 0; i < wordLength; i++) { //moving pointer to the beginning of the word
					ptr2--;
				}
				for(int i = 0; i < wordLength; i++) {
					stringToPlace[i] = *ptr2;
					ptr2++;
				}
				stringToPlace[wordLength] = '\0';
				listInsertLast(argList, stringToPlace);
			}
			wordLength = 0;
			pointer++;
			isWord = false;
			continue;
		}
		if(*pointer == '#' && listGetSize(argList)==0) { //we've hit a comment, ignore
			listDestroy(argList);
			return true;
		}
		isWord = true;
		wordLength++;
		pointer++;
	}
	ListElement currentNode = listGetFirst(argList);
	ListElement nextNode = listGetNext(argList);
	if((char*)currentNode == NULL || (char*)nextNode == NULL) { //TODO what should i do here?
		listDestroy(argList);
		return INVALID_REQ;
	}
    MatchResult res = readCommandCall(match, (char*)currentNode,(char*)nextNode, argList, outputFile);
    bool outCome = processMatchResult(res, match, argList);
   if(!outCome) {
	   listDestroy(argList);
	   return FATAL_ERROR;
   }
	listDestroy(argList);
	return VALID_REQ;
}

int main (int argc, char** argv) {
	FILE* inputFile;
	FILE* outputFile;
	bool flagsCheck = argumentCounter(argc);
	if(!flagsCheck) { //if arg count is incorrect, print err message and return 0
		EXIT_WITH_ERR(MTM_INVALID_COMMAND_LINE_PARAMETERS)
	}
	MatchResult checkChannels = analyzeCommandLineArgs(argc,argv,&inputFile,&outputFile);
	if(checkChannels != MATCH_SUCCESS) {
	      CLOSE_FILES(inputFile,outputFile)
		  if(checkChannels == MATCH_CANNOT_OPEN_FILE){
			  EXIT_WITH_ERR(MTM_CANNOT_OPEN_FILE)
		  }
		  else{
			  EXIT_WITH_ERR(MTM_INVALID_COMMAND_LINE_PARAMETERS)
		  }
	   }

//-----------------------------------------------------------------------------
	   Match match = matchCreate();
	   if(match == NULL) {
		   EXIT_WITH_ERR(MTM_OUT_OF_MEMORY)
	   }
	   char buffer[BUFFER_SIZE] = "";
	   while(fgets(buffer, BUFFER_SIZE, inputFile)) {
		  bool outCome = readCurrentLine(buffer, match, outputFile, inputFile);
		  if(!outCome) {
			  break;
		  }
	   }
	   matchDestroy(match);
	   CLOSE_FILES(inputFile,outputFile)
	   EXIT_PROG
   }




