/*
    Minimally, it should list the contents of a directory including some information about each file,
    such as file size. As a stretch goal, use man ls to identify any interesting flags you may wish
    to support, and implement them.
*/

#include <dirent.h>
/*
  struct dirent
  DIR *
  opendir()
  dirfd()
  scandir()
*/
#include <fcntl.h>
/*
  the constant
  AT_SYMLINK_NOFOLLOW
  used for the final argument of 'fstatat'
*/
#include <grp.h>
/*
  This, plus sys/types.h are required for:
  struct group
  getgrgid()
*/
#include <pwd.h>
/*
  This, plus sys/types.h, plus uuid/uuid.h are required for:
  struct passwd
  getpwuid()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
/*
  struct stat
  stat()
  fstatat()
*/
#include <sys/types.h>
#include <time.h>
/*
  struct tm
  localtime_r()
  strftime()
*/
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
      // not implemented
        flags.multi_column = 1;
      break;
      case 'p':
      // not implemented
        flags.slash_after_if_dir = 1;
      break;
    }
    return 1;
  }
  return 0;
}

static int hereFileDescriptor;

int main(int argc, char * argv[]) {
  DIR * here;
  here = opendir(".");
  hereFileDescriptor = dirfd(here);

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

  closedir(here);
  exit(0);
}

void ls(char * path) {
  int numdir;
  DIR * directoryPointer;
  struct dirent * directoryEntity;

  char relpath[PATH_LEN];

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
    numdir = scandir(path, &namelist, select, alphasort);
    if(numdir == -1) {
      printf("Something went very wrong\n");
      exit(1);
    }

    nameliststart = namelist;
    while (numdir > 0) {
      /* create a relative path to each file */
      strcpy(relpath, path);
      strcat(relpath, "/");
      strcat(relpath, (*namelist)->d_name);

      if (fstatat(hereFileDescriptor, relpath, &statbuffer, 0) == 1) {
        printf("Couldn't run stat on known file %s\n", relpath);
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
