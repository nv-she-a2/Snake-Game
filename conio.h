#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

struct termios oldattr, newattr;

/* Initialize new terminal i/o settings */
void initTermios()
{
  tcgetattr(0, &oldattr); //grab old terminal i/o settings
  newattr = oldattr; //make new settings same as old settings
  newattr.c_lflag &= ~ICANON; //disable buffered i/o
  newattr.c_lflag &= ~ECHO; //disable echo mode
  tcsetattr(0, TCSANOW, &newattr); //apply terminal i/o settings
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &oldattr);//apply old terminal i/o settings
}

//check if keyboard is pressed
int kbhit(void)
{
  struct timeval tv;
   fd_set rdfs;
  
   tv.tv_sec = 0;
   tv.tv_usec = 0;
  
   FD_ZERO(&rdfs);
   FD_SET (STDIN_FILENO, &rdfs);
  
   select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
   return FD_ISSET(STDIN_FILENO, &rdfs);
}

