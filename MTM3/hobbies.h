
#ifndef HOBBIES_H_
#define HOBBIES_H_


#include "user.h"

typedef enum HobbyResult_t {
	HOBBY_SUCCESS,
	HOBBY_NULL_ARGUMENT,
	HOBBY_OUT_OF_MEMORY,
} HobbyResult;


typedef struct hobby_t *Hobby;

/*
 * This function retrieves a set of the hobbies users.
 */
Set hobbyGetUsers(Hobby hobby);
/*
 * This function retrieves the name of the hobby.
 */
char* hobbyGetName(Hobby hobby);
/*
 * HobbyCreate func creates a new hobby in our database using the Hobby Struct.
 */
Hobby hobbyCreate(char* name);
/*
 * This is the destroyer function responsible for releasing all of the memory associated with a given hobby.
 */
void hobbyDestroy(MapDataElement hobbyToDestroy);
/*
 * This function returns a new copy of the hobby including all of its internal fields.
 */
MapDataElement hobbyCopy(MapDataElement hobby);
/*
 * This function removes the passed ID from the targeted ID's hobby List. The user is no longer
 * an active participant in the hobby.
 */
HobbyResult removeUserFromHobby(Hobby hobby, SetElement id);
/*
 * This function checks whether or not a specific user participates in a given hobby.
 */
bool UserInHobby(Hobby hobby, MapKeyElement ID);
/*
 * Function that copies a hobbies name and returns a copy.
 */
MapKeyElement hobbyNameCopy(MapKeyElement hobbyName);
/*
 * This frees the string that previously held the Hobby Name.
 */
void hobbyNameFree(MapKeyElement hobbyName);
/*
 * This compares hobby names using the string compare function from the string.h library.
 *
 */
int hobbyNameCompare(MapKeyElement string1, MapKeyElement string2);



#endif /* HOBBIES_H_ */
