#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}
                                      };

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            if (seed <= 0)
            	printf("Error: Seed not received or negative.");
            break;
          case 1:
            array_size = atoi(optarg);
            if (array_size <= 0)
            	printf("Error: array_size variable must be a positive number.");
            break;
          case 2:
            pnum = atoi(optarg);
            if (array_size <= 0)
            	printf("Error: pnum variable must be a positive number.");
            break;
        
            break;
          case 3:
            with_files = true;
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc-1) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  //For one thread processing.
  int processing_len = (pnum < array_size)? (array_size/pnum ) : 1;

  //Preparing bytes transfer.
  int pipe_entered_points[2];
  FILE* shared_file;
  if(with_files){
    shared_file = fopen("lab3_file", "w+"); //Create or rewrite.
  }
  else if (pipe(pipe_entered_points) == -1){
    //If we don't have a file flag and pipes.
    printf("Error: Output place are incorrect (pipes of file flag require).");
    return -1;
  }


  for (int i = 0; i < pnum; i++) {
    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0) {
        // child process
        // parallel somehow
        unsigned int begin = processing_len * (active_child_processes-1);
        begin = (begin >= array_size)? (array_size-1): begin;
        unsigned int end = processing_len * active_child_processes;
        end = (end >= array_size)? (array_size) : end; 
        struct MinMax curr_min_max = GetMinMax(array, begin, end);

        if (with_files) {
          // use files here
          fwrite(&curr_min_max, sizeof(struct MinMax), 1, shared_file);
        } else {
          // use pipe here
          write(pipe_entered_points[1], &curr_min_max, sizeof(struct MinMax));
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  while (active_child_processes > 0) {
    // your code here
    wait(NULL);// wait childs processings.
    active_child_processes -= 1;
  }
  //End childs processings.

  struct MinMax min_max, tmp_minmax;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (int i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files) {
      // read from files
      fclose(shared_file);
      shared_file = fopen("lab3_file", "r");
      fread(&tmp_minmax, sizeof(struct MinMax), 1, shared_file);
    } else {
      // read from pipes
      read(pipe_entered_points[0], &tmp_minmax, sizeof(struct MinMax));
    }

    min = tmp_minmax.min; max = tmp_minmax.max;

    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}
