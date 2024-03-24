//lcd,led and keypad microcontoller
  
   #include<lpc21xx.h>
   #include"lcd_fun.c"

   #define ROWS 
   #define COLS 

   unsigned int new;
   unsigned int Current_position=0, Next_position=0;
   int diffrence=0;
   unsigned int old=0X0E;
 
   void col_scan(void);
   void row_scan1(void);
   //void led(unsigned int);

   unsigned int reg;

   int main()
   {
   //define gpio pins

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
	 	//led and fan
       diffrence=Next_position-Current_position;
        if(diffrence<0)
        {
            diffrence=diffrence*(-1);
        }
		
		IOSET0=(1<<LED);

       for(i=0;i<diffrence;i++)
	   {
	   		    
             
			LED++;
			
			Current_position++;
  		}
		

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
				
				Current_position--;

  			}
	        
			Next_position=0;
		}
		else
		{
			IOSET0=(1<<LED);

		}
  	  
}
