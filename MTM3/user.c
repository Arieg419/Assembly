
#include "user.h"

//**************** MACRO ******************************************************


#define NULL_ARG(arg, returnVal) if(arg == NULL) { \
													return returnVal; \
												}

//**************** STRUCT ******************************************************

struct user_t {
	int id;
	char* name;
	sexualOrientation gender;
	int birthYear;
	sexualOrientation pref;
	Set friends;
	Set friendRequests;
	double grade;
} ;

//**************** FUNCTIONS - GET THE FIELD **********************************

int userGetID(User user) {
	return user->id;
}

char* userGetName(User user) {
	return user->name;
}

sexualOrientation userGetGender(User user) {
	return user->gender;
}

int userGetBirthYear(User user) {
	return user->birthYear;
}

sexualOrientation userGetPref(User user) {
	return user->pref;
}

Set userGetFriends(User user) {
	return user->friends;
}

Set userGetFriendRequest(User user) {
	return user->friendRequests;
}

double* userGetGrade(User user) {
	return &(user->grade);
}

//**************** HELPER FUNCTIONS - CREATE MAP ******************************

// for the Key
int IDCompare(SetElement id1, SetElement id2) {
	if(*(int*)id1 > *(int*)id2) {
		return 1;
	}
	if(*(int*)id1 < *(int*)id2) {
		return -1;
	}
	return 0;
 }

void IDFree(SetElement id) {
	free(id);
}

SetElement IDCopy(SetElement id) {
	int* IDCopied = malloc(sizeof(*IDCopied));
	*IDCopied = *(int*)id;
	return IDCopied;
}

// for the Data
MapDataElement userCopy(MapDataElement user) {
	NULL_ARG(user, NULL)
	MapDataElement copiedUser = userCreate(((User)user)->id, ((User)user)->name,
			((User)user)->birthYear, ((User)user)->gender, ((User)user)->pref);
	NULL_ARG(copiedUser, NULL)
	((User)copiedUser)->grade = ((User)user)->grade;
	Set temp = ((User)copiedUser)->friends;
	((User)copiedUser)->friends = setCopy(((User)user)->friends);
	if(!((User)copiedUser)->friends) {
		userDestroy(copiedUser);
		return NULL;
	}
	setDestroy(temp);
	temp = ((User)copiedUser)->friendRequests;
	((User)copiedUser)->friendRequests = setCopy(((User)user)->friendRequests);
	if(!(((User)copiedUser)->friendRequests)) {
		userDestroy(copiedUser);
		return NULL;
	}
	setDestroy(temp);
	return copiedUser;
}


void userDestroy(MapDataElement user) {
	if(!user) {
		return;
	}
	free(((User)user)->name);
	setDestroy(((User)user)->friends);
	setDestroy(((User)user)->friendRequests);
	free(user);
}

//*****************************************************************************


User userCreate(int id, char* name, int birthYear, sexualOrientation gender,
		sexualOrientation pref) {
	NULL_ARG(name, NULL)
	User newUser = malloc(sizeof(*newUser));
	NULL_ARG(newUser, NULL)
	newUser->name = malloc(strlen(name) + 1);
	if(!newUser->name) {
		free(newUser);
		return NULL;
	}
	strcpy(newUser->name, name);
	newUser->id = id;
	newUser->gender = gender;
	newUser->birthYear = birthYear;
	newUser->pref = pref;
	newUser->grade = -1.0;
	newUser->friends = setCreate(IDCopy, IDFree, IDCompare);
	if(!newUser->friends) {
		free(newUser->name);
		free(newUser);
		return NULL;
	}
	newUser->friendRequests = setCreate(IDCopy, IDFree, IDCompare);
	if(!newUser->friendRequests) {
		setDestroy(newUser->friends);
		free(newUser->name);
		free(newUser);
		return NULL;
	}
	return newUser;
}


//*****************************************************************************

UserResult removeUserFromFriend(User user, SetElement id) {
	NULL_ARG(user, USER_NULL_ARGUMENT)
	NULL_ARG(id, USER_NULL_ARGUMENT)
	setRemove(user->friends, id);
	return USER_SUCCESS;
}

//*****************************************************************************

UserResult removeUserFromFriendReq(User user, SetElement id) {
	NULL_ARG(user, USER_NULL_ARGUMENT)
	NULL_ARG(id, USER_NULL_ARGUMENT)
	setRemove(user->friendRequests, id);
	return USER_SUCCESS;
}

//*****************************************************************************

bool checkIfIDFriend(User user, SetElement ID) {
	NULL_ARG(user, false)
	NULL_ARG(ID, false)
	if(setIsIn(user->friends, ID)) {
		return true;
	}
	return false;
}

//*****************************************************************************

bool checkIfIDInFriendRequests(User user, SetElement ID) {
	NULL_ARG(user, false)
	NULL_ARG(ID, false)
	if(setIsIn(user->friendRequests, ID)) {
		return true;
	} else {
		return false;
	}
}

//*****************************************************************************

int cntFriends(User user) {
	NULL_ARG(user, -1)
	int friendsCnt = setGetSize(user->friends);
	return friendsCnt;
}




