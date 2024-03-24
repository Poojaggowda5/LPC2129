// final mixture of pot, led,lcd,keypad
   #include<lpc21xx.h>
   #include"lcd_fun.c"
   //#include"potentio.c"

   #define ROWS 
   #define COLS 

   unsigned int new;
   unsigned int Current_position=0, Next_position=0; 
   int diffrence=0;
   unsigned int old=0X0E;
   unsigned int value;
 
   void col_scan(void);
   void row_scan1(void);
   //void led(unsigned int);

   unsigned int reg;

   int main()
   {
   //define gpio pins
   PINSEL1=(1<<22);
   PINSEL1&=~(1<<23);

   ADCR=(1<<0)|(4<<8)|(1<<16)|(1<<21);

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
  
    
   switch(val)
   {
   case 0X0E:row_scan1();
             delay(400);
			 break;
   case 0X0D:row_scan2();
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
	 	//lcd_str("LIGHT");
       diffrence=Next_position-Current_position;
        if(diffrence<0)
        {
            diffrence=diffrence*(-1);
        }
		

       for(i=0;i<diffrence;i++)
	   {
	   		   
			LED++;
			
			Current_position++;
  		}
		
		//lcd_cmd(0XC0);
		lcd_str("OPEN");
		
        
        while(!(ADDR & (1<<31))); //moniotr done bit to check end of conversion,polling
        value=(ADDR &(0X3FF<<6)); //extract 10 bit digital results
        value=value>>6;//to get as LSB
        value=value/3.3; //to get equivalent 8 bit value
        lcd_num(value);
        

		lcd_cmd(0XC0);
		lcd_str("POT:");
        lcd_num(value);
		if(value>80)
		{
		IOSET0=(1<<11);
		delay(1000);
		}
		
        delay(1000);
        //lcd_cmd(0X01);//clear

		
		lcd_str("CLOSE");
		lcd_cmd(0X01);
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
	
       		for(j=0;j<diffrence;j++)
            {
			
				
				LED--;
				lcd_num(LED);
				Current_position--;

  			}
	        IOCLR0|=(1<<18)|(1<<19)|(1<<20)|(1<<17);
			IOSET0=(1<<LED);
			delay(3000);
			//lcd_cmd(0XC0);
		   lcd_str("OPEN");
		
       
        
        while(!(ADDR & (1<<31))); //moniotr done bit to check end of conversion,polling
        val=(ADDR &(0X3FF<<6)); //extract 10 bit digital results
        value=value>>6;//to get as LSB
        value=value/3.3; //to get equivalent 8 bit value
		lcd_cmd(0XC0);
		lcd_str("POT:");
        lcd_num(value);
		if(value>80)
		{
		IOSET0=(1<<11);
		delay(1000);
		}
		
        delay(1000);
        //lcd_cmd(0X01);//clear


		lcd_str("CLOSE");
		lcd_cmd(0X01);
			Next_position=0;
		}
		else
		{
			IOSET0=(1<<LED);

		}
  	  
}
