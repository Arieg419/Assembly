
#include "hobbies.h"

//**************** MACRO ******************************************************

#define NULL_ARG(arg, returnVal) if(arg == NULL) { \
													return returnVal; \
												}
//**************** STRUCT ******************************************************

struct hobby_t {
	Set users;
	char* name;
};

//**************** FUNCTIONS - GET THE FIELD **********************************

Set hobbyGetUsers(Hobby hobby) {
	return hobby->users;
}

char* hobbyGetName(Hobby hobby) {
	return hobby->name;
}

//**************** HELPER FUNCTIONS - CREATE MAP ******************************

// for the Key
MapKeyElement hobbyNameCopy(MapKeyElement hobbyName) {
	MapKeyElement nameCopy = malloc(strlen(hobbyName) + 1);
	NULL_ARG(nameCopy, NULL)
	strcpy(nameCopy, hobbyName);
	return nameCopy;
}

void hobbyNameFree(MapKeyElement hobbyName) {
	if(!hobbyName) {
		return;
	}
	free(hobbyName);
}

int hobbyNameCompare(MapKeyElement string1, MapKeyElement string2) { //compare keyEl func
	int cmpRes = strcmp((char*)string1, (char*)string2);
	if(cmpRes > 0) {
		return 1;
	}
	if(cmpRes < 0) {
		return -1;
	}
	return 0;
}

// for the Data
MapDataElement hobbyCopy(MapDataElement hobby) {
	NULL_ARG(hobby, NULL)
	MapDataElement newHobby = hobbyCreate(((Hobby)hobby)->name);
	Set temp = ((Hobby)newHobby)->users;
	((Hobby)newHobby)->users = setCopy(((Hobby)hobby)->users);
	setDestroy(temp);
	NULL_ARG(((Hobby)newHobby)->users, NULL)
	return newHobby;
}


void hobbyDestroy(MapDataElement hobbyToDestroy) {
	if(!hobbyToDestroy) {
		return;
	}
	if(!(((Hobby)hobbyToDestroy)->users)) {
		return;
	}
	setDestroy(((Hobby)hobbyToDestroy)->users);
	if(!(((Hobby)hobbyToDestroy)->name)) {
		return;
	}
	free(((Hobby)hobbyToDestroy)->name);
	free(hobbyToDestroy);
}

//*****************************************************************************

Hobby hobbyCreate(char* name) {
	NULL_ARG(name, NULL)
	Hobby newHobby = malloc(sizeof(*newHobby));
	NULL_ARG(newHobby, NULL)
	newHobby->name = malloc(strlen(name)+1);
	NULL_ARG(newHobby->name, NULL)
	strcpy(newHobby->name,name);
	newHobby->users =  setCreate(IDCopy, IDFree, IDCompare);
	if(!newHobby->users) {
		free(newHobby);
		return NULL;
	}
	return newHobby;
}

//*****************************************************************************


HobbyResult removeUserFromHobby(Hobby hobby, SetElement id) {
	NULL_ARG(hobby, HOBBY_NULL_ARGUMENT)
	NULL_ARG(id, HOBBY_NULL_ARGUMENT)
	Set usersInThisHobby = hobbyGetUsers(hobby);
	setRemove(usersInThisHobby, id);
	return HOBBY_SUCCESS;
}

//*****************************************************************************

bool UserInHobby(Hobby hobby, MapKeyElement ID) {
	NULL_ARG(hobby, false)
	NULL_ARG(ID, false)
	if(setIsIn(hobby->users, ID)) {
		return true;
	}
	return false;
}

//*****************************************************************************

