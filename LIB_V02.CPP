#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<dos.h>

/*------------------------Macros Definition Begins-------------------------*/

#define	TRUE	1
#define	FALSE	0

#define	PASSWORD_COMP	FALSE

#define print_screen_border	print_Box(1,1,78,24,DBL_LINE)

#define RECORDS      3
#define KEY_UP 		72
#define KEY_DOWN   	80
#define KEY_LEFT   	75
#define KEY_RIGHT  	77
#define KEY_ESC		27
#define KEY_ENTER   13

#define SGL_LINE	0
#define DBL_LINE	1

#define DBL_TOP_RIGHT	187
#define DBL_TOP_LEFT	201
#define DBL_BOT_RIGHT	188
#define DBL_BOT_LEFT	200

#define SGL_TOP_RIGHT	191
#define SGL_TOP_LEFT	218
#define SGL_BOT_RIGHT	217
#define SGL_BOT_LEFT	192

#define	DBL_LINE_HOR	205
#define	DBL_LINE_VER	186

#define	SGL_LINE_HOR	196
#define	SGL_LINE_VER	179

#define LOGINPAGE_ROW	8
#define LOGINPAGE_COL	26
#define LOGINPAGE_WID	25
#define LOGINPAGE_HIG	9

#define LOADING_ROW	12
#define LOADING_COL	32
#define LOADING_WID	15
#define LOADING_HIG	2

#define ACCESSWIN_ROW	12
#define ACCESSWIN_COL	30
#define ACCESSWIN_WID	20
#define ACCESSWIN_HIG	2

#define	BRMENU_EXIT	0
#define	BRMENU_PRCD	1
#define	BRMENU_MAIN	2

/*---------------------Macros Definitions Ends-----------------------------*/

int book_count=0;

char menu_str[8][30] =	{
						{"WELCOME TO LIBRARY"},
						{"MENU"},
						{"Borrow a book"},
						{"Return a book"},
						{"Check a book"},
						{"Exit"},
						{"PROCEED"},
						{"EXIT"}
						};

char borrow_menu1[] = "     -> Exit <-         PROCEED           MENU      ";
char borrow_menu2[] = "        Exit         -> PROCEED <-        MENU      ";
char borrow_menu3[] = "        Exit            PROCEED        -> MENU <-   ";



union REGS in,out;
char user_name[10],password[5],word1[]="surya",word2[]="rahul",
	 word3[]="gokul";


char bbooks[20];                    //To get the book name from user
void print_HLine(int row,int linetype);
void print_VLine(int col, int linetype);
char list_book[RECORDS][30];



/*-----------------------Mouse Fuctions Begins-------------------------------*/

int callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}


void mouseposi(unsigned int &xpos,unsigned int &ypos,int &click)
{
//	click=0;
	in.x.ax=3;
	int86(51,&in,&out);
	click=out.x.bx;
	xpos=out.x.cx;
	ypos=out.x.dx;
}

void setposi(unsigned int &xpos,unsigned int &ypos)
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}

/*-----------------------Mouse Fuctions Ends-------------------------------*/


/*-----------------------Line Functions Begins------------------------------*/


void print_HLine(int row, int linetype)
{
	char ch;
	if (linetype == SGL_LINE)
		ch=SGL_LINE_HOR;
	else
		ch=DBL_LINE_HOR;
	for(int j=1;j<=79;j++)
	{
		gotoxy(j,row);
		cout<<ch;
	}
}

void print_VLine(int col,int linetype)
{
	char ch;
	if (linetype == SGL_LINE)
		ch=SGL_LINE_VER;
	else
		ch=DBL_LINE_VER;
	for(int j=1;j<=24;j++)
	{
		gotoxy(col,j);
		cout<<ch;
	}
}

void print_HLineSeg(int row, int col, int len, int linetype)
{
	char ch;
	if (linetype == SGL_LINE)
		ch=SGL_LINE_HOR;
	else
		ch=DBL_LINE_HOR;
	for(int j=0;j<len;j++)
	{
		gotoxy(col+j,row);
		cout<<ch;
	}
}

void print_VLineSeg(int row, int col, int len, int linetype)
{
	char ch;
	if (linetype == SGL_LINE)
		ch=SGL_LINE_VER;
	else
		ch=DBL_LINE_VER;
	for(int j=0;j<len;j++)
	{
		gotoxy(col,row+j);
		cout<<ch;
	}
}

void print_UL(int x, int y, int lenUL)
{
	gotoxy(x,y);
	for(int i=0;i<lenUL;i++)
		cout<<"~";
}

void print_Box (int row, int col, int width, int height, int linetype)
{
	char ch;
	print_HLineSeg(row,col,width, linetype); // top row
	print_HLineSeg(row+height,col,width, linetype); // bottom row
	print_VLineSeg(row, col, height,linetype); // left vertical line
	print_VLineSeg(row, col+width, height,linetype); // right vertical line
	if (linetype == SGL_LINE)
		ch=SGL_TOP_LEFT;
	else
		ch=DBL_TOP_LEFT;
	gotoxy(col,row);
	cout << ch;
	if (linetype == SGL_LINE)
		ch=SGL_TOP_RIGHT;
	else
		ch=DBL_TOP_RIGHT;
	gotoxy(col+width,row);
	cout << ch;
	if (linetype == SGL_LINE)
		ch=SGL_BOT_LEFT;
	else
		ch=DBL_BOT_LEFT;
	gotoxy(col, row+height);
	cout << ch;
	if (linetype == SGL_LINE)
		ch=SGL_BOT_RIGHT;
	else
		ch=DBL_BOT_RIGHT;
	gotoxy(col+width,row+height);
	cout << ch;
}

void Loading()
{
	textcolor(GREEN);
	clrscr();
	_setcursortype(_NOCURSOR);
	print_screen_border;
	char a=177, b=254,c=219;
	for(int t=0;t<4;t++)
	{
		int x=32;
		for (int j=0;j<=17;j++)
		{
			gotoxy(35,11);
			cout<<"AUTHENTICATING...";
			print_Box ( 12,31,24,2, SGL_LINE);
			gotoxy(32,13);
			for(int k=0;k<23;k++)
				cout<<a;
			gotoxy(x,13);
			cout<<c<<a;
			cout<<c<<a;
			cout<<c<<a;
			x++;
			delay(200);
		}
	}
}

/*-----------------------------Line Functions Ends--------------------------*/



void login_page()
{
		clrscr();
		_setcursortype(_SOLIDCURSOR);
		print_screen_border;
		print_Box(LOGINPAGE_ROW,LOGINPAGE_COL,LOGINPAGE_WID,LOGINPAGE_HIG,SGL_LINE);
		gotoxy(LOGINPAGE_COL+8,LOGINPAGE_ROW+1);
		cout<<"LIBRARY";
		for(int x=0;x<7;x++)
		{
			gotoxy(LOGINPAGE_COL+8+x,LOGINPAGE_ROW+2);
			cout<<"~";
		}
		gotoxy(LOGINPAGE_COL+2,LOGINPAGE_ROW+5);
		cout<<"USER_NAME: ";
		gets(user_name);
		gotoxy(LOGINPAGE_COL+2,LOGINPAGE_ROW+7);
		cout<<"PASSWORD: ";
		for(int j=0;j<5;j++)
		{
			password[j]=getch();
			cout<<"*";
		}
	getch();
	clrscr();
	print_screen_border;
	Loading();
	clrscr();
	print_screen_border;
	print_Box(ACCESSWIN_ROW,ACCESSWIN_COL,ACCESSWIN_WID,ACCESSWIN_HIG,SGL_LINE);
	gotoxy(ACCESSWIN_COL+3,ACCESSWIN_ROW+1);
	cout<<"ACCESS GRANTED";
	gotoxy(54,23);
	cout<<"Hit Enter to proceed....";
	getch();
	clrscr();
 }

void print_MainMenu()
{
	gotoxy(25,3);
	cout<<menu_str[0];
	print_UL(25,4,18);
	gotoxy(33,7);
	cout<<menu_str[1];
	print_UL(33,8,4);
	gotoxy(24,9);
	cout<<"    "<<menu_str[2]<<"    ";
	gotoxy(24,11);
	cout<<"    "<<menu_str[3]<<"    ";
	gotoxy(24,13);
	cout<<"    "<<menu_str[4]<<"    ";
	gotoxy(28,15);
	cout<<"    "<<menu_str[5]<<"    ";
	gotoxy(28,17);
}

/*---------------------------The Class Begins--------------------------------*/

/*This class has the fields neccessary for library management*/

class Library
{
	public:
	char book_name[10],author_name[10];
	int copies;
	void input()                             //To get the details of book
	{
		clrscr();
		static int roll=0;
		roll++;
		cout<<"\n\n\tFill the details of book\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t(S.No "<<roll<<")";
		cout<<"\nName: ";
		gets(book_name);
		cout<<endl<<"Author: ";
		gets(author_name);
		cout<<endl<<"Copies: ";
		cin>>copies;
		cout<<"\n-----------------------------------------------------------------------------\n\n";
	}
	void showdata()
	{
		static int roll=0;
		roll++;
		cout<<"  "<<roll;
		cout<<"\t"<<book_name;
		cout<<"\t"<<author_name;
		cout<<"\t"<<copies;cout<<'\n';

	}
}books;

/*---------------------------The Class Ends--------------------------------*/

void list_books()
{
	char ch=SGL_LINE_HOR;
	gotoxy(23,6);
	cout<<"S.NO      Name       Author";
	for(int j=0;j<27;j++)
	{
		gotoxy(j+23,7);
		cout<<ch;
	}
	fstream bkfile("LIST.dat",ios::binary|ios::out|ios::in);
	int no=1,q=9;
	book_count=0;
	while(bkfile.read((char*)&books,sizeof(books)))
	{
		  gotoxy(21,q);
		  cout<<no;no++;
		  gotoxy(33,q);
		  cout<<books.book_name;
		  gotoxy(45,q);
		  cout<<books.author_name;
		  q++;
		  book_count++;
	}
	print_Box(5,19,35,book_count+5,SGL_LINE);
//	gotoxy(5,23);
//	cout<<"    "<<menu_str[7]<<"    ";
//	gotoxy(67,23);
//	cout<<"    "<<menu_str[1]<<"    ";
//	gotoxy(33,23);
//	cout<<"    "<<menu_str[6]<<"    ";
}

void borrow_books()                    //Function to borrow a book
{
	int menu_ctr=0, getch_val,loop_exit=0;
	clrscr();
	print_screen_border;
	char ch=SGL_LINE_HOR,name[10],chr;
	gotoxy(21,3);
	cout<<"Choose a book from the list to borrow";
	gotoxy(21,4);
	for(int i=0;i<37;i++)
	cout<<ch;
	list_books();
	fstream bkfile("LIST.dat",ios::binary|ios::out|ios::in);
	gotoxy(4,20);
	cout<<"Name of the book: ";
	cin>>name;
	do
	{
		gotoxy(14,22);
		if (menu_ctr == BRMENU_EXIT)
			cout<<borrow_menu1;
		if (menu_ctr == BRMENU_PRCD)
			cout<<borrow_menu2;
		if (menu_ctr == BRMENU_MAIN)
			cout<<borrow_menu3;
		getch_val = getch();
		if (getch_val == 0)
			getch_val = getch();
		switch (getch_val)
		{
			case KEY_LEFT:
				 if (menu_ctr == BRMENU_EXIT)
					menu_ctr=BRMENU_MAIN;
				 else
					menu_ctr--;
				 break;
			case KEY_RIGHT:
				 if (menu_ctr == BRMENU_MAIN)
					menu_ctr=BRMENU_EXIT;
				 else
					menu_ctr++;
				 break;
			case KEY_ENTER:
				 if (menu_ctr == BRMENU_EXIT)
					exit(0);
				 if (menu_ctr == BRMENU_MAIN || menu_ctr == BRMENU_PRCD)
					loop_exit=1;
				 break;
		}
	} while(loop_exit == 0);

	if (menu_ctr == BRMENU_PRCD)
	{
		while(bkfile.read((char*)&books,sizeof(books)))
		{
			if((strcmp(name,books.book_name)==0) && (books.copies!=0))
			{
				clrscr();
				print_screen_border;
				gotoxy(30,12);
				cout<<"BORROWING ";
				delay(700);
				clrscr();
				gotoxy(35,5);
				cout<<"DETAILS";
				gotoxy(35,6);
				for(int j=0;j<7;j++)
					cout<<ch;
				print_screen_border;
				gotoxy(30,8);
				cout<<"Name: "<<books.book_name;
				gotoxy(30,10);
				cout<<"Author: "<<books.author_name;
				gotoxy(30,12);
				cout<<"Remaining copies are "<<books.copies-1;
				gotoxy(18,16);
				cout<<">>>>> SUCCESSFULLY BORROWED <<<<<<< ";
				--books.copies;
				bkfile.seekg(bkfile.tellg()-sizeof(books));
				bkfile.write((char*)&books,sizeof(books));
				getch();
				clrscr();
				print_screen_border;
				gotoxy(28,12);
				cout<<"RETURNING TO MENU ";
				for(int x=0;x<6;x++)
				{
				 delay(700);
				 cout<<"!";
				}
			}
		}
	}
	clrscr();
}

void return_books()            //Function to return a book
{
	int menu_ctr=0, getch_val,loop_exit=0;
	clrscr();
	print_screen_border;
	char ch=SGL_LINE_HOR,name[10],chr;
	gotoxy(21,3);
	cout<<"Choose A Book From The List To Return";
	gotoxy(21,4);
	for(int i=0;i<37;i++)
	cout<<ch;
	list_books();
	fstream bkfile("LIST.dat",ios::binary|ios::out|ios::in);
	gotoxy(4,20);
	cout<<"Name of the book: ";
	cin>>name;
	do
	{
		gotoxy(14,22);
		if (menu_ctr == BRMENU_EXIT)
			cout<<borrow_menu1;
		if (menu_ctr == BRMENU_PRCD)
			cout<<borrow_menu2;
		if (menu_ctr == BRMENU_MAIN)
			cout<<borrow_menu3;
		getch_val = getch();
		if (getch_val == 0)
			getch_val = getch();
		switch (getch_val)
		{
			case KEY_LEFT:
				 if (menu_ctr == BRMENU_EXIT)
					menu_ctr=BRMENU_MAIN;
				 else
					menu_ctr--;
				 break;
			case KEY_RIGHT:
				 if (menu_ctr == BRMENU_MAIN)
					menu_ctr=BRMENU_EXIT;
				 else
					menu_ctr++;
				 break;
			case KEY_ENTER:
				 if (menu_ctr == BRMENU_EXIT)
					exit(0);
				 if (menu_ctr == BRMENU_MAIN || menu_ctr == BRMENU_PRCD)
					loop_exit=1;
				 break;
		}
	} while(loop_exit == 0);

	if (menu_ctr == BRMENU_PRCD)
	{
		while(bkfile.read((char*)&books,sizeof(books)))
		{
			if((strcmp(name,books.book_name)==0) && (books.copies!=0))
			{
				clrscr();
				print_screen_border;
				gotoxy(30,12);
				cout<<"RETURNING ";
				delay(700);
				clrscr();
				gotoxy(35,5);
				cout<<"DETAILS";
				gotoxy(30,6);
				for(int j=0;j<7;j++)
					cout<<ch;
				print_screen_border;
				gotoxy(30,8);
				cout<<"Name: "<<books.book_name;
				gotoxy(30,10);
				cout<<"Author: "<<books.author_name;
				gotoxy(30,12);
				cout<<"No of copies: "<<books.copies;
				gotoxy(15,14);
				cout<<">>>>>>>> SUCCESSFULLY RETURNED <<<<<<<< ";
				gotoxy(20,16);
				cout<<"Remaining copies are "<<books.copies+1;
				++books.copies;
				bkfile.seekg(bkfile.tellg()-sizeof(books));
				bkfile.write((char*)&books,sizeof(books));
				getch();
				clrscr();
				print_screen_border;
				gotoxy(28,12);
				cout<<"RETURNING TO MENU ";
				for(int x=0;x<6;x++)
				{
				 delay(700);
				 cout<<"!";
				}

			}
		}
	}
	clrscr();
}


void availability()
{
	int menu_ctr=0, getch_val,loop_exit=0;
	clrscr();
	print_screen_border;
	char ch=SGL_LINE_HOR,name[10],chr;
	gotoxy(18,3);
	cout<<"Choose A Book From The List To View Its Details";
	gotoxy(18,4);
	for(int i=0;i<47;i++)
	cout<<ch;
	list_books();
	fstream bkfile("LIST.dat",ios::binary|ios::out|ios::in);
	gotoxy(4,20);
	cout<<"Name of the book: ";
	cin>>name;
	do
	{
		gotoxy(14,22);
		if (menu_ctr == BRMENU_EXIT)
			cout<<borrow_menu1;
		if (menu_ctr == BRMENU_PRCD)
			cout<<borrow_menu2;
		if (menu_ctr == BRMENU_MAIN)
			cout<<borrow_menu3;
		getch_val = getch();
		if (getch_val == 0)
			getch_val = getch();
		switch (getch_val)
		{
			case KEY_LEFT:
				 if (menu_ctr == BRMENU_EXIT)
					menu_ctr=BRMENU_MAIN;
				 else
					menu_ctr--;
				 break;
			case KEY_RIGHT:
				 if (menu_ctr == BRMENU_MAIN)
					menu_ctr=BRMENU_EXIT;
				 else
					menu_ctr++;
				 break;
			case KEY_ENTER:
				 if (menu_ctr == BRMENU_EXIT)
					exit(0);
				 if (menu_ctr == BRMENU_MAIN || menu_ctr == BRMENU_PRCD)
					loop_exit=1;
				 break;
		}
	} while(loop_exit == 0);

	if (menu_ctr == BRMENU_PRCD)
	{
		while(bkfile.read((char*)&books,sizeof(books)))
		{
			if((strcmp(name,books.book_name)==0) && (books.copies!=0))
			{
				clrscr();
				print_screen_border;
				gotoxy(30,12);
				cout<<"\CHECKING";
				delay(600);
				clrscr();
				print_screen_border;
				gotoxy(35,5);
				cout<<"DETAILS";
				gotoxy(35,6);
				for(int j=0;j<7;j++)
					cout<<ch;
				gotoxy(30,8);
				cout<<"Name: "<<books.book_name;
				gotoxy(30,10);
				cout<<"Author: "<<books.author_name;
				gotoxy(30,12);
				cout<<"No of copies: "<<books.copies;
				gotoxy(15,15);
				for(int q=0;q<50;q++)
					cout<<"*";
				getch();
				clrscr();
				print_screen_border;
				gotoxy(28,12);
				cout<<"RETURNING TO MENU ";
				for(int x=0;x<6;x++)
				{
				 delay(700);
				 cout<<"!";
				}

			}
		}
	}
	clrscr();
}


void main()
 {
	clrscr();
	unsigned  int x,y,a,b;
	int cl;
	clrscr();
	a=100;
	b=100;
	textbackground(GREEN);
	textcolor(BLUE);
	clrscr();
	_setcursortype(_SOLIDCURSOR);

	fstream bkfile("LIST.dat",ios::binary|ios::app|ios::in);

 	for(int i=0;i<RECORDS;i++) 			//
	 {                          			/* This block of code takes input data from the user at start */
	   books.input();           			//
	   bkfile.write((char*)&books,sizeof(books)); 	//
	 }  						//
	bkfile.seekg(0);
	clrscr();

	while(bkfile.read((char*)&books,sizeof(books)))
	 {

	   books.showdata();

	  }
	getch();
	textbackground(RED);
	textcolor(YELLOW);
	clrscr();
	login_page();
	textbackground(RED);
	textcolor(YELLOW);
	clrscr();
	print_screen_border;
	_setcursortype(_NOCURSOR);
	setposi(a,b);
	callmouse();
	do
	 {
		mouseposi(x,y,cl);
		if((x>=216&&x<=320)&&(y>63 && y<=71))
		{
			gotoxy(24,9);
			cout<<"-> " <<menu_str[2]<< " <-";
			if(cl==1)
			{

				borrow_books();
				print_screen_border;
				print_MainMenu();
			}

		}
		else if((x>=216&&x<=320)&&(y>81 && y<=87))
		{
			gotoxy(24,11);
			cout<<"-> " <<menu_str[3]<< " <-";
			if(cl==1)
			{

				return_books();
				print_screen_border;
				print_MainMenu();
			}
		}
		else if((x>=216&&x<=320)&&(y>96 && y<=103))
		{
			gotoxy(24,13);
			cout<<"-> " <<menu_str[4]<< " <-";
			if(cl==1)
			{

				availability();
			}
		}
		else if((x>=216&&x<=320)&&(y>112 && y<=119))
		{
			gotoxy(28,15);
			cout<<"-> " <<menu_str[5]<< " <-";

			if(cl==1)
			{

				exit(0);
			}
		}
		else
		{
			print_screen_border;
			print_MainMenu();
		}
	}
//	while(!kbhit());
	while(1);
	getch();

 }








































