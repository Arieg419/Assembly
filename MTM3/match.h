
#ifndef MTM_MATCH_H_
#define MTM_MATCH_H_

#include "mtm_ex3.h"
#include "hobbies.h"
#include "list.h"




typedef struct mtm_match_t *Match;

typedef enum match_t {
	MATCH_SUCCESS,
	MATCH_NULL_ARGUMENT,
	MATCH_USER_DOES_NOT_EXIST,
	MATCH_USER_ALREADY_EXISTS,
	MATCH_INVALID_PARAMETERS,
	MATCH_OUT_OF_MEMORY,
	MATCH_NO_USERS,
	MATCH_NO_HOBBIES,
	MATCH_USER_ALREADY_FRIEND,
	MATCH_USER_NOT_FRIEND,
	MATCH_USER_NO_IN_USER_REQUEST,
	MATCH_HOBBY_DOES_NOT_EXIST,
	MATCH_USER_ALREADY_PARTICIPATES_HOBBY,
	MATCH_USER_DOESNT_PARTICIPATE_HOBBY,
	MATCH_HOBBY_ALREADY_EXISTS,
	MATCH_CANNOT_OPEN_FILE,
	MATCH_INVALID_COMMAND_LINE_PARAMETERS,

} MatchResult;

typedef enum choice_t{
	deny,
	accept,
} choice;
/*
 * This function return the users associated with any given Match. In other words, it
 * returns a map of users.
 */
Map matchGetUsers(Match match);
/*
 * Function returns the hobbies associated with any given match.
 * Returns a map of Hobbies.
 */
Map matchGetHobbies(Match match);
/*
 * This function is responsible for allocating the needed memory to support our Match Struct.
 * Returns a pointer pointing to the newly allocated match.
 */
Match matchCreate();
/*
 * This is a destroyer function responsible for destroying all the allocated memory needed originally for the Match.
 */
void matchDestroy(Match matchToDestroy);
/*
 * Function creates a new copy of the passed Match including all of it's internal fields.
 */
MatchResult matchCopy(Match match);
/*
 * The function is passed a function pointer. The  function checks whether or not
 * an element is in a certain set.
 *
 */
typedef bool(*CheckIfElementInSet)(User, SetElement);
/*
 * The function is passed a function pointer. The function removes an element from a set.
 */
typedef UserResult(*removeElementFromSet)(User, SetElement);
/*
 * This function removes a user from all of the friends in the database, while also
 * removing the user from all existing friend requests.
 */
void removeUserFromFriendsAndFriendReq(Map users, MapKeyElement id,
		CheckIfElementInSet checkFunc, removeElementFromSet removeFunc);
/*
 * This function removes a user from his hobbies.
 */
void removeUserFromHobbies(Map hobbies, MapKeyElement id);

MatchResult userRemove(Match match, int id);

MatchResult userAdd(Match match, int id, char* nameOfUser, int birthYear, sexualOrientation gender, sexualOrientation pref);
/*
 * This function converts a map to a list.
 */
List mapToList(Map map, CompareListElements cmpFunc, CopyListElement copyFunc, FreeListElement destroyFunc);
/*
 * This function counts how many users are in a given hobby.
 */
int userHobbyCnt(ListElement id, Map hobbies);
/*
 * This function compares ID's. This is a normal numerical comparison.
 */
int userIDCompare(ListElement user1, ListElement user2);

MatchResult reportUsers(Match match, FILE* outputFile);

MatchResult friendRequest(int requesting_id, int requested_id, Match match);

UserResult userUnFriend(int requesting_id, int requested_id, Match match);

MatchResult handleRequest(int requesting_id, int requested_id, choice userChoice, Match match);

MatchResult hobbyRemove(Match match, char* name);

MatchResult hobbyJoin(Match match, char* name, int id);
/*
 * This function checks whether or not a Hobby already exists.
 */
bool hobbyAlreadyExist(char** namesOfHobbies, int index, MapKeyElement name);
/*
 * This function is used as a helper function by reporthobbiesByAge. For a given age it checks what hobbies people participate
 * in that age group.
 */
void findHobbies(Map hobbies, MapKeyElement id, char** namesOfHobbies, int* index, bool* flag);
/*
 * Receives an array of hobby names, and sorts them lexicographically.
 */
void sortString(char** stringToPrint, int len);
/*
 * This function finds the minimum birth year in the user map.
 */
int findMinBirthYear(Map users);

MatchResult reportHobbiesByAge(Match match, FILE* outputFile);

MatchResult hobbyAdd(Match match, char* hobbyName);

MatchResult hobbyLeave(Match match, char* hobbyName, int id);
/*
 * CalcGrade is a helper function that calculates grades for every user.
 */
void calcGrade(User userForDate, int id1, User userToCheck, int id2, Map hobbies);
/*
 * Check the conditions(sexual preferences, etc). If a user is a match for the requested user
 * it will be printed to the standard output.
 */
ListResult printByGrade(int id,char* name, int count, Match match, FILE* outputFile);
/*
 * This function compares grades numerically.
 */
int userGradeCompare(ListElement user1, ListElement user2);

MatchResult userWhoCanIDate(int id, int count, Match match, FILE* outputFile);
/*
 * This function compares hobbies by number of users.
 */
int compareByNumOfUsers(ListElement hobby1, ListElement hobby2);

MatchResult hobbyReport(Match match, int count, FILE* outputFile);





#endif /* MTM_MATCH_H_ */
