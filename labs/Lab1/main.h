// A.h
int f(int);

// B.h
#include <A.h>

void g(int);
// prog.h
#include <A.h>
#include <B.h>

int main();