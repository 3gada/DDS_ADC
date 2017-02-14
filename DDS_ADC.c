#include "LPC43xx.h" /* LPC43xx Definitions                */

#define Base_address_ext_RAM 0x1C000000;
#define Size_ext_RAM_16 (1 << 22);
#define Max_address_ext_RAM 0x1C3FFFFF - 1;

unsigned int i0;
unsigned int in5_1;
unsigned char in5;
unsigned char in6;
unsigned char on_off_led;
unsigned char number_led;

unsigned int const Base_address_ext_RAM_ = 0x1C000000;
unsigned int const Size_ext_RAM_16_ = (1 << 22);

unsigned int k;
unsigned int k7;
unsigned int k8;

unsigned int i0_tmp;
unsigned int i1_tmp;

unsigned int i0_t;
unsigned int i1_t;
unsigned int ik_t;
unsigned char RAM_test_continue = 0;

double Time = 10000.0 / 1500.0;

void SysTick_Handler(void)
{
  static uint32_t ticks;

  ticks++;
  if (ticks >= 400)
  {
    ticks = 0;
    on_off_led ^= 0x01;

    switch (number_led)
    {
    //			case 0: {if (on_off_led != 0){LPC_GPIO_PORT->CLR[3] = (1<<5);} else { LPC_GPIO_PORT->SET[3] = (1<<5) ; number_led = 1;} break;}
    //			case 1:	{if (on_off_led != 0){LPC_GPIO_PORT->CLR[3] = (1<<7);} else { LPC_GPIO_PORT->SET[3] = (1<<7) ; number_led = 2;} break;}
    //			case 2: {if (on_off_led != 0){LPC_GPIO_PORT->CLR[0] = (1<<7);} else { LPC_GPIO_PORT->SET[0] = (1<<7) ; number_led = 0;} break;}
    case 0:
    {
      if (on_off_led != 0)
      {
        LPC_GPIO_PORT->CLR[3] = (1 << 5);
      }
      else
      {
        LPC_GPIO_PORT->SET[3] = (1 << 5);
        number_led = 1;
      }
      break;
    }
    case 1:
    {
      if (on_off_led != 0)
      {
        LPC_GPIO_PORT->CLR[3] = (1 << 7);
      }
      else
      {
        LPC_GPIO_PORT->SET[3] = (1 << 7);
        number_led = 2;
      }
      break;
    }
    case 2:
    {
      if (on_off_led != 0)
      {
        LPC_GPIO_PORT->CLR[0] = (1 << 7);
      }
      else
      {
        LPC_GPIO_PORT->SET[0] = (1 << 7);
        number_led = 0;
      }
      break;
    }
    default:
    {
      number_led = 0;
      break;
    }
    }

    LPC_GPIO_PORT->NOT[3] = (1 << 8);
  }
}

int main(void)
{

  SystemCoreClockUpdate(); /* Update system core clock       */

  SysTick_Config(204000); /* Generate interrupt each 10 ms  */

  LPC_CGU->BASE_SSP0_CLK = (0x09 << 24); // CLK_SEL = PLL1

  LPC_CGU->BASE_M4_CLK = (0x01 << 11) |       /* Autoblock En               */
                         (0x09 << 24);        /* Set clock source PLL1      */
  LPC_CGU->BASE_PERIPH_CLK = (0x01 << 11) |   /* Autoblock En               */
                             (0x09 << 24);    /* Set clock source PLL1      */
  LPC_CGU->BASE_APB1_CLK = (0x01 << 11) |     /* Autoblock En               */
                           (0x09 << 24);      /* Set clock source PLL1      */
  LPC_CGU->BASE_APB3_CLK = (0x01 << 11) |     /* Autoblock En               */
                           (0x09 << 24);      /* Set clock source PLL1      */
  LPC_CGU->BASE_CGU_OUT0_CLK = (0x01 << 11) | /* Autoblock En               */
                               (0x09 << 24);  /* Set clock source PLL1      */
  LPC_CGU->BASE_CGU_OUT1_CLK = (0x01 << 11) | /* Autoblock En               */
                               (0x09 << 24);  /* Set clock source PLL1      */
  LPC_CGU->BASE_APLL_CLK = (0x01 << 11) |     /* Autoblock En               */
                           (0x09 << 24);      /* Set clock source PLL1      */
  LPC_CGU->BASE_OUT_CLK = (0x01 << 11) |      /* Autoblock En               */
                          (0x09 << 24);       /* Set clock source PLL1      */

  LPC_CGU->BASE_UART1_CLK = (0x01 << 11) | /* Autoblock En               */
                            (0x09 << 24);  /* Set clock source PLL1      */

  LPC_CGU->BASE_OUT_CLK = (0x01 << 11) | /* Autoblock En               */
                          (0x09 << 24);  /* Set clock source PLL1      */

  LPC_CGU->BASE_CGU_OUT0_CLK = (0x01 << 11) | /* Autoblock En               */
                               (0x09 << 24);  /* Set clock source PLL1      */

  LPC_CGU->BASE_CGU_OUT1_CLK = (0x01 << 11) | /* Autoblock En               */
                               (0x09 << 24);  /* Set clock source PLL1      */

  LPC_CGU->BASE_PHY_RX_CLK = (0x01 << 11) | /* Autoblock En               */
                             (0x09 << 24);  /* Set clock source PLL1      */

  LPC_CGU->BASE_PHY_TX_CLK = (0x01 << 11) | /* Autoblock En               */
                             (0x09 << 24);  /* Set clock source PLL1      */

  LPC_GPIO_PORT->DIR[3] = (1 << 5) | (1 << 7);
  LPC_GPIO_PORT->DIR[0] = (1 << 7);
  LPC_GPIO_PORT->SET[3] = (1 << 5) | (1 << 7);
  LPC_GPIO_PORT->SET[0] = (1 << 7);

  while (1)
  {
  }

  for (in5_1 = 0; in5_1 < 50000; in5_1++)
  {
  }
}
