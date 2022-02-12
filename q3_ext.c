#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define time_cost \
    end_t.tv_sec * 1e9 + end_t.tv_nsec - start_t.tv_sec * 1e9 - start_t.tv_nsec

typedef struct div_info_s div_info_t;
struct div_info_s {
    uint32_t magic;
    size_t d;
};

void div_init(div_info_t *div_info, size_t d)
{
    assert(d != 0);
    assert(d != 1);

    uint64_t two_to_k = ((uint64_t) 1 << 32);
    uint32_t magic = (uint32_t)(two_to_k / d);

    if (two_to_k % d != 0) {
        magic++;
    }
    div_info->magic = magic;
    div_info->d = d;
}

static inline size_t div_compute(div_info_t *div_info, size_t n)
{
    size_t i = ((uint64_t) n * (uint64_t) div_info->magic) >> 32;
    return i;
}

size_t div_normal(size_t num, int divisor)
{
    size_t i = num / divisor;
    return i;
}



int main()
{
    printf("pid: %d\n", getpid());
    struct timespec start_t, end_t;
    const int max_i = 46340;  // choose a propriate integer, make sure that
                              // integer overflow won't be occurred in num.
    size_t num[max_i - 2];
    long long int fast_times = 0,
                  normal_times = 0;  // record the time cost by divisions.
    div_info_t M;                    // a struct where magic number stored.

    FILE *fp;
    fp = fopen("q3_ext_output.txt", "w");
    assert(fp);


    srand(time(NULL));
    /*******************************************************
for (int i = 2; i < max_i; i++) {
    num[i - 2] =
        rand() % max_i * i;  //試試把亂數存在 array , 給兩個 division 去取用
    div_init(&M, i);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
    answer = div_compute(&M, num[i - 2]);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
    fast_times += end_t.tv_sec * 1e9 + end_t.tv_nsec -
                  start_t.tv_sec * 1e9 - start_t.tv_nsec;
}
printf("The average time costs by jemalloc_division is %lld nanoseconds.\n",
       fast_times / (max_i - 2));

for (int i = 2; i < max_i; i++) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
    answer = div_normal(num[i - 2], i);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
    normal_times += end_t.tv_sec * 1e9 + end_t.tv_nsec -
                    start_t.tv_sec * 1e9 - start_t.tv_nsec;
}
printf("The average time costs by normal_division is %lld nanoseconds.\n",
       normal_times / (max_i - 2));
    *******************************************************/
    ///********************************************************
    for (int i = 2; i < max_i; i++) {
        long long int output_t;
        num[i - 2] = rand() % max_i * i;
        div_init(&M, i);

        fprintf(fp, "%3d ", i);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
        div_compute(&M, num[i - 2]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
        fast_times += time_cost;
        output_t = time_cost;
        fprintf(fp, "%3lld ", output_t);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
        div_normal(num[i - 2], i);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);
        normal_times += time_cost;
        output_t = time_cost;
        fprintf(fp, "%3lld \n", output_t);
    }

    printf("The average time costs by jemalloc_division is %lld nanoseconds.\n",
           fast_times / (max_i - 2));
    printf("The average time costs by normal_division is %lld nanoseconds.\n",
           normal_times / (max_i - 2));
    fclose(fp);
    //*******************************************************/
    //    size_t sss = 123;
    //    sss = do_nothing(&answer);
    /*******************************************************
     * 以下是用來測試 clock_gettime() 的其他參數
    ////////////////////////////////////////////////////////

    clock_gettime(CLOCK_MONOTONIC_RAW, &start_t);
    // answer = div_normal(num, max_i - 1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_t);

    printf("MONOTONIC:\n%ld\n%ld\n%ld\n%ld\n", start_t.tv_sec,
    start_t.tv_nsec, end_t.tv_sec, end_t.tv_nsec); long long tt =
    end_t.tv_sec * 1e9 + end_t.tv_nsec - start_t.tv_sec * 1e9 -
                   start_t.tv_nsec;
    printf("Wall-time : %lld\n", tt);

    //////////////////////////////////////////////////////////

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_t);
    // answer = div_normal(num, max_i - 1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_t);

    printf("CPUTIME:\n%ld\n%ld\n%ld\n%ld\n", start_t.tv_sec,
    start_t.tv_nsec, end_t.tv_sec, end_t.tv_nsec); tt = end_t.tv_sec *
    1000000000 + end_t.tv_nsec - start_t.tv_sec * 1000000000 -
    start_t.tv_nsec; printf("CPU clocks elapsed: %lld\n", tt);
    printf("CPU-time : %lu\n", CLOCKS_PER_SEC);

    ///////////////////////////////////////////////////////////
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    // answer = div_normal(num, max_i - 1);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nclock_t start =  %ld\nclock_t end = %ld\n", start, end);
    *************************************************************/
}
