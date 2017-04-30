#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // include all of the potential chars and then pick a random value
    char chars[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    int c = rand() % 9;

    // return a randomized char made up of the potential chars
    return chars[c];
}

char *inputString()
{
    static char s[6];

    // include the potential chars
    char chars[] = {'r', 'e', 's', 't', '\0'};

    // pick a random value from the array of potential chars and place in string
    int i, c;
    for (i = 0; i < 6; i++)
    {
      c = rand() % 5;
      s[i] = chars[c];
    }

    // return a randomized string made up of the potential chars
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
