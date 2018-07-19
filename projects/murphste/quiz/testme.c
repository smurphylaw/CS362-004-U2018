#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Using ASCII Format - Set bounds
    int lower = 32;
    int upper = 125;
    
    return (rand() % (upper - lower + 1)) + lower;
}

char *inputString()
{
    // Limit size of string to 5 (per the testme function)
    int length = 5;
    
    // Using ASCII Format - Set bounds (using only lowercase alphabet characters)
    int lower = 97;
    int upper = 122;
    
    
    char *randomString = malloc(length * sizeof(char) + 1);
    
    for (int i = 0; i < length; i++) {
        // Append character to random string
        randomString[i] = (rand() % (upper - lower + 1)) + lower;
    }
    
    // Add null terminator at the end of the string
    randomString[5] = '\0';
    
    return randomString;
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
