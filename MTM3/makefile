CC = gcc 
COMPILATION_FLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
OBJECT_LIST = hobbies.o user.o match.o mtm_match.o list_mtm.o
RUN_FLAGS = -L. -lmtm
MATCH_TEST_ARGS = ./tests/match_test.c match.h list.h hobbies.h user.h set.h map.h mtm_ex3.h

USER_TEST_ARGS = ./tests/user_test.c user.h set.h map.h

HOBBY_TEST_ARGS = ./tests/hobby_test.c hobbies.h user.h set.h map.h

LIST_TEST_ARGS = ./tests/list_test.c list_mtm1.h

EXEC = match_executable
RUN_TESTS = match_test hobby_test user_test list_test 
TEST_OBJECT_LIST = hobby_test.o user_test.o match_test.o list_test.o

$(EXEC): $(OBJECT_LIST)
	$(CC) $(COMPILATION_FLAGS) $(OBJECT_LIST) $(RUN_FLAGS) -o $(EXEC)

mtm_match.o:  match.h hobbies.h user.h set.h map.h mtm_ex3.h list.h
	$(CC) -c $(COMPILATION_FLAGS) $*.c

match.o: match.c match.h hobbies.h user.h set.h map.h mtm_ex3.h list.h
	$(CC) -c $(COMPILATION_FLAGS) $*.c

hobbies.o: hobbies.c hobbies.h user.h set.h map.h
	$(CC) -c $(COMPILATION_FLAGS) $*.c

user.o: user.c user.h set.h map.h
	$(CC) -c $(COMPILATION_FLAGS) $*.c

list_mtm.o: ./list_mtm/list_mtm.c list_mtm1.h
	$(CC) -c $(COMPILATION_FLAGS) ./list_mtm/$*.c

#-c flag says stop after compilation and do not link yet

tests: $(RUN_TESTS)
#tests is the targets while RUN TESTS is all the files  I need to create

match_test.o: $(MATCH_TEST_ARGS)
	$(CC) -c $(COMPILATION_FLAGS) ./tests/$*.c

hobby_test.o: $(HOBBY_TEST_ARGS)
	$(CC) -c $(COMPILATION_FLAGS) ./tests/$*.c

user_test.o: $(USER_TEST_ARGS)
	$(CC) -c $(COMPILATION_FLAGS) ./tests/$*.c

list_test.o: $(LIST_TEST_ARGS)
	$(CC) -c $(COMPILATION_FLAGS) ./tests/$*.c



match_test: match_test.o
	$(CC) match_test.o match.o hobbies.o user.o $(RUN_FLAGS) -o $@
user_test: user_test.o
	$(CC) user_test.o user.o $(RUN_FLAGS) -o $@

hobby_test: hobby_test.o 
	$(CC) hobby_test.o hobbies.o user.o $(RUN_FLAGS) -o $@

list_test: list_test.o
	$(CC) list_test.o $(RUN_FLAGS) -o $@

clean:
	rm -f $(OBJECT_LIST) $(TEST_OBJECT_LIST) $(RUN_TESTS) $(EXEC)
