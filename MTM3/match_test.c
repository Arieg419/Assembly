
#include "../match.h"

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

int main() {

	// data for users
	    char *names[10];
		names[0] = "omer";
		names[1] = "nela";
		names[2] = "reut";
		names[3] = "david";
		names[4] = "nimit";
		names[5] = "harris";
		names[6] = "james";
		names[7] = "oded";
		names[8] = "galit";
		names[9] = "dor";

		int omerID = 8;
		int nelaID = 2;
		int reutID = 3;
		int davidID = 4;
		int nimitID = 5;
		int harrisID = 6;
		int jamesID = 7;
		int galitID = 1;
		int odedID = 9;
		int dorID = 10;

		sexualOrientation gender[10];
		gender[0] = M;
		gender[1] = F;
		gender[2] = F;
		gender[3] = M;
		gender[4] = F;
		gender[5] = M;
		gender[6] = F;
		gender[7] = M;
		gender[8] = F;
		gender[9] = M;



	    int birthYear[10];
		birthYear[0] = 1991;
		birthYear[1] = 1991;
		birthYear[2] = 1989;
		birthYear[3] = 800;
		birthYear[4] = 123;
		birthYear[5] = 1990;
		birthYear[6] = 1989;
		birthYear[7] = 800;
		birthYear[8] = 1991;
		birthYear[9] = 121;

		sexualOrientation pref[10];
		pref[0] = F;
		pref[1] = B;
		pref[2] = M;
		pref[3] = B;
		pref[4] = M;
		pref[5] = B;
		pref[6] = M;
		pref[7] = B;
		pref[8] = M;
		pref[9] = B;

		// data for hobbies
		char* basketball = "basketball";
		char* swimming = "swimming";
		char* reading = "reading";
		char* movies = "movies";
		char* sharkFishing = "sharkFishing";
		char* guitar = "guitar";
		char* dancing = "dancing";
		char* running = "running";
		char* kayak = "kayak";
		char* travel = "travel";


		Match match = matchCreate();
		bool flag = true;

		//**************** test some cases
		MatchResult flagReport = hobbyReport(match, 3, stdout);
		TEST_RESULT_IS(flag, flagReport, MATCH_NO_HOBBIES);

		flagReport = reportHobbiesByAge(match, stdout);
		TEST_RESULT_IS(flag, flagReport, MATCH_NO_HOBBIES);

		CHECK_IF_NOT_GOOD(flag, "test some cases")

		//**************** test hobbyAdd
		MatchResult hobbyChecker;

		hobbyChecker = hobbyAdd(match, basketball);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, swimming);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, reading);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, movies);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, sharkFishing);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, guitar);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
		hobbyChecker = hobbyAdd(match, dancing);
		TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
	   hobbyChecker = hobbyAdd(match, running);
	   TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
	   hobbyChecker = hobbyAdd(match, kayak);
	   TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);
	   hobbyChecker = hobbyAdd(match, travel);
	   TEST_RESULT_IS(flag, hobbyChecker, MATCH_SUCCESS);

		CHECK_IF_NOT_GOOD(flag, "hobbyAdd")

		//**************** test userAdd
		flagReport = reportHobbiesByAge(match, stdout);
		TEST_RESULT_IS(flag, flagReport, MATCH_NO_USERS);
		MatchResult check;
		check = userAdd(match, omerID, names[0], birthYear[0], gender[0], pref[0]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, nelaID, names[1], birthYear[1], gender[1], pref[1]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, reutID, names[2], birthYear[2], gender[2], pref[2]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, davidID, names[3], birthYear[3], gender[3], pref[3]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);

		check = userAdd(match, reutID, names[2], birthYear[2], gender[2], pref[2]);
		TEST_RESULT_IS(flag, check, MATCH_USER_ALREADY_EXISTS);
		check = userAdd(match, davidID, names[3], birthYear[3], gender[3], pref[3]);
		TEST_RESULT_IS(flag, check, MATCH_USER_ALREADY_EXISTS);

		check = userAdd(match, nimitID, names[4], birthYear[4], gender[4], pref[4]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, harrisID, names[5], birthYear[5], gender[5], pref[5]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, jamesID, names[6], birthYear[6], gender[6], pref[6]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, odedID, names[7], birthYear[7], gender[7], pref[7]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, galitID, names[8], birthYear[8], gender[8], pref[8]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);
		check = userAdd(match, dorID, names[9], birthYear[9], gender[9], pref[9]);
		TEST_RESULT_IS(flag, check, MATCH_SUCCESS);

		check = userAdd(match, 0, "nnn", -1990, F,M);
		TEST_RESULT_IS(flag, check, MATCH_INVALID_PARAMETERS);

		printf("-----------------test reportUsers------------------------\n");
		reportUsers(match, stdout);

		reportHobbiesByAge(match, stdout);

		CHECK_IF_NOT_GOOD(flag, "userAdd")

		//**************** test ask for friend and handle the req
		// nela friends

				MatchResult flagger = friendRequest(nelaID, omerID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				MatchResult handleCheck;
				handleCheck = handleRequest(nelaID, omerID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer + Nela

				flagger = friendRequest(nelaID, reutID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, reutID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + Reut

				flagger = friendRequest(nelaID, nimitID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, nimitID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + Nimit

				flagger = friendRequest(nelaID, davidID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, davidID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + David

				flagger = friendRequest(nelaID, dorID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, dorID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + Dor

				flagger = friendRequest(nelaID, galitID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, galitID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + Galit

				flagger = friendRequest(nelaID, odedID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);

				handleCheck = handleRequest(nelaID, odedID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + Oded

				flagger = friendRequest(nelaID, jamesID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, jamesID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela + James

				flagger = friendRequest(nelaID, harrisID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, harrisID, deny, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Nela and Harris  NOT friends!!!
				CHECK_IF_NOT_GOOD(flag, "friend req-nela's friends")
		// omer friends
				flagger = friendRequest(omerID, reutID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, reutID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and Reut

				flagger = friendRequest(omerID, odedID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, odedID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer And Oded

				flagger = friendRequest(omerID, galitID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, galitID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and Galit

				flagger = friendRequest(omerID, davidID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, davidID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and David

				flagger = friendRequest(omerID, harrisID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, harrisID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and Harris

				flagger = friendRequest(omerID, nimitID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, nimitID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and Nimit

				flagger = friendRequest(omerID, dorID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, dorID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and Dor

				flagger = friendRequest(omerID, jamesID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(omerID, jamesID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer and James
				CHECK_IF_NOT_GOOD(flag, "friend req-omer's friends")

		// Jame's Friends
				flagger = friendRequest(jamesID, odedID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(jamesID, odedID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				// James and Oded

				flagger = friendRequest(jamesID, harrisID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(jamesID, harrisID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				// James and Harris

				flagger = friendRequest(jamesID, reutID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(jamesID, reutID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				// James and Reut

				flagger = friendRequest(jamesID, nimitID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(jamesID, nimitID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//James and Nimit

				flagger = friendRequest(jamesID, davidID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(jamesID, davidID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//James and David

				CHECK_IF_NOT_GOOD(flag, "friend req-James's friends")

		// test other cases
				flagger = friendRequest(jamesID, davidID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_USER_ALREADY_FRIEND);

				flagger = friendRequest(omerID, nelaID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_USER_ALREADY_FRIEND);

				int fakeID = 123;
				flagger = friendRequest(fakeID, davidID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_USER_DOES_NOT_EXIST);

				handleCheck = handleRequest(galitID, jamesID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_USER_NO_IN_USER_REQUEST);

				handleCheck = handleRequest(fakeID, davidID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_USER_DOES_NOT_EXIST);

				CHECK_IF_NOT_GOOD(flag, "friend req-other cases")

		//**************** test hobbyJoin
			printf("-------------------- test hobbyReport--------------------------------\n");
			 hobbyReport(match, 0, stdout);

				//JOINING BASKETBALL
				MatchResult flagHobbyJoin;
				flagHobbyJoin = hobbyJoin(match, basketball, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, basketball, odedID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

		//**************** test reportHobbiesByAge
				printf("------------------ test reportHobbiesByAge----------------\n");
				reportHobbiesByAge(match, stdout);


				flagHobbyJoin = hobbyJoin(match, basketball, harrisID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

			// JOINING SWIMMING
				flagHobbyJoin = hobbyJoin(match, swimming, harrisID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, odedID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, reutID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, nimitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, davidID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, jamesID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, swimming, odedID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_USER_ALREADY_PARTICIPATES_HOBBY);
				CHECK_IF_NOT_GOOD(flag, "hobbyJoin")


		//**************** test reportHobbies
					printf("------------------ test hobbyReport----------------\n");
					hobbyReport(match, 5, stdout);

				// JOINING READING
				flagHobbyJoin = hobbyJoin(match, reading, dorID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				CHECK_IF_NOT_GOOD(flag, "hobbyReport")


		//**************** test reportHobbiesByAge
				printf("-----------------test reportHobbiesByAge------------------\n");
				 reportHobbiesByAge(match, stdout);
				CHECK_IF_NOT_GOOD(flag, "reportHobbiesByAge")


				flagHobbyJoin = hobbyJoin(match, reading, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				//JOINING SHARKFISHING
				flagHobbyJoin = hobbyJoin(match, sharkFishing, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				flagHobbyJoin = hobbyJoin(match, sharkFishing, nelaID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);


				//**************** test userWhoCanIDate
				flagReport = userWhoCanIDate(nelaID, -13, match, stdout);
				TEST_RESULT_IS(flag, flagReport, MATCH_INVALID_PARAMETERS);

				flagHobbyJoin = userUnFriend(nelaID, omerID, match);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagReport = userWhoCanIDate(nelaID, 3, match, stdout);
				CHECK_IF_NOT_GOOD(flag, "userWhoCanIDate")

				// return omer



				flagger = friendRequest(nelaID, omerID, match);
				TEST_RESULT_IS(flag, flagger, MATCH_SUCCESS);
				handleCheck = handleRequest(nelaID, omerID, accept, match);
				TEST_RESULT_IS(flag, handleCheck, MATCH_SUCCESS);
				//Omer + Nela

				//JOINING TRAVEL
				flagHobbyJoin = hobbyJoin(match, travel, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				flagHobbyJoin = hobbyJoin(match, travel, reutID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				flagHobbyJoin = hobbyJoin(match, travel, dorID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				printf("-------------------- hobbyReport -------------------------\n");
				 hobbyReport(match, 20, stdout);
				printf("-----------------------------------------------------------\n");

				flagReport = hobbyReport(match, -20, stdout);
				TEST_RESULT_IS(flag, flagReport, MATCH_INVALID_PARAMETERS);

				// JOINING RUNNING
				flagHobbyJoin = hobbyJoin(match, running, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, running, nelaID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, running, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				// JOIN KAYAK
				flagHobbyJoin = hobbyJoin(match, kayak, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, kayak, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);
				flagHobbyJoin = hobbyJoin(match, kayak, odedID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				// DANCING
				flagHobbyJoin = hobbyJoin(match, dancing, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_SUCCESS);

				// Checking edge cases for Hobby Join function
				char* baseball = "baseball";
				flagHobbyJoin = hobbyJoin(match, baseball, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_HOBBY_DOES_NOT_EXIST);

				char* dragonTaming = "dragonTaming";
				flagHobbyJoin = hobbyJoin(match, dragonTaming, galitID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_HOBBY_DOES_NOT_EXIST);

				// Fake ID
				flagHobbyJoin = hobbyJoin(match, reading, fakeID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_USER_DOES_NOT_EXIST);

				// Already Part of Hobby
				flagHobbyJoin = hobbyJoin(match, basketball, omerID);
				TEST_RESULT_IS(flag, flagHobbyJoin, MATCH_USER_ALREADY_PARTICIPATES_HOBBY);

				CHECK_IF_NOT_GOOD(flag, "hobbyJoin")

		//**************** test hobbyLeave

				 MatchResult FYI;
				 FYI = hobbyLeave(match, basketball, omerID);
				 TEST_RESULT_IS(flag, FYI, MATCH_SUCCESS)
				  FYI = hobbyLeave(match, swimming, nelaID);
				 TEST_RESULT_IS(flag, FYI, MATCH_USER_DOESNT_PARTICIPATE_HOBBY)
				 FYI = hobbyLeave(match, swimming, reutID);
				 TEST_RESULT_IS(flag, FYI, MATCH_SUCCESS)
				 FYI = hobbyLeave(match, running, nelaID);
				 TEST_RESULT_IS(flag, FYI, MATCH_SUCCESS)
				 FYI = hobbyLeave(match, travel, dorID);
				 TEST_RESULT_IS(flag, FYI, MATCH_SUCCESS)
				 FYI = hobbyLeave(match, sharkFishing, nelaID);
				 TEST_RESULT_IS(flag, FYI, MATCH_SUCCESS)

				 char* fakeHobby = "icecurling";
				 FYI = hobbyLeave(match, fakeHobby, nelaID);
				 TEST_RESULT_IS(flag, FYI, MATCH_HOBBY_DOES_NOT_EXIST)
				 FYI = hobbyLeave(match, basketball, fakeID);
				 TEST_RESULT_IS(flag, FYI, MATCH_USER_DOES_NOT_EXIST)

				 MatchResult hobbyRemoveFlag;
				 hobbyRemoveFlag = hobbyRemove(match, dancing);
				 TEST_RESULT_IS(flag, hobbyRemoveFlag, MATCH_SUCCESS);

				  char* skydiving = "skydiving";
				  hobbyRemoveFlag = hobbyRemove(match, skydiving);
				  TEST_RESULT_IS(flag, hobbyRemoveFlag, MATCH_HOBBY_DOES_NOT_EXIST);

				CHECK_IF_NOT_GOOD(flag, "hobbyLeave")

		//**************** test userRemove
			  MatchResult userRemoveFlag;
			  userRemoveFlag = userRemove(match, fakeID);
			  TEST_RESULT_IS(flag, userRemoveFlag, MATCH_USER_DOES_NOT_EXIST);
			  CHECK_IF_NOT_GOOD(flag, "userRemove")

		//**************** test userUnFriend
			  MatchResult userUnfriendFlag;
			   userUnfriendFlag = userUnFriend(nelaID, reutID, match);
			   TEST_RESULT_IS(flag, userUnfriendFlag, MATCH_SUCCESS)
			  userUnfriendFlag = userUnFriend(nelaID, reutID, match);
			  TEST_RESULT_IS(flag, userUnfriendFlag, MATCH_USER_NOT_FRIEND)
		      userUnfriendFlag = userUnFriend(nimitID, fakeID, match);
		      TEST_RESULT_IS(flag, userUnfriendFlag, MATCH_USER_DOES_NOT_EXIST)

			CHECK_IF_NOT_GOOD(flag, "userUnFriend")

		//**************** test matchDestroy
			   matchDestroy(match);

	   if(flag) {
		   printf("good job darling :) \n" );
	   }
	   else {
		   printf("failed..try again :) \n");
	   }

	return 0;
}

