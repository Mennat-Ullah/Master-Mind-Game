#include <iostream>
#include <string> 
#include <Windows.h> // for sleep and gotoXY
#include <ctime> // for time rand
#include <conio.h>// for getch
#include <fstream> // for io in file
#include<algorithm>//pair ,
#include<mmstream.h> //for sound
#pragma comment(lib, "winmm.lib") //for sound
#define SND_FILENAME 0x20000//for sound
#define SND_LOOP 8//for sound
#define SND_ASYNC 1//for sound

using namespace std;
int irandomdigit[4] , ipositive=0 , inegative=0, inofplayers , iplayercheck=0 ;
string  ccases , swinner="" ;
pair< int, pair < string ,string >> player[100];// for top 10

/* this function setup the color of both the background & writings in the project*/
void setColor(int color)    
{
	HANDLE  hColor;	
	hColor = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, color);
} 

//this function aim to make the cosole page as atype of graph having x & y coordinates
// this help in controling the place of output
//›‰ﬂ‘‰ ⁄·‘«‰ ‰ Õﬂ„ ÂÊ ÂÌÿ·⁄ ›Ì‰ ⁄·Ï «·‘«‘Â
void gotoXY(int x, int y)    
{                         
	COORD coord;          
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//this function for organizing the output of the first 2 screens
void welcome ()
{
	system("cls");
	setColor(253);
	//----------------first screen------------------
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	gotoXY(25,8) ;  cout<<"READY";
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	gotoXY(35,10) ; cout<<"STEADY";
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	gotoXY(45,12) ; cout<<"GO !!!";
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	PlaySound(TEXT("test.wav"),NULL, SND_ALIAS | SND_APPLICATION);
	system("cls");
	string swelcome ="** Welcome to the MASTER MIND Game ^_^ **" ;
	//-----------------------------------
	for(int i = 0 ; i <swelcome.size(); i++)//output the welcome message
	{
		gotoXY(i+20,9); 
		cout << swelcome[i];
		Sleep(50);
	}
	int x=swelcome.size();
	setColor(245);
	for(int i = 0 ; i <x; i++) // Ìÿ·⁄ ”ÿ—Ì‰ ›Êﬁ —”«·… «· —ÕÌ»  To out put 2 lines above & below the welcome message
	{
		gotoXY(x+19-i,7);
		cout << '=';
		gotoXY(i+20,8);    
		cout << '=';
		gotoXY(x+19-i,10);
		cout << '=';
		gotoXY(i+20,11);
		cout << '=';
		Sleep(50);
	}
}

//this function output the word congratulation with sound after guessing the right number
//it's called by the win function
void Congratulations ()
{
	PlaySound(TEXT("Cheering 2.wav"),NULL, SND_ASYNC );
	setColor(90);
	string swelcome =" Congratulations" ;
	for(int i = 0 ; i <swelcome.size(); i++)
	{
		gotoXY(i,11); 
		cout << swelcome[i];
		Sleep(50);
	}
	//----------------------------
	for(int i = 0 ; i <swelcome.size(); i++)
	{
		gotoXY(i,11); 
		cout << " ";
		Sleep(50);
	}
}

//this function organize the output after guessing the right number
void win()
{
	setColor(94);
	system("cls");
	for (int c=0 ;c<6 ;c++)                               //0 to 5
	{
		for (int d=0 ;d<=c ;d++)
		{
			gotoXY(d,c);
			cout<<"*";
			gotoXY(d,c+12);
			cout<<" ";
			Sleep(50);
		}
	}
	//----------------------------
	int i=1;
	for (int c=6 ;c<=10 ;c++)                              //6 to 10
	{
		int h=0;
		for(int d=c-i; d>0 ;d--)
		{
			gotoXY(h,c);
			cout<<"*";
			gotoXY(h,c+12);
			cout<<" ";
			h++;
			Sleep(50);
		}
		i+=2;
	}
	//----------------------------
	Congratulations();
	setColor(94);
	i=1;
	for (int c=12 ;c<=17 ;c++)                               //12 to 17
	{
		for (int d=0 ;d<i ;d++)
		{
			gotoXY(d,c);
			cout<<"*";
			gotoXY(d,c-12);
			cout<<" ";
			Sleep(50);
		}
		i++;
	}
	//----------------------------
	i=5;
	for (int c=18 ;c<=22 ;c++)                              //18 to 22
	{
		int h=0;
		for(int d=i; d>0 ;d--)
		{
			gotoXY(h,c);
			cout<<"*";
			gotoXY(h,c-12);
			cout<<" ";
			h++;
			Sleep(50);
		}
		i--;
	}
	system("cls");
}

//this function is for releasing the random numbers it get the range from the programmer & outputthe no. according to some laws
//it depends on time too so every time you close & reopen the program you'll get new numbers
void random ()
{
	srand((unsigned)time(0)); 
	int lowest=0 , highest=9 , range=(highest-lowest)+1;
	do
	{
		for(int index=0; index<4; index++)
		{ 
			irandomdigit[index] = lowest+int(range*rand()/(RAND_MAX + 1.0));
		} 
	} while(
		irandomdigit[0] == 0
		|| irandomdigit[0] == irandomdigit[1] 
	|| irandomdigit[0] == irandomdigit[2]
	|| irandomdigit[0] == irandomdigit[3]
	|| irandomdigit[1] == irandomdigit[2] 
	|| irandomdigit[1] == irandomdigit[3] 
	|| irandomdigit[2] == irandomdigit[3]);
}

//this function is called if 2 players have the same score
//it sort them according to their names
bool compare(pair<int, pair<string ,string>> a, pair<int, pair<string ,string>>b)
{
	if(a.first == b.first)
	{
		if(!a.second.first.empty() && a.second.first < b.second.first)
			return true;
		else
			return false;                                                                                                               
	}
	else
	{
		if(a.first > b.first)
			return true;
		else
			return false;
	}
}

// this function aim to filter the string of entered numbers if it contain any spaces
// after leaving this function the string won't contain any space
void vclean (string &sguess)
{
	for (int g=0 ; g<sguess.size() ; g++)
	{
		if (sguess[g] ==' ')
		{
			sguess.erase(g,1) ;
			g--;
		}
	}
}

// this function is called when the user enter the password to check if it's right one
// the user enters the password through it passing by some tests to ensure it;s the right password
void vpassword()
{
	setColor(116);
	string  password = "";
	int ix=0 ;
	cout << "pleace enter the password : "<<endl;
	do
	{
		password += getch();
		if( password[ ix ] =='\b') //if you press \b the couner reurns back 2 places to re-enter in the place of the wrong char.
		{
			cout<<"\b";
			password.erase(ix-1,2) ;
			ix-=2;
		}
		else
		{
			if (password[ix]!=13)
			{
				setColor(124);
				cout <<	"*";
			}
		}		
		ix++;
	}while( password[ix - 1] != 13 );

	password.erase((password.size()-1),1);//erase the character of enter key from the string

	if( password ==  player[0].second.second  )
	{
		setColor(115);
		cout<<endl<<irandomdigit[0]<<irandomdigit[1]<<irandomdigit[2]<<irandomdigit[3]<<endl;
	}
	else
	{
		setColor(114);
		cout<<endl<<"Sorry wrong answer :("<<endl;
	}
}

//this function is called at the end
void exit ()
{
	//top ten //sort //cout
	setColor(253);
	system("cls");
	sort(player, player + inofplayers , compare); //sort the players according to the highest score
	cout<<"** Top Ten **"<<endl;
	/*-------output the topten-----------*/
	for (int it =0 ; it < 10 && it < (inofplayers - iplayercheck ) ;it++)
	{
		setColor(253);
		gotoXY(20,it+5);
		if( swinner == player[it].second.first)
			setColor(252);
		cout<<player[it].second.first<<".................."<<player[it].first<<endl;
	}

	Sleep(5000);
	setColor(253);
	system("cls");
	//-------------------------displaying the goodbye message-----------------------------
	PlaySound(TEXT("bitter sweet symphony.wav"),NULL, SND_ASYNC );
	setColor(253); gotoXY(18,9); cout << "We hope you will come soon .. Good bye ^_^ ! ";
	setColor(252);gotoXY(35,2) ; cout<<(char)14 ; Sleep(500) ; gotoXY(35,2) ; cout<<" ";
	setColor(244);gotoXY(15,6) ; cout<<(char)6 ; Sleep(500) ; gotoXY(15,6) ; cout<<" ";
	setColor(248);gotoXY(40,4) ; cout<< (char)2 ; Sleep(500) ; gotoXY(40,4) ; cout<<" ";
	setColor(243);gotoXY(26,15) ; cout<<(char)3 ; Sleep(500) ; gotoXY(26,15) ; cout<<" ";
	setColor(252);gotoXY(22,5) ; cout<<(char)15 ; Sleep(500) ; gotoXY(22,5) ; cout<<" ";
	setColor(249);gotoXY(40,18) ; cout<<(char)14 ; Sleep(500) ; gotoXY(40,18) ; cout<<" ";
	setColor(246);gotoXY(45,2) ; cout<<(char)5 ; Sleep(500) ; gotoXY(45,2) ; cout<<" ";
	setColor(244);gotoXY(36,13) ; cout<<(char)1 ; Sleep(500) ; gotoXY(36,13) ; cout<<" ";
	setColor(243);gotoXY(30,3) ; cout<<(char)14 ; Sleep(500) ; gotoXY(30,3) ; cout<<" ";
	setColor(250);gotoXY(40,20) ; cout<<(char)6 ; Sleep(500) ; gotoXY(40,20) ; cout<<" ";
	setColor(254);gotoXY(50,1) ; cout<< (char)2 ; Sleep(500) ; gotoXY(50,1) ; cout<<" ";
	setColor(252);gotoXY(50,15) ; cout<<(char)3 ; Sleep(500) ; gotoXY(50,15) ; cout<<" ";
	setColor(245);cout <<endl<<endl<<endl<<"\t\t\t";

	//----------------writing on the file the scores ,names & passwords of players-------------------------
	ofstream fout;
	fout.open("score.txt");
	fout<<inofplayers - iplayercheck<<endl;
	for(int i=0 ; i < (inofplayers - iplayercheck ) ; i++ )     
	{
		fout << player[i].first << endl;
		fout << player[i].second.first << endl;
		fout << player[i].second.second << endl;
	}
	fout.close();
	exit( 0 );	
}

//to repeat the level
void again ()
{
	cout<<endl<<"Do you want to play again ? (y/n)" ;
	string sagain;
	do
	{
		getline ( cin , sagain);
		if ( sagain == "y" || sagain == "Y")
			ccases="3";
		else if (sagain == "n" || sagain == "N")
			exit();
		else 
			cout << "pleac enter y or n bas  @"<<endl;
	}while ( sagain != "y" && sagain != "Y"&& sagain != "n" && sagain != "N");
}

//this function for getting or confirming the player passwords
void vpassword2()
{
	int iy=0;
	do
	{
		player[0].second.second += getch();
		if( player[0].second.second[ iy ] =='\b') 
		{
			cout<<"\b";
			player[0].second.second.erase(iy-1,2) ;
			iy-=2;
		}
		else
		{
			if (player[0].second.second[iy]!=13)
			{
				setColor(252);
				cout <<	"*";
			}
		}		
		iy++;
	}while( player[0].second.second[iy - 1] != 13 );
	player[0].second.second.erase((player[0].second.second.size()-1),1);
}

//this function desplays small menu during the plaer tries
//through this menu the player can choose to continue, close or change his password 
void menu ()
{
	setColor(381);
	cout << "/t/t/tChange password press 1";
	cout << "/t/t/tcontinue game press 2";
	cout << "/t/t/tExit press 3";
	cout<<endl<<"\t\t\t\t\t";
	string smenu ;
	cin >> smenu;
	if ( smenu =="1")
	{
		system("cls");
		cout<<"Please enter your password :"<<endl;
		getline ( cin , player[0].second.second );
	}
	else if (smenu == "3")
		exit();

}

//this function check the entered numbers and return the result to the player
//it takes the input in string and respond to what it gets through several messages
void check ()
{ 

	string sguess ;       // string to take any value without breaking down ,,⁄·‘«‰ ·Ê Õ—› „Ì÷—»‘ «··⁄»Â  
	int icheckguess, passwordcheck , inotnumber=0;
	do //»‰«Œœ «—»⁄ «—ﬁ«„ ›ﬁÿ 
	{
		icheckguess=0;// · Ã«Â· «Ï «„— cin ﬁ»·Â«
		inotnumber=0;
		setColor(115);
		getline(cin,sguess);
		vclean(sguess);
		if( sguess== "C" )
			menu();
		if( sguess=="-1"  )            //if yes it calls the password function to check this password 
		{
			vpassword(); 
			continue;
		}
		for (int g=0 ;g<sguess.size() ; g++)  
		{

			if( sguess[g]=='-' && g != (sguess.size()-1))      //check for the presence of negative numbers
			{	
				setColor(114);
				cout << "Please enter four positive numbers"<<endl;
				icheckguess++;
				break;
			}
			if (sguess[g] < '0' || sguess[g] > '9')      // check for presence of any character which isn't a number
			{
				setColor(114);
				cout << "Beware !! not all of your input are numbers"<<endl;
				inotnumber++;break;

			}
		}
		if (inotnumber !=0)
			continue;
		if (sguess.size()==0)
		{
			setColor(114);
			cout <<"Watch your hands !!!! you forget to enter the numbers "<<endl;
		}
		else if( sguess.size()!=4 && icheckguess ==0 ) //if the characters entered are more than 4 
		{
			setColor(114);
			cout << "pleace enter just 4 numbers"<<endl;
		}
		else if (sguess.size() ==4 && icheckguess ==0)// if there was repeated number
		{
			if(sguess[0]==sguess[1] || sguess[0]==sguess[2] || sguess[0]==sguess[3] || sguess[1]==sguess[2] || sguess[1]==sguess                  [3] || sguess[2]==sguess[3])
			{
				setColor(114);
				cout << "Please don't repeat any number "<<endl; 
				icheckguess++;
			}
		}
	}
	while (sguess.size() !=4 || icheckguess!=0 || inotnumber !=0 );
	//-------------------------------
	int iguess[4];   //the four numbers are put in an array       »‰ﬁ”„ «·«—»⁄ «—ﬁ«„ ﬂ· Ê«Õœ ›Ï «—«Ï
	for (int x=3 ; x>=0 ; x--)
	{
		iguess[x]=sguess[x]-'0';
	}
	//===============================
	ipositive=0 , inegative=0 ;// check if the entered numbers & random numbers are alike
	for ( int y=0 ; y<4 ; y++)
	{
		for ( int d=0 ; d<4 ; d++)
		{
			if ( irandomdigit[y] == iguess[d] )
			{
				if (y==d)
					ipositive++;
				else
					inegative++;
			}
		}
	}
	//=================== respond to the previous test  ÂÌÿ·⁄ «·«Ã«»Â
	if (inegative == 0 && ipositive == 0)
	{
		setColor(114);
		cout << "Totaly wrong answer";
	}
	for (int n = 0 ; n < inegative ; n++)
	{ 
		setColor(126);cout << 'n';
	}

	for (int p = 0 ; p < ipositive ; p++ )
	{ 
		setColor(125);
		cout <<'p';
	}
	cout <<endl;
}

//the main body of the game
int main()
{
	setColor(253);
	system("cls");
	welcome();
	Sleep(1500);
	//------------getting the scores ,names & passwords of last players-----------------------
	ifstream fin ;
	fin.open("score.txt");
	fin>>inofplayers;
	fin.ignore();
	for (int ig=1 ; ig<=inofplayers ; ig++)
	{
		fin>>player[ig].first;
		fin.ignore();
		getline ( fin , player[ig].second.first );
		getline ( fin , player[ig].second.second );
	}
	fin.close();
	//-----------------------------------
	do
	{
		setColor(253);
		system("cls");
		gotoXY(32,8); cout << "to Play press 1 ";
		gotoXY(32,10); cout<<"to Exit press 2";
		gotoXY(40,12); cin >>ccases;
		cin.ignore();
		//----------------------------------
		if(ccases =="1")
		{
			system("cls");
			cout<<"\n\nPlease enter your name "<<endl<<"\nyour name :";
			inofplayers++;
			getline (cin ,player[0].second.first);
			swinner = player[0].second.first ;

			int x=0;//this counter for y||n && new password

			for (int ig=1 ; ig<=inofplayers ; ig++)
			{

				if (player[0].second.first == player[ig].second.first)//if the player has played before he will get his results from their place in the array & put them in another place where they'll be affected by the changes in the game
				{
					iplayercheck++;          
					cout << "\n\n\n\t\t\t\tWelcome back \n";
					system("cls");
					player[ig].second.first="";
					player[0].first=player[ig].first;
					player[ig].first=NULL;

					cout<<"\n\n\n\t\t\t To change your password press '1'" <<endl;
					cout<<"\n\n\t\t   To confirm your old password press '2'"<<endl;
					string schang="";
					while(getline( cin, schang))
					{
						x++;
						if (schang!="1" && schang!="2" )
							cout<<"\t\t You aren't allowed to enter any number except 1 & 2 ! ";
						else
							break;
					}
					system("cls");
					if (schang=="1")
					{
						cout<< "\nEnter your new password : ";
						vpassword2();
					}
					else
					{
						cout<<"\nEnter your old password :";
						vpassword2();
						cout<<endl<<endl;
						if(player[0].second.second == player[ig].second.second)
							break;
						else
						{
							cout<<"Doesn't match"<<endl<<"Enter your new password"<<endl;
							vpassword2();
						}
					}
					player[ig].second.second="";// the old password is deleted 
				}
			}

			if (x==0)
			{
				cout<< "\n\nEnter your new password ";
				vpassword2();
			}


			//----------------------------------------
			Sleep(1000);
			string cleval;

			do
			{
				setColor(253);
				system("cls");
				gotoXY(29,6); cout<<"to play Level 1 press 1";
				gotoXY(29,8); cout<<"to play Level 2 press 2";
				gotoXY(29,10); cout<<"to Exit press 3";
				gotoXY(40,13); cin >> cleval;
				cin.ignore();
				//=================================================================
				if(cleval == "1")
				{

					system("cls");//leval 1
					//-------------------level laws---------------------------
					setColor(244);
					cout<<"\n\n\t\t\t\t LEVEL LAWS :"<<endl<<endl;
					setColor(253);
					cout<<"1)Enter only 4 positive numbers.\n\n"<<endl;
					cout<<"2)Press '-1' & enter yor password for the right answer.\n\n"<<endl;
					cout<<"3)The password is entered once.\n";
					cout<<endl<<endl<<"4)Press 'C' for the menu.\n\n\n"<<endl;
					cout<<"\t\t\t To continue press 1 ."<<endl;
					string spress;
					while(getline ( cin , spress ) )
					{
						if(spress != "1" )
							cout<<"Please press 1 to continue."<<endl;
						else
							break;
					}
					setColor(113);
					system("cls");
					//---------------------------------------------------
					random();//calls random function for the numbers
					signed int iscore1=0,itry=0;
					cout <<"Enter four numbers : "<<endl<<endl;
					while ( ipositive != 4)
					{
						check();//calls check function  for checking the input
						iscore1++;
					}
					itry = iscore1;
					iscore1 = 100-(iscore1*5);
					if (iscore1 <0)
						iscore1=0;
					if (iscore1 > player[0].first )
						player[0].first = iscore1;
					system("cls");
					win();
					system("cls");
					cout << "\nYour score = "<<iscore1<<endl;
					cout<<"\nNumber of your steps ="<<itry<<endl<<endl;
					 again ();
				}
				//=================================================================
				else if (cleval == "2")//level 2
				{
					//------------------level laws-------------
					setColor(253);
					system("cls");
					cout<<"\n\n\t\t\t\t LEVEL LAWS :"<<endl<<endl;
					setColor(253);
					cout<<"1)Enter only 4 positive numbers.\n\n"<<endl;
					cout<<"2)Press '-1' & enter yor password for the right answer.\n\n"<<endl;
					cout<<"3)The password is entered once.\n";
					cout<<endl<<endl<<"4)Press 'C' for the menu.\n\n\n"<<endl;
					cout<<"\t\t\t To continue press 1 ."<<endl;
					string spress;
					while(getline ( cin , spress ) )
					{
						if(spress != "1" )
							cout<<"Please press 1 to continue."<<endl;
						else
							break;
					}
					setColor(113);
					system("cls");
					//-------------------------------------
					setColor(113);
					random();
					cout <<"Enter four numbers :\n"<<endl;
					for (int iscore = 300 ; iscore >0 ; iscore -=10 )
					{
						check();
						if (ipositive == 4)
						{
							if (iscore > player[0].first )
								player[0].first=iscore;
							system("cls");
							win();
							system("cls");
							cout << "Your score = "<<iscore<<endl;
							break;
						}
					}
					if (ipositive != 4)//if the player couldn't guess the right numbers during limited number of tries
					{
						setColor(118);
						cout << "Game Over :( "<<endl << "The numbers are : "<<irandomdigit[0]<<irandomdigit[1]<<irandomdigit[2];                         cout<<irandomdigit[3];
					}
					cout <<endl;
					 again ();
				}
				//=================================================================
				else if(cleval == "3")
					exit();
				else
				{
					gotoXY(29,15); cout << "please enter 1 or 2 or 3 ";
					Sleep(1000);
				}
			}while (cleval != "1" && cleval != "2" && cleval != "3");
		}
		//=========================================================================
		else if(ccases=="2")
			exit();
		//=========================================================================
		else 
		{
			gotoXY(30,15); cout << "please enter 1 or 2 ";
			Sleep(1000);
		}
	}while (ccases != "1" && ccases != "2" );
	cout<<endl;
}