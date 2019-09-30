#include "Robots_Modified.h"
#include "MiniFW_Modified.h"
#include "strutils.h"



void BoulderMovesDirection(Robot& boulder,Robot& Player,Direction dir)	// dont need to write same things so i made a free function that resurrect and stop before a boulder or wall
{
	
				
	boulder.Resurrect();			//main program will call this function after player crashed to a boulder so i resurrect them first
	Player.Resurrect();
	boulder.TurnFace(dir);			//in case of turning the same direction that robot is looking 
	while(!boulder.Blocked())		// it will stop whe it sees a wall or boulder so i dont need to resurrect because it cant hit anything
		{
			boulder.Move();
		}


}


void function1(Robot& r , Color a)
{
	r.SetColor(a);
}


int main()
{
	string bagC,playerXstr,playerYstr,playerXYstr;
	int playerX,playerY;
	int xPos1,xPos2,xPos3,yPos1,yPos2,yPos3;
	Robot Player(0,0);
	function1(Player,yellow);	
	Player.SetBagCount(50);	
	GetInput("Please enterthe X coordinate for Boulder 1",xPos1);									//asking for positions
	GetInput("Please enter the Y coordinate for Boulder 1",yPos1);
	Robot boulder1(xPos1,yPos1);
	GetInput("Please enter the X coordinate for Boulder 2",xPos2);
	GetInput("Please enter theY coordinate for Boulder 2",yPos2);
	Robot boulder2(xPos2,yPos2);
	GetInput("Please enter the X coordinate for Boulder 3",xPos3);
	GetInput("Please enter the Y coordinate for Boulder 3",yPos3);
	Robot boulder3(xPos3,yPos3);	
	
	while( (boulder1.GetXCoordinate()!=10 || boulder1.GetYCoordinate()!=10) && (boulder2.GetXCoordinate()!=10 || boulder2.GetYCoordinate()!=10)&&
		(boulder3.GetXCoordinate()!=10 || boulder3.GetYCoordinate()!=10) && Player.GetBagCount()>0)	//conditions to program keep going

	{

		if(IsPressed(keyUpArrow))																	//if pressed up arrow
		{
			Player.TurnFace(north);																	//turns north by using the member function that we wrote
				if(Player.FacingWall() == false)
					{   
					  if(Player.Blocked() == false)													//if not blocked by boulder it will move and bag-1
						{   
							Player.Move();
							Player.5();	
							Player.PickAllThings();
						}
					  else                                                                          //if blocked by boulder it will just hit by moving
						 {
							  Player.Move();
						 }

					}
		
			
				if(!boulder1.isAlive())						//checking if player hit a boulder and checked for all boulder's  the dead one is the one that player hit
					BoulderMovesDirection(boulder1,Player,north);
				else if(!boulder2.isAlive())
					BoulderMovesDirection(boulder2,Player,north);
				else if(!boulder3.isAlive())
					BoulderMovesDirection(boulder3,Player,north);
		}
		else if(IsPressed(keyRightArrow))															//if pressed right arrow
		{
			Player.TurnFace(east);																	//turns east by using the member function that we wrote
					if(Player.FacingWall() == false)
					{   
					  if(Player.Blocked() == false)
					{   
						Player.Move();
					    Player.ThingCountStep();
						Player.PickAllThings();
					}
					  else
					  {
						  Player.Move();
					  }

					}
				if(!boulder1.isAlive())
					BoulderMovesDirection(boulder1,Player,east);
				else if(!boulder2.isAlive())
					BoulderMovesDirection(boulder2,Player,east);
				else if(!boulder3.isAlive())
					BoulderMovesDirection(boulder3,Player,east);
		}
		else if(IsPressed(keyDownArrow))															//if pressed down arrow
		{
			Player.TurnFace(south);																	//turns south by using the member function that we wrote
			if(Player.FacingWall() == false)
					{   
					  if(Player.Blocked() == false)
					{   
						Player.Move();
					    Player.ThingCountStep();
						Player.PickAllThings();
					}
					  else
					  {
						  Player.Move();
					  }

					}
				if(!boulder1.isAlive())
					BoulderMovesDirection(boulder1,Player,south);
				else if(!boulder2.isAlive())
					BoulderMovesDirection(boulder2,Player,south);
				else if(!boulder3.isAlive())
					BoulderMovesDirection(boulder3,Player,south);
		}
		else if(IsPressed(keyLeftArrow))															//if pressed left arrow
		{
			Player.TurnFace(west);																	//turns west by using the member function that we wrote
					if(Player.FacingWall() == false)
					{   
					  if(Player.Blocked() == false)
					{   
						Player.Move();
					    Player.ThingCountStep();
						Player.PickAllThings();
					}
					  else
					  {
						  Player.Move();
					  }

					}
		
					if(!boulder1.isAlive())
					BoulderMovesDirection(boulder1,Player,west);
				else if(!boulder2.isAlive())
					BoulderMovesDirection(boulder2,Player,west);
				else if(!boulder3.isAlive())
					BoulderMovesDirection(boulder3,Player,west);
		}
		else if(IsPressed(keyHome))																	//if pressed Home key
		 {
			 Player.SetBagCount(50);																//Sets bagcount back to 50
			 Player.Teleport(0,0,east);																//teleporting all robots to starting positions
			 boulder1.Teleport(xPos1,yPos1,east);
			 boulder2.Teleport(xPos2,yPos2,east);
			 boulder3.Teleport(xPos3,yPos3,east);	
			 															
		 }
	}

if( Player.GetBagCount()==0)	//only condition to loose
	{
		playerX=Player.GetXCoordinate();
		playerY=Player.GetYCoordinate();
		playerXstr=itoa(playerX);
		playerYstr=itoa(playerY);
		playerXYstr=playerXstr +", "+ playerYstr; //its not neccesary
		ShowMessage("You couldn't reach to exit in time and blacked out in "+ playerXYstr);
	}
else												// there is no other end condition so other then if can only win 
	{
		bagC=itoa(Player.GetBagCount());		// make it a string because i need a string for showmessage	
		ShowMessage("Congratulations, solved the puzzle with " + bagC + " energy"); 
	}
return 0;
}