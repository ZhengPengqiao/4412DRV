#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int fp = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int screenSize = 0;
    char *fbp = 0;
    int x = 0;
    int y = 0;
    int location = 0;
    unsigned char r,g,b;
    /* 每个像素点的位数 */
    int byte_per_pixel;  

    /* 打开一个FrameBuffer设备 */
    fp = open("/dev/fb0", O_RDWR);
    if( fp < 0 )
    {
        perror("open /dev/fb0:");
        exit(1);
    }

    /* Get fixed screen information  */
    if( ioctl(fp, FBIOGET_FSCREENINFO, &finfo) )
    {
        perror("read fixed Error:");
        exit(2);
    }

    /* Get variable screen information  */
    if( ioctl( fp, FBIOGET_VSCREENINFO, &vinfo ) )
    {
        perror("read variable Error");
        exit(3);
    }

    /*  show these information */
    byte_per_pixel = vinfo.bits_per_pixel / 8;
    screenSize = vinfo.xres * vinfo.yres * byte_per_pixel;

    printf("x=%d    y=%d  byte_per_pixel=%d\n", vinfo.xres, vinfo.yres, byte_per_pixel);
    printf("screenSize=%d\n", screenSize);

    fbp = (char *)mmap(0, screenSize, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);
    if( (long)fbp == -1 )
    {
        perror("mmap fbp Error:");   
        exit(4);
    }

    while(1)
    {
        r += 1;
	g += 4;
	b += 2;
        for( x = 0; x < 150; x++)   
        {
            for( y = 0; y < 150; y++)
            {
                location = x*byte_per_pixel + y*finfo.line_length;
                *(fbp + location) = b;    //blue
                *(fbp + location + 1) = g;  //green
                *(fbp + location + 2) = r;  //red
                *(fbp + location + 3) = 0;  //a
            }
        }
	usleep(33000);
    }

    munmap(fbp, screenSize);
    close(fp);

    return 0;
}
