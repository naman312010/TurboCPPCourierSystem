//**********************************************************

//	PROJECT COURIER SERVICE

//**********************************************************



//**********************************************************

//	INCLUDED HEADER FILES

//**********************************************************

#include <iostream.h>

#include <fstream.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

#include <conio.h>

#include <dos.h>





class station

{

	public:

		void addition(void);

		void modification(void);

		void deletion(void);

		void list(void);

		void search(void);

		float amount(char [], float, char);

		int foundcode(char []);

	private:

		char stcode[10], name[20];

		float doc, docadd, ndoc, ndocadd;

};





class Date

{

	public:

		int valid(void);



		int dd, mm, yy;

};





class customer

{

	public:

		void booking(void);

		void search(void);

		void dailylist(void);

		void monthlylist(void);

	private:

		int lastcustcode(void);



		int custcode;

		char name[20], address[30], phone[10], stcode[10], cname[20], caddress[30], cphone[10], type;

		float weight, amount;

		Date DoB;

};





// FUNCTION TO CHECK THE VALIDITY OF THE GIVEN DATE



int Date :: valid(void)

{

	int days[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

	if ((yy<1900 || dd<1 || dd>31 || mm<1 || mm>12) || ((dd>days[mm]) || ((yy%4!=0) && mm==2 && dd>28)))

		return 0;

	else

		return 1;

}





// FUNCTION RETURN LAST CODE NO. OF THE CUSTOMER



int customer :: lastcustcode(void)

{

	int tcode=0;

	fstream f;

	f.open("customer.dat",ios::in);

	while (f.read((char *) this, sizeof(customer)))

		tcode = custcode;

	f.close();

	return tcode;

}





// FUNCTION TO BOOK COURIER FOR THE CUSTOMER



void customer :: booking(void)

{

	clrscr();

	char tstcode[10], ch;

	int tcustcode;

	station s;

	cout<<"BOOKING COURIER\n\n";

	cout<<"Enter Station Code (Destination) : ";

	gets(tstcode);

	if (!s.foundcode(tstcode))

	{

		cout<<"\n\nStation code does not exist.";

		getch();

		return;

	}

	cout<<"\nINPUT CONSIGNOR INFORMATION";

	tcustcode = lastcustcode()+1;

	cout<<"\n\nCustomer Code : "<<tcustcode;

	cout<<"\nEnter Name of the consignor : ";

	gets(name);

	cout<<"Enter Address of the consignor : ";

	gets(address);

	cout<<"Enter Phone no. of the consignor : ";

	gets(phone);

	cout<<"\nINPUT CONSIGNEE INFORMATION";

	cout<<"\n\nEnter Name of the consignee : ";

	gets(cname);

	cout<<"Enter Address of the consignee : ";

	gets(caddress);

	cout<<"Enter Phone no. of the consignee : ";

	gets(cphone);

	cout<<"\n";

	while(1)

	{

		cout<<"Enter Date of Booking (dd mm yyyy) : ";

		cin>>DoB.dd>>DoB.mm>>DoB.yy;

		if (DoB.valid())

			break;

		else

			cout<<"Invalid Date\n";

	}

	do

	{

		cout<<"\nEnter Type of courier (D=Doc.  N=Non doc.) : ";

		type = getche();

		type = toupper(type);

	} while (type != 'D' && type != 'N');

	cout<<"\nEnter Weight (in gms) : ";

	cin>>weight;

	amount = s.amount(tstcode,weight,type);

	cout<<"Amount : "<<amount<<"\n";

	do

	{

		cout<<"\nSave? (y/n) : ";

		ch = getche();

		ch = toupper(ch);

	} while (ch != 'Y' && ch != 'N');

	if (ch == 'Y')

	{

		strcpy(stcode,strupr(tstcode));

		custcode = tcustcode;

		fstream f;

		f.open("customer.dat",ios::app);

		f.write((char *) this, sizeof(customer));

		f.close();

		cout<<"\n\nRecord Saved";

		getch();

	}

}





// FUNCTION TO SEARCH FOR THE CUSTOMER RECORD



void customer :: search(void)

{

	int tcode;

	clrscr();

	cout<<"SEARCH CUSTOMER RECORD\n\n";

	cout<<"Enter customer code : ";

	cin>>tcode;

	fstream f;

	int found=0;

	f.open("customer.dat",ios::in);

	while (f.read((char *) this, sizeof(customer)))

	{

		if (tcode == custcode)

		{

			found = 1;

			cout<<"\nStation Code : "<<stcode;

			cout<<"\n\nCONSIGNOR INFORMATION";

			cout<<"\n\nName of the consinor : "<<name;

			cout<<"\nAddress of the consignor : "<<address;

			cout<<"\nPhone no. of hte consignor : "<<phone;

			cout<<"\n\nCONSIGNEE INFORMATION";

			cout<<"\n\nName of the consignee : "<<cname;

			cout<<"\nAddress of the consignee : "<<caddress;

			cout<<"\nPhone no. of hte consignee : "<<cphone;

			cout<<"\n\nDate of booking : "<<DoB.dd<<"/"<<DoB.mm<<"/"<<DoB.yy;

			if (type == 'D')

				cout<<"\nType of courier : Document";

			else

				cout<<"\nType of courier : Non-Document";

			cout<<"\nWeight (in gms) : "<<weight;

			cout<<"\nAmount : Rs."<<amount;

			break;

		}

	}

	f.close();

	if (!found)

		cout<<"\n\nCustomer code does not exist.";

	getch();

}





// FUNCTION TO DISPLAY DAILY LIST OF THE BOOKING STATUS



void customer :: dailylist(void)

{

	clrscr();

	Date tdate;

	while(1)

	{

		cout<<"Enter Date of Booking (dd mm yyyy) : ";

		cin>>tdate.dd>>tdate.mm>>tdate.yy;

		if (tdate.valid())

			break;

		else

			cout<<"Invalid Date\n";

	}

	clrscr();

	fstream f;

	f.open("customer.dat", ios::in);

	int row=5, found=0;

	gotoxy(23,1);

	cout<<"DAILY BOOKING STATUS ("<<tdate.dd<<"/"<<tdate.mm<<"/"<<tdate.yy<<")";

	gotoxy(23,2);

	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	gotoxy(1,3);

	cout<<"CODE  CONSIGNOR        CONSIGNEE          STATION CODE  TYPE      WEIGHT  AMOUNT";

	gotoxy(1,4) ;

	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	while (f.read((char *) this, sizeof(customer)))

	{

		if (tdate.dd==DoB.dd && tdate.mm==DoB.mm && tdate.yy==DoB.yy)

		{

			found = 1;

			gotoxy(2,row);

			cout<<custcode;

			gotoxy(7,row);

			cout<<name;

			gotoxy(23,row);

			cout<<cname;

			gotoxy(41,row);

			cout<<stcode;

			gotoxy(55,row);

			if (type == 'D')

				cout<<"Doc.";

			else

				cout<<"Non-Doc.";

			gotoxy(65,row);

			cout<<weight;

			gotoxy(73,row);

			cout<<amount;

			if (row == 23)

			{

				row = 5;

				gotoxy(1,25);

				cout<<"Press any key to continue...";

				getche();

				clrscr();

				gotoxy(23,1);

				cout<<"DAILY BOOKING STATUS ("<<tdate.dd<<"/"<<tdate.mm<<"/"<<tdate.yy<<")";

				gotoxy(23,2);

				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

				gotoxy(1,3);

				cout<<"CODE  CONSIGNOR        CONSIGNEE          STATION CODE  TYPE      WEIGHT  AMOUNT";

				gotoxy(1,4) ;

				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

			}

			else

				row++;

		}

	}

	if (!found)

	{

		gotoxy(5,10);

		cout<<"Records not found";

	}

	gotoxy(1,25);

	cout<<"Press any key to continue...";

	getche();

	f.close();

}





// FUNCTION TO DISPLAY MONTHLY LIST OF THE BOOKING STATUS



void customer :: monthlylist(void)

{

	clrscr();

	Date tdate;

	while(1)

	{

		cout<<"Enter month and year of Booking (mm yyyy) : ";

		cin>>tdate.mm>>tdate.yy;

		tdate.dd = 1;

		if (tdate.valid())

			break;

		else

			cout<<"Invalid Date\n";

	}

	clrscr();

	fstream f;

	f.open("customer.dat", ios::in);

	int row=5, found=0;

	char month[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

	gotoxy(22,1);

	cout<<"MONTHLY BOOKING STATUS ("<<month[tdate.mm-1]<<", "<<tdate.yy<<")";

	gotoxy(1,3);

	cout<<"CODE  CONSIGNOR        CONSIGNEE          STATION CODE  TYPE      WEIGHT  AMOUNT";

	gotoxy(1,4) ;

	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	while (f.read((char *) this, sizeof(customer)))

	{

		if (tdate.mm==DoB.mm && tdate.yy==DoB.yy)

		{

			found = 1;

			gotoxy(2,row);

			cout<<custcode;

			gotoxy(7,row);

			cout<<name;

			gotoxy(23,row);

			cout<<cname;

			gotoxy(41,row);

			cout<<stcode;

			gotoxy(55,row);

			if (type == 'D')

				cout<<"Doc.";

			else

				cout<<"Non-Doc.";

			gotoxy(65,row);

			cout<<weight;

			gotoxy(73,row);

			cout<<amount;

			if (row == 23)

			{

				row = 5;

				gotoxy(1,25);

				cout<<"Press any key to continue...";

				getche();

				clrscr();

				gotoxy(23,1);

				cout<<"DAILY BOOKING STATUS ("<<tdate.dd<<"/"<<tdate.mm<<"/"<<tdate.yy<<")";

				gotoxy(23,2);

				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

				gotoxy(1,3);

				cout<<"CODE  CONSINOR        CONSINEE          STATION CODE  TYPE      WEIGHT  AMOUNT";

				gotoxy(1,4) ;

				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

			}

			else

				row++;

		}

	}

	if (!found)

	{

		gotoxy(5,10);

		cout<<"Records not found";

	}

	gotoxy(1,25);

	cout<<"Press any key to continue...";

	getche();

	f.close();

}





// FUNCTION TO RETURN WHETHER STATION CODE FOUND IN STATION FILE OR NOT



int station :: foundcode(char tcode[10])

{

	int found=0;

	fstream f;

	f.open("station.dat",ios::in);

	while (f.read((char *) this, sizeof(station)))

	{

		if (!strcmpi(tcode,stcode))

		{

			found = 1;

			break;

		}

	}

	f.close();

	return found;

}





// FUNCTION TO CALCULATE AND RETURN AMOUNT



float station :: amount(char tcode[10], float weight, char type)

{

	float tweight, amount=0.0;

	fstream f;

	f.open("station.dat",ios::in);

	while (f.read((char *) this, sizeof(station)))

	{

		if (!strcmpi(tcode,stcode))

		{

			tweight = weight;

			if (type == 'D')

			{

				amount = doc;

				tweight = tweight - 500;

				while (tweight > 0)

				{

					amount = amount + docadd;

					tweight = tweight - 500;

				}

			}

			else

			{

				amount = ndoc;

				tweight = tweight - 500;

				while (tweight > 0)

				{

					amount = amount + ndocadd;

					tweight = tweight - 500;

				}

			}

			break;

		}

	}

	f.close();

	return amount;

}





// FUNCTION TO ADD NEW RECORD FOR STATION



void station :: addition(void)

{

	char tcode[10], ch;

	clrscr();

	cout<<"ADD NEW STATION RECORD\n\n";

	cout<<"Enter Station Code : ";

	gets(tcode);

	if (foundcode(tcode))

	{

		cout<<"\n\nStation code already exist.";

		getch();

		return;

	}

	cout<<"Enter name of the Station : ";

	gets(name);

	cout<<"Enter charges for document (upto 500g)         : Rs.";

	cin>>doc;

	cout<<"Enter charges for document (addition 500g)     : Rs.";

	cin>>docadd;

	cout<<"Enter charges for non-document (upto 500g)     : Rs.";

	cin>>ndoc;

	cout<<"Enter charges for non-document (addition 500g) : Rs.";

	cin>>ndocadd;

	do

	{

		cout<<"\nSave? (y/n) : ";

		ch = getche();

		ch = toupper(ch);

	} while (ch != 'Y' && ch != 'N');

	if (ch == 'Y')

	{

		strcpy(stcode,strupr(tcode));

		fstream f;

		f.open("station.dat",ios::app);

		f.write((char *) this, sizeof(station));

		f.close();

		cout<<"\n\nRecord Saved";

		getch();

	}

}





// FUNCTION TO MODIFY EXISTING RECORD OF STATION



void station :: modification(void)

{

	char tcode[10], ch;

	char tname[20];

	float tdoc, tdocadd, tndoc, tndocadd;

	clrscr();

	cout<<"MODIFY STATION RECORD\n\n";

	cout<<"Enter Station Code : ";

	gets(tcode);

	fstream f, t;

	int found=0;

	f.open("station.dat",ios::in);

	t.open("temp.dat",ios::out);

	while (f.read((char *) this, sizeof(station)))

	{

		if (!strcmpi(tcode,stcode))

		{

			found = 1;

			cout<<"\n\nINPUT NEW DATA\n\n";

			cout<<"Enter name of the Station : ";

			gets(tname);

			cout<<"Enter charges for document (upto 500g)         : Rs.";

			cin>>tdoc;

			cout<<"Enter charges for document (addition 500g)     : Rs.";

			cin>>tdocadd;

			cout<<"Enter charges for non-document (upto 500g)     : Rs.";

			cin>>tndoc;

			cout<<"Enter charges for non-document (addition 500g) : Rs.";

			cin>>tndocadd;

			do

			{

				cout<<"\nUpdate? (y/n) : ";

				ch = getche();

				ch = toupper(ch);

			} while (ch != 'Y' && ch != 'N');

			if (ch == 'Y')

			{

				strcpy(name,tname);

				doc = tdoc;

				docadd = tdocadd;

				ndoc = tndoc;

				ndocadd = tndocadd;

				t.write((char *) this, sizeof(station));

			}

			else

				t.write((char *) this, sizeof(station));

		}

		else

			t.write((char *) this, sizeof(station));

	}

	f.close();

	t.close();

	if (!found)

	{

		cout<<"\n\nStation code does not exist.";

		getch();

		return;

	}

	if (ch == 'N')

		return;

	f.open("station.dat",ios::out);

	t.open("temp.dat",ios::in);

	while (t.read((char *) this, sizeof(station)))

		f.write((char *) this, sizeof(station));

	f.close();

	t.close();

	cout<<"\n\nRecord modified.";

	getch();

}





// FUNCTION TO DELETE EXISTING RECORD OF STATION



void station :: deletion(void)

{

	char tcode[10], ch;

	clrscr();

	cout<<"DELETE STATION RECORD\n\n";

	cout<<"Enter Station Code : ";

	gets(tcode);

	fstream f, t;

	int found=0;

	f.open("station.dat",ios::in);

	t.open("temp.dat",ios::out);

	while (f.read((char *) this, sizeof(station)))

	{

		if (!strcmpi(tcode,stcode))

		{

			found = 1;

			cout<<"\nName of the Station : "<<name;

			cout<<"\nCharges for document (upto 500g)         : Rs."<<doc;

			cout<<"\nCharges for document (addition 500g)     : Rs."<<docadd;

			cout<<"\nCharges for non-document (upto 500g)     : Rs."<<ndoc;

			cout<<"\nCharges for non-document (addition 500g) : Rs."<<ndocadd;

			do

			{

				cout<<"\n\nDelete? (y/n) : ";

				ch = getche();

				ch = toupper(ch);

			} while (ch != 'Y' && ch != 'N');

			if (ch == 'N')

				t.write((char *) this, sizeof(station));

		}

		else

			t.write((char *) this, sizeof(station));

	}

	f.close();

	t.close();

	if (!found)

	{

		cout<<"\n\nStation code does not exist.";

		getch();

		return;

	}

	if (ch == 'N')

		return;

	f.open("station.dat",ios::out);

	t.open("temp.dat",ios::in);

	while (t.read((char *) this, sizeof(station)))

		f.write((char *) this, sizeof(station));

	f.close();

	t.close();

	cout<<"\n\nRecord deleted.";

	getch();

}





// FUNCTION TO SEARCH RECORD FOR THE STATION



void station :: search(void)

{

	char tcode[10];

	clrscr();

	cout<<"SEARCH STATION RECORD\n\n";

	cout<<"Enter Station Code : ";

	gets(tcode);

	fstream f;

	int found=0;

	f.open("station.dat",ios::in);

	while (f.read((char *) this, sizeof(station)))

	{

		if (!strcmpi(tcode,stcode))

		{

			found = 1;

			cout<<"\nName of the Station : "<<name;

			cout<<"\nCharges for document (upto 500g)         : Rs."<<doc;

			cout<<"\nCharges for document (addition 500g)     : Rs."<<docadd;

			cout<<"\nCharges for non-document (upto 500g)     : Rs."<<ndoc;

			cout<<"\nCharges for non-document (addition 500g) : Rs."<<ndocadd;

			break;

		}

	}

	f.close();

	if (!found)

		cout<<"\n\nStation code does not exist.";

	getch();

}





// FUNCTION TO DISPLAY LIST OF THE STATIONS



void station :: list(void)

{

	clrscr();

	fstream f;

	f.open("station.dat", ios::in);

	int row=5, found=0;

	gotoxy(28,1);

	cout<<"STATION INFORMATION";

	gotoxy(28,2);

	cout<<"~~~~~~~~~~~~~~~~~~~";

	gotoxy(1,3);

	cout<<"CODE      NAME               CHARGES : DOC.   ADDITIONAL   NON.DOC  ADDITIONAL";

	gotoxy(1,4) ;

	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	while (f.read((char *) this, sizeof(station)))

	{

		found = 1;

		gotoxy(1,row);

		cout<<stcode;

		gotoxy(11,row);

		cout<<name;

		gotoxy(40,row);

		cout<<doc;

		gotoxy(47,row);

		cout<<docadd;

		gotoxy(60,row);

		cout<<ndoc;

		gotoxy(69,row);

		cout<<ndocadd;

		if (row == 23)

		{

			row = 5;

			gotoxy(1,25);

			cout<<"Press any key to continue...";

			getche();

			clrscr();

			gotoxy(28,1) ;

			cout<<"STATION INFORMATION";

			gotoxy(28,2);

			cout<<"~~~~~~~~~~~~~~~~~~~";

			gotoxy(1,3);

			cout<<"CODE      NAME               CHARGES : DOC.   ADDITIONAL   NON.DOC  ADDITIONAL";

			gotoxy(1,4) ;

			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

		}

		else

			row++;

	}

	if (!found)

	{

		gotoxy(5,10);

		cout<<"Records not found";

	}

	gotoxy(1,25);

	cout<<"Press any key to continue...";

	getche();

	f.close();

}





// MAIN FUNCTION



void main()

{

	station s;

	customer c;

	char ch, ch1;

	do

	{

		clrscr();

		gotoxy(30,6);

		cout<<"COURIER SERVICE";

		gotoxy(30,7);

		cout<<"^^^^^^^^^^^^^^^^^^^";

		gotoxy(30,10);

		cout<<"1. STATION INFORMATION";

		gotoxy(30,11);

		cout<<"2. BOOKING";

		gotoxy(30,12);

		cout<<"3. SEARCH STATION";

		gotoxy(30,13);

		cout<<"4. CUSTOMER RECORD";

		gotoxy(30,14);

		cout<<"5. REPORTS";

		gotoxy(30,15);

		cout<<"6. EDIT STATION";

		gotoxy(30,16);

		cout<<"0. QUIT";

		gotoxy(30,18);

		cout<<"Enter your choice : ";

		ch = getch();

		switch(ch)

		{

			case '1':

				s.list();

				break;

			case '2':

				c.booking();

				break;

			case '3':

				s.search();

				break;

			case '4':

				c.search();

				break;

			case '5':

				do

				{

					clrscr();

					gotoxy(34,8);

					cout<<"REPORTS MENU";

					gotoxy(34,9);

					cout<<"^^^^^^^^^^^^";

					gotoxy(28,12);

					cout<<"1. DAILY BOOKING STATUS";

					gotoxy(28,13);

					cout<<"2. MONTHLY BOOKING STATUS";

					gotoxy(28,14);

					cout<<"0. EXIT";

					gotoxy(28,16);

					cout<<"Enter your choice : ";

					ch1 = getch();

					switch(ch1)

					{

						case '1':

							c.dailylist();

							break;

						case '2':

							c.monthlylist();

							break;

					}

				} while (ch1 != '0' && ch1 != 27);

				break;

			case '6':

				do

				{

					clrscr();

					gotoxy(31,8);

					cout<<"EDIT STATION MENU";

					gotoxy(31,9);

					cout<<"^^^^^^^^^^^^^^^^^";

					gotoxy(28,12);

					cout<<"1. ADD NEW STATION RECORD";

					gotoxy(28,13);

					cout<<"2. DELETE STATION RECORD";

					gotoxy(28,14);

					cout<<"3. MODIFY STATION RECORD";

					gotoxy(28,15);

					cout<<"0. EXIT";

					gotoxy(28,17);

					cout<<"Enter your choice : ";

					ch1 = getch();

					switch(ch1)

					{

						case '1':

							s.addition();

							break;

						case '2':

							s.deletion();

							break;

						case '3':

							s.modification();

							break;

					}

				} while (ch1 != '0' && ch1 != 27);

				break;



		}

	} while (ch != '0' && ch != 27);

}
