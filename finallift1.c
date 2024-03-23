//lcd,led and keypad microcontoller
  
   #include<lpc21xx.h>
   #include"lcd_fun.c"

   #define ROWS (0X0F<<21)
   #define COLS (0X0F<<17)

   unsigned int new;
   unsigned int Current_position=0, Next_position=0,LED=17; 
   int diffrence=0;
   unsigned int old=0X0E;
 
   void col_scan(void);
   void row_scan1(void);
   //void led(unsigned int);

   unsigned int reg;

   int main()
   {
   IODIR0=(1<<18);
   IODIR0=(1<<19);
   IODIR0=(1<<20);
   IODIR0=(1<<17);
   IOCLR0=(1<<18);
   IOCLR0=(1<<19);
   IOCLR0=(1<<20);
   IOCLR0=(1<<17);

   lcd_config();
   while(1)
   {
   IOSET0=(1<<LED);
   col_scan();
   }
   }
   void col_scan(void)
   {
   unsigned int val;
   IODIR1=ROWS;
   IODIR1&=~(COLS);
   val=(IOPIN1&COLS);
   val=val>>17;
    
   switch(val)
   {
   case 0X0E:row_scan1();
             delay(400);
			 break;
                
  }
  }
  void row_scan1(void)
  {
  int i,j;
  unsigned int val;
  IODIR1=COLS;
  IODIR1&=~(ROWS);
  val=(IOPIN1&ROWS);
  val=val>>21;


  
  switch(val)
   {
   case 0X0E:Next_position=0;
   			 lcd_cmd(0X01);
   			lcd_str("GROUND FLOOR");
             delay(400);
			 //lcd_cmd(0X01);
			 break;
   case 0X0D:Next_position=1;
   			 lcd_cmd(0X01);
   			lcd_str("FIRST FLOOR");
			 delay(400);
			 //lcd_cmd(0X01);			  
			 break;
   case 0X0B:Next_position=2;
    		lcd_cmd(0X01);
   			lcd_str("SECOND FLOOR");
			 delay(400);
			 //lcd_cmd(0X01);
			 break;
   case 0X07:Next_position=3;
   			 lcd_cmd(0X01);
			lcd_str("THIRD FLOOR");
			 delay(400);
			 //lcd_cmd(0X01);
			 break;
	 default: lcd_cmd(0X01);
            delay(400);
	}


	 if(Current_position<Next_position)
	 {
	 	//led and fan
       diffrence=Next_position-Current_position;
        if(diffrence<0)
        {
            diffrence=diffrence*(-1);
        }
		IOCLR0|=(1<<18)|(1<<19)|(1<<20)|(1<<17);
		IOSET0=(1<<LED);

       for(i=0;i<diffrence;i++)
	   {
	   		    IOSET0=(1<<LED);
				delay(2000);
				IOCLR0=(1<<LED);
				delay(2000);
             
			LED++;
			lcd_num(LED);
			Current_position++;
  		}
		IOCLR0|=(1<<18)|(1<<19)|(1<<20)|(1<<17);
		IOSET0=(1<<LED);

		Next_position=0;


	}
   		else if(Current_position>Next_position) 
   		{
		//led fan
        	diffrence=Next_position-Current_position;
        	if(diffrence<0)
        	{
            diffrence=diffrence*(-1);									   
        	}
			 IOCLR0|=(1<<18)|(1<<19)|(1<<20)|(1<<17);
			 IOSET0=(1<<LED);
	
	
       		for(j=0;j<diffrence;j++)
            {
			
				IOSET0=(1<<LED);
				delay(2000);
				IOCLR0=(1<<LED);
				delay(2000);
				LED--;
				lcd_num(LED);
				Current_position--;

  			}
	        IOCLR0|=(1<<18)|(1<<19)|(1<<20)|(1<<17);
			IOSET0=(1<<LED);
			Next_position=0;
		}
		else
		{
			IOSET0=(1<<LED);

		}
  	  
}