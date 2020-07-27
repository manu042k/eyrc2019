/*
 * Team Id          :    EYRC-415
 * Author List      :    Manoj M ,koustub SH,Sujeeth kumar,Kiran S
 * Filename         :    built_fun.h
 * Theme            :    Construct-O-Bot         
 * Functions        :    void buzzer_on(void),
                          void buzzer_on(void),
                          void forward_by_count(unsigned long int count,int left_velocity,int right_velocity),
                          void left_by_count(unsigned long int count,int left_velocity,int right_velocity),
                          //void right_by_count(unsigned long int count,int left_velocity,int right_velocity),
                          void backward_by_count(int count,int left_velocity,int right_velocity),
                          void node(void),
                          void turn_right(int left_velocity,int right_velocity),
                          void turn_left(int left_velocity,int right_velocity),
                          void right_pick(),
                          void left_pick(),
                          void right_place(int type_floor),
                          void left_place(int type_floor),
                          void staright_place(int floor_type),
						  void place_h5(int floor_type),
						  void find_left(int left_velocity,int right_velocity).
 *Global Variables :     global variables required are declared in configure.h file
 *Functionality    :     All the function related to motion are declared here.
*/






//includes configure header file
#include "configure.h"



//functions declaration 
void buzzer_on(void);
void buzzer_on(void);
void forward_by_count(unsigned long int count,int left_velocity,int right_velocity);
void left_by_count(unsigned long int count,int left_velocity,int right_velocity);
//void right_by_count(unsigned long int count,int left_velocity,int right_velocity);
void backward_by_count(int count,int left_velocity,int right_velocity);
void node(void);
void turn_right(int left_velocity,int right_velocity);
void turn_left(int left_velocity,int right_velocity);
void right_pick();
void left_pick();
void right_place(int type_floor);
void left_place(int type_floor);
void staright_place(int floor_type);
void find_left(int left_velocity,int right_velocity);
void place_h5(int floor_type);



/*
*Function Name: buzzer_on (void)
*Input        : void 
*Output       : void
*Logic        : turns on buzzer for 5 seconds  
*Example call : buzzer_on();
*/

void buzzer_on (void)
{
	unsigned char port_restore = 0;
	port_restore = PINJ;
	port_restore = port_restore | 0x08;
	PORTJ = port_restore;
	_delay_ms(5000);
}


/*
*Function     : buzzer_off (void)
*Input        : void
*Output       : void
*Logic        : turns off buzzer 
*Example call : buzzer_off();
*/
void buzzer_off (void)
{
	unsigned char port_restore = 0;
	port_restore = PINJ;
	port_restore = port_restore & 0xF7;
	PORTJ = port_restore;
}



/*
*Function     : void forward_by_count(unsigned long int count,int left_velocity,int right_velocity)
*Input        : counts,left_velocity,right_velocity
*Output       : void
*Logic        : moves forward by specified no. of counts at specified velocity,used instead of delays 
*Example call : forward_by_count(200,150,150);
*/
void forward_by_count(unsigned long int count,int left_velocity,int right_velocity)
{
	//setting counts to zero
   	ShaftCountLeft=0;
	ShaftCountRight=0;
	
	//starting the infinite loop
	while(1)
	{
		//terminates if counts is greater then specified 
		if (ShaftCountRight >= count)
		{
			break;
		}
		//moves at given velocity 
		else
		{
			//lcd_print(1,1,ShaftCountRight,4);
		    forward();
			velocity(left_velocity,right_velocity);
		}
	}
	stop();
}


/*
*Function     : void left_by_count(unsigned long int count,int left_velocity,int right_velocity)
*Input        : counts,left_velocity,right_velocity
*Output       : void
*Logic        : moves left by specified no. of counts at specified velocity,used instead of delays 
*Example call : left_by_count(200,150,150);
*/

void left_by_count(unsigned long int count,int left_velocity,int right_velocity)
{
	//setting counts to zero
	ShaftCountLeft=0;
	ShaftCountRight=0;
	
	//starting the infinite loop
	while(1)
	{
		//terminates if counts is greater then specified
		if (ShaftCountRight>=count)
		{
			break;
		}
		//moves at given velocity 
		else
		{
			left();
			velocity(left_velocity,right_velocity);
		}
	}
	stop();
}

/* NOTE LEFT ENCODER IS NOT WORKING HENCE WE ARE NOT INCLUCDING THIS FUNCTION
*Function     : void right_by_count(unsigned long int count,int left_velocity,int right_velocity)
*Input        : counts,left_velocity,right_velocity
*Output       : void
*Logic        : moves right by specified no. of counts at specified velocity
*Example call : right_by_count(200,150,150);

void right_by_count(int count,int left_velocity,int right_velocity)
{
	//setting counts to zero
	ShaftCountLeft=0;
	ShaftCountRight=0;
	
	//starting the infinite loop
	while(ShaftCountLeft<=count||ShaftCountRight<=count)
	{
		//moves at given velocity
		right();
		velocity(left_velocity,right_velocity);
	}
	stop();
}
*/

/*
*Function     : void backward_by_count(unsigned long int count,int left_velocity,int right_velocity)
*Input        : counts,left_velocity,right_velocity
*Output       : void
*Logic        : moves backward by specified no. of counts at specified velocity
*Example call : backward_by_count(200,150,150);
*/

void backward_by_count(int count,int left_velocity,int right_velocity)
{
	//setting counts to zero
	ShaftCountLeft=0;
	ShaftCountRight=0;
	
	//starting the infinite loop
	while(1)
	{
		//terminates if counts is greater then specified
		if (ShaftCountRight>=count)
		{
			break;
		}
		//moves at given velocity
		else
		{
			
			
			backward();
			velocity(left_velocity,right_velocity);
		}
	}
	stop();
}

/*
*Function     : void node()
*Logic        : function to follow black lines,follow wall and follow zig_zag ,
                depending on the values white_line_sensor and sharpe_sensor following function is written 
*Input        : void
*Output       : void
*Example call : node();
*/


void node ()
{
	//starting infinte loop
	while (1)
	{
		Left_white_line = ADC_Conversion(1);                   //Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);                 //Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(3);                  //Getting data of Right WL Sensor
		
		sharp_left = ADC_Conversion(4);						    //Stores the Analog value of front sharp connected to ADC channel 4 into variable "sharp_left"
		value_left = Sharp_GP2D12_estimation(sharp_left);		//Stores Distance calculated in a variable "value_left".
		lcd_print(2,5,value_left,3);
		sharp_right = ADC_Conversion(5);						//Stores the Analog value of front sharp connected to ADC channel 5 into variable "sharp"
		value_right = Sharp_GP2D12_estimation(sharp_right);		//Stores Distance calculated in a variable "value_right".
		lcd_print(2,10,value_right,3);
		
		
		//sets flag to zero
		flag=0;
		
        //stops if Left_WL and Center_WL or Right_WL and Center_WL are greater then thershold
		if ((Center_white_line>thershold && Left_white_line>thershold )||(Center_white_line>thershold&& Right_white_line>thershold))
		{
			//moves forward by 100 counts
			forward_by_count(150,110,110);
			//stops
			forward();
			velocity(0,0);
			//terminates the loop
			break;
		}

          //moves forward if center_WL greater then thershold
		 if(Center_white_line>thershold)
		{
			//sets flag to 1
			flag=1;
		   //moves forward
			forward();
			velocity(110,110);
			
		}
         //takes soft_left if left_WL is greater then thershold and flag is zero
		else if((Left_white_line>thershold) && (flag==0))
		{
			//sets flag to 1
			flag=1;
			//takes soft_left
			forward();
			velocity(0,100);
			
		}
        //takes soft_right if right_WL is greater then thershold and flag is zero
		else if((Right_white_line>thershold) && (flag==0))
		{
			//sets flag to 1
			flag=1;
			//takes soft_right
			forward();
			velocity(100,0);
					}
		//when all three sensor are less then thershold and distance form wall is less than 300 mm
        else if (flag==0 && Right_white_line<thershold && Left_white_line<thershold && value_left<300 )
		{
			//NOTE:ONLY LEFT SHAPRE SENSOR DATA IS USED
			
			//distance less 80mm takes slight right turn
			if (value_left<80)
			{
				
				forward();
				velocity(100,80);
			}
			//distance between 80mm and 95mm moves forward
			else if ((value_left>=80) && (value_left<=95))
			{
				forward();
				velocity(100,100);
				_delay_ms(50);
			}
			//distance above 95mm and below 150 takes slight left turn
			else if ((value_left>95)&&(value_left<=250))
			{
				
				forward();
				velocity(100,80);
			}
			//else takes slight right turn

			else
			{
				velocity(80,100);
			}
			
		}
		
		
	}
	//stops 
   //	stop();
	
}


void follow_black()
{
	while(1)
	{

		Left_white_line = ADC_Conversion(1);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(3);	//Getting data of Right WL Sensor

		flag=0;

		print_sensor(1,1,3);	//Prints value of White Line Sensor1
		print_sensor(1,5,2);	//Prints Value of White Line Sensor2
		print_sensor(1,9,1);	//Prints Value of White Line Sensor3
		
		unsigned char thershold1=0x78;

		if(Center_white_line<thershold1)
		{
			flag=1;
			forward();
			velocity(100,100);
		}

		if((Left_white_line>thershold1) && (flag==0))
		{
			flag=1;
			forward();
			velocity(100,0);
		}

		if((Right_white_line>thershold1) && (flag==0))
		{
			flag=1;
			forward();
			velocity(0,100);
		}
		
		if((Center_white_line< thershold1&& Left_white_line<thershold1)||( Center_white_line< thershold1&& Right_white_line<thershold1))
		{
			forward_by_count(100,100,100);
			forward();
			velocity(0,0);
			break;
		}
		
		
		
	}
}



/*
*Function     : void turn_left(int left_velocity,int right_velocity)
*Logic        : function to turn towards left until black is found 
*Input        : left_velocity,right_velocity
*Output       : void
*Logic        : function to turn towards left until black is found,robot is moved out line initially then turned left until left_WL is greater than thershold  
*Example call : turn_left(100,100);
*/

void turn_left(int left_velocity,int right_velocity)
{
	//moves out of present black line
	left();
	velocity(100,100);
	_delay_ms(300);
	
	//starting infinite loop
	while(1)
	{
		
		Left_white_line=ADC_Conversion(1);         //Getting data of Left WL Sensor 
		Center_white_line=ADC_Conversion(2);       //Getting data of Center WL Sensor
		Right_white_line=ADC_Conversion(3);        //Getting data of Right WL Sensor
		
		//terminates if left_WL is greater then thershold
		if(Left_white_line>thershold)
		{
			break;
		}
		//turn left
		else
		{
			left();
			velocity(left_velocity,right_velocity);
		}
	}
	stop();
}

/*
*Function     : void turn_right(int left_velocity,int right_velocity)
*Input        : left_velocity,right_velocity
*Logic        : function to turn towards right until black is found,robot is moved out line initially then turned right until right_WL is greater than thershold  
*Output       : void
*Example call : turn_right(100,100);
*/

void turn_right(int left_velocity,int right_velocity)
{
	//moves out of present black line
	
	right();
	velocity(100,100);
	_delay_ms(300);
	
	//starting infinite loop
	while(1)
	{
		Left_white_line=ADC_Conversion(1);            //Getting data of Left WL Sensor
		Center_white_line=ADC_Conversion(2);          //Getting data of center WL Sensor
		Right_white_line=ADC_Conversion(3);           //Getting data of right WL Sensor
		
		//terminates if right_WL is greater then thershold
		if(Right_white_line>thershold)
		{
			break;
		}
		//turns right
		else
		{
			right();
			velocity(left_velocity,right_velocity);
		}
	}
	stop();
}

/*
*Function     : void find_left(int left_velocity,int right_velocity)
*Input        : left_velocity,right_velocity
*Logic        : function to turn towards right until white line is found,robot is initially on the black then turned left until right_WL is less than thershold
*Output       : void
*Example call : turn_left(100,100);
*/

void find_left(int left_velocity,int right_velocity)
{
	//starts infinite loop
	while(1)
	{ 
		
		Left_white_line=ADC_Conversion(1);                //Getting data of Left WL Sensor
		Center_white_line=ADC_Conversion(2);              //Getting data of center WL Sensor   
		Right_white_line=ADC_Conversion(3);               //Getting data of right WL Sensor
		
		//if left_Wl less than thershold 
		if(Left_white_line<thershold)
		{
			break;
		}
		//turns left 
		else
		{
			left();
			velocity(left_velocity,right_velocity);
		}
	}
	
}

/*
*Function     : void left_pick(void)
*Logic        : function to pick CM form left warehouse, bot turns left and gets aligned to pick CM ,then turns right in order be in the same direction 
*Input        : void
*Output       : void
*Example call : left_pick();
*/

void left_pick(void)
{
	//iteration variable 
	int i=0;
	forward_by_count(150,110,110);
	//stops 
	stop();
	
   //moves gripper to zero position 
	servo_1(0);
	
	//moves arm down
	for(i=0;i<140;i++)
	{   
		servo_2(i);
		_delay_ms(10);
	}
	
	//turns left
	turn_left(150,150);
	
    //stops 
	stop();
	
	//moves forward by 180 counts 
	forward_by_count(150,150,100);
	stop();
	
	//gripper holds the CM
	for (i=0;i<120;i++)
	{
		servo_1(i);
		_delay_ms(10);
	}
 
    //moves arm upward 
	for(i=140;i>=0;i--)
	{
		servo_2(i);
		_delay_ms(10);
	}
	
	//sets servo free
	servo_1_free();
	servo_2_free();
	
	//moves backward
	backward_by_count(100,110,110);
	//turn right
	turn_right(100,100);
	stop();

}

/*
*Function     : void right_pick(void)
*Input        : void
*Output       : void
*Logic        : function to pick CM form right warehouse, bot turns right and gets aligned to pick CM ,then turns left in order be in the same direction
*Example call : right_pick();
*/

void right_pick(void)
{
	//iteration variable
	int i=0;
	
	forward_by_count(100,110,110);
	//stops 
	stop();
    
	//moves gripper to zero position 
	servo_1(0);
	
	//moves arm down
	for(i=0;i<140;i++)
	{  
		servo_2(i);
		_delay_ms(10);
	}

    //turn right 
	turn_right(150,150);
	stop();
	
	//moves forward 
	forward_by_count(150,100,150);
	stop();
	
	//gripper holds the CM
	for (i=0;i<120;i++)
	{
		servo_1(i);
		_delay_ms(10);
	}
	
	//arm moves upward
	for(i=140;i>=0;i--)
	{
		servo_2(i);
		_delay_ms(10);
	}
	
	//sets servo free
	servo_1_free();
	servo_2_free();
	
	//moves backward
	backward_by_count(100,110,110);
	
    //turn right
	turn_left(100,100);


	stop();

}

/*
*Function     : void right_place(int type_floor)
*Input        : 0 for lower rise or 1 for high rise 
*Output       : void
*Logic        : function to place  CM at right house, if the house is right of  robot this function is used .It takes right turn then drop CM
                by check whether high rise or low rise ,takes left turn to be in current direction 
*Example call : right_place(1); for high rise ,right_place(0); for low rise 
*/

void right_place( int type_floor)
{  
	
	forward_by_count(100,110,110);
	//takes right
   	turn_right(130,130);
	stop();
	
	
	//checks for high rise or lower rise 
	if (type_floor==0)
	{
		//lower rise
		
		  
		  //arms moves
		  for (i=0;i<=100;i++)
		  {
			  servo_2(i);
			  _delay_ms(10);
		  }
		  //gripper open slowly
		  for (i=120;i>=0;i--)
		  {
			  servo_1(0);
			  _delay_ms(10);
		  }
		  //arms moves back to initial position
		  for (i=100;i>=0;i--)
		  {
			  servo_2(i);
			  _delay_ms(10);
		  }
 
	} 
	else
	{  //high rise 
		
		//arm moves 
		for (i=0;i<=50;i++)
		{
			servo_2(i);
			_delay_ms(10);
		}
		//gripper opens 
		 for (i=120;i>=0;i--)
		 {
			 servo_1(0);
			 _delay_ms(10);
		 }
		//arm back to initial position  
		for (i=50;i>=0;i--)
		{
			servo_2(i);
			_delay_ms(10);
		}
	}
	 
	//sets servo free 
	servo_1_free();
	servo_2_free();
	
	//moves out of black line 
	backward_by_count(100,130,100);
	//turn right
	turn_left(130,130);

}

/*
*Function     : void left_place(int type_floor)
*Input        : 0 for lower rise or 1 for high rise
*Output       : void
*Logic        : function to place  CM at left house, if the house is left of  robot this function is used .It takes left turn then drop CM
                by check whether high rise or low rise ,takes right turn to be in current direction 
*Example call : left_place(1); for high rise ,left_place(0); for low rise
*/

void left_place( int type_floor)
{
	forward_by_count(100,110,110);
	//takes left
	turn_left(130,130);
	stop();
	 
	
	//checks for high rise or lower rise
	if (type_floor==0)
	{
		//lower rise
		
		//arms moves 
		for (i=0;i<=100;i++)
		{
			servo_2(i);
			_delay_ms(10);
		}
		//gripper open slowly 
		for (i=120;i>=0;i--)
		{
			servo_1(0);
			_delay_ms(10);
		}
		//arms moves back to initial position 
		for (i=100;i>=0;i--)
		{
			servo_2(i);
			_delay_ms(10);
		}

		
	}
	else
	{  //high rise
		
		//arm moves
		for (i=0;i<=50;i++)
		{
			servo_2(i);
			_delay_ms(10);
		}
		//gripper opens
		 for (i=120;i>=0;i--)
		 {
			 servo_1(0);
			 _delay_ms(10);
		 }
		//arm back to initial position
		for (i=50;i>=0;i--)
		{
			servo_2(i);
			_delay_ms(10);
		}
	}
	
	//sets servo free
	servo_1_free();
	servo_2_free();
	
	//turn left
	turn_right(130,130);
	
}

/*
*Function     : void staright_place(int type_floor)
*Input        : 0 for lower rise or 1 for high rise
*Output       : void
*Logic        : function to place  CM  house when bot is at same direction to that of house
*Example call : staright_place(1); for high rise ,starigh_place(0);for low rise 
*/

void staright_place(int floor_type)
{   
	//moves forward 
   	forward_by_count(50,150,150);
	
	if (floor_type==0)
	{   
		//lower rise 
		
		 // moves forward
		forward_by_count(100,150,150);
		
		//arms moves
		for (i=0;i<=100;i++)
		{
			servo_2(i);
			_delay_ms(10);
		}
		//gripper open slowly
		for (i=120;i>=0;i--)
		{
			servo_1(0);
			_delay_ms(10);
		}
		//arms moves back to initial position
		for (i=100;i>=0;i--)
		{
			servo_2(i);
			_delay_ms(10);
		}

	}
	else 
	{
		//high rise 
		//arm moves 
	   for (i=0;i<=60;i++)
	   {
		   servo_2(i);
		   _delay_ms(10);
	   }
	   //gripper opens 
	    for (i=120;i>=0;i--)
	    {
		    servo_1(0);
		    _delay_ms(10);
	    }
	   
	   //arm moves to initial position 
	   for (i=60;i>=0;i--)
	   {
		   servo_2(i);
		   _delay_ms(10);
	   }
	}
	
	//sets servo free
	servo_1_free();
	servo_2_free();
	
	//moves out of line 
	backward_by_count(30,100,100);
	
} 

/*
*Function     : void place_h5(int floor_type)
*Input        : 0 for lower rise or 1 for high rise
*Output       : void
*Logic        : this function takes floor type as input then moves to house no 5 ,
                 every time function is called bot moves from east to west ,place the cm then returns back.  
*Example call : void place_h5(0)
*/

void place_h5(int floor_type)
{
	//turns sharp left
	turn_left(0,100);
	stop();
	
	//bot is on black part moves left to find white line 
	find_left(0,100);
	stop();
	_delay_ms(100);
	
	//follows white line  
	follow_black();
	stop();
	//moves forward by 150 counts 
	forward_by_count(150,100,100);
	
	//turns left 
	left_by_count(800,100,100);
	
	//moves back 
	backward_by_count(300,100,100);
      
	  //place the cm 
	  if (floor_type==0)
      {
	      //lower rise
	      
	      //arms moves
	      for (i=0;i<=100;i++)
	      {
		      servo_2(i);
		      _delay_ms(10);
	      }
	      //gripper open slowly
	      for (i=120;i>=0;i--)
	      {
		      servo_1(0);
		      _delay_ms(10);
	      }
	      //arms moves back to initial position
	      for (i=100;i>=0;i--)
	      {
		      servo_2(i);
		      _delay_ms(10);
	      }

      }
      else
      {
	      //high rise
	      //arm moves
	      for (i=0;i<=60;i++)
	      {
		      servo_2(i);
		      _delay_ms(10);
	      }
	      //gripper opens
	      for (i=120;i>=0;i--)
	      {
		      servo_1(0);
		      _delay_ms(10);
	      }
	      
	      //arm moves to initial position
	      for (i=60;i>=0;i--)
	      {
		      servo_2(i);
		      _delay_ms(10);
	      }
      }

	//sets servo free
	servo_1_free();
	servo_2_free();
	  	
	//finds white line 
	find_left(100,100);
	stop();
	
	//follow white line 
	follow_black();
	
	//moves forward by 400 counts 
	forward_by_count(400,100,100);
	
	//turns right 
	turn_right(100,100);
	stop();
    
}