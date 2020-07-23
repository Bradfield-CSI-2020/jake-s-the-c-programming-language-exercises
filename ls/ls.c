/*
    Minimally, it should list the contents of a directory including some information about each file,
    such as file size. As a stretch goal, use man ls to identify any interesting flags you may wish
    to support, and implement them.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


#define PATH_LEN 100

void ls(char *);
int alphasort(const struct dirent **d1, const struct dirent **d2);
int select(const struct dirent *);

int main(int argc, char * argv[]) {
  if (argc == 1) {
    ls(".");
  } else {
    ls(argv[1]);
  }
  exit(0);
}

void ls(char * path) {
  int numdir;
  DIR * directoryPointer;
  struct dirent * directoryEntity;
  struct stat statbuffer;
  struct dirent ** namelist;

  // load stat into statbuffer
  stat(path, &statbuffer);
  if ((statbuffer.st_mode & S_IFMT) == S_IFDIR) {
    // true if file is a directory
    // directoryPointer = opendir(path);
    // if (directoryPointer == NULL) exit(1);
    numdir = scandir(path, &namelist, select, alphasort);
    while (numdir > 0) {
      printf("%s\n", (*namelist)->d_name);
      namelist++;
      numdir--;
    }

  } else {    
    printf("%s\n", path);
  }

}

int select(const struct dirent * d) {
  if(d->d_name[0] == '.') return 0;
  return 1;
}

/*
  DIR * directoryPointer;
  FILE * filePointer;
  struct dirent * directoryEntity;
  struct stat currentStat;
  char pathspace[PATH_LEN];
  char * path = pathspace;

  directoryPointer = opendir(".");
  stat(path, &currentStat);

  if (directoryPointer == NULL) {
    printf("fuck\n");
    exit(1);
  } else {
    while((directoryEntity = readdir(directoryPointer)) != NULL) {
      printf("%s\n", directoryEntity->d_name);
      sprintf(path, "./%s", directoryEntity->d_name);

      printf("%s\n", ((currentStat.st_mode & S_IFMT) == S_IFDIR) ? "directory" : "file");
    }
  }

*/