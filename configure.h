/*
 * Team Id          :    EYRC-415
 * Author List      :    Manoj M ,koustub SH,Sujeeth kumar,Kiran S
 * Filename         :    configure.h
 * Theme            :    Construct-O-Bot  
 * Functions        :    void lcd_port_config (void);
                         void adc_pin_config (void);
                         void motion_pin_config (void);
                         void left_encoder_pin_config (void);
                         void right_encoder_pin_config (void);
                         void servo1_pin_config (void);
                         void servo2_pin_config (void);
                         void servo3_pin_config (void);
                         void port_init(void);
                         void left_position_encoder_interrupt_init (void);
                         void right_position_encoder_interrupt_init (void);
                         void timer5_init();
                         void adc_init();
                         unsigned char ADC_Conversion(unsigned char Ch);
                         void print_sensor(char row, char coloumn,unsigned char channel);
                         void velocity (unsigned char left_motor, unsigned char right_motor);
                         void timer1_init(void);

 *Global Variables:      unsigned long int ShaftCountLeft ,
                         unsigned long int ShaftCountRight ,
                         unsigned char ADC_Value,
                         unsigned char flag ,
                         unsigned char Center_white_line ,
                         unsigned char Right_white_line ,
                         unsigned char sharp_left,sharp_right, distance, adc_reading,
                         unsigned int value_left,value_right,
                         unsigned char thershold, 
					   
 *FUNCTIONALITY   : HEADER FILE TO INITIALIZE PORTS ,ADC_CONVERSATION AND PWM .
 *HEADER FOLDER   : avr/io.h,avr/interrupt.h,util/delay.h,math.h,lcd.c.
*************************************************************************************
****PORT**********CONNECTION*********
  1)PORTC          LCD
  2)PORTA          MOTION DIRECTION
  3)PORTL          MOTION VELOCITY
  4)PORTD          LEFT ENCODER 
  5)PORTE          RIGHT ENCODER
  6)PORTB          SERVO PWM
  7)PORTJ           BUZZER 

*/







//setting the clock frequency
#define F_CPU 14745600  
  
  
//including header files  
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h> 
#include "lcd.c"

//global variables declarations 

unsigned long int ShaftCountLeft = 0;      //counts no. of rotations     
unsigned long int ShaftCountRight = 0;    
unsigned char ADC_Value;                   //ADC declarations 
unsigned char flag = 0;
unsigned char Left_white_line = 0;         //line sensor declarations
unsigned char Center_white_line = 0;
unsigned char Right_white_line = 0;
unsigned char sharp_left,sharp_right, distance, adc_reading;   //sharp sensor vales 
unsigned int value_left,value_right;

unsigned char thershold=  0x64; //0x78;// 0x8C ;  //0x50; //                  //thershold vales of line sensor (80)


//Functions declarations 

void lcd_port_config (void); 
void adc_pin_config (void);
void motion_pin_config (void);
void left_encoder_pin_config (void);
void right_encoder_pin_config (void);
void servo1_pin_config (void);
void servo2_pin_config (void);
void servo3_pin_config (void);
void port_init(void);
void left_position_encoder_interrupt_init (void);
void right_position_encoder_interrupt_init (void);
void timer5_init();
void adc_init();
unsigned char ADC_Conversion(unsigned char Ch);
void print_sensor(char row, char coloumn,unsigned char channel);
void velocity (unsigned char left_motor, unsigned char right_motor);
void timer1_init(void);


/*
*Function Name: void lcd_port_config (void)
*Input        : void
*Output       : void
*Logic        : LCD pin configuration setting
*Example call : void lcd_port_config ();
*/

void lcd_port_config (void)
{
DDRC = DDRC | 0xF7; //all the LCD pin's direction set as output
PORTC = PORTC & 0x80; // all the LCD pins are set to logic 0 except PORTC 7
}

/*
*Function Name: void motion_pin_config (void)
*Input        : void
*Output       : void
*Logic        : Motion pin configuration setting
*Example call : void motion_pin_config ();
*/

 
void motion_pin_config (void)
{
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM.
}

/*
*Function Name: left_encoder_pin_config (void)
*Input        : void
*Output       : void
*Logic        : Left encoder pin configuration setting
*Example call : left_encoder_pin_config ();
*/
  
void left_encoder_pin_config (void)
{
	DDRD  = 0x0C;  //Set the direction of the PORTE 4 pin as input
	PORTD = 0x0C; //Enable internal pull-up for PORTE 4 pin
}

/*
*Function Name: right_encoder_pin_config (void)
*Input        : void
*Output       : void
*Logic        : right encoder pin configuration setting
*Example call : right_encoder_pin_config ();
*/

void right_encoder_pin_config (void)
{
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 4 pin
}

/*
*Function Name: adc_pin_config (void)
*Input        : void
*Output       : void
*Logic        : ADC pin configuration setting 
*Example call : adc_pin_config ();
*/

void adc_pin_config (void)
{
DDRF = 0x00;              //setting PORTF and PORTK as input pins 
PORTF = 0x00;             
DDRK = 0x00;
PORTK = 0x00;
}

/*
*Function Name: void servo1_pin_config (void)
*Input        : void
*Output       : void
*Logic        : Servo1 pin configuration setting 
*Example call : servo1_pin_config ();
*/

void servo1_pin_config (void)
{
	DDRB  = DDRB | 0x20;  //making PORTB 5 pin output
	PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
}

/*
*Function Name: void servo1_pin_config (void)
*Input        : void
*Output       : void
*Logic        : Servo2 pin configuration setting
*Example call : servo2_pin_config ();
*/
 
void servo2_pin_config (void)
{
	DDRB  = DDRB | 0x40;  //making PORTB 6 pin output
	PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
}

/*
*Function Name: void servo1_pin_config (void)
*Input        : void
*Output       : void
*Logic        : Servo3 pin configuration setting
*Example call : servo3_pin_config ();
*/

void servo3_pin_config (void)
{
	DDRB  = DDRB | 0x80;  //making PORTB 7 pin output
	PORTB = PORTB | 0x80; //setting PORTB 7 pin to logic 1
}

/*
*Function Name: void buzzer_pin_config (void)
*Input        : void
*Output       : void
*Logic        : buzzer pin configuration 
*Example call : buzzer_pin_config ();
*/

void buzzer_pin_config (void)
{
	DDRJ = DDRJ | 0x08;		//Setting PORTJ 3 as output
	PORTJ = PORTJ & 0xF7;		//Setting PORTJ 3 logic low to turnoff buzzer
}

/*
*Function Name: void port_init(void)
*Input        : void
*Output       : void
*Logic        : Function to Initialize PORTS
*Example call : port_init();
*/

void port_init(void)
{
lcd_port_config();             //LCD pins config

adc_pin_config();              //ADC pins config

motion_pin_config();           //motion pins config

left_encoder_pin_config();     //left encoder pin config
right_encoder_pin_config();    //right encoder pin config

servo1_pin_config();           //Configure PORTB 5 pin for servo motor 1 operation
servo2_pin_config();           //Configure PORTB 6 pin for servo motor 2 operation
servo3_pin_config();           //Configure PORTB 7 pin for servo motor 3 operation

buzzer_pin_config();           //configure PORTJ 3 pin for buzzer  
}

/*
*Function Name: void left_position_encoder_interrupt_init (void) 
*Input        : void
*Output       : void
*Logic        : Function to enable Interrupt 4
*Example call : left_position_encoder_interrupt_init (); 
*/
 
void left_position_encoder_interrupt_init (void) 
{
	cli();                   //Clears the global interrupt
	EICRB = EICRB | 0x02;    // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10;    // Enable Interrupt INT4 for left position encoder
	sei();                   // Enables the global interrupt
}

/*
*Function Name: void right_position_encoder_interrupt_init (void)
*Input        : void
*Output       : void
*Logic        : Function to enable Interrupt 5
*Example call : right_position_encoder_interrupt_init ();
*/

void right_position_encoder_interrupt_init (void) 
{
	cli();                      //Clears the global interrupt
	EICRB = EICRB | 0x08;       // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20;       // Enable Interrupt INT5 for right position encoder
	sei();                      // Enables the global interrupt
}

/*
*Function Name: ISR(INT5_vect)
*Input        : void
*Output       : void
*Logic        : ISR for right position encoder
*Example call : ISR(INT5_vect)
*/

ISR(INT5_vect)
{
	ShaftCountRight++;  //increment right shaft position count
}

/*
*Function Name: ISR(INT4_vect)
*Input        : void
*Output       : void
*Logic        : ISR for right position encoder
*Example call : ISR(INT4_vect)
*/

ISR(INT4_vect)
{
	ShaftCountLeft++;  //increment left shaft position count
}


/*
*Function Name: void timer5_init()
*Input        : void
*Output       : void
*Logic        : Function to initialize timer5 for Velocity control
                Timer 5 initialized in PWM mode for velocity control
                Per-scale:256
                PWM 8bit fast,  TOP=0x00FF
                Timer Frequency:225.000Hz
*Example call : timer5_init();
*/

void timer5_init()
{
TCCR5B = 0x00; //Stop
TCNT5H = 0xFF; //Counter higher 8-bit value to which OCR5xH value is compared with
TCNT5L = 0x01; //Counter lower 8-bit value to which OCR5xH value is compared with
OCR5AH = 0x00; //Output compare register high value for Left Motor
OCR5AL = 0xFF; //Output compare register low value for Left Motor
OCR5BH = 0x00; //Output compare register high value for Right Motor
OCR5BL = 0xFF; //Output compare register low value for Right Motor
OCR5CH = 0x00; //Output compare register high value for Motor C1
OCR5CL = 0xFF; //Output compare register low value for Motor C1
TCCR5A = 0xA9; /*{COM5A1=1, COM5A0=0; COM5B1=1, COM5B0=0; COM5C1=1 COM5C0=0}
  For Overriding normal port functionality to OCRnA outputs.
    {WGM51=0, WGM50=1} Along With WGM52 in TCCR5B for Selecting FAST PWM 8-bit Mode*/

TCCR5B = 0x0B; //WGM12=1; CS12=0, CS11=1, CS10=1 (Prescaler=64)
}



/*
*Function Name: void velocity (unsigned char left_motor, unsigned char right_motor)
*Input        : void
*Output       : unsigned char left_motor, unsigned char right_motor
*Logic        : Function for velocity control
*Example call : velocity (unsigned char left_motor, unsigned char right_motor);
*/

void velocity (unsigned char left_motor, unsigned char right_motor)
{
OCR5AL = (unsigned char)left_motor;  //sets velocity of both motors
OCR5BL = (unsigned char)right_motor;
}

/*
*Function Name: void forward (void)
*Input        : void
*Output       : void
*Logic        : Function to set forward motion
*Example call : void forward (void)
*/

void forward (void) 
{
  PORTA=0x06;
}

/*
*Function Name: void stop (void)
*Input        : void
*Output       : void
*Logic        : Function to set stop motion
*Example call : void stop (void)
*/

void stop (void)
{
  PORTA =0x00;
}

/*
*Function Name: void right (void)
*Input        : void
*Output       : void
*Logic        : Function to set right motion
*Example call : void right (void)
*/

void right(void)
{
	PORTA=0x05;
}

/*
*Function Name: void left(void)
*Input        : void
*Output       : void
*Logic        : Function to set left motion
*Example call : void left(void)
*/

void left(void)
{
	PORTA=0x0A;
}


/*
*Function Name: void backward(void)
*Input        : void
*Output       : void
*Logic        : Function to set backward motion
*Example call : void backward(void)
*/

void backward(void)
{
	PORTA=0x09;
}

/*
*Function Name: void timer1_init(void)
*Input        : void
*Output       : void
*Logic        : Function to initialize Timer1 for servo control
                TIMER1 initialization in 10 bit fast PWM mode
                pre-scale:256
                WGM: 7) PWM 10bit fast, TOP=0x03FF
                actual value: 52.25Hz
*Example call : void timer1_init(void)
*/

void timer1_init(void)
{
TCCR1B = 0x00; //stop
TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
TCNT1L = 0x01; //Counter low value to which OCR1xH value is to be compared with
OCR1AH = 0x03; //Output compare Register high value for servo 1
OCR1AL = 0xFF; //Output Compare Register low Value For servo 1
OCR1BH = 0x03; //Output compare Register high value for servo 2
OCR1BL = 0xFF; //Output Compare Register low Value For servo 2
OCR1CH = 0x03; //Output compare Register high value for servo 3
OCR1CL = 0xFF; //Output Compare Register low Value For servo 3
ICR1H  = 0x03; 
ICR1L  = 0xFF;
TCCR1A = 0xAB; /*{COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0}
For Overriding normal port functionality to OCRnA outputs.
  {WGM11=1, WGM10=1} Along With WGM12 in TCCR1B for Selecting FAST PWM Mode*/
TCCR1C = 0x00;
TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}

/*
*Function Name: void servo_1(unsigned char degrees)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to rotate Servo 1 by a specified angle in the multiples of 1.86 degrees
*Example call : servo_1(90);
*/

void servo_1(unsigned char degrees)  
{
float PositionPanServo = 0;
  PositionPanServo = ((float)degrees / 1.86) + 35.0;
OCR1AH = 0x00;
OCR1AL = (unsigned char) PositionPanServo;
}


/*
*Function Name: void servo_2(unsigned char degrees)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to rotate Servo 2 by a specified angle in the multiples of 1.86 degrees
*Example call : servo_2(90);
*/

void servo_2(unsigned char degrees)
{
float PositionTiltServo = 0;
PositionTiltServo = ((float)degrees / 1.86) + 35.0;
OCR1BH = 0x00;
OCR1BL = (unsigned char) PositionTiltServo;
}

/*
*Function Name: void servo_3(unsigned char degrees)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to rotate Servo 3 by a specified angle in the multiples of 1.86 degrees
*Example call : servo_3(90);
*/

void servo_3(unsigned char degrees)
{
float PositionServo = 0;
PositionServo = ((float)degrees / 1.86) + 35.0;
OCR1CH = 0x00;
OCR1CL = (unsigned char) PositionServo;
}

/*
*Function Name: void servo_1_free (void)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to make servo 1 rotate freely
*Example call : servo_1_free ();
*/

void servo_1_free (void) 
{
OCR1AH = 0x03; 
OCR1AL = 0xFF; //Servo 1 off
}

/*
*Function Name: void servo_2_free (void)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to make servo 2 rotate freely
*Example call : servo_2_free ();
*/

void servo_2_free (void) 
{
OCR1BH = 0x03;
OCR1BL = 0xFF; //Servo 2 off
}

/*
*Function Name: void servo_3_free (void)
*Input        : unsigned char degrees
*Output       : void
*Logic        : Function to make servo 3 rotate freely
*Example call : servo_3_free ();
*/

void servo_3_free (void) 
{
OCR1CH = 0x03;
OCR1CL = 0xFF; //Servo 3 off
} 

/*
*Function Name: void adc_init()
*Input        : void 
*Output       : void
*Logic        : ADC port initialization
*Example call : adc_init();
*/
 
void adc_init()
{
	ADCSRA = 0x00;
	ADCSRB = 0x00;     //MUX5 = 0
	ADMUX = 0x20;      //Vref=5V external --- ADLAR=1 --- MUX4:0 = 0000
	ACSR = 0x80;
	ADCSRA = 0x86;     //ADEN=1 --- ADIE=1 --- ADPS2:0 = 1 1 0
}

/*
*Function Name:unsigned char ADC_Conversion(unsigned char Ch)
*Input        : unsigned char Ch
*Output       : unsigned char Ch
*Logic        : Function for Analog to digital conversion
*Example call : ADC_Conversion(1);
*/

unsigned char ADC_Conversion(unsigned char Ch)
{
	unsigned char a;
	if(Ch>7)
	{
		ADCSRB = 0x08;
	}
	Ch = Ch & 0x07;
	ADMUX= 0x20| Ch;
	ADCSRA = ADCSRA | 0x40;      //Set start conversion bit
	while((ADCSRA&0x10)==0);     //Wait for conversion to complete
	a=ADCH;
	ADCSRA = ADCSRA|0x10;        //clear ADIF (ADC Interrupt Flag) by writing 1 to it
	ADCSRB = 0x00;
	return a;
}

/*
*Function Name: unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
*Input        : unsigned char adc_reading 
*Output       : unsigned int
*Logic        : Function to convert the sharp sensor reading from char to decimal value
*Example call : Sharp_GP2D12_estimation(sharp);
*/

unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}

/*
*Function Name: void print_sensor(char row, char coloumn,unsigned char channel)
*Input        : unsigned char adc_reading
*Output       : unsigned int
*Logic        : Function To Print Sensor Values At Desired Row And Column Location on LCD
*Example call : void print_sensor(1,2,13);
*/

void print_sensor(char row, char coloumn,unsigned char channel)
{

	ADC_Value = ADC_Conversion(channel);
	lcd_print(row, coloumn, ADC_Value, 3);
}

/*
*Function Name: void init_devices (void)
*Input        : unsigned char adc_reading
*Output       : unsigned int
*Logic        : Function to initialize ports and timers
*Example call : init_devices ();
*/

void init_devices (void)
{
	cli(); //Clears the global interrupts
	port_init();
	adc_init();
	timer5_init();
	timer1_init();
    left_position_encoder_interrupt_init();
    right_position_encoder_interrupt_init();
	sei(); //re-enable interrupts
}

