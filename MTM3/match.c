#include "match.h"

//**************** MACRO ******************************************************

#define NULL_ARG(arg, returnVal) if(arg == NULL) { \
													return returnVal; \
												}

#define NULL_ARG_AND_RETURN_VOID(arg) if(arg == NULL) { \
													return; \
												}

#define CHECK_ARG(arg, val, returnVal) if(arg == val) { \
													return returnVal; \
												}
#define CHECK_IF_NOT(arg, val, returnVal) if(arg != val) { \
													return returnVal; \
												}
//*********************** STRUCT **********************************************

struct mtm_match_t {
	Map users;
	Map hobbies;
};

//**************** FUNCTIONS - GET THE FIELD **********************************

Map matchGetUsers(Match match) {
	return match->users;
}

Map matchGetHobbies(Match match) {
	return match->hobbies;
}

//**************** FUNCTIONS FOR THE ADT **************************************

MatchResult matchCopy(Match match) {
	NULL_ARG(matchGetUsers(match), MATCH_NULL_ARGUMENT)
	NULL_ARG(matchGetHobbies(match), MATCH_NULL_ARGUMENT)
	Match newMatch = malloc(sizeof(*newMatch));
	newMatch->hobbies = mapCopy(matchGetHobbies(match));
	NULL_ARG(newMatch->users, MATCH_NULL_ARGUMENT)
	newMatch->hobbies = mapCopy(matchGetUsers(match));
	NULL_ARG(newMatch->users, MATCH_NULL_ARGUMENT)
	return 	MATCH_SUCCESS;
}

void matchDestroy(Match matchToDestroy) {
	NULL_ARG_AND_RETURN_VOID(matchToDestroy)
	NULL_ARG_AND_RETURN_VOID(matchToDestroy->hobbies)
	NULL_ARG_AND_RETURN_VOID(matchToDestroy->users)
	mapDestroy(matchToDestroy->hobbies);
	mapDestroy(matchToDestroy->users);
	free(matchToDestroy);
}

Match matchCreate() {
	Match newMatch = malloc(sizeof(*newMatch));
	NULL_ARG(newMatch, NULL)
	newMatch->users = mapCreate(userCopy, IDCopy,userDestroy,IDFree,IDCompare);
	if(!newMatch->users) {
		free(newMatch);
		return NULL;
	}
	newMatch->hobbies = mapCreate(hobbyCopy, hobbyNameCopy, hobbyDestroy,
			hobbyNameFree, hobbyNameCompare);
	if(!newMatch->hobbies) {
		mapDestroy(newMatch->users);
		free(newMatch);
		return NULL;
	}
	return newMatch;
}

//*****************************************************************************
void removeUserFromFriendsAndFriendReq(Map users, MapKeyElement id,
		CheckIfElementInSet checkFunc, removeElementFromSet removeFunc) {
	MAP_FOREACH(MapKeyElement,iterator,users) { //iterator=id
		if(iterator == id) {
			continue;
		}
		MapDataElement userI = mapGet(users, iterator);
		NULL_ARG_AND_RETURN_VOID(userI)
		if(checkFunc(userI, id)) {
			removeFunc(userI, id);
		}
	}
}


void removeUserFromHobbies(Map hobbies, MapKeyElement id) {
	MAP_FOREACH(MapKeyElement,iterator,hobbies) { //iterator=name
		MapDataElement hobbyI = mapGet(hobbies, iterator);
		if(UserInHobby(hobbyI, id)) {
			removeUserFromHobby(hobbyI, id);
		}
	}
}

MatchResult userRemove(Match match, int id) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(match->users, MATCH_NULL_ARGUMENT)
	bool flag = mapContains(match->users, &id);
	CHECK_ARG(flag, false, MATCH_USER_DOES_NOT_EXIST)
	removeUserFromFriendsAndFriendReq(match->users, &id, checkIfIDFriend,
			removeUserFromFriend);
	removeUserFromFriendsAndFriendReq(match->users, &id,
			checkIfIDInFriendRequests, removeUserFromFriendReq);
	//removeUserFromFriendRequests(match->users, id);  //TODO if work remove this line
	NULL_ARG(match->hobbies, MATCH_NULL_ARGUMENT)
	removeUserFromHobbies(match->hobbies, &id);
	mapRemove(match->users, &id);
	return MATCH_SUCCESS;
}

//*****************************************************************************

MatchResult userAdd(Match match, int id, char* nameOfUser, int birthYear,
		sexualOrientation gender, sexualOrientation pref) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(nameOfUser, MATCH_NULL_ARGUMENT)
	NULL_ARG(match->users, MATCH_NULL_ARGUMENT)
	bool flag  = mapContains(match->users, &id);
	CHECK_ARG(flag, true, MATCH_USER_ALREADY_EXISTS)
	if(birthYear < 0 || birthYear > YEAR) {
		return MATCH_INVALID_PARAMETERS;
	}
	if(gender != F && gender != M) {
		return MATCH_INVALID_PARAMETERS;
	}
	if((pref != F) && (pref != M) && (pref != B)) {
		return MATCH_INVALID_PARAMETERS;
	}
	User newUser = userCreate(id, nameOfUser, birthYear, gender, pref);
	NULL_ARG(newUser, MATCH_OUT_OF_MEMORY)
	User temp = newUser;
	MapResult flag2 = mapPut(match->users, &id, newUser);
	CHECK_ARG(flag2, MAP_OUT_OF_MEMORY, MATCH_OUT_OF_MEMORY)
	userDestroy(temp);
	return MATCH_SUCCESS;
}

//*****************************************************************************

List mapToList(Map map, CompareListElements cmpFunc, CopyListElement copyFunc,
		FreeListElement destroyFunc) {
	List newList = listCreate(copyFunc, destroyFunc);
	NULL_ARG(newList, NULL)
	MAP_FOREACH(MapKeyElement,iterator,map) {
		ListResult flag = listInsertFirst(newList, mapGet(map,iterator));
		CHECK_IF_NOT(flag, LIST_SUCCESS, NULL)
	}
	ListResult flag = listSort(newList, cmpFunc);
	CHECK_IF_NOT(flag, LIST_SUCCESS, NULL)
	return newList;
}

int userHobbyCnt(ListElement id, Map hobbies) {
	int counter = 0;
	MAP_FOREACH(MapKeyElement,iterator,hobbies) { //iterator = name
		bool flag = UserInHobby(mapGet(hobbies, iterator), id);
		if(flag) {
			counter++;
		}
	}
	return counter;
}

int userIDCompare(ListElement user1, ListElement user2) {
	int id1 = userGetID((User)user1);
	int id2 = userGetID((User)user2);
	if(id1 > id2) {
		return 1;
	}
	if(id1 < id2) {
		return -1;
	}
	return 0;
}

MatchResult reportUsers(Match match, FILE* outputFile) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapGetSize(match->users), 0, MATCH_NO_USERS)
	List usersSortList = mapToList(match->users, userIDCompare, userCopy,
			userDestroy);
	NULL_ARG(usersSortList, MATCH_OUT_OF_MEMORY)
	LIST_FOREACH(ListElement,iterator,usersSortList) {
		int id = userGetID((User)iterator);
		MapDataElement userToPrint = mapGet(match->users, &id);
		int numOfHobbies = userHobbyCnt(&id, match->hobbies);
		int numOfFriends = cntFriends((User)userToPrint);
		const char* stringForUser = mtmPrintUser(userGetName((User)userToPrint), userGetBirthYear((User)userToPrint), id, numOfFriends, numOfHobbies);
		fprintf(outputFile, stringForUser);
	}
	listDestroy(usersSortList);
	return USER_SUCCESS;
}

//****************************************************************************

MatchResult friendRequest(int requesting_id, int requested_id, Match match) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapContains(match->users, &requested_id), false, MATCH_USER_DOES_NOT_EXIST)
	CHECK_ARG(mapContains(match->users, &requesting_id), false, MATCH_USER_DOES_NOT_EXIST)
	CHECK_ARG(requesting_id, requested_id, MATCH_USER_ALREADY_FRIEND)
	MapDataElement userToCheck = mapGet(match->users, &requested_id);
	bool tempFlag = checkIfIDFriend(userToCheck, &requesting_id);
	CHECK_ARG(tempFlag, true, MATCH_USER_ALREADY_FRIEND)
	Set friendRequest = userGetFriendRequest(userToCheck);
	setAdd(friendRequest, &requesting_id);
	return MATCH_SUCCESS;
}

//***************************************************************************

UserResult userUnFriend(int requesting_id, int requested_id, Match match) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapContains(match->users, &requested_id), false,
			MATCH_USER_DOES_NOT_EXIST)
	CHECK_ARG(mapContains(match->users, &requesting_id), false,
			MATCH_USER_DOES_NOT_EXIST)
	CHECK_ARG(requesting_id, requested_id, MATCH_USER_NOT_FRIEND)
	MapDataElement userToCheck1 = mapGet(match->users, &requested_id);
	MapDataElement userToCheck2 = mapGet(match->users, &requesting_id);
	Set friendOfRequested = userGetFriends(userToCheck1);
	Set friendOfRequesting = userGetFriends(userToCheck2);
	SetResult flag = setRemove(friendOfRequested, &requesting_id);
	CHECK_ARG(flag, SET_ITEM_DOES_NOT_EXIST, MATCH_USER_NOT_FRIEND)
	setRemove(friendOfRequesting, &requested_id);
	return MATCH_SUCCESS;
}

//**********************************************************************************

MatchResult handleRequest(int requesting_id, int requested_id, choice userChoice,
		Match match) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapContains(match->users, &requested_id), false,
			MATCH_USER_DOES_NOT_EXIST)
	CHECK_ARG(mapContains(match->users, &requesting_id), false,
			MATCH_USER_DOES_NOT_EXIST)
	MapDataElement userToCheck1 = mapGet(match->users, &requested_id);
	CHECK_ARG(checkIfIDInFriendRequests(userToCheck1, &requesting_id), false,
			MATCH_USER_NO_IN_USER_REQUEST)
	Set friendList = userGetFriendRequest(userToCheck1);
	setRemove(friendList, &requesting_id);
	CHECK_ARG(userChoice, deny, MATCH_SUCCESS)
	Set friends = userGetFriends((User)userToCheck1);
	setAdd(friends, &requesting_id);
	MapDataElement userToCheck2 = mapGet(match->users, &requesting_id);
	Set friends2 = userGetFriends((User)userToCheck2);
	setAdd(friends2, &requested_id);
	return MATCH_SUCCESS;
}

//**********************************************************************************

MatchResult hobbyRemove(Match match, char* name) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(name, MATCH_NULL_ARGUMENT)
	bool flag = mapContains(match->hobbies, name);
	CHECK_ARG(flag, false, MATCH_HOBBY_DOES_NOT_EXIST)
	mapRemove(match->hobbies, name);
	return MATCH_SUCCESS;
}

//*********************************************************************************

MatchResult hobbyJoin(Match match, char* name, int id) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(name, MATCH_NULL_ARGUMENT)
	bool flagHobby = mapContains(match->hobbies, name);
	CHECK_ARG(flagHobby, false, MATCH_HOBBY_DOES_NOT_EXIST)
	bool flagUser = mapContains(match->users, &id);
	CHECK_ARG(flagUser, false, MATCH_USER_DOES_NOT_EXIST)
	MapDataElement hobbyToCheck = mapGet(match->hobbies, name);
	SetResult flag = setAdd(hobbyGetUsers((Hobby)hobbyToCheck),&id);
	CHECK_ARG(flag, SET_ITEM_ALREADY_EXISTS,
			MATCH_USER_ALREADY_PARTICIPATES_HOBBY)
	return MATCH_SUCCESS;
}

//*****************************************************************************

bool hobbyAlreadyExist(char** namesOfHobbies, int index, MapKeyElement name) {
	for(int i=0; i<index; i++){
		if(strcmp(namesOfHobbies[i], (char*)name) == 0) {
			return true;
		}
	}
	return false;
}

void findHobbies(Map hobbies, MapKeyElement id, char** namesOfHobbies,
		int* index, bool* flag) {
	MAP_FOREACH(MapKeyElement,iterator,hobbies) {	//iterator = hobby name
			MapDataElement HobbyI = mapGet(hobbies, iterator);
			bool userInHobbyI = UserInHobby((Hobby)HobbyI, id);
			if(userInHobbyI) {
				if(!hobbyAlreadyExist(namesOfHobbies, *index, iterator)) {
					namesOfHobbies[*index] = iterator;
					*index = (*index) + 1;
					*flag = true;
				}
			}
	}
}

void sortString(char** stringToPrint, int len) {
	if(len == 1) {
		return;
	}
	for(int i=0; i<len; i++) {
		int place;
		for(int j=0; j<len; j++) {
			if(strcmp(stringToPrint[i], stringToPrint[j]) < 0) {
				place = j;
				char* temp = stringToPrint[place];
				stringToPrint[place] = stringToPrint[i];
				stringToPrint[i] = temp;
			}
		}
	}
}


int findMinBirthYear(Map users) {
	int min = YEAR;
	MAP_FOREACH(MapKeyElement,iterator,users) {
		MapDataElement userI = mapGet(users, iterator);
		int tmpYear = userGetBirthYear((User)userI);
		if(tmpYear < min) {
			min = tmpYear;
		}
	}
	return min;
}


MatchResult reportHobbiesByAge(Match match, FILE* outputFile) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapGetSize(match->hobbies), 0, MATCH_NO_HOBBIES)
	CHECK_ARG(mapGetSize(match->users), 0, MATCH_NO_USERS)
	int numOfHobbies = mapGetSize(match->hobbies);
	char** namesOfHobbies = malloc(numOfHobbies*sizeof(char*));
	NULL_ARG(namesOfHobbies, MATCH_OUT_OF_MEMORY)
	int minYear = findMinBirthYear(match->users);
	for(int i=YEAR; i>=minYear; i--) {
		int index = 0;
		bool flag = false;
		int age = YEAR - i;
		MAP_FOREACH(MapKeyElement,iterator,match->users) {//iterator1 = user id
			MapDataElement userI = mapGet(match->users, iterator);
			int userAge = YEAR - userGetBirthYear((User)userI);
			if(userAge == age) {
				findHobbies(match->hobbies, iterator, namesOfHobbies,
						&index, &flag);
			}
		}
		if(flag) {
			sortString(namesOfHobbies, index);
			const char* stringToPrint = mtmPrintHobbiesByAge((YEAR-age), (const char**)namesOfHobbies, index);
			fprintf(outputFile, stringToPrint);
		}
	}
	free(namesOfHobbies);
	return  MATCH_SUCCESS;
}

//*****************************************************************************

MatchResult hobbyAdd(Match match, char* hobbyName) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(hobbyName, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapContains(match->hobbies, hobbyName), true,
			MATCH_HOBBY_ALREADY_EXISTS)
	Hobby hobbyToAdd = hobbyCreate(hobbyName);
	NULL_ARG(hobbyToAdd, MATCH_OUT_OF_MEMORY)
	Hobby temp = hobbyToAdd;
	mapPut(match->hobbies, hobbyName, hobbyToAdd);
	hobbyDestroy(temp);
	return MATCH_SUCCESS;
}

//*****************************************************************************

MatchResult hobbyLeave(Match match, char* hobbyName, int id) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	NULL_ARG(hobbyName, MATCH_NULL_ARGUMENT)
	CHECK_ARG(mapContains(match->hobbies, hobbyName), false,
			MATCH_HOBBY_DOES_NOT_EXIST)
	CHECK_ARG(mapContains(match->users, &id), false, MATCH_USER_DOES_NOT_EXIST)
	Hobby hobbyToRemove = mapGet(match->hobbies, hobbyName);
	bool flag = UserInHobby(hobbyToRemove, &id);
	CHECK_ARG(flag, false, MATCH_USER_DOESNT_PARTICIPATE_HOBBY)
	setRemove(hobbyGetUsers(hobbyToRemove), &id);
	return MATCH_SUCCESS;
}

//*****************************************************************************

void calcGrade(User userForDate, int id1, User userToCheck, int id2,
		Map hobbies) {
	sexualOrientation pref1 = userGetPref(userForDate);
	sexualOrientation pref2 = userGetPref(userToCheck);
	sexualOrientation gender1 = userGetGender(userForDate);
	sexualOrientation gender2 = userGetGender(userToCheck);
	if((pref1 != B) && (pref1 != gender2)) {
		*(userGetGrade(userToCheck)) = 0.0;
		return;
	}
	if((pref2 != B) && (pref2 != gender1)) {
		*(userGetGrade(userToCheck)) = 0.0;
		return;
	}
	int age1 = YEAR - userGetBirthYear(userForDate);
	int age2 = YEAR - userGetBirthYear(userToCheck);
	int A = abs(age1-age2);
	int F = 0;
	SET_FOREACH(SetElement,iterator, (userGetFriends(userForDate))) {
		if(setIsIn(userGetFriends(userToCheck), iterator)) {
			F++;
		}
	}
	int H = 0;
	MAP_FOREACH(MapKeyElement,iterator,hobbies) {
		Hobby hobbyI = mapGet(hobbies, iterator);
		Set setOfUsers = hobbyGetUsers(hobbyI);
		if(setIsIn(setOfUsers, &id1) && setIsIn(setOfUsers, &id2)) {
			H++;
		}
	}
	double grade = ((double)((1+H)*(1+F)))/(1+A);
	*(userGetGrade(userToCheck)) = grade;
}

ListResult printByGrade(int id,char* name, int count, Match match, FILE* outputFile) {
	List newList = mapToList(match->users, userGradeCompare, userCopy,
			userDestroy);
	NULL_ARG(newList, LIST_OUT_OF_MEMORY)
	int idToDate;
	int index = 0;
	LIST_FOREACH(ListElement,iterator,newList) {
		idToDate = userGetID((User)iterator);
		double grade = *(userGetGrade((User)iterator));
		if((id != idToDate) && (grade != 0.0))  {
				const char* stringToPrint = mtmWhoCanIDate(id, name, idToDate,
						userGetName((User)iterator));
				fprintf(outputFile, stringToPrint);
				index++;
				if(index == count) {
					return LIST_SUCCESS;
				}
		}

	}
	listDestroy(newList);
	return LIST_SUCCESS;
}

int userGradeCompare(ListElement user1, ListElement user2) {
	double g1 = *userGetGrade((User)user1);
	double g2 = *userGetGrade((User)user2);
	double temp = g1 - g2;
	if(temp < 0) {
		temp = temp*(-1);
		if(temp <= EPSILON) {
			int sortById = userIDCompare(user1, user2);
			CHECK_ARG(sortById, 1, -1)
			return 1;
		}
		else {
			return 1;
		}
	}
	return -1;
}

MatchResult userWhoCanIDate(int id, int count, Match match, FILE* outputFile) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	MapDataElement userNeedDate = mapGet(match->users, &id);
	CHECK_ARG(userNeedDate, false, MATCH_USER_DOES_NOT_EXIST)
	if(count <= 0) {
		return MATCH_INVALID_PARAMETERS;
	}
	MAP_FOREACH(MapKeyElement,iterator,match->users)  {
		if(*((int*)iterator) != id) {
			MapDataElement userI = mapGet(match->users, iterator);
			calcGrade(userNeedDate, id,  userI, *((int*)iterator),
					match->hobbies);
		}
	}
	ListResult flag = printByGrade(id, userGetName((User)userNeedDate),
			count, match, outputFile);
	CHECK_ARG(flag, LIST_OUT_OF_MEMORY, MATCH_OUT_OF_MEMORY)
	return MATCH_SUCCESS;
}

//*************************************************************************

int compareByNumOfUsers(ListElement hobby1, ListElement hobby2) {
	int num1 = setGetSize(hobbyGetUsers((Hobby)hobby1));
	int num2 = setGetSize(hobbyGetUsers((Hobby)hobby2));
	if(num1 > num2) {
		return -1;
	}
	if(num1 < num2) {
		return 1;
	}
	char* name1 = hobbyGetName((Hobby)hobby1);
	char* name2 = hobbyGetName((Hobby)hobby2);
	int delta = strcmp(name1, name2);
	if(delta < 0) {
		return -1;
	}
	return 1;
}


MatchResult hobbyReport(Match match, int count, FILE* outputFile) {
	NULL_ARG(match, MATCH_NULL_ARGUMENT)
	int hobbyCount = mapGetSize(match->hobbies);// getting size
	CHECK_ARG(hobbyCount, 0, MATCH_NO_HOBBIES)
	if(count < 0) {
		return MATCH_INVALID_PARAMETERS;
	}
	if((count == 0) || (count > hobbyCount)) {
		count = hobbyCount;
	}
	List newList = mapToList(match->hobbies, compareByNumOfUsers, hobbyCopy, hobbyDestroy);
	NULL_ARG(newList, MATCH_OUT_OF_MEMORY)
	ListElement el = listGetFirst(newList);
	for(int i=0; i<count; i++) {
		const char* name = hobbyGetName((Hobby)el);
		int size = setGetSize(hobbyGetUsers((Hobby)el));
		const char* stringToPrint = mtmPrintHobby(name, size);
		fprintf(outputFile, stringToPrint);
		el = listGetNext(newList);
	}
	listDestroy(newList);
	return MATCH_SUCCESS;
}










