CC = gcc
CFLAGS = -O1 -g -Wall -Wextra

GIT_HOOKS := .git/hooks/applied



all: $(GIT_HOOKS) q1 q2 q3 q4 q5 q6
clean:
		rm -rf q1 q2 q3 q4 q5 q6



$(GIT_HOOKS):
		@scripts/install-git-hooks
		@echo

q1: q1.c
	$(CC) $(CFLAGS) q1.c -o q1

q2: q2.c
	$(CC) $(CFLAGS) q2.c -o q2
q3: q3.c
	$(CC) $(CFLAGS) q3.c -o q3
q4: q4.c
	$(CC) $(CFLAGS) q4.c -o q4
q5: q5.c
	$(CC) $(CFLAGS) q5.c -o q5
q6: q6.c
	$(CC) $(CFLAGS) q6.c -o q6
