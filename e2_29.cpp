int main() {
  int i, *const cp = &i;
  int *p1, *const p2 = p1;
  const int ic = 5, &r = ic;
  const int *const p3 = &ic;
  const int *p;

  int const iic = 666;    // testing "const int name -->> int const name
  /*
   * Exercise 2.29 : Using the variables in the previous exercise, which of the
   * following assignments are legal? Explain wyhy.
   * */

  i = ic;
  p1 = p3;
  p1 = &ic;
  p3 = &ic;
  p2 = p1;
  ic = *p3;

  return 0;
}
