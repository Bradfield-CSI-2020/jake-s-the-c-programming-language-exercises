#include <stdio.h>
#include <stdlib.h>
// Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside.)
// Write a version with only one test inside the loop and measure the difference in runtime.


/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
  int low, mid, high;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) / 2;
    if (x < v[mid]) { /* target is to the left */
      high = mid - 1;
    } else if (x > v[mid]) { /* target is to the right */
      low = mid + 1;
    } else { /* found match */
      return mid;
    }
  }
  return -1; /* no match */
}

/* binsearch2: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch2(int x, int v[], int n) {
  int low, mid, high;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) / 2;
    if (x < v[mid]) { /* target is to the left */
      high = mid - 1;
    } else { /* target is to the right */
      low = mid + 1;
    }
  }
  if(x == v[mid]) return mid;
  if(x == v[mid+1]) return mid+1;
  if(x == v[mid-1]) return mid-1;
  return -1; /* no match */
}

// ./binsearch target el0 el1 el2 el3 ... elN
int main(int argc, char *argv[]) {
  int numsc = argc-2;
  int numsv[numsc];
  for(int i = 2; i < argc; i++) {
    numsv[i-2] = atoi(argv[i]);
  }
  printf("%d\n", binsearch2(atoi(argv[1]), numsv, numsc));
  return 0;
}
