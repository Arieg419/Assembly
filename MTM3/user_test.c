
#include "../user.h"

//**************************** MACROS *********************************************

#define TEST_RESULT_IS(flag, funcToRun, result) if(flag && (funcToRun != result)) { \
													flag = false; \
												}

#define CHECK_IF_NOT_GOOD(flag, stringToPrint)  if(flag == false) { \
							printf("problems in the block: %s\n", stringToPrint);\
													flag = true; \
												}
//*****************************************************************************

int main() {
	char *names[6];
	names[0] = "omer";
	names[1] = "nela";
	names[2] = "reut";
	names[3] = NULL;
	names[4] = "KimKardashian";
	names[5] = "theHULK";

	int ids[6];
	ids[0] = 1234;
	ids[1] = 123445;
	ids[2] = 1234677;
	ids[3] = 123498666;
	ids[4] = 123454;
	ids[5] = 1234333333;


	sexualOrientation gender[6];
	gender[0] = M;
	gender[1] = F;
	gender[2] = F;
	gender[3] = M;
	gender[4] = F;
	gender[5] = M;

    int birthYear[6];
	birthYear[0] = 1991;
	birthYear[1] = 1991;
	birthYear[2] = 1989;
	birthYear[3] = 800;
	birthYear[4] = -69;
	birthYear[5] = 121;

	sexualOrientation pref[6];
	pref[0] = F;
	pref[1] = B;
	pref[2] = M;
	pref[3] = B;
	pref[4] = M;
	pref[5] = B;

	bool flag = true;

	//**************** create user

	int i = 0;
	User omer = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);
	i++;

	User nela = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);

	i++;
	User reut = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);
	i++;
	User nullFace = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);
	TEST_RESULT_IS(flag, nullFace, (NULL));
	i++;
	User kimKardashian = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);
	i++;
	User theHulkDude = userCreate(ids[i], names[i], birthYear[i], gender[i], pref[i]);
	i++;

	CHECK_IF_NOT_GOOD(flag, "userCreate")

	//**************** friendship

	SetResult flagger = setAdd(userGetFriends(nela), &ids[0]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(omer), &ids[1]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(nela), &ids[2]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(reut), &ids[1]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(nela), &ids[5]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(theHulkDude), &ids[1]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(omer), &ids[2]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);
	flagger = setAdd(userGetFriends(reut), &ids[0]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);

	CHECK_IF_NOT_GOOD(flag, "userGetFriends")

	//**************** test checkIfIDFriend

	TEST_RESULT_IS(flag, checkIfIDFriend(nela, &ids[0]), true);
	TEST_RESULT_IS(flag, checkIfIDFriend(omer, &ids[5]), false);

	CHECK_IF_NOT_GOOD(flag, "checkIfIDFriend")

	//**************** test cntFriends

	TEST_RESULT_IS(flag, cntFriends(nela), 3);
	TEST_RESULT_IS(flag, cntFriends(kimKardashian), 0);

	CHECK_IF_NOT_GOOD(flag, "cntFriends")

	//**************** test removeUserFromFriend

	UserResult check1 = removeUserFromFriend(nela, &ids[0]);
	TEST_RESULT_IS(flag, check1, USER_SUCCESS);
	check1 = removeUserFromFriend(omer, &ids[1]);
	TEST_RESULT_IS(flag, check1, USER_SUCCESS);

	TEST_RESULT_IS(flag, cntFriends(nela), 2);
	TEST_RESULT_IS(flag, cntFriends(omer), 1);

	CHECK_IF_NOT_GOOD(flag, "removeUserFromFriend")

	//**************** test userCopy

	MapDataElement copiedReut =  userCopy(reut);

	CHECK_IF_NOT_GOOD(flag, "userCopy")

	//**************** test userGetFriendRequest

	flagger = setAdd(userGetFriendRequest((User)copiedReut), &ids[4]);
	TEST_RESULT_IS(flag, flagger, SET_SUCCESS);

	TEST_RESULT_IS(flag, checkIfIDInFriendRequests((User)copiedReut, &ids[4]), true);

	CHECK_IF_NOT_GOOD(flag, "userGetFriendRequest")

	//**************** test removeUserFromFriendReq

	check1 =  removeUserFromFriendReq((User)copiedReut, &ids[4]);
	TEST_RESULT_IS(flag, checkIfIDInFriendRequests((User)copiedReut, &ids[4]), false);

	CHECK_IF_NOT_GOOD(flag, "removeUserFromFriendReq")

	//**************** test userDestroy

	userDestroy(nela);
	userDestroy(omer);
	userDestroy(reut);
	userDestroy(copiedReut);
	userDestroy(kimKardashian);
	userDestroy(theHulkDude);


    if(flag) {
    	printf("thats good\n");
    } else {
    	printf("nop, try again");
    }

	return 0;
}




