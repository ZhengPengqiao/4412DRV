#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEV_FILE_NAME "/dev/tiny4412_leds"
#define LED_ON      1
#define LED_OFF     0

#define LED0     0
#define LED1     1
#define LED2     2
#define LED3     3

static int ledsOn(int fb, int ledNum)
{
    int ret = ioctl(fb, LED_ON, ledNum);
    return ret;
}

static int ledsOff(int fb, int ledNum)
{
    int ret = ioctl(fb, LED_OFF, ledNum);
    return ret;
}

static int ledsSetStatus(int fb, int ledsStatus)
{
    int i;
    for( i = 0; i < 4; i++ )
    {
        if( (ledsStatus & (1 << i)) != 0 )
        {
            ledsOn(fb, i);
        }
        else
        {
            ledsOff(fb, i);
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    int fb = open(DEV_FILE_NAME, O_RDWR);

    int ledsStatus = 1;
    printf("LED%d=%d\n", LED_ON, LED0);
    while(1)
    {
        ledsStatus++;
        ledsStatus = ledsStatus & 0xF;
        ledsSetStatus(fb,ledsStatus);
        sleep(1);
    }

    close(fb);
    return 0;
}