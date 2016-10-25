//C++ program to implement working of hospital management system
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<ctime>
using namespace std;
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int leap(int y,int m)
{ 
	if(m==2&&(y%4==0&&y%100!=0||y%400==0))
          return 1;
        else 
          return 0;
}
class date
{
  public: int year;
          int month;
          int day;
  public:
          void curdate();
       
}; 

/*curdate()-Member function of date class.
  Retrieves and stores current date in date object.*/
void date::curdate()
{
  	time_t now = time(0);
  	tm *ltm = localtime(&now);
  	year= 1900 + ltm->tm_year;
  	month= 1 + ltm->tm_mon;
  	day=ltm->tm_mday;
}

struct address
{
  	int hno;
  	char area[10];
  	char city[20];
  	char pin[8];
};

/*patient class which contains details of patients like name,age etc.
  Common to both in-patients and out-patients.*/
class patient 
{
  protected: char firstname[30];
             char lastname[30];
             date dob,doa;
             address addr;
             char bloodgrp[10];
             char phno[15];
             char sex;
             int pid;
             char doc[30];         
  public:    char status[15];
             void getdata();
             void printdata();
	     int search(int);
};

void patient::getdata()
{
        doa.curdate();
 	cout<<"\nEnter Patient ID:";
 	cin>>pid;
 	cout<<"\nEnter Patient name :";
 	cin>>firstname>>lastname;
 	a:
 	cout<<"\nEnter patient gender M/F/O :";
 	cin>>sex;
 	if(sex=='M'||sex=='F'||sex=='O'||sex=='m'||sex=='f'||sex=='o')
	{
 	cout<<"\nEnter Patient phone no.:";
 	cin>>phno;
	}
  	else goto a;
 	b:
 	cout<<"\nEnter date of birth in ddmmyyyy format:";
 	cin>>dob.day>>dob.month>>dob.year;
 	if(dob.day<0||dob.day>(month[dob.month]+leap(dob.year,dob.month))||dob.month<0||dob.month>12||dob.year<1904||dob.year>2014)
          goto b;
 	c:
 	cout<<"\nEnter patient blood group:";
 	cin>>bloodgrp;
 	if(!strcmp(bloodgrp,"A+")||!strcmp(bloodgrp,"A-")||!strcmp(bloodgrp,"B+")||!strcmp(bloodgrp,"B-")||!strcmp(bloodgrp,"O+")||
          !strcmp(bloodgrp,"O-")||!strcmp(bloodgrp,"AB+")||!strcmp(bloodgrp,"AB-")||!strcmp(bloodgrp,"a+")||!strcmp(bloodgrp,"a-")||
          !strcmp(bloodgrp,"b+")||!strcmp(bloodgrp,"b-")||!strcmp(bloodgrp,"o+")||!strcmp(bloodgrp,"o-")||!strcmp(bloodgrp,"ab+")||
          !strcmp(bloodgrp,"ab-"))
	{
 	cout<<"\nEnter name of doctor:";
 	cin>>doc;
	}
 	else goto c;
	cout<<"\nEnter Patient address\nEnter house no.:";
 	cin>>addr.hno;
 	cout<<"\nEnter area name:";
 	cin>>addr.area;
 	cout<<"\nEnter city name:";
 	cin>>addr.city;
 	cout<<"\nEnter pin code:";
 	cin>>addr.pin;
}

void patient::printdata()
{
	cout<<"\nPatient ID\t\t: "<<pid;
	cout<<"\nPatient Name\t\t: "<<firstname<<" "<<lastname;
	cout<<"\nPatient gender\t\t: "<<sex;
	cout<<"\nPatient type\t\t: "<<status;
	cout<<"\nBlood Group\t\t: "<<bloodgrp;
	cout<<"\nDate of birth\t\t: "<<dob.day<<" "<<dob.month<<" "<<dob.year;
	cout<<"\nDate of visit/admission\t: "<<doa.day<<" "<<doa.month<<" "<<doa.year;
	cout<<"\nPatient address\t\t: "<<addr.hno<<"\n\t\t\t  "
            <<addr.area<<"\n\t\t\t  "<<addr.city<<"\n\t\t\t  "<<addr.pin;
	cout<<"\nPatient Phone\t\t: "<<phno;
	cout<<"\nDoctor Assigned\t\t: "<<doc;
}

int patient::search(int id)
{
 	if(pid==id)
   	 return 1;
  	else
   	 return 0;
}
class counter
{
	public: int n,s,d;
		int N[150],S[100],D[50];
		friend int check(int,counter);
};

class inpatient:public patient
{
  protected:    int wardno;
	        date dod;
	        char wardtype[10];
  public: 	void getinfo();
		void printinfo();
		friend int check(int,counter);

};


void inpatient::getinfo()
{     
	counter count;
	int ch;
	d:
	cout<<"Enter the preferred ward type: 1.Normal\t2.Semi\t3.Deluxe\n";
	cin>>ch;
	if(ch==1) strcpy(wardtype,"Normal");
	else if(ch==2) strcpy(wardtype,"Semi");
	else if(ch==3) strcpy(wardtype,"Deluxe");   
	else goto d;
	int a=check(ch,count);
	if(a!=-1)
	{
	wardno=a;
	cout<<"Ward number assigned is : "<<wardno<<" of type :"<<wardtype;
	}
	else
	{
	cout<<"Sorry all such wards are full. Try another type.\n";
	goto d;
	} 
	
	dod.day=0;
	dod.month=0;
	dod.year=0;   
}

void inpatient::printinfo()
{
	cout<<"\nWard No\t\t\t: "<<wardno;
	cout<<"\nWard Type\t\t: "<<wardtype;
	if(dod.day!=0)
	cout<<"\nDate of discharge\t\t: "<<dod.day<<" "<<dod.month<<" "<<dod.year;
	cout<<"\n\n";
}

int check(int ch,counter count)
{
 	int ret,i=0;
	fstream c;
	c.open("count",ios::in|ios::out|ios::app);
	if(!c)
        {
	cout<<"File cannot be opened\n";
	exit(0);
	}
	c.read((char *)&count,sizeof(count));
	switch(ch)
	{
 		case 1: 
		{
				if(count.n==0)
				        return -1;
				else
				{       while(i<150&&count.N[i]!=0)
					    i++;
					count.N[i]=1;
					ret=i+1;
                                }
					count.n=(count.n)-1;
                                        int l=c.tellg();
					c.close();
                                        c.open("count",ios::out|ios::binary|ios::ate);
					c.seekg(l-sizeof(count));
					c.write((char *)&count,sizeof(count));
					return ret;
		}
		case 2: 
		{
				if(count.s==0)
				   return -1;
				else
				{   
					while(i<100&&count.S[i]!=0)
					    i++;
					count.S[i]=1;
					ret=i+1;
				}
					count.s=(count.s)-1;
                                        int l=c.tellg();
					c.close();
                                        c.open("count",ios::out|ios::binary|ios::ate);
					c.seekg(l-sizeof(count));
					c.write((char *)&count,sizeof(count));
					return ret;
				
		}
		case 3: 
		{
				if(count.d==0)
				   return -1;
				else
				{
					while(i<150&&count.D[i]!=0)
					    i++;
					count.D[i]=1;
					ret=i+1;
				}
					count.d=(count.d)-1;
                                        int l=c.tellg();
					c.close();
                                        c.open("count",ios::out|ios::binary|ios::ate);
					c.seekg(l-sizeof(count));
					c.write((char *)&count,sizeof(count));
					return ret;
				
		}
	
	}		

}
	
int main()
{	
	counter ctr;
 	fstream c;
	c.open("count",ios::in|ios::out|ios::app);
	if(!c)
        {
	cout<<"File cannot be opened\n";
	exit(0);
	}
	c.seekg(0,ios::end);
	int len=c.tellg();
	if(len==0)
	{
	c.seekg(0,ios::beg);
	ctr.n=150;
	ctr.s=100;
	ctr.d=50;
	for(int i=0;i<150;i++)
           ctr.N[i]=0;
	for(int i=0;i<100;i++)
	    ctr.S[i];
	for(int i=0;i<50;i++)
	    ctr.D[i]=0;
	c.write((char *)&ctr,sizeof(ctr));
  	getchar();
	}
	c.close();
        menu:
	fstream f1,f2;
 	patient obj;
	inpatient obj1;
 	int choice;
 	char ans;
 	cout<<"**********************************************************************\n";
 	cout<<"\n\t\tHOSPITAL MANAGEMENT SYSTEM\n";
 	cout<<"**********************************************************************\n";
 	cout<<"MENU:\n1.Enter patient information\n"<<
               "2.Display all patient information\n"<<
               "3.Search & display patient information\n"<<
               "4.Discharge & Invoice details\n"<<endl;
 	cin>> choice;
 	f1.open("outpatient",ios::in|ios::out|ios::app|ios::binary);
        if(!f1)
        {
	cout<<"File cannot be opened\n";
	exit(0);
	}
	f2.open("inpatient",ios::in|ios::out|ios::app|ios::binary);
        if(!f2)
        {
	cout<<"File cannot be opened\n";
	exit(0);
	}
 	switch(choice)
	{
 	 case 1:
	{       
		cout<<"**********************************************************************\n";
 		cout<<"\n\t\tCREATE NEW PATIENT DATABASE\n";
 		cout<<"**********************************************************************\n";
 		z:
 		cout<<"Enter patient type 1.Inpatient\t2.Outpatient: ";
 		cin>>choice;
 		if(choice==2)
 		{	
		strcpy(obj.status,"Outpatient");
  		obj.getdata();
  		f1.write((char *)&obj,sizeof(obj));
  		getchar();
		f1.close();
 		}
 		else if(choice==1)
		{
		strcpy(obj1.status,"Inpatient");
		obj1.getdata();
		obj1.getinfo();
		f2.write((char *)&obj1,sizeof(obj1));
		getchar();
		f2.close();
		}
		else goto z;
	        cout<<"\nDo You Want To Continue? y/n  :";
		cin>>ans;
		if(ans=='Y' || ans=='y')
		 goto menu;
		else
 		 break;
	}
 	case 2:
        {       int ch;
		cout<<"**********************************************************************\n";
 		cout<<"\n\t\tDISPLAY PATIENT DATABASE\n";
 		cout<<"**********************************************************************\n";
		e:
		cout<<"Display 1.Inpatients\t2.Outpatients:";
		cin>>ch;
		if(ch==1)
		{
		f2.seekg(0);
 		while(f2.read((char *)&obj1,sizeof(obj1)))
		{
 		 obj1.printdata();
		 obj1.printinfo();
 		 if(f2.eof()==1)
	        {
 		  break;
		}
		}
 		f2.close();
		}
		else if(ch==2)
		{
		f1.seekg(0);
 		while(f1.read((char *)&obj,sizeof(obj)))
		{
 		 obj.printdata();
 		 if(f1.eof()==1)
	        {
 		  break;
		}
		}
 		f1.close();
		}
		else goto e;
		cout<<"\nDo You Want To Continue? y/n  :";
		cin>>ans;
		if(ans=='Y' || ans=='y')
		 goto menu;
		else
 		 break;
		}
	case 3:
	{	
		cout<<"**********************************************************************\n";
 		cout<<"\n\t\tSEARCH PATIENT DATABASE\n";
 		cout<<"**********************************************************************\n";
 		int id,flag,ch;
		f:
		cout<<"Search 1.Inpatient\t2.Outpatient:";
		cin>>ch;
 		cout<<"Enter pid of patient to be searched: ";
 		cin>>id;
		if(ch==1)
		{
 		f2.seekg(0);
		while(f2.read((char *)&obj1,sizeof(obj1)))
		{
  		 flag=obj1.search(id);
  		 if(flag==1)
  		{ 
		 obj1.printdata();
		 obj1.printinfo();
    		 break;
  		}
  		if(f2.eof())
		{
 		 break;
		}
		}
		if(flag!=1)
		 cout<<"Patient not found\n";
		f2.close();
		}
		else if(ch==2)
		{
		f1.seekg(0);
		while(f1.read((char *)&obj,sizeof(obj)))
		{
  		 flag=obj.search(id);
  		 if(flag==1)
  		{ 
		 obj.printdata();
    		 break;
  		}
  		if(f1.eof())
		{
 		 break;
		}
		}
		if(flag!=1)
		 cout<<"Patient not found\n";
		f1.close();
		}
		else goto f;
		cout<<"\nDo You Want To Continue? y/n  :";
		cin>>ans;
		if(ans=='Y'||ans=='y')
		  goto menu;
		else
 		  break;
	}
	case 4:
	default: exit(0);
	}
}

