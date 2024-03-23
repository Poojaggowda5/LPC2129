# LPC2129
Continuing My Journey in the Embedded 
👉🏻Ongoing Learning for project
For this project, I had designed and built a elevator operating system using LPC2129 microcontroller.
Here are some key technical aspects:
🧠Microcontroller: I used the LPC2129 Microcontroller, I began programming our microcontroller to interpret button and light signals.
Keypad configuration: Here is have taken rows as ouput and columns as input.The rows and columns are manipulated to read the pressed key.
LED indication: The led function takes a floor number and illuminates the appropriate LED segments on the floor indicator to show the elevator’s position. The led indication gradually lights up as you go through any floor.
If there is more weight in lift then led indicator stops in that floor indicating through buzzer lift have more weight.
Potentiometer: Here i have interfaced the potentiometer (ADC) values to indicate the weight inside the lift. If the weight inside lift exceeds the predefined value then BUZZER will beep as indication the lift have more weight and lift stops for certain time.( TIMER INTERRUPTS) 
LCD 16*02 (standard LCD) : The microcontroller sends commands to illuminate specific lights and display the choosen floor number. As well as to display open and close of lift and weigh of lift of choosen floor.

Building this project from scratch has been rewarding journey and I had learnt how to program in embedded c, knowledge about ADC, PWM, Timers and interrupts. 
Never used protocol if incase used it would be automated lift operation. I had made manual operation of inside as well as outside the lift
For fan and light i had used PWM concept for fan using a servo motor for continuous rotation and for light led indication.

Thank you!
