/*
 * Team Id           :   EYRC-415
 * Author List       :   Manoj M ,koustub SH,Sujeeth kumar,Kiran S
 * Filename          :   astar.c
 * Theme             :   Construct-O-Bot         
 * Functions         :   void get_postion(char pos),
                         void cal_herustic(char des),
                         void find_openlist(int ox,int oy),
                         void change_direction (unsigned char desired_direction),
                         void call_astar(char des,char source),
                         void execute_path(char des,char source),
                         void guide_pick(int ware_house),
                         void guide_place(int house, int mat)
 * Global Variables  :	 char arena[9][5],
                         int herustic[9][5],
                         int open_list[4],
                         int cordinates[2],
                         int i,j,
                         char current_direction,
                         int floor_array[5],
                         int material[10],
                         char present,
                         int x_cor[10],
                         int y_cor[10],
                         int m
                          
 
 *FUNCTIONALITY     : MODIFIED VERSION OF ASTAR ALGORITHM IS USED TO FIND SHORTEST DISTANCE ,BASED ON REQURIMENT OF HOUSES CM ARE PICKED .
 *HEADER FOLDER     : built_fun.h
*/




/*Includes header file*/
#include "built_fun.h"

/*Function declarations */
void get_postion(char pos);
void cal_herustic(char des);
void find_openlist(int ox,int oy);
void change_direction (unsigned char desired_direction);
void call_astar(char des,char source);
void execute_path(char des,char source);
void guide_pick(int ware_house);
void guide_place(int house, int mat);




/*Global variables declarations */

/* There are 16 nodes in arena ,we have created a 9*5 matrix to store those nodes .
   --> here char '0' is gaurd varibles required to calculate open_list,without it leads to garbage values.
   --> char 'n' indicates no connection its herustic value is set to high value
   --> char '1','2','3','4','5' is the house 
   --> char 'w' is wall ,char 'z'is zig_zag line 
   --> char 'b' is bricks cm
       char 'c' is cement cm
	   char 'e' is electrical cm
	   char 'p' is paint cm
	   char 's' is sand cm
	   char 'g' is gravel cm
  -->  placements of this char is key to get index vales inorder to calulate distance .	    
*/
char arena[9][5]={{'0','0','0','0','0'},
                  {'0','q','5','r','0'},
                  {'0','e','n','p','0'},
                  {'0','3','z','4','0'},
                  {'0','c','n','s','0'},
                  {'0','1','w','2','0'},
                  {'0','b','n','g','0'},
                  {'0','l','i','m','0'},
                  {'0','0','0','0','0'},
                  };
				  
int herustic[9][5];                  //this array stores distance from destination to each node  
int open_list[4];                    //this array store the distance of adjacent cell
int cordinates[2];                   //this array store the index vales (x,y)
int i,j;                             //iteration variables 
char current_direction='W';          //stores the current direction of bot initially set to
char present ='i';                   //stores the present position of the bot 
int x_cor[10];                       //array to store x vertex
int y_cor[10];                       //array to store y vertex
int m=0;                             //to store index value of x_cor[] & y_cor[] array

/* Input variables */
int floor_array[5]={1,0,0,1,0};              //array to store level of house 1 for high rise ,0 for low rise.      
int material[10] ={3,2,4,0,7,0,8,0,1,0};     //array to store material required ,index  0&1 are for house and so on,number indicates the warehouse number.




/*
*Function Name: void get_postion (char pos)
*Input        : char pos 
*Output       : void
*Logic        : searches for the pos in the arena array ,when found stores its index values in cordinates[] array
*Example call : get_postion('i');
*/

void get_postion (char pos)
{
	//starts iterations 
	for(i=0;i<9;i++)
	{
		for(j=0;j<5;j++)
		{   
			//if match is found
			if(pos==arena[i][j])
			{   
				//stores index values
				cordinates[0]=i;
				cordinates[1]=j;
				//terminates
				break;
			}
		}
	}
}


/*
*Function Name: void cal_herustic(char des)
*Input        : char des 
*Output       : void
*Logic        : searches for the destination index value by calling function get_postion(des),stores the value in x&y.
                inside the loop Manhattan distance between every node to goal node is found and stored in array herustic[][]
				index (1,2),(2,2),(4,2) have no connection hence are set to high value 1000.
				house no 5 is alway set to high value in order to avoid following white line.
*Example call : get_postion('g'); 
                 for the above goal node herustic values are
				 
			      9       8       7       6       7
				  8       7       1000    5       6
				  7       6       1000    4       5
				  6       5       4       3       4
				  5       4       1000    2       3
				  4       3       2       1       2
				  3       2       1000    0       1
				  4       3       2       1       2
				  5       4       3       2       3
				  

                   
*/


void cal_herustic(char des)
 {
	  int x,y;                     //stores index
	  get_postion(des);            //function call of get_postion(),to get index of goal node
	  x=cordinates[0];             //stores x index 
	  y=cordinates[1];             //stores y index
        
	  //starts iterations 	
	  for(i=0;i<9;i++)
	   {
		 for(j=0;j<5;j++)
		  {
			  //sets values of (1,2),(2,2),(4,2),(6,2) to high vales 
			 if((i==1&&j==2)||(i==2&&j==2)||(i==4&&j==2)||(i==6&&j==2))
			  {
			      herustic[i][j]=1000;
			  }
			  //gets Manhattan distance of every node
			  else
			  {
			      herustic[i][j]=abs(x-i)+abs(y-j);
			  }
 		  }
	   }
 }


/*
*Function Name: find_openlist(int ox,int oy);
*Input        : int ox,int oy 
*Output       : void
*Logic        : gets the index value as input (ox,oy),finds out the herustic values of adjacent cell which is stored in array open_list
                open_list[0]  ---->west cell
				open_list[1]  ---->east cell
				open_list[2]  ---->north cell
				open_list[3]  ---->south cell
				                                  north  
										           ^
										           |
										  west<--value--> east
										           |
										          south
*Example call : find_openlist(7,2); 
                values of it in above herustic array is 3,1,1000,3 
*/

void find_openlist(int ox,int oy)
 {
	  //this function execute only if next nearest node to goal is persent hence the parmeters are the present nearest ones 
	              
      x_cor[m]=ox;      //stores cordinates of next nodes
      y_cor[m]=oy;
      m++;              //increments index
      
	  //stores open_list values
      open_list[0] = herustic[ox][oy-1];       //west
	  open_list[1] = herustic[ox][oy+1];       //east
	  open_list[2] = herustic[ox-1][oy];       //north
	  open_list[3] = herustic[ox+1][oy];       //south
	
 }

/*
*Function Name: void change_direction (unsigned char desired_direction)
*Input        : unsigned char desired_direction
*Output       : void
*Logic        : takes desired direction as input ,check the current direction then turn accordingly 
                   current direction       desired direction         motion 
				        north                  north                  terminates
						north                  west                    left 
						north                  east                    right 
						north                  south                   double turn 
						
						south                  north                  double turn 
						south                  west                    left 
						south                  east                    right 
						south                  south                   terminates 
						
						east                   north                   left 
						east                   west                    double turn 
						east                   east                    terminates 
						east                   south                   right
						
						west                   north                  right 
						west                   west                   terminates 
						west                   east                   double turn 
						west                   south                  left 
						
					this function is called at every node .	        
*Example call : change_direction ('N'); changes direction to north 
*/


void change_direction (unsigned char desired_direction)
{
	
	   //current direction is same as desired direction then gets terminates  
    	if (current_direction == desired_direction)
	    {
		   return 0;
     	}
	   
	   /*if current direction is north*/
	    
	   if (current_direction == 'N' && desired_direction == 'W')
	   {  
		  turn_left(100,100);
		  current_direction = 'W';
	   }
	   else if (current_direction == 'N' && desired_direction == 'E')
	   {  
		 turn_right(100,100);
		 current_direction = 'E';
	   }
	   else if (current_direction == 'N' && desired_direction == 'S')
	   {  
		 turn_right(100,100);
		 turn_right(100,100);
		current_direction = 'S';
	   }
	   /*if current direction is south*/
	   else if (current_direction == 'S' && desired_direction == 'N')
	   {		
		turn_right(100,100);
		turn_right(100,100);
		current_direction = 'N';
	   }
	   else if (current_direction == 'S' && desired_direction == 'E')
	   {
		turn_left(100,100);
		current_direction = 'E';
	   }
	   else if (current_direction == 'S' && desired_direction == 'W')
	   {
		turn_right(100,100);
		current_direction = 'W';
	   }
	   
	   /*if current direction is east */
	   else if (current_direction == 'E' && desired_direction == 'N')
	   {
		turn_left(100,100);
		current_direction = 'N';
	   }
    	else if (current_direction == 'E' && desired_direction == 'W')
	   {
		turn_right(100,100);
		turn_right(100,100);
		current_direction = 'W';
	   }
	   else if (current_direction == 'E' && desired_direction == 'S')
	   { 
		turn_right(100,100);
		current_direction = 'S';
	   }
	   
	   /*if current direction is west*/
	   else if (current_direction == 'W' && desired_direction == 'N')
	   { 
		turn_right(100,100);
		current_direction = 'N';
	   }
	  else if (current_direction == 'W' && desired_direction == 'E')
	  { 
		turn_right(100,100);
		turn_right(100,100);
		current_direction = 'E';
	  }
	  else if (current_direction == 'W' && desired_direction == 'S')
	  { 
		turn_left(100,100);
		current_direction = 'S';
	  }
	 
}



/*
*Function Name: void call_astar(char des,char source)
*Input        : char des ,char source 
*Output       : void
*Logic        : this function takes destination node and source node as input and stores the vertex to be traveled in array 
                 logic is herustic is found for the destination node , then starting from source node open_list is found out 
				 minimum value in open_list is the next node to be traveled , vertex of source are changed accordingly.
				 This is repeated until the herustic of source and node are equal 
				                                          (x-1,y)
				                                            |
                                                            |
											  (x,y-1)<----(x,y)---->(x,y+1)
											                |
															|
														  (x+1,y)
														  
				 this method works for left to right approach ,solution to this problem is given in next function   										   				 
*Example call : call_astar('b','i')
*/


void call_astar(char des,char source)
{   
	  /*
	    sx and sy stores vertex of source node 
	    dx and dy stores vertex of destination node 
	    smin stores minimum value in open_list 
	    element stores index of minimum value  
	   */
    	int sx, sy, dx,dy,smin, element = 0;  
	
	
	     cal_herustic(des);      //herustic array of destination node is defined 
	     
		 //source index are taken
		 get_postion(source);
	     sx = cordinates[0];
	     sy = cordinates[1];
		 
		 //destination index are taken 
       	 get_postion(des);
	     dx=cordinates[0];
	     dy=cordinates[1];

           //repeats until the herustic of source and destination are same 
	
	    while (herustic[sx][sy]!= herustic[dx][dy])
	     {
                //find out the open_list 
        		find_openlist(sx, sy);
				
				//to find minimum value smin is initialized to 1st element
	        	smin = open_list[0];
				//finds out the minimum value
		        for (i = 0; i < 4; i++)
		        {
                      
		     	    if (open_list[i]<smin )
        			{ 
						    smin = open_list[i];
				            element = i;
			        }
	            }
                //by the end as a index value of minimum herustic 
				
				//following codes to reduce the error between source and node 
		        
				//if element equal to zero then next nearest node is west node  
				if(element==0)
		        {
                      //west cell has same x coordinate ,y coordinate reduces by 1 
			           sx=sx;
					   
					  //if x coordinate is 5 or 3 then wall and zig_zag are present each two node are present as per the arena array hence one node is bypassed
			         if(sx==5||sx==3)
			          {
				          sy=sy-2;
			          }
					 //y value is reduce by 1
			         else
					 {
				       sy=sy-1;
			         }
		        }
				
			//if element equal to zero then next nearest node is east node  	
		       if(element==1)
		       {
				     //east cell has same x coordinate ,y coordinate added by 1
			          sx=sx;
					 //if x coordinate is 5 or 3 then wall and zig_zag are present each two node are present as per the arena array hence one node is bypassed 
			        if(sx==5||sx==3)
			         {
				        sy=sy+2;
			         }
					 
					 //y value gets added by 1
			        else
					{
				        sy=sy+1;
			        }
		        }
				
			 //if element equal to zero then next nearest node is north node  	
		      if(element==2)
		       {
				   //north cell has same y coordinate ,x coordinate reduces by 1
			       sx=sx-1;
			       sy=sy;
		       }
			   
			  //if element equal to zero then next nearest node is south node  	
		      if(element==3)
		       {
				   //south cell has same y coordinate ,x coordinate added by 1
			      sx=sx+1;
			       sy=sy;
		       }


	      }
	
	    //the final vertex to be traveled 
	     x_cor[m]=sx;
	     y_cor[m]=sy;

}

/*
*Function Name: void execute_path(char des,char source)
*Input        : char des,char source
*Output       : void
*Logic        : This function takes source and node as input ,calls the Astar function to get nearest paths .make the bot to follow that path.
                 It is also the solution to left to right approach problem ,
				 initially source is checked if it is 'r','p','4','s','2','g' then source and destination are interchanged for the same Astar function  is called
				 we have the coordinates now which is been followed in reverse order, else it will be followed in correct order .
				 For following the coordinates ,present and next coordinates are checked comparing it change_direction function is called ,and a node() is executed 
				     
*Example call : execute_path('g','i');
*/


void execute_path(char des,char source)
{
      //iteration variable 
      int n=0;
      
	  //check right to left approach 
	  if(source =='g'||source=='s'||source=='p'||source=='r'||source=='4'||source=='2')
       {     
		    //source and destination are interchanged
            call_astar(source,des);
            
		   //cordinates are executed in reverse order 
           for(n=m-1;n>=0;n--)
           {
                // if x=x+1 and y>y+1 east direction   
              if(x_cor[n]==x_cor[n+1]&&y_cor[n]>y_cor[n+1])
               {
                  change_direction('E');
                   node();
               }
			   // if x=x+1 and y<y+1 west direction 
              else if (x_cor[n]==x_cor[n+1]&&y_cor[n]<y_cor[n+1])
              {
                  change_direction('W');
                  node();  
			  }
			   //if x<x+1 and y=y+1 north direction 
              else if (x_cor[n]<x_cor[n+1]&&y_cor[n]==y_cor[n+1])
              {
                 change_direction('N');
                  node();
              }
			  //if x>x+1 and y=y+1 south direction 
             else if(x_cor[n]>x_cor[n+1]&&y_cor[n]==y_cor[n+1])
             {
               change_direction('S');
                node();
             }
       
          }

      }
	  //if left to right approach 
     else
      {
         //calls astar 
         call_astar(des,source);
          
		  //executes in correct order
	       for(n=0;n<m;n++)
           {
			   //x=x+1 and y<y+1 east direction 
              if(x_cor[n]==x_cor[n+1]&&y_cor[n]<y_cor[n+1])
               {
                 change_direction('E');
                   node();
               }
			   //x=x+1 and y>y+1 west direction
              else if (x_cor[n]==x_cor[n+1]&&y_cor[n]>y_cor[n+1])
              {
               change_direction('W');
               node();
			  }
			  //x>x+1 and y=y+1 north direction
             else if (x_cor[n]>x_cor[n+1]&&y_cor[n]==y_cor[n+1])
             {
              change_direction('N');
               node();
             }
			 //x<x+1 and y=y+1 south direction
             else if(x_cor[n]<x_cor[n+1]&&y_cor[n]==y_cor[n+1])
             {
             change_direction('S');
              node();
		     }
          }
       }
	 //sets index vales to zero 
	 m=0;	 
}


/*
*Function Name: guide_pick(int ware_house)
*Input        : int ware_house
*Output       : void
*Logic        : takes input from the material[] array,
                    material        warehouse            source node      
					 brick             1 or 2                 b
					 gravel            3 or 4                 g
					 cement            5 or 6                 c 
					 sand              7 or 8                 s 
					 electrical        9 or 10                e
					 paint             11 or 12               p 
				robot moves to corresponding warehouse,then depending on the current direction does right_pick(),left_pick()
				 sets its current present source to warehouse node 					  
*Example call : guide_pick(material[5]);
*/


void guide_pick(int ware_house)
{
    //executes the cases depending on warehouse  
	switch (ware_house)
	{
              //for warehouse 1
	   case 1: execute_path('b',present);
	           //depending on the current direction picking option are chosen 
	           if(current_direction=='N')
			   {
				   left_pick();
			   }
			   else if (current_direction=='S')
			   {
				   right_pick();
			   }
			   //sets source node 
			   present='b';
	           break;
			   //for warehouse 2
	   case 2: execute_path('b',present);
	           //depending on the current direction picking option are chosen
	           if(current_direction=='N')
			   {
				   right_pick();
			   }
			   else if (current_direction=='S')
			   {
				   left_pick();
			   }
			   //sets source node
			   present='b';
	           break;
			   //for warehouse 3
        case 3: execute_path('g',present);
		      //depending on the current direction picking option are chosen
              if(current_direction=='N')
              {
	              left_pick();
              }
              else if (current_direction=='S')
              {
	              right_pick();
              }
			  //sets source node
              present='g';
              break;
			  //for warehouse 4
		case 4: execute_path('g',present);
		       //depending on the current direction picking option are chosen
		       if(current_direction=='N')
		       {
			       right_pick();
		       }
		       else if (current_direction=='S')
		       {
			       left_pick();
		       }
			   //sets source node
		       present='g';
		       break;
			   //for warehouse 5
		case 5: execute_path('c',present);
		       //depending on the current direction picking option are chosen
		       if(current_direction=='N')
		       {
			       left_pick();
		       }
		       else if (current_direction=='S')
		       {
			       right_pick();
		       }
			   //sets source node
		       present='c';
		       break;
			   //for warehouse 6
		case 6 :execute_path('c',present);
		        //depending on the current direction picking option are chosen
		        if(current_direction=='N')
		        {
			        right_pick();
		        }
		        else if (current_direction=='S')
		        {
			        left_pick();
		        }
				//sets source node
		        present='c';
		        break;
				//for warehouse 7
		case 7:	 execute_path('s',present);
		         //depending on the current direction picking option are chosen
			     if(current_direction=='N')
			     {
				     left_pick();
			     }
			     else if (current_direction=='S')
			     {
				     right_pick();
			     }
				 //sets source node
			     present='s';
			     break;
				 //for warehouse 8
		case 8: execute_path('s',present);
		        //depending on the current direction picking option are chosen
		        if(current_direction=='N')
		        {
			        right_pick();
		        }
		        else if (current_direction=='S')
		        {
			        left_pick();
		        }
				//sets source node
		        present='s';
		        break;
				//for warehouse 9
		case 9:execute_path('e',present);
		        //depending on the current direction picking option are chosen
				if(current_direction=='N')
		        {
			        left_pick();
		        }
		        else if (current_direction=='S')
		        {
			        right_pick();
		        }
				//sets source node
		        present='e';
		        break;
				//for warehouse 10
		case 10:execute_path('e',present);
		        //depending on the current direction picking option are chosen
                if(current_direction=='N')
                {
	                right_pick();
                }
                else if (current_direction=='S')
                {
	                left_pick();
                }
				//sets source node
                present='e';
                break;
				//for warehouse 11
		case 11:execute_path('p',present);
		         //depending on the current direction picking option are chosen
		         if(current_direction=='N')
		         {
			         left_pick();
		         }
		         else if (current_direction=='S')
		         {
			         right_pick();
		         }
				 //sets source node
		         present='p';
		         break;
				 //for warehouse 12
		case 12:execute_path('p',present);
		        //depending on the current direction picking option are chosen
		        if(current_direction=='N')
		        {
			        right_pick();
		        }
		        else if (current_direction=='S')
		        {
			        left_pick();
		        }
				//sets source node
		        present='p';
		        break;
				//default cases breaks 
		  default: break;

	}
}

/*
*Function Name: void guide_place(int house, int mat)
*Input        : int house, int mat
*Output       : void
*Logic        : takes inputs as house number then moves to corresponding house ,if material is zero then terminates
                depending the current direction does either left_place ,right_place or straight_place
				 house 5 is not included here   
*Example call : guide_place(1,material[0]);
*/

void guide_place(int house, int mat)
{
	//if material is zero terminates 
    if(mat==0)
    {
        return 0;
    }
	
	//executes the cases depending on warehouse  
	switch(house)
	{
           //for house 1 
		case 1: execute_path('1',present);
		         //depending on the current direction placing option are chosen
		        if (current_direction=='N')
		        {
					left_place(floor_array[0]);
		        }
				else if (current_direction=='S')
				{
					right_place(floor_array[0]);
				}
				else if (current_direction=='W')
				{
					staright_place(floor_array[0]);
				}
				//sets source node
				present='1';
				break;
	       //for house 2
	   case 2: execute_path('2',present);
	           //depending on the current direction placing option are chosen
			   if (current_direction=='N')
	           {
		           right_place(floor_array[1]);
	           }
	           else if (current_direction=='S')
	           {
		           left_place(floor_array[1]);
	           }
	           else if (current_direction=='E')
	           {
		           staright_place(floor_array[1]);
	           }
			   //sets source node
	           present='2';
			   break;
			   //for house 3 
		case 3: execute_path('3',present);
		       //depending on the current direction placing option are chosen
			   if (current_direction=='N')
		       {
			       left_place(floor_array[2]);
		       }
		       else if (current_direction=='S')
		       {
			       right_place(floor_array[2]);
		       }
		       else if (current_direction=='W')
		       {
			       staright_place(floor_array[2]);
		       }
			   //sets source node
		       present='3';
		       break;
			   //for house 4
        case 4: execute_path('4',present);
		         //depending on the current direction placing option are chosen
		        if (current_direction=='N')
		        {
			        right_place(floor_array[3]);
		        }
		        else if (current_direction=='S')
		        {
			        left_place(floor_array[3]);
		        }
		        else if (current_direction=='E')
		        {
			        staright_place(floor_array[3]);
		        }
				//sets source node
		        present='4';
		        break;
		    //default case 
			default: break;
	   }
}
int main()
{
     //initiating the devices 
	init_devices();
	lcd_set_4bit();
	lcd_init();
    
	//default moves from start to node 'i'
	node();
	//moves to initial direction 
	turn_right(100,100); 
	
	//executes for house 5
	//checks for requirement of house 5 ,moves to node r
	 if (material[8]!=0)
	 {
	 guide_pick(material[8]);
	 execute_path('r',present);
	 place_h5(floor_array[4]);
	 present='r';
	 current_direction='S';
	 }
	 
	 if (material[9]!=0)
	 {
	 guide_pick(material[9]);
	 execute_path('r',present);
	 place_h5(floor_array[4]);
	 present='r';
	 current_direction='S';
	 }
	
	//executes for house 1
    guide_pick(material[0]);
	guide_place(1,material[0]);
	guide_pick(material[1]);
	guide_place(1,material[1]);
	
	//executes for house 2
    guide_pick(material[2]);
	guide_place(2,material[2]);
	guide_pick(material[3]);
	guide_place(2,material[3]);
	
	//executes for house 3
	guide_pick(material[4]);
	guide_place(3,material[4]);
	guide_pick(material[5]);
	guide_place(3,material[5]);
	
	//executes for house 4
	guide_pick(material[6]);
	guide_place(4,material[6]);
	guide_pick(material[7]);
	guide_place(4,material[7]);

     //turns on buzzer for 5 sec 
     buzzer_on();
     buzzer_off();
}