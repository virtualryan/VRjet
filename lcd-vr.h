#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

static int __LCD_FD, __LCD_ioctl_RETURN_STATUS, __LCD_IS_OPEN;
static int __LCD_IS_LEFT;
static int __LCD_PORT_STATUS;

void print_status( int status )
{
  printf("CAR:%d", (status & TIOCM_CAR ) / TIOCM_CAR );
  printf("\tDSR:%d", (status & TIOCM_DSR ) / TIOCM_DSR ); 
  printf("\tDTR:%d", ( status & TIOCM_DTR ) / TIOCM_DTR );
  printf("\tRTS:%d", ( status & TIOCM_RTS ) / TIOCM_RTS );
  printf("\tRNG:%d", ( status & TIOCM_RNG ) / TIOCM_RNG ); 
  printf("\tCTS:%d\n\n", ( status & TIOCM_CTS ) / TIOCM_CTS );

  return;
}

void lcdInitialize()
{ 
  __LCD_FD = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (__LCD_FD == -1)
    {
      perror("Opening Port: Unable to open /dev/ttyS0: ");
      exit(1);
    }
  else
    {
      __LCD_IS_OPEN = 1;
      fcntl(__LCD_FD, F_SETFL, 0);
    }
 ioctl(__LCD_FD, TIOCMGET, &__LCD_PORT_STATUS); 
  
 printf("Initial State:\n");
 print_status(__LCD_PORT_STATUS);
  
  __LCD_PORT_STATUS = TIOCM_RTS;
  
  __LCD_ioctl_RETURN_STATUS = ioctl(__LCD_FD, TIOCMSET, &__LCD_PORT_STATUS);  
  __LCD_ioctl_RETURN_STATUS = ioctl(__LCD_FD, TIOCMGET, &__LCD_PORT_STATUS);   

  if( __LCD_ioctl_RETURN_STATUS == -1 )
    {
      perror("ioctl failed: ");         
    }

  if( (__LCD_PORT_STATUS & TIOCM_RTS) > 0 )
    {
      printf("Stereo Enabled:\n");
      print_status(__LCD_PORT_STATUS);
    }
  else
    {
      printf("Stereo not enabled.  Aborting.\n");
      exit(1);
    }

}

#define lcdIsLeft( ) __LCD_IS_LEFT


#define lcdSwitchLens( ) \
\
if(!__LCD_IS_OPEN) \
    { \
      lcdInitialize(); \
    } \
  if( __LCD_IS_LEFT ) \
    { \
      __LCD_PORT_STATUS |= TIOCM_DTR; \
      __LCD_ioctl_RETURN_STATUS = ioctl(__LCD_FD, TIOCMSET, &__LCD_PORT_STATUS);  \
    } \
  else \
    { \
      __LCD_PORT_STATUS &= ~TIOCM_DTR ; \
      __LCD_ioctl_RETURN_STATUS = ioctl(__LCD_FD, TIOCMSET, &__LCD_PORT_STATUS); \
    } \
  __LCD_IS_LEFT = !__LCD_IS_LEFT; 





