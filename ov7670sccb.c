static void delay(int c){
for(int i=0;i<c;i++){
__nop();
}
}
static void sccb_start(){
GPIOB->BSRRH=GPIO_BSRR_BS_5;
   delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
   delay(20);
   delay(100);
}
static void sccb_stop(){
   delay(100);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
   delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_5;
   delay(20);
}

static void sccb_write(char addr){
GPIOB->BSRRL=GPIO_BSRR_BS_4|GPIO_BSRR_BS_5;//clk high,data high
delay(100);
sccb_start();
for(int i=0;i<9;i++)
{
   if(i<8){
   if((0x42<<i)&0x80){
GPIOB->ODR=(GPIOB->ODR|0x0020)&0xFFEF;
   }
else
   {
GPIOB->ODR&=0xFFCF;

}
   delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);   
   }
   else   
   {
GPIOB->BSRRH=GPIO_BSRR_BS_4;
GPIOB->MODER &= ~GPIO_MODER_MODER5;
GPIOB->OTYPER|=GPIO_ODR_ODR_5;
delay(20);   
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
delay(20);
GPIOB->MODER|=GPIO_MODER_MODER5_0;
GPIOB->OTYPER&=~GPIO_ODR_ODR_5;
GPIOB->BSRRH=GPIO_BSRR_BS_5;
   }   
}
delay(100);
for(int i=0;i<9;i++)
{
   if(i<8){
   if((addr<<i)&0x80){
GPIOB->ODR=(GPIOB->ODR|0x0020)&0xFFEF;
   }
else
   {
GPIOB->ODR&=0xFFCF;

}
   delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);   
   }
   else   
   {
GPIOB->BSRRH=GPIO_BSRR_BS_4;
GPIOB->MODER &= ~GPIO_MODER_MODER5;
GPIOB->OTYPER|=GPIO_ODR_ODR_5;
delay(20);   
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
delay(20);
GPIOB->MODER|=GPIO_MODER_MODER5_0;
GPIOB->OTYPER&=~GPIO_ODR_ODR_5;
GPIOB->BSRRH=GPIO_BSRR_BS_5;
   }   
}

}

static char sccb_read(){
char response=0;
GPIOB->BSRRL=GPIO_BSRR_BS_4|GPIO_BSRR_BS_5;//clk high,data high
delay(100);
sccb_start();
for(int i=0;i<9;i++)
{
   if(i<8){
   if((0x43<<i)&0x80){
GPIOB->ODR=(GPIOB->ODR|0x0020)&0xFFEF;
   }
else
   {
GPIOB->ODR&=0xFFCF;

}
   delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);   
   }
   else   
   {
GPIOB->BSRRH=GPIO_BSRR_BS_4;
GPIOB->MODER &= ~GPIO_MODER_MODER5;
GPIOB->OTYPER|=GPIO_ODR_ODR_5;
delay(20);   
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
delay(20);
GPIOB->MODER|=GPIO_MODER_MODER5_0;
GPIOB->OTYPER&=~GPIO_ODR_ODR_5;
GPIOB->BSRRH=GPIO_BSRR_BS_5;
   }   
}
delay(100);
//Reading
GPIOB->MODER &= ~GPIO_MODER_MODER5;
GPIOB->OTYPER|=GPIO_ODR_ODR_5;
for(int i=0;i<9;i++)
{
   if(i<8){
delay(20);
response|=(((GPIOB->IDR)&GPIO_IDR_IDR_5)>>5)<<(7-i);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
   }
else
{
GPIOB->MODER|=GPIO_MODER_MODER5_0;
GPIOB->OTYPER&=~GPIO_ODR_ODR_5;
GPIOB->BSRRL=GPIO_BSRR_BS_5;
delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_5;
GPIOB->BSRRH=GPIO_BSRR_BS_4;
sccb_stop();   
}   
}
return response;
}

static char sccb_read_reg(char reg){
sccb_write(reg);
   sccb_stop();
return sccb_read();   
}

static void sccb_write_reg(char reg,char val){
sccb_write(reg);
for(int i=0;i<9;i++)
{
   if(i<8){
   if((val<<i)&0x80){
GPIOB->ODR=(GPIOB->ODR|0x0020)&0xFFEF;
   }
else
   {
GPIOB->ODR&=0xFFCF;

}
   delay(20);
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);   
   }
   else   
   {
GPIOB->BSRRH=GPIO_BSRR_BS_4;
GPIOB->MODER &= ~GPIO_MODER_MODER5;
GPIOB->OTYPER|=GPIO_ODR_ODR_5;
delay(20);   
GPIOB->BSRRL=GPIO_BSRR_BS_4;
delay(20);
GPIOB->BSRRH=GPIO_BSRR_BS_4;
delay(20);
GPIOB->MODER|=GPIO_MODER_MODER5_0;
GPIOB->OTYPER&=~GPIO_ODR_ODR_5;
GPIOB->BSRRH=GPIO_BSRR_BS_5;
   }   
}
sccb_stop();
}
