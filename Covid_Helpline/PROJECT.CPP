#include<conio.h>
#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
void displayName(int);
char pattern[] = {0x00, 0x70, 0x20, 0x27, 0x00, 0x27, 0x20, 0x70};

class node{
 int priority, bedCount;
 char city[20], data[5], name[20];
 node *next;
 public:
   node(){
     next = NULL;
   }
   friend class Zones;
   friend class Hospital;
};

class Zones{
 node *newNode, *front, *temp;
 public:
    Zones(){
      front = temp = NULL;
    }
    void enQueue(char [], char [], int);
    void display();
};

class Hospital{
  node *start, *temp, *newNode;
  public:
     Hospital(){
       start = temp = NULL;
     }
     void addHospital(char[], char[], int);
     void removeHospital(char []);
     void checkBedAvailability(char []);
     void covidHospitals();
};

void Zones :: enQueue(char c[], char d[], int p){
  newNode = new node();
  strcpy(newNode->city, c);
  strcpy(newNode->data, d);
  newNode->priority = p;
  newNode->next = NULL;
  if(front == NULL || p<front->priority){
    newNode->next = front;
    front = newNode;
  }
  else{
    temp = front;
    while(temp->next != NULL && temp->next->priority <= p)
       temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
  }
}

void Zones :: display(){
  int r = 25, g=25, o=25;
  char pt[5];
  cleardevice();
  temp = front;
  if(front == NULL)
     cout<<"\nNo data currently available";
  else{
    outtextxy(150, 30, "------------Zones-----------");
//    setfillstyle(1,4);
    setcolor(RED);
    outtextxy(100, 70, "RED: >=1000");
//    floodfill(100, 100, RED);
    rectangle(100, 100, 300, 250);
    setcolor(RED+YELLOW+LIGHTGREEN);
    outtextxy(100, 285 ,"ORANGE: <1000 & >=500");
    rectangle(100, 300, 300, 450);
    setcolor(GREEN);
    outtextxy(400, 170, "GREEN: <500");
    rectangle(400, 200, 600, 350);
   // cout<<"\n\t\t-------------Zones-----------------\n";
    //cout<<"\nRed\t\tOrange\t\tGreen\n";
    while(temp != NULL){
     // strcpy(pt, char(temp->data));
      if(temp->priority == 3){
	setcolor(RED);
	outtextxy(120, 100+r, temp->city);
	outtextxy(220, 100+r, temp->data);
	r+=25;
      }
      //	cout<<temp->city<<"\n";
      else if(temp->priority == 2){
	 setcolor(LIGHTRED);
	 outtextxy(120, 300+o, temp->city);
	 outtextxy(220, 300+o, temp->data);
	 o+=25;
      }
      //	cout<<"\t\t"<<temp->city<<endl;
      else if(temp->priority == 1){
	 setcolor(GREEN);
	 outtextxy(420, 200+g, temp->city);
	 outtextxy(520, 200+g, temp->data);
	 g+=25;
      }
      //	cout<<"\t\t\t\t"<<temp->city<<endl;
      temp = temp->next;
      //i+=25;
    }
  }
}

void Hospital :: addHospital(char nm[], char ct[], int bed){
  newNode = new node();
  strcpy(newNode->name, nm);
  strcpy(newNode->city, ct);
  newNode->bedCount = bed;
  newNode->next = NULL;

  if(start == NULL)
     start = newNode;
  else{
    temp = start;
    while(temp->next != NULL)
	temp = temp->next;
    temp->next = newNode;
    temp = newNode;
  }
}

void Hospital :: removeHospital(char nm[]){
    int flag = 0;
    node *prev;
    if(start == NULL)
	cout<<"\nNo Hospital is currently added...";
    else{
      temp = start;
      prev = temp;
      while(temp != NULL){
	if(temp->name == nm){
	  if(temp == start)
	    start = temp->next;
	flag = 1;
	cout<<"\nDeleting Hospital...";
	prev->next = temp->next;
	delete(temp);
	break;
      }
      else{
	 prev = temp;
	 temp = temp->next;
      }
    }
    if(flag == 0)
	cout<<"\nNo Hospital found";
    else{
	cout<<"\nHospital deleted!\n";
    }
  }
}


void Hospital :: checkBedAvailability(char ct[]){
      int flag=0;
    if(start == NULL)
        cout<<"\nNo information available...";
    else{
        cout<<"\nCurrent statistics of bed availability in :"<<ct<<"\n";
        cout<<"Name\t\t\tCity\t\tBeds Availability\n";
        cout<<"-----------------------------------------------------------------\n";
        temp = start;
        while(temp != NULL){
            if(temp->city == ct){
                cout<<temp->name<<"\t\t\t"<<temp->city<<"\t\t"<<temp->bedCount;
                cout<<"\n";
                flag = 1;
            }
            temp = temp->next;
        }
        if(flag == 0)
            cout<<"\nNo record found";
    }}

void Hospital :: covidHospitals(){
    if(start == NULL)
	cout<<"\nNo information available...";
  else{
    cout<<"\n\t\tHospitals";
    cout<<"\n-------------------------------------------------------------";
    temp = start;
    while(temp != NULL){
	cout<<"\n\tName: \t"<<temp->name;
	cout<<"\n\tCity: \t"<<temp->city;
	cout<<"\n\tBeds: \t"<<temp->bedCount;
	cout<<"\n-------------------------------------------";
	cout<<"\n";
	temp = temp->next;
    }
  }
}

char dispMenu(){
 char op[1];
 settextstyle(8,0,2);
 outtextxy(100, 150, "*************Welcome to CoVID - HELPLINE*************");
 setcolor(WHITE);
 settextstyle(3,0,1);
 outtextxy(150, 200, "1. Zones");
 outtextxy(150, 240, "2. Vaccination");
 outtextxy(150, 280, "3. Hospitals");
 outtextxy(130, 320, "Enter your choice: ");
  op[0] = getch();
  gotoxy(130,360);
  outtextxy(130, 360, op);
  getch();
  cleardevice();
  return op[0];
}

char dispHosp(){
 char op[1];
 cleardevice();
 settextstyle(8,0,2);
 outtextxy(100, 100, "*************HOSPITAL*************");
 setcolor(WHITE);
 settextstyle(3,0,1);
 outtextxy(150, 160, "A. Add Hospital");
 outtextxy(150, 200, "B. Delete Hospital");
 outtextxy(150, 240, "C. Check Availability");
 outtextxy(150, 280, "D. View Hospitals");
 outtextxy(150, 320, "E. Exit");
 outtextxy(130, 360, "Enter your choice: ");
  op[0] = getch();
  gotoxy(130,380);
  outtextxy(130, 380, op);
  getch();
  cleardevice();
  return op[0];
}

void main(){
 int i;
 int gd=DETECT, gm, x, y;
 char ch = 0;
 initgraph(&gd, &gm, "c:\\turboc3\\bgi");
 cleardevice();
 setfillpattern(pattern, BLUE);
 for(i=0; i<=320; i++){
   bar(320-i, 240-i, 320+i, 240+i);
   delay(4);
 }
 displayName(150);
 getch();
 cleardevice();
 Zones z;
 Hospital h;
 char c[20], d[5], nm[20], ct[20];
 char op[1];
 int p, dt, o, bed;
// cout<<"Welcome to CoVID - HELPLINE";
// settextstyle(8,0,2);
// outtextxy(100, 150, "*************Welcome to CoVID - HELPLINE*************");
// setcolor(WHITE);
// settextstyle(3,0,1);
// outtextxy(150, 200, "1. Zones");
// outtextxy(150, 240, "2. Vaccination");
// outtextxy(150, 280, "3. Hospitals");
// outtextxy(130, 320, "Enter your choice: ");
//  op[0] = getch();
//  gotoxy(130,360);
//  outtextxy(130, 360, op);
//  cleardevice();
 do{
  char n;
  o = (int)dispMenu();
 // cout<<o;
  switch(o){
    case '1':// outtextxy(100, 100, "Zones: ");
		cout<<"\n\n\t--------------Zones-------------- \n";
	      do{
	       //	cleardevice();
		//outtextxy(100, 150, "City: ");
		gotoxy(120, 150);
		cout<<"\n\t\tCity: ";
		//cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t";
		gets(c);
		cout<<"\n\t\tPatients: ";
		//outtextxy(100, 210, "Patients: ");
		//cout<<"\n\n\t\t\t\t";
		cin>>d;
		dt = (int)d;
		sscanf(d, "%d", &dt);
//		cout<<dt;
		cout<<"\t------------------------------------";
		if(dt>=1000)
		   p = 3;
		else if(dt<1000 && dt>=500)
		   p = 2;
		else if(dt<500)
		   p = 1;
		z.enQueue(c,d,p);
		//outtextxy(100, 250, "Do you want to continue? Y/N: ");
		cout<<"\n\tDo you want to continue? Y/N: ";
	       //	cout<<"\n\n\n\t\t\t\t";
		cin>>ch;
		cout<<"\t_______________________________________";
		cout<<"\r";
	       //cleardevice();
		//clrscr();
	      }while(ch!='N' && ch!='n');
	      z.display();
	      getch();
	      cleardevice();
	      break;
      case '2': cout<<"\n\n\t\t\t----------------Vaccines--------------------";
	      break;
      case '3': //outtextxy(100, 100, "**********Hospital***********");
	      do{
		n = dispHosp();
	       //	cout<<n;
		switch(n){
		case 'A':clrscr();
			cleardevice();
			cout<<"\n\t\tEnter Hospital Details: ";
			cout<<"\n\t\t\tName: ";
			gets(nm);
			cout<<"\n\t\t\tCity: ";
			gets(ct);
			cout<<"\n\t\t\tBed Count: ";
			cin>>bed;
			cout<<"\n\t\t---------------------------------";
			h.addHospital(nm, ct, bed);
			break;
		case 'B':clrscr();
			cleardevice();
			cout<<"\n\tEnter the name of Hospital: ";
			gets(nm);
			cout<<"\n\t------------------------------------";
			h.removeHospital(nm);
			getch();
			break;
		case 'C': clrscr();
			  cleardevice();
			 cout<<"\n\t\tCity: ";
			gets(ct);
			cout<<"\n\t------------------------------";
			h.checkBedAvailability(ct);
			getch();
			break;
		case 'D':clrscr();
			cleardevice();
			 h.covidHospitals();
			getch();
			break;
		case 'E': break;
		}
	      }while(n!='E');
	      break;
      case '4': exit(0);
		break;
  }
 }while(o!=4);
 getch();
}

void displayName(int y){
 char *name[] = {"C", "o", "V", "I", "D", "-", "H", "E", "L", "P", "L", "I", "N", "E"};
 int i;
 settextjustify(0,0);
 settextstyle(7,0,7);
 for(i=0; i<15; i++){
   setcolor(WHITE);
   outtextxy(30+i*40, y, name[i]);
 }
 settextstyle(1,0,1);
 setcolor(YELLOW);
 outtextxy(310,320,"All Rights Reserved To: ");
 settextstyle(1,0,1);
 outtextxy(320,360,"2377: Sayali Chaudhari");
 outtextxy(320, 400, "2378: Gargi Shekhar Joshi");
 outtextxy(320, 440, "2382: Durga Pandharkar");
}

