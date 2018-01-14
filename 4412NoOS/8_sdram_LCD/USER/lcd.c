/****************************************
NAME:LCD.C
TRAD:/USER/
PROJECT:
CREATER:Zhang Taohua
DATA:2014-05-07
DESCRIPTION:

 LCD relation function

 *****************************************/


#include  "lcd.h"



// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--)
		;
}


void led_show_val(unsigned char val)
{
	GPM4CON = 0x00001111;			// 配置引脚
	GPM4DAT = (~val)&0xF;				 	// LED val
}

void led_allOn()
{
	GPM4CON = 0x00001111;			// 配置引脚
	GPM4DAT = 0;				 	// LED on
}

void led_allOff()
{
	GPM4CON = 0x00001111;			// 配置引脚
	GPM4DAT = 0xF;				 	// LED off
}

void memset(unsigned int * s, int c,unsigned int count)
{
	unsigned int *xs = (unsigned int *) s;

	while (count--)
		*xs++ = c;

	return s;
}



/****************************************
FUNCTION :lcd_init()
PARAMETERS:	link_times : blink times
REMARKS:
EXAMPLE

SEE ALSO:
DATA:
 *****************************************/

void lcd_init (void)
{

	//indicate LCD start Init
	
	

    /*
     *SET IO IS LCD
     *<Exyons 4412 datasheet pg138 pg141 pg144 pg147>
     *
     * GPF0CON : [31:0] : 0x2
     * GPF1CON : [31:0] : 0x2
     * GPF2CON : [31:0] : 0x2
     * GPF3CON : [31:0] : 0x2
     * */	

	GPF0CON = 0x22222222;				
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON = 0x00222222;
	// Set pull-up,down disable
	GPF0PUD = 0x0000FFFF;
	GPF1PUD = 0x0000FFFF;
	GPF2PUD = 0x0000FFFF;
	GPF3PUD = 0x00000FFF;
	
	//MAX drive strength---------//
	GPF0DRV = 0x0000FFFF;
	GPF1DRV = 0x0000FFFF;
	GPF2DRV = 0x0000FFFF;
	GPF3DRV = 0x00000FFF;
    /*
     *<Exyons 4412 datasheet pg526>
     *CLK_DIV_LCD: 
     *              [3:0]:FIMD0_RATIO   0
     *              SCLK_FIMD0 = MOUTFIMD0/(FIMD0_RATIO + 1) 
     *                         = MOUTFIMD0/1 = 800MHz
     *              MOUTFIMD0 == SCLKmpll_user_t == 800MHz      <Exyons 4412 datasheet pg453> LCD0_BLK
     * */
	CLK_DIV_LCD &= ~0xf;
    /*
     *<Exyons 4412 datasheet pg501>
     *CLK_SRC_LCD0:
     *          [3:0]:FIMD0_SEL 0110 ===> SCLKmpll_user_t 选择时钟源为SCLKmpll_user_t
     *
     * */
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 6;
	//LCD0_SYS_PWR_REG == 7 Don't use
    
    
    /*<Exyons 4412 datasheet pg1799>
     *Using the display controller data, you can select one of the above data paths by setting LCDBLK_CFG Register
     *(0x1001_0210). For more information, refer to the "System Others" manual.
     *
     *
     * <Exyons 4412 datasheet pg880>
     * LCDBLK_CFG: 
     *          [1] : FIMD of LBLK0 Bypass Selection    1 : FIMD Bypass 使用FIMD接口
     *
     * LCDBLK_CFG :
     *          [0]:MIE0_DISPON     1 :  PWM outpupt enable 
     *
     *
     * */
	LCDBLK_CFG |= 1 << 1;
       LCDBLK_CFG2 |= 1;

	   
    /*
     *clear the Framer buffer
     * */
	memset(LCD_VIDEO_ADDR, 0xFF00, VIDEO_MEM_SIZE);

    /*
     *<Exyons 4412 datasheet pg1869>
     *VIDCON0:
     *     [13:6]: CLKVAL_F     //设置LCD时钟分频系数
     *
     *  VCLK == 33.3Mhz         <S700-AT070TN92 pg14> DCLK  Frequency ===> Type : 33.3Mhz
     *  VCLK = FIMD * SCLK/(CLKVAL+1)
     *  VCLK =  800000000 / (CLKVAL + 1)   
     *  33300000 = 800000000 /(CLKVAL + 1)
     *  CLKVAL + 1 = 24.02 
     *  CLKVAL = 23
     * */
     VIDCON0 = (23 << 6);
	//VIDCON0 =  EXYNOS_VIDCON0_CLKVAL_F(23);   //not use this method ,it does not work???

    /*
     *<Exyons 4412 datasheet pg1870 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
     *VIDTCON1:
     *      [5]:IVSYNC  ===> 1 : Inverted(反转)
     *      [6]:IHSYNC  ===> 1 : Inverted(反转)
     *      [7]:IVCLK   ===> 1 : Fetches video data at VCLK rising edge (下降沿触发)
     *      [10:9]:FIXVCLK  ====> 01 : VCLK running 
     * */

	VIDCON1 = (1 << 9) | (1 << 7) | (1 << 5) | (1 << 6);
	//VIDCON1 =  ( EXYNOS_VIDCON1_VCLK_RUNNING | EXYNOS_VIDCON1_IVCLK_RISING_EDGE|EXYNOS_VIDCON1_IVSYNC_INVERT | EXYNOS_VIDCON1_IHSYNC_INVERT);      

	/*
	  *<Exyons 4412 datasheet pg1874 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
	  *VIDTCON0: 
	  * 	  [23:16]:	VBPD + 1 <------> tvpw 23
	  * 	  [15:8]: VFPD + 1 <------> tvfp 22
	  * 	  [7:0]: VSPW  + 1 <------> tvb - tvpw = 525-480-23-22=0
	  * */

    VIDTCON0 = (12 << 16) | (21 << 8) | (9);
	//VIDTCON0 = ( EXYNOS_VIDTCON0_VBPD(VBPD) |	EXYNOS_VIDTCON0_VFPD(VFPD) |EXYNOS_VIDTCON0_VSPW(VSPW));   
	

	/*<Exyons 4412 datasheet pg1874 pg1848(时序)> <S700-AT070TN92 pg13(时序)>
	 *VIDTCON1: 
	 *		 [23:16]:  HBPD + 1 <------> thpw 46
	 *		 [15:8]:   HFPD + 1 <------> thfp 210 
	 *		 [7:0]:    HSPW  + 1 <------> thb - thpw =1056- 800-210-46=0
	 */

     	VIDTCON1 = (35 << 16) | (209 << 8) | (9);
	//VIDTCON1 = ( EXYNOS_VIDTCON1_HBPD(HBPD) | EXYNOS_VIDTCON1_HFPD(HFPD) |EXYNOS_VIDTCON1_HSPW(HSPW));  

    /*
     *<Exyons 4412 datasheet pg1875>
     * 
     *HOZVAL = (Horizontal display size) – 1 and LINEVAL = (Vertical display size) – 1.
     * Horizontal(水平) display size : 800 
     *Vertical(垂直) display size : 480
     * */

	VIDTCON2 = (479 << 11) | 799;
	//VIDTCON2 = ( EXYNOS_VIDTCON2_LINEVAL(LINEVAL) |EXYNOS_VIDTCON2_HOZVAL(HOZVAL));
	

	//win0
    /*
     *<Exyons 4412 datasheet pg1877>
     *WINCON0:
     *  [5:2]: Selects Bits Per Pixel (BPP) mode for Window image : 1011 ===> 24BPP
     *  [1]:Enables/disables video output   1 = Enables
     *
     *modify by zth; have an error;add [15] : specifies word swap control bit :1=Enable ;2014 06-15
     * */
     WINCON0 =( (1<<15) | (11 << 2) | 1);
	//WINCON0 =(EXYNOS_WINCON_WSWP_ENABLE | EXYNOS_WINCON_BPPMODE_24BPP_888 |EXYNOS_WINCON_ENWIN_ENABLE);

   /*
     *<Exyons 4412 datasheet pg1895>
     *VIDOSD0C:Specifies the Window Size (窗口尺寸 单位为word)
     *          
     *
     * */
     VIDOSD0C = 480 * 800;
	//VIDOSD0C = EXYNOS_VIDOSD_SIZE(ROW * COL);




    /*
     *<Exyons 4412 datasheet pg1891 pg1801>
     *[0]: Enables Channel 0. 1 = Enables
     * */
      SHADOWCON |= 1;
     // SHADOWCON |= EXYNOS_WINSHMAP_CH_ENABLE(0);


    /*
     *<Exyons 4412 datasheet  pg1894 pg1801>
     *[18:16] Selects Channel 0's channel. ===> 001 = Window 0
     *[2:0] Selects Window 0's channel.  ===> 001 = Channel 0 
     * 
     *
     * */
	WINCHMAP2 &= ~(7 << 16);
	WINCHMAP2 |= 1 << 16;
	WINCHMAP2 &= ~7;
	WINCHMAP2 |= 1;

	/*
	WINCHMAP2 &=  EXYNOS_WINSHMAP_CH_DISABLE(16);
	WINCHMAP2 |= EXYNOS_WINSHMAP_CH_ENABLE(16);
	WINCHMAP2 &=  EXYNOS_WINSHMAP_CH_DISABLE(0);
	WINCHMAP2 |= EXYNOS_WINSHMAP_CH_ENABLE(0);
	*/

    /*
     *<Exyons 4412 datasheet  pg1895>
     *VIDOSD0A: LCD左上角坐标
     *VIDOSD0B: LCD右下角坐标
     */

	
	VIDOSD0A = 0;
	VIDOSD0B = (799 << 11) | 479;
	//VIDOSD0A =  ( EXYNOS_VIDOSD_LEFT_X(0) | EXYNOS_VIDOSD_TOP_Y(0));//0
	//VIDOSD0B =  ( EXYNOS_VIDOSD_RIGHT_X(HOZVAL) | EXYNOS_VIDOSD_BOTTOM_Y(LINEVAL));


    /*
     *<Exyons 4412 datasheet  pg1902>
     * VIDW00ADD0B0 : window0 frame buffer 起始地址 
     *  VIDW00ADD1B0 : window0 frame buffer 结束地址
     * */
     
	VIDW00ADD0B0 = LCD_VIDEO_ADDR;
	VIDW00ADD1B0 = LCD_VIDEO_ADDR + VIDOSD0C * 4;

    /*
     * <Exyons 4412 datasheet pg1869>
     * Display On: ENVID and ENVID_F are set to "1".
     *  [0]:ENVID ===> 1 = Enables
     *  [1]:ENVID_F ===> 1 = Enables 
     * */
     VIDCON0 |= 3;
	//VIDCON0 |=  (EXYNOS_VIDCON0_ENVID_ENABLE |EXYNOS_VIDCON0_ENVID_F_ENABLE);	

    led_allOn();
    delay(0x200000);
    led_allOff();
    delay(0x200000);
}




// 描点
void lcd_draw_pixel(int row, int col, int color)
{
	unsigned long * pixel = (unsigned long  *)LCD_VIDEO_ADDR;

	*(pixel + row * COL + col) = color;

}


// 清屏
void lcd_clear_screen(int color)
{
	int i, j;

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			lcd_draw_pixel(i, j, color);

}

// 划横线
void lcd_draw_hline(int row, int col1, int col2, int color)
{
	int j;

	// 描第row行，第j列
	for (j = col1; j <= col2; j++)
		lcd_draw_pixel(row, j, color);

}

// 划竖线
void lcd_draw_vline(int col, int row1, int row2, int color)
{
	int i;
	// 描第i行，第col列
	for (i = row1; i <= row2; i++)
		lcd_draw_pixel(i, col, color);

}

// 划十字
void lcd_draw_cross(int row, int col, int halflen, int color)
{
	lcd_draw_hline(row, col-halflen, col+halflen, color);
	lcd_draw_vline(col, row-halflen, row+halflen, color);
}

