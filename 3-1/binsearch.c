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

int main(int argc, char *argv[]) {
  return 0;
}
