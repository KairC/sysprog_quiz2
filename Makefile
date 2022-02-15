CC = gcc
CFLAGS = -O1 -g -Wall -Wextra

GIT_HOOKS := .git/hooks/applied



all: $(GIT_HOOKS) q1 q2 q3 q4 q5 q6 q1_ext2 q1_ext3 q2_ext q3_ext
plot: q1_ext3_plot q3_ext_plot
clean:
		rm -rf q1 q1_ext2 q1_ext3 q2 q2_ext q3 q3_ext q4 q5 q6
format:
	    clang-format -i *.c


$(GIT_HOOKS):
		@scripts/install-git-hooks
		@echo

q3_ext_plot: q3_ext_output.txt
		gnuplot scripts/q3_ext_runtime.gp

q1_ext3_plot: q1_ext3_output.txt
	    gnuplot scripts/q1_ext3_runtime.gp

q1: q1.c
	$(CC) $(CFLAGS) q1.c -o q1
q1_ext2: q1_ext2.c
	$(CC) $(CFLAGS) q1_ext2.c -o q1_ext2
q1_ext3: q1_ext3.c
	$(CC) -msse4.2 -O0 -g -Wall q1_ext3.c -o q1_ext3
q2: q2.c
	$(CC) $(CFLAGS) q2.c -o q2
q2_ext: q2_ext.c
	$(CC) $(CFLAGS) q2_ext.c -o q2_ext
q3: q3.c
	$(CC) $(CFLAGS) q3.c -o q3
q3_ext: q3_ext.c
	$(CC) -O0 -g -Wall q3_ext.c -o q3_ext
q4: q4.c
	$(CC) $(CFLAGS) q4.c -o q4
q5: q5.c
	$(CC) $(CFLAGS) q5.c -o q5
q6: q6.c
	$(CC) $(CFLAGS) q6.c -o q6
