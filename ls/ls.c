/*
    Minimally, it should list the contents of a directory including some information about each file,
    such as file size. As a stretch goal, use man ls to identify any interesting flags you may wish
    to support, and implement them.
*/

#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <uuid/uuid.h>


#define PATH_LEN 100
#define TIME_STR_LEN 13

void ls(char *);
int alphasort(const struct dirent **d1, const struct dirent **d2);
int select(const struct dirent *);

int cmpstr(const void * a, const void * b) {
  return strcmp(* (const char **) a, * (const char **) b);
}

/* p. 149-150 K&R */
struct {
  unsigned int include_dot : 1;
  unsigned int list_long : 1;
  unsigned int multi_column : 1;
  unsigned int slash_after_if_dir : 1;
} flags;

int handleFlags(char * arg) {
  if(arg[0] == '-') {
    // it's a flag
    switch(arg[1]) {
      case 'a':
        flags.include_dot = 1;
      break;
      case 'l':
        flags.list_long = 1;
      break;
      case 'C':
        flags.multi_column = 1;
      break;
      case 'p':
        flags.slash_after_if_dir = 1;
      break;
    }
    return 1;
  }
  return 0;
}

int main(int argc, char * argv[]) {
  if (argc == 1) {
    ls(".");
  } else if (argc == 2) {
    if(handleFlags(argv[1])) {
      // the arg was a flag
      ls(".");
    } else {
      // the arg was an arg
      ls(argv[1]);
    }
  } else {
    argv++;
    qsort(argv, argc-1, sizeof(char *), cmpstr);
    while(argc > 1) {
      if(!handleFlags(*argv)) {
        // it's an arg
        printf("%s:\n", *argv);
        ls(*argv);
      }
      argv++;
      argc--;
    }
  }
  exit(0);
}

void ls(char * path) {
  int numdir;
  DIR * directoryPointer;
  struct dirent * directoryEntity;
  struct stat statbuffer;
  struct dirent ** namelist;
  struct dirent ** nameliststart;
  struct tm datetime;
  char * timefmt = "%b %d %H:%M";
  char timebuffer[TIME_STR_LEN];
  struct passwd *pwd;
  struct group *grp;

  // load stat into statbuffer
  if(stat(path, &statbuffer) == -1) {
    printf("ls: %s: No such file or directory\n", path);
    return;
  }
  if ((statbuffer.st_mode & S_IFMT) == S_IFDIR) {
    // true if file is a directory
    // directoryPointer = opendir(path);
    // if (directoryPointer == NULL) exit(1);
    numdir = scandir(path, &namelist, select, alphasort);
    if(numdir == -1) {
      printf("Something went very wrong\n");
      exit(1);
    }

    nameliststart = namelist;
    while (numdir > 0) {
      if (stat((*namelist)->d_name, &statbuffer) == 1) {
        printf("Couldn't run stat on known file %s\n", (*namelist)->d_name);
        exit(1);
      }
      if(flags.list_long) {
        if(!localtime_r(&(statbuffer.st_mtime), &datetime)) perror("localtime_r failed.\n");
        if(!strftime(timebuffer, TIME_STR_LEN, timefmt, &datetime)) perror("strftime failed.\n");
        pwd = getpwuid(statbuffer.st_uid);
        if(pwd == NULL) perror("getpwuid");
        grp = getgrgid(statbuffer.st_gid);
        if(grp == NULL) perror("getgrgid");

        printf("%c%c%c%c%c%c%c%c%c%c %3jd %s %6s %6jd %s %s %d\n",
          '-',
          (statbuffer.st_mode & S_IRUSR) == S_IRUSR ? 'r' : '-',
          (statbuffer.st_mode & S_IWUSR) == S_IWUSR ? 'w' : '-',
          (statbuffer.st_mode & S_IXUSR) == S_IXUSR ? 'x' : '-',
          (statbuffer.st_mode & S_IRGRP) == S_IRGRP ? 'r' : '-',
          (statbuffer.st_mode & S_IWGRP) == S_IWGRP ? 'w' : '-',
          (statbuffer.st_mode & S_IXGRP) == S_IXGRP ? 'x' : '-',
          (statbuffer.st_mode & S_IROTH) == S_IROTH ? 'r' : '-',
          (statbuffer.st_mode & S_IWOTH) == S_IWOTH ? 'w' : '-',
          (statbuffer.st_mode & S_IXOTH) == S_IXOTH ? 'x' : '-',
          (intmax_t)statbuffer.st_nlink,
          pwd->pw_name,
          grp->gr_name,
          (intmax_t)statbuffer.st_size,
          timebuffer,
          (*namelist)->d_name,
          (*namelist)->d_ino == statbuffer.st_ino
        );
      } else {
        printf("%s\n", (*namelist)->d_name);
      }
      free(*namelist);
      namelist++;
      numdir--;
    }
    free(nameliststart);
  } else {
    printf("%s\n", path);
  }
}

int select(const struct dirent * d) {
  if(d->d_name[0] == '.' && !flags.include_dot) return 0;
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