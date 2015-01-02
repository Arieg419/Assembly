
#ifndef USER_H_
#define USER_H_

#include "set.h"
#include "map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum sexualOrientation_t{
	M,
	F,
	B,
} sexualOrientation;

typedef enum UserResult_t {
	USER_SUCCESS,
	USER_NULL_ARGUMENT,
	USER_OUT_OF_MEMORY,
} UserResult;


typedef struct user_t *User;
/*
 * This function gets every users ID.
 */
int userGetID(User user);
/*
 * This function fetches every users name.
 */
char* userGetName(User user);
/*
 * This function fetches a users gender.
 */
sexualOrientation userGetGender(User user);
/*
 * This function fetches a users birth year and returns an int.
 */
int userGetBirthYear(User user);
/*
 * This function gets user preference and returns his sexualOrientation.
 */
sexualOrientation userGetPref(User user);
/*
 * This function fetches a users friends and returns a point to a set.
 */
Set userGetFriends(User user);
/*
 * This function fetches all of a users friend requests and returns a pointer to the set of fh
 * his friend requests.
 */
Set userGetFriendRequest(User user);
/*
 * This function returns a users grade.
 */
double* userGetGrade(User user);
/*
 * This is a function that compares User ID's. It is a standrard numerical comparision.
 */
int IDCompare(SetElement id1, SetElement id2);
/*
 * This function frees aan Id previously allocated with malloc.
 */
void IDFree(SetElement id);
/*
 * This functions returns a newly created copy of the ID
 */
SetElement IDCopy(SetElement id);
/*
 * This functions allocates the needed memory determined by our user Struct. Returns a pointer to the newly
 * created user.
 */
User userCreate(int id, char* name, int birthYear, sexualOrientation gender, sexualOrientation pref);
/*
 * This is a destroyer function responsible for freeing the memory.
 */
void userDestroy(MapDataElement user);

MapDataElement userCopy(MapDataElement user);
/*
 * Iterating over all of users friends. Erasing the users ID from everyone elses friends lists.
 */
UserResult removeUserFromFriend(User user, SetElement id);
/*
 * After removing a friend, this function will delete the removed friends existing friends requests.
 * This should happen because he is no longer part of the database.
 */
UserResult removeUserFromFriendReq(User user, SetElement id);
/*
 * This function checks if the ID passed is part of the users friends list. In essence, we are checking whether
 * or not they are actually friends.
 */
bool checkIfIDFriend(User user, SetElement ID);
/*
 * Here we are checking whether or not the passed ID is in the user friend request "inbox." We are checking if a friend request has
 * been made yet.
 */
bool checkIfIDInFriendRequests(User user, SetElement ID);
/*
 * This function counts how many friends the User has.
 */
int cntFriends(User user);


#endif /* USER_H_ */
