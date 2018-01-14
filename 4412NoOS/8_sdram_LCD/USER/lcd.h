#ifndef __LCD_H
#define __LCD_H

extern void lcd_init(void);
extern void lcd_draw_pixel(int row, int col, int color);
extern void lcd_clear_screen(int color);
extern void lcd_draw_hline(int row, int col1, int col2, int color);
extern void lcd_draw_vline(int col, int row1, int row2, int color);
extern void lcd_draw_cross(int row, int col, int halflen, int color);
extern void delay(unsigned long count);
extern void led_show_val(unsigned char val);
extern void led_allOn();
extern void led_allOff();
extern void memset(unsigned int * s, int c,unsigned int count);
extern void draw_point(int x, int y, int r, int g, int b);
extern void memset(unsigned int * s, int c,unsigned int count);


#define readb(a)			(*(volatile unsigned char *)(a))
#define readw(a)			(*(volatile unsigned short *)(a))
#define readl(a)			(*(volatile unsigned int *)(a))

#define writeb(v,a)		(*(volatile unsigned char *)(a) = (v))
#define writew(v,a)		(*(volatile unsigned short *)(a) = (v))
#define writel(v,a)		(*(volatile unsigned int *)(a) = (v))

//LCD Clock Relate Register
#define CLK_DIV_LCD (*(volatile unsigned int *)0x1003c534)
#define CLK_SRC_MASK_LCD (*(volatile unsigned int *)0x1003c334)
#define CLK_GATE_IP_LCD (*(volatile unsigned int *)0x1003c934)
#define CLK_SRC_LCD0 (*(volatile unsigned int *)0x1003c234)

//Framer Buffer Address And Size

#define LCD_VIDEO_ADDR	 (0x54000000)     
#define 	VIDEO_MEM_SIZE  0x200000        /* 800x480x24bit = 0X119400 bytes */



//LED IO Control Regiester
#define GPM4CON 	(*(volatile unsigned long *) 0x110002E0)
#define GPM4DAT		(*(volatile unsigned long *) 0x110002E4)
//LCD OP Control Regiester
#define GPF0CON		(*(volatile unsigned int *)0x11400180)
#define GPF0DAT		(*(volatile unsigned int *)0x11400184)
#define GPF0PUD		(*(volatile unsigned int *)0x11400188)
#define GPF0DRV		(*(volatile unsigned int *)0x1140018C)

#define GPF1CON 	(*(volatile unsigned int *)0x114001a0)
#define GPF1DAT	 	(*(volatile unsigned int *)0x114001a4)
#define GPF1PUD 	(*(volatile unsigned int *)0x114001a8)
#define GPF1DRV 	(*(volatile unsigned int *)0x114001ac)

#define GPF2CON		(*(volatile unsigned int *)0x114001c0)
#define GPF2DAT   	(*(volatile unsigned int *)0x114001c4)
#define GPF2PUD 	(*(volatile unsigned int *)0x114001c8)
#define GPF2DRV 	(*(volatile unsigned int *)0x114001cc)

#define GPF3CON 	(*(volatile unsigned int *)0x114001e0)
#define GPF3DAT  	(*(volatile unsigned int *)0x114001e4)
#define GPF3PUD 	(*(volatile unsigned int *)0x114001e8)
#define GPF3DRV 	(*(volatile unsigned int *)0x114001ec)

#define LCDBLK_CFG (*(volatile unsigned int *)0x10010210)
#define LCDBLK_CFG2 (*(volatile unsigned int *)0x10010214)

//LCD Control Register 
#define LCD_BASE 0x11C00000

#define VIDCON0 	(*(volatile unsigned int *)(LCD_BASE + 0x0000)) 
#define VIDCON1 	(*(volatile unsigned int *)(LCD_BASE + 0x0004)) 
#define VIDCON2 	(*(volatile unsigned int *)(LCD_BASE + 0x0008)) 
#define VIDCON3 	(*(volatile unsigned int *)(LCD_BASE + 0x000C)) 
#define VIDTCON0 	(*(volatile unsigned int *)(LCD_BASE + 0x0010))
#define VIDTCON1 	(*(volatile unsigned int *)(LCD_BASE + 0x0014))
#define VIDTCON2 	(*(volatile unsigned int *)(LCD_BASE + 0x0018))
#define VIDTCON3 	(*(volatile unsigned int *)(LCD_BASE + 0x001C))
#define WINCON0 	(*(volatile unsigned int *)(LCD_BASE + 0x0020)) 
#define WINCON1 	(*(volatile unsigned int *)(LCD_BASE + 0x0024)) 
#define WINCON2 	(*(volatile unsigned int *)(LCD_BASE + 0x0028)) 
#define WINCON3 	(*(volatile unsigned int *)(LCD_BASE + 0x002C)) 
#define WINCON4 	(*(volatile unsigned int *)(LCD_BASE + 0x0030)) 
#define SHADOWCON 	(*(volatile unsigned int *)(LCD_BASE + 0x0034))
#define WINCHMAP2 	(*(volatile unsigned int *)(LCD_BASE + 0x003C))
#define VIDOSD0A 	(*(volatile unsigned int *)(LCD_BASE + 0x0040)) 
#define VIDOSD0B 	(*(volatile unsigned int *)(LCD_BASE + 0x0044)) 
#define VIDOSD0C 	(*(volatile unsigned int *)(LCD_BASE + 0x0048)) 
#define VIDOSD1A 	(*(volatile unsigned int *)(LCD_BASE + 0x0050)) 
#define VIDOSD1B 	(*(volatile unsigned int *)(LCD_BASE + 0x0054)) 
#define VIDOSD1C 	(*(volatile unsigned int *)(LCD_BASE + 0x0058)) 
#define VIDOSD1D 	(*(volatile unsigned int *)(LCD_BASE + 0x005C)) 
#define VIDOSD2A 	(*(volatile unsigned int *)(LCD_BASE + 0x0060)) 
#define VIDOSD2B 	(*(volatile unsigned int *)(LCD_BASE + 0x0064)) 
#define VIDOSD2C 	(*(volatile unsigned int *)(LCD_BASE + 0x0068)) 
#define VIDOSD2D 	(*(volatile unsigned int *)(LCD_BASE + 0x006C)) 
#define VIDOSD3A 	(*(volatile unsigned int *)(LCD_BASE + 0x0070)) 
#define VIDOSD3B 	(*(volatile unsigned int *)(LCD_BASE + 0x0074)) 
#define VIDOSD3C 	(*(volatile unsigned int *)(LCD_BASE + 0x0078)) 
#define VIDOSD4A 	(*(volatile unsigned int *)(LCD_BASE + 0x0080)) 
#define VIDOSD4B 	(*(volatile unsigned int *)(LCD_BASE + 0x0084)) 
#define VIDOSD4C 	(*(volatile unsigned int *)(LCD_BASE + 0x0088)) 
#define VIDW00ADD0B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00A0)) 
#define VIDW00ADD0B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00A4)) 
#define VIDW00ADD0B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20A0)) 
#define VIDW01ADD0B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00A8)) 
#define VIDW01ADD0B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00AC)) 
#define VIDW01ADD0B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20A8)) 
#define VIDW02ADD0B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00B0)) 
#define VIDW02ADD0B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00B4)) 
#define VIDW02ADD0B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20B0)) 
#define VIDW03ADD0B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00B8)) 
#define VIDW03ADD0B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00BC)) 
#define VIDW03ADD0B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20B8)) 
#define VIDW04ADD0B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00C0)) 
#define VIDW04ADD0B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00C4)) 
#define VIDW04ADD0B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20C0)) 
#define VIDW00ADD1B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00D0)) 
#define VIDW00ADD1B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00D4)) 
#define VIDW00ADD1B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20D0)) 
#define VIDW01ADD1B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00D8)) 
#define VIDW01ADD1B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00DC)) 
#define VIDW01ADD1B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20D8)) 
#define VIDW02ADD1B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00E0)) 
#define VIDW02ADD1B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00E4)) 
#define VIDW02ADD1B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20E0)) 
#define VIDW03ADD1B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00E8)) 
#define VIDW03ADD1B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00EC)) 
#define VIDW03ADD1B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20E8)) 
#define VIDW04ADD1B0 	(*(volatile unsigned int *)(LCD_BASE + 0x00F0)) 
#define VIDW04ADD1B1 	(*(volatile unsigned int *)(LCD_BASE + 0x00F4)) 
#define VIDW04ADD1B2 	(*(volatile unsigned int *)(LCD_BASE + 0x20F0)) 
#define VIDW00ADD2 	(*(volatile unsigned int *)(LCD_BASE + 0x0100)) 
#define VIDW01ADD2 	(*(volatile unsigned int *)(LCD_BASE + 0x0104)) 
#define VIDW02ADD2 	(*(volatile unsigned int *)(LCD_BASE + 0x0108)) 
#define VIDW03ADD2 	(*(volatile unsigned int *)(LCD_BASE + 0x010C)) 
#define VIDW04ADD2 	(*(volatile unsigned int *)(LCD_BASE + 0x0110)) 
#define VIDINTCON0 	(*(volatile unsigned int *)(LCD_BASE + 0x0130)) 
#define VIDINTCON1 	(*(volatile unsigned int *)(LCD_BASE + 0x0134)) 
#define W1KEYCON0 	(*(volatile unsigned int *)(LCD_BASE + 0x0140)) 
#define VIDW0ALPHA0 	(*(volatile unsigned int *)(LCD_BASE + 0x021C)) 
#define VIDW0ALPHA1 	(*(volatile unsigned int *)(LCD_BASE + 0x0220)) 
#define VIDW1ALPHA0 	(*(volatile unsigned int *)(LCD_BASE + 0x0224)) 
#define VIDW1ALPHA1 	(*(volatile unsigned int *)(LCD_BASE + 0x0228)) 
#define VIDW2ALPHA0 	(*(volatile unsigned int *)(LCD_BASE + 0x022C)) 
#define VIDW2ALPHA1 	(*(volatile unsigned int *)(LCD_BASE + 0x0230)) 
#define VIDW3ALPHA0 	(*(volatile unsigned int *)(LCD_BASE + 0x0234)) 
#define VIDW3ALPHA1 	(*(volatile unsigned int *)(LCD_BASE + 0x0238)) 
#define VIDW4ALPHA0 	(*(volatile unsigned int *)(LCD_BASE + 0x023C)) 
#define VIDW4ALPHA1 	(*(volatile unsigned int *)(LCD_BASE + 0x0240)) 

/*
  *<Exyons 4412 datasheet pg1874 pg1848(ʱ��)> <S700-AT070TN92 pg13(ʱ��)>
  *VIDTCON0: 
  * 	  [23:16]:	VBPD + 1 <------> tvpw 23
  * 	  [15:8]: VFPD + 1 <------> tvfp 22
  * 	  [7:0]: VSPW  + 1 <------> tvb - tvpw = 525-480-23-22=0
  * */

#define VBPD				(12)
#define VFPD				(21)
#define VSPW			(9)


 /*<Exyons 4412 datasheet pg1874 pg1848(ʱ��)> <S700-AT070TN92 pg13(ʱ��)>
  *VIDTCON1: 
  * 	  [23:16]:	HBPD + 1 <------> thpw 46
  * 	  [15:8]:	HFPD + 1 <------> thfp 210 
  * 	  [7:0]:	HSPW  + 1 <------> thb - thpw =1056- 800-210-46=0
  */

#define HBPD			(35)
#define HFPD				(209)
#define HSPW			(9)

#define ROW				(480)
#define COL				(800)
#define HOZVAL			(COL-1)
#define LINEVAL			(ROW-1)// 479 


/*
 *  Register offsets
*/
#define EXYNOS_WINCON(x)				(x * 0x04)
#define EXYNOS_VIDOSD(x)				(x * 0x10)
#define EXYNOS_BUFFER_OFFSET(x)				(x * 0x08)
#define EXYNOS_BUFFER_SIZE(x)				(x * 0x04)

/*
 * Bit Definitions
*/

/* VIDCON0 */
#define EXYNOS_VIDCON0_DSI_DISABLE			(0 << 30)
#define EXYNOS_VIDCON0_DSI_ENABLE			(1 << 30)
#define EXYNOS_VIDCON0_SCAN_PROGRESSIVE			(0 << 29)
#define EXYNOS_VIDCON0_SCAN_INTERLACE			(1 << 29)
#define EXYNOS_VIDCON0_SCAN_MASK			(1 << 29)
#define EXYNOS_VIDCON0_VIDOUT_RGB			(0 << 26)
#define EXYNOS_VIDCON0_VIDOUT_ITU			(1 << 26)
#define EXYNOS_VIDCON0_VIDOUT_I80LDI0			(2 << 26)
#define EXYNOS_VIDCON0_VIDOUT_I80LDI1			(3 << 26)
#define EXYNOS_VIDCON0_VIDOUT_WB_RGB			(4 << 26)
#define EXYNOS_VIDCON0_VIDOUT_WB_I80LDI0		(6 << 26)
#define EXYNOS_VIDCON0_VIDOUT_WB_I80LDI1		(7 << 26)
#define EXYNOS_VIDCON0_VIDOUT_MASK			(7 << 26)
#define EXYNOS_VIDCON0_PNRMODE_RGB_P			(0 << 17)
#define EXYNOS_VIDCON0_PNRMODE_BGR_P			(1 << 17)
#define EXYNOS_VIDCON0_PNRMODE_RGB_S			(2 << 17)
#define EXYNOS_VIDCON0_PNRMODE_BGR_S			(3 << 17)
#define EXYNOS_VIDCON0_PNRMODE_MASK			(3 << 17)
#define EXYNOS_VIDCON0_PNRMODE_SHIFT			(17)
#define EXYNOS_VIDCON0_CLKVALUP_ALWAYS			(0 << 16)
#define EXYNOS_VIDCON0_CLKVALUP_START_FRAME		(1 << 16)
#define EXYNOS_VIDCON0_CLKVALUP_MASK			(1 << 16)
#define EXYNOS_VIDCON0_CLKVAL_F(x)			(((x) & 0xff) << 6)
#define EXYNOS_VIDCON0_VCLKEN_NORMAL			(0 << 5)
#define EXYNOS_VIDCON0_VCLKEN_FREERUN			(1 << 5)
#define EXYNOS_VIDCON0_VCLKEN_MASK			(1 << 5)
#define EXYNOS_VIDCON0_CLKDIR_DIRECTED			(0 << 4)
#define EXYNOS_VIDCON0_CLKDIR_DIVIDED			(1 << 4)
#define EXYNOS_VIDCON0_CLKDIR_MASK			(1 << 4)
#define EXYNOS_VIDCON0_CLKSEL_HCLK			(0 << 2)
#define EXYNOS_VIDCON0_CLKSEL_SCLK			(1 << 2)
#define EXYNOS_VIDCON0_CLKSEL_MASK			(1 << 2)
#define EXYNOS_VIDCON0_ENVID_ENABLE			(1 << 1)
#define EXYNOS_VIDCON0_ENVID_DISABLE			(0 << 1)
#define EXYNOS_VIDCON0_ENVID_F_ENABLE		(1 << 0)
#define EXYNOS_VIDCON0_ENVID_F_DISABLE		(0 << 0)

/* VIDCON1 */
#define EXYNOS_VIDCON1_VCLK_HOLD                     	(0 << 9)
#define EXYNOS_VIDCON1_VCLK_RUNNING			 	(1 << 9)
#define EXYNOS_VIDCON1_VCLK_RUNNING_DIS_VDEN	 (3 << 9)
#define EXYNOS_VIDCON1_IVCLK_FALLING_EDGE	(0 << 7)
#define EXYNOS_VIDCON1_IVCLK_RISING_EDGE		(1 << 7)
#define EXYNOS_VIDCON1_IHSYNC_NORMAL		(0 << 6)
#define EXYNOS_VIDCON1_IHSYNC_INVERT			(1 << 6)
#define EXYNOS_VIDCON1_IVSYNC_NORMAL		(0 << 5)
#define EXYNOS_VIDCON1_IVSYNC_INVERT			(1 << 5)
#define EXYNOS_VIDCON1_IVDEN_NORMAL			(0 << 4)
#define EXYNOS_VIDCON1_IVDEN_INVERT			(1 << 4)

/* VIDCON2 */
#define EXYNOS_VIDCON2_EN601_DISABLE			(0 << 23)
#define EXYNOS_VIDCON2_EN601_ENABLE			(1 << 23)
#define EXYNOS_VIDCON2_EN601_MASK			(1 << 23)
#define EXYNOS_VIDCON2_WB_DISABLE			(0 << 15)
#define EXYNOS_VIDCON2_WB_ENABLE			(1 << 15)
#define EXYNOS_VIDCON2_WB_MASK				(1 << 15)
#define EXYNOS_VIDCON2_TVFORMATSEL_HW			(0 << 14)
#define EXYNOS_VIDCON2_TVFORMATSEL_SW			(1 << 14)
#define EXYNOS_VIDCON2_TVFORMATSEL_MASK			(1 << 14)
#define EXYNOS_VIDCON2_TVFORMATSEL_YUV422		(1 << 12)
#define EXYNOS_VIDCON2_TVFORMATSEL_YUV444		(2 << 12)
#define EXYNOS_VIDCON2_TVFORMATSEL_YUV_MASK		(3 << 12)
#define EXYNOS_VIDCON2_ORGYUV_YCBCR			(0 << 8)
#define EXYNOS_VIDCON2_ORGYUV_CBCRY			(1 << 8)
#define EXYNOS_VIDCON2_ORGYUV_MASK			(1 << 8)
#define EXYNOS_VIDCON2_YUVORD_CBCR			(0 << 7)
#define EXYNOS_VIDCON2_YUVORD_CRCB			(1 << 7)
#define EXYNOS_VIDCON2_YUVORD_MASK			(1 << 7)

/* PRTCON */
#define EXYNOS_PRTCON_UPDATABLE				(0 << 11)
#define EXYNOS_PRTCON_PROTECT				(1 << 11)

/* VIDTCON0 */
#define EXYNOS_VIDTCON0_VBPDE(x)			(((x) & 0xff) << 24)
#define EXYNOS_VIDTCON0_VBPD(x)				(((x) & 0xff) << 16)
#define EXYNOS_VIDTCON0_VFPD(x)				(((x) & 0xff) << 8)
#define EXYNOS_VIDTCON0_VSPW(x)				(((x) & 0xff) << 0)

/* VIDTCON1 */
#define EXYNOS_VIDTCON1_VFPDE(x)			(((x) & 0xff) << 24)
#define EXYNOS_VIDTCON1_HBPD(x)				(((x) & 0xff) << 16)
#define EXYNOS_VIDTCON1_HFPD(x)				(((x) & 0xff) << 8)
#define EXYNOS_VIDTCON1_HSPW(x)				(((x) & 0xff) << 0)

/* VIDTCON2 */
#define EXYNOS_VIDTCON2_LINEVAL(x)			(((x) & 0x7ff) << 11)
#define EXYNOS_VIDTCON2_HOZVAL(x)			(((x) & 0x7ff) << 0)
#define EXYNOS_VIDTCON2_LINEVAL_E(x)			((((x) & 0x800) >> 11) << 23)
#define EXYNOS_VIDTCON2_HOZVAL_E(x)			((((x) & 0x800) >> 11) << 22)

/* Window 0~4 Control - WINCONx */
#define EXYNOS_WINCON_DATAPATH_DMA			(0 << 22)
#define EXYNOS_WINCON_DATAPATH_LOCAL			(1 << 22)
#define EXYNOS_WINCON_DATAPATH_MASK			(1 << 22)
#define EXYNOS_WINCON_BUFSEL_0				(0 << 20)
#define EXYNOS_WINCON_BUFSEL_1				(1 << 20)
#define EXYNOS_WINCON_BUFSEL_MASK			(1 << 20)
#define EXYNOS_WINCON_BUFSEL_SHIFT			(20)
#define EXYNOS_WINCON_BUFAUTO_DISABLE			(0 << 19)
#define EXYNOS_WINCON_BUFAUTO_ENABLE			(1 << 19)
#define EXYNOS_WINCON_BUFAUTO_MASK			(1 << 19)
#define EXYNOS_WINCON_BITSWP_DISABLE			(0 << 18)
#define EXYNOS_WINCON_BITSWP_ENABLE			(1 << 18)
#define EXYNOS_WINCON_BITSWP_SHIFT			(18)
#define EXYNOS_WINCON_BYTESWP_DISABLE			(0 << 17)
#define EXYNOS_WINCON_BYTESWP_ENABLE			(1 << 17)
#define EXYNOS_WINCON_BYTESWP_SHIFT			(17)
#define EXYNOS_WINCON_HAWSWP_DISABLE			(0 << 16)
#define EXYNOS_WINCON_HAWSWP_ENABLE			(1 << 16)
#define EXYNOS_WINCON_HAWSWP_SHIFT			(16)
#define EXYNOS_WINCON_WSWP_DISABLE			(0 << 15)
#define EXYNOS_WINCON_WSWP_ENABLE			(1 << 15)
#define EXYNOS_WINCON_WSWP_SHIFT			(15)
#define EXYNOS_WINCON_INRGB_RGB				(0 << 13)
#define EXYNOS_WINCON_INRGB_YUV				(1 << 13)
#define EXYNOS_WINCON_INRGB_MASK			(1 << 13)
#define EXYNOS_WINCON_BURSTLEN_16WORD			(0 << 9)
#define EXYNOS_WINCON_BURSTLEN_8WORD			(1 << 9)
#define EXYNOS_WINCON_BURSTLEN_4WORD			(2 << 9)
#define EXYNOS_WINCON_BURSTLEN_MASK			(3 << 9)
#define EXYNOS_WINCON_ALPHA_MULTI_DISABLE		(0 << 7)
#define EXYNOS_WINCON_ALPHA_MULTI_ENABLE		(1 << 7)
#define EXYNOS_WINCON_BLD_PLANE				(0 << 6)
#define EXYNOS_WINCON_BLD_PIXEL				(1 << 6)
#define EXYNOS_WINCON_BLD_MASK				(1 << 6)
#define EXYNOS_WINCON_BPPMODE_1BPP			(0 << 2)
#define EXYNOS_WINCON_BPPMODE_2BPP			(1 << 2)
#define EXYNOS_WINCON_BPPMODE_4BPP			(2 << 2)
#define EXYNOS_WINCON_BPPMODE_8BPP_PAL			(3 << 2)
#define EXYNOS_WINCON_BPPMODE_8BPP			(4 << 2)
#define EXYNOS_WINCON_BPPMODE_16BPP_565			(5 << 2)
#define EXYNOS_WINCON_BPPMODE_16BPP_A555		(6 << 2)
#define EXYNOS_WINCON_BPPMODE_18BPP_666			(8 << 2)
#define EXYNOS_WINCON_BPPMODE_18BPP_A665		(9 << 2)
#define EXYNOS_WINCON_BPPMODE_24BPP_888			(0xb << 2)
#define EXYNOS_WINCON_BPPMODE_24BPP_A887		(0xc << 2)
#define EXYNOS_WINCON_BPPMODE_32BPP			(0xd << 2)
#define EXYNOS_WINCON_BPPMODE_16BPP_A444		(0xe << 2)
#define EXYNOS_WINCON_BPPMODE_15BPP_555			(0xf << 2)
#define EXYNOS_WINCON_BPPMODE_MASK			(0xf << 2)
#define EXYNOS_WINCON_BPPMODE_SHIFT			(2)
#define EXYNOS_WINCON_ALPHA0_SEL			(0 << 1)
#define EXYNOS_WINCON_ALPHA1_SEL			(1 << 1)
#define EXYNOS_WINCON_ALPHA_SEL_MASK			(1 << 1)
#define EXYNOS_WINCON_ENWIN_DISABLE			(0 << 0)
#define EXYNOS_WINCON_ENWIN_ENABLE			(1 << 0)

/* WINCON1 special */
#define EXYNOS_WINCON1_VP_DISABLE			(0 << 24)
#define EXYNOS_WINCON1_VP_ENABLE			(1 << 24)
#define EXYNOS_WINCON1_LOCALSEL_FIMC1			(0 << 23)
#define EXYNOS_WINCON1_LOCALSEL_VP			(1 << 23)
#define EXYNOS_WINCON1_LOCALSEL_MASK			(1 << 23)

/* WINSHMAP */
#define EXYNOS_WINSHMAP_PROTECT(x)			(((x) & 0x1f) << 10)
#define EXYNOS_WINSHMAP_CH_ENABLE(x)			       (1 << (x))
#define EXYNOS_WINSHMAP_CH_DISABLE(x)			(~(7 << (x)))
#define EXYNOS_WINSHMAP_LOCAL_ENABLE(x)			(0x20 << (x))
#define EXYNOS_WINSHMAP_LOCAL_DISABLE(x)		(0x20 << (x))

/* VIDOSDxA, VIDOSDxB */
#define EXYNOS_VIDOSD_LEFT_X(x)				(((x) & 0x7ff) << 11)
#define EXYNOS_VIDOSD_TOP_Y(x)				(((x) & 0x7ff) << 0)
#define EXYNOS_VIDOSD_RIGHT_X(x)			(((x) & 0x7ff) << 11)
#define EXYNOS_VIDOSD_BOTTOM_Y(x)			(((x) & 0x7ff) << 0)
#define EXYNOS_VIDOSD_RIGHT_X_E(x)			(((x) & 0x1) << 23)
#define EXYNOS_VIDOSD_BOTTOM_Y_E(x)			(((x) & 0x1) << 22)

/* VIDOSD0C, VIDOSDxD */
#define EXYNOS_VIDOSD_SIZE(x)				(((x) & 0xffffff) << 0)

/* VIDOSDxC (1~4) */
#define EXYNOS_VIDOSD_ALPHA0_R(x)			(((x) & 0xf) << 20)
#define EXYNOS_VIDOSD_ALPHA0_G(x)			(((x) & 0xf) << 16)
#define EXYNOS_VIDOSD_ALPHA0_B(x)			(((x) & 0xf) << 12)
#define EXYNOS_VIDOSD_ALPHA1_R(x)			(((x) & 0xf) << 8)
#define EXYNOS_VIDOSD_ALPHA1_G(x)			(((x) & 0xf) << 4)
#define EXYNOS_VIDOSD_ALPHA1_B(x)			(((x) & 0xf) << 0)
#define EXYNOS_VIDOSD_ALPHA0_SHIFT			(12)
#define EXYNOS_VIDOSD_ALPHA1_SHIFT			(0)

/* Start Address */
#define EXYNOS_VIDADDR_START_VBANK(x)			(((x) & 0xff) << 24)
#define EXYNOS_VIDADDR_START_VBASEU(x)			(((x) & 0xffffff) << 0)

/* End Address */
#define EXYNOS_VIDADDR_END_VBASEL(x)			(((x) & 0xffffff) << 0)

/* Buffer Size */
#define EXYNOS_VIDADDR_OFFSIZE(x)			(((x) & 0x1fff) << 13)
#define EXYNOS_VIDADDR_PAGEWIDTH(x)			(((x) & 0x1fff) << 0)
#define EXYNOS_VIDADDR_OFFSIZE_E(x)			((((x) & 0x2000) >> 13) << 27)
#define EXYNOS_VIDADDR_PAGEWIDTH_E(x)			((((x) & 0x2000) >> 13) << 26)

/* WIN Color Map */
#define EXYNOS_WINMAP_COLOR(x)				((x) & 0xffffff)

/* VIDINTCON0 */
#define EXYNOS_VIDINTCON0_SYSMAINCON_DISABLE		(0 << 19)
#define EXYNOS_VIDINTCON0_SYSMAINCON_ENABLE		(1 << 19)
#define EXYNOS_VIDINTCON0_SYSSUBCON_DISABLE		(0 << 18)
#define EXYNOS_VIDINTCON0_SYSSUBCON_ENABLE		(1 << 18)
#define EXYNOS_VIDINTCON0_SYSIFDONE_DISABLE		(0 << 17)
#define EXYNOS_VIDINTCON0_SYSIFDONE_ENABLE		(1 << 17)
#define EXYNOS_VIDINTCON0_FRAMESEL0_BACK		(0 << 15)
#define EXYNOS_VIDINTCON0_FRAMESEL0_VSYNC		(1 << 15)
#define EXYNOS_VIDINTCON0_FRAMESEL0_ACTIVE		(2 << 15)
#define EXYNOS_VIDINTCON0_FRAMESEL0_FRONT		(3 << 15)
#define EXYNOS_VIDINTCON0_FRAMESEL0_MASK		(3 << 15)
#define EXYNOS_VIDINTCON0_FRAMESEL1_NONE		(0 << 13)
#define EXYNOS_VIDINTCON0_FRAMESEL1_BACK		(1 << 13)
#define EXYNOS_VIDINTCON0_FRAMESEL1_VSYNC		(2 << 13)
#define EXYNOS_VIDINTCON0_FRAMESEL1_FRONT		(3 << 13)
#define EXYNOS_VIDINTCON0_INTFRMEN_DISABLE		(0 << 12)
#define EXYNOS_VIDINTCON0_INTFRMEN_ENABLE		(1 << 12)
#define EXYNOS_VIDINTCON0_FIFOSEL_WIN4			(1 << 11)
#define EXYNOS_VIDINTCON0_FIFOSEL_WIN3			(1 << 10)
#define EXYNOS_VIDINTCON0_FIFOSEL_WIN2			(1 << 9)
#define EXYNOS_VIDINTCON0_FIFOSEL_WIN1			(1 << 6)
#define EXYNOS_VIDINTCON0_FIFOSEL_WIN0			(1 << 5)
#define EXYNOS_VIDINTCON0_FIFOSEL_ALL			(0x73 << 5)
#define EXYNOS_VIDINTCON0_FIFOSEL_MASK			(0x73 << 5)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_25			(0 << 2)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_50			(1 << 2)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_75			(2 << 2)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_EMPTY		(3 << 2)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_FULL		(4 << 2)
#define EXYNOS_VIDINTCON0_FIFOLEVEL_MASK		(7 << 2)
#define EXYNOS_VIDINTCON0_INTFIFO_DISABLE		(0 << 1)
#define EXYNOS_VIDINTCON0_INTFIFO_ENABLE		(1 << 1)
#define EXYNOS_VIDINTCON0_INT_DISABLE			(0 << 0)
#define EXYNOS_VIDINTCON0_INT_ENABLE			(1 << 0)
#define EXYNOS_VIDINTCON0_INT_MASK			(1 << 0)

/* VIDINTCON1 */
#define EXYNOS_VIDINTCON1_INTVPPEND			(1 << 5)
#define EXYNOS_VIDINTCON1_INTI80PEND			(1 << 2)
#define EXYNOS_VIDINTCON1_INTFRMPEND			(1 << 1)
#define EXYNOS_VIDINTCON1_INTFIFOPEND			(1 << 0)

/* WINMAP */
#define EXYNOS_WINMAP_ENABLE				(1 << 24)

/* WxKEYCON0 (1~4) */
#define EXYNOS_KEYCON0_KEYBLEN_DISABLE			(0 << 26)
#define EXYNOS_KEYCON0_KEYBLEN_ENABLE			(1 << 26)
#define EXYNOS_KEYCON0_KEY_DISABLE			(0 << 25)
#define EXYNOS_KEYCON0_KEY_ENABLE			(1 << 25)
#define EXYNOS_KEYCON0_DIRCON_MATCH_FG			(0 << 24)
#define EXYNOS_KEYCON0_DIRCON_MATCH_BG			(1 << 24)
#define EXYNOS_KEYCON0_COMPKEY(x)			(((x) & 0xffffff) << 0)

/* WxKEYCON1 (1~4) */
#define EXYNOS_KEYCON1_COLVAL(x)			(((x) & 0xffffff) << 0)

/* DUALRGB */
#define EXYNOS_DUALRGB_BYPASS_SINGLE			(0x00 << 0)
#define EXYNOS_DUALRGB_BYPASS_DUAL			(0x01 << 0)
#define EXYNOS_DUALRGB_MIE_DUAL				(0x10 << 0)
#define EXYNOS_DUALRGB_MIE_SINGLE			(0x11 << 0)
#define EXYNOS_DUALRGB_LINESPLIT			(0x0 << 2)
#define EXYNOS_DUALRGB_FRAMESPLIT			(0x1 << 2)
#define EXYNOS_DUALRGB_SUB_CNT(x)			((x & 0xfff) << 4)
#define EXYNOS_DUALRGB_VDEN_EN_DISABLE			(0x0 << 16)
#define EXYNOS_DUALRGB_VDEN_EN_ENABLE			(0x1 << 16)
#define EXYNOS_DUALRGB_MAIN_CNT(x)			((x & 0xfff) << 18)

/* I80IFCONA0 and I80IFCONA1 */
#define EXYNOS_LCD_CS_SETUP(x)				(((x) & 0xf) << 16)
#define EXYNOS_LCD_WR_SETUP(x)				(((x) & 0xf) << 12)
#define EXYNOS_LCD_WR_ACT(x)				(((x) & 0xf) << 8)
#define EXYNOS_LCD_WR_HOLD(x)				(((x) & 0xf) << 4)
#define EXYNOS_RSPOL_LOW				(0 << 2)
#define EXYNOS_RSPOL_HIGH				(1 << 2)
#define EXYNOS_I80IFEN_DISABLE				(0 << 0)
#define EXYNOS_I80IFEN_ENABLE				(1 << 0)

/* TRIGCON */
#define EXYNOS_I80SOFT_TRIG_EN				(1 << 0)
#define EXYNOS_I80START_TRIG				(1 << 1)
#define EXYNOS_I80STATUS_TRIG_DONE			(1 << 2)

/* DP_MIE_CLKCON */
#define EXYNOS_DP_MIE_DISABLE				(0 << 0)
#define EXYNOS_DP_CLK_ENABLE				(1 << 1)
#define EXYNOS_MIE_CLK_ENABLE				(3 << 0)

#endif
