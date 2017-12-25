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

int main(int argc, char **argv)
{
    int fb = open(DEV_FILE_NAME, O_RDWR);

    printf("LED%d=%d\n", LED_ON, LED0);
    ioctl(fb, LED_ON, LED0);
    
    close(fb);
    return 0;
}