#include<iostream>
#include<string.h>
using namespace std;

class Covid_Testing {
	string sample_id, sample_testing_date;
	string lname, fname, mname, contact_no, symptoms, address, gender, Detection;
	int age, ID;
	Covid_Testing* next_person;
	int report_status=2;

public:
	Covid_Testing(string lname, string fname, string mname, int age, string contact_no, string symptoms, string address, string gender) {
		this->lname = lname;
		this->fname = fname;
		this->mname = mname;
		this->age = age;
		this->contact_no = contact_no;
		this->symptoms = symptoms;
		this->address = address;
		this->gender = gender;
		next_person = NULL;
	}
	friend class People;
};

class People {
public:
	Covid_Testing* head, * temp;
	People() {
		head = temp= NULL;
	}
	void registration(int);
	void view_report(int);
	void admin();
};

//---------------------------------Register for corona test---------------------------------
void People::registration(int family_member) {
	Covid_Testing* new_person;
	string lname_, fname_, mname_, contact_, symptoms_, address_, gender_;
	int age_, Id = 8677;
	for (int i = 0; i < family_member; i++) {
		cout << "\nFill details of patient " << i + 1;
		cout << "\nEnter name: (lastname firstname middlename): ";
		cin >> lname_ >> fname_ >> mname_;
		cout << "Enter age: ";
		cin >> age_;
		cout << "Enter gender: ";
		cin >> gender_;
		cout << "Enter contact number: ";
		cin >> contact_;
		cout << "Enter symptoms (if no symptoms: type No): ";
		cin >> symptoms_;
		cout << "Enter city: ";
		cin >> address_;
		Id++;
		new_person = new Covid_Testing(lname_, fname_, mname_, age_, contact_, symptoms_, address_, gender_);
		new_person->ID = Id;
		if (head == NULL) {
			head = new_person;
			head->next_person = NULL;
		}
		else {
			temp = head;
			while (temp->next_person != NULL) {

				temp = temp->next_person;
			}
			temp->next_person = new_person;
			new_person->next_person = NULL;
		}
		cout << "\n--------------------------------------------------------------------------------------------------------";
		cout << "\nDear "<<new_person->fname<<", You are Registered for Covid-19 testing. \nOur Team member will come to your specified address and will collect the sample.";
		cout << "\nYOUR ID IS: " << Id;
		cout << "\nStay Safe! Stay Secure, Wear Mask!";
		cout << "\n..........................................................................................................";
	}
}
//------------------------------------------------------VIEW REPORT----------------------------------------
void People::view_report(int PatientID) {
	Covid_Testing* temp1; int flag = 0;
	temp = head;
	if (head == NULL) {
		cout << "No reports are there. Please try again later.";
	}
	else {
		for (temp1 = head; temp1 != NULL; temp1 = temp1->next_person)
		{
			if (temp1->report_status == 0)
				temp1->Detection = "NEGATIVE";
			else if (temp1->report_status == 1)
				temp1->Detection = "POSITIVE";
			else
				temp1->Detection = "PENDING";
			if (temp1->ID == PatientID) {
				flag = 1;
				cout << "\n----------------------------------------------------------------------------------------------------------";
				cout << "\n	                                          RTPCR TEST REPORTS                                            ";
				cout << "\t\t\t\t\t\t\t\tMODULAR DIAGNOSTIC LABORATORY";
				cout << "\n__________________________________________________________________________________________________________";
				cout << "\n Sample ID: \t\t\t\t\t|" << temp1->ID;
				cout << "\n Patient Name:\t\t\t\t\t|" << temp1->lname << " " << temp1->fname << " " << temp1->mname;
				cout << "\n Age\t\t\t\t\t\t|" << temp1->age;
				cout << "\n Gender\t\t\t\t\t\t|" << temp1->gender;
				cout << "\n Contact number\t\t\t\t\t|" << temp1->contact_no;
				cout << "\n Specimen type\t\t\t\t\t|Nasopharyngeal and Oropharyngeal";
				cout << "\n SARS-CoV2\t\t\t\t\t|" << temp1->Detection;
				cout << "\n__________________________________________________________________________________________________________";
			}
		}
		if (flag == 0) {
			cout << "No record Found!";
		}
	}
}

//------------------------------------------ADMIN-----------------------------------------
void People::admin() {
	Covid_Testing* RTPCR();
	string pass,ch;
	int detection;
	Covid_Testing* pending_status=NULL;
	cout << "Enter Password: ";
	cin >> pass;
	if (pass == "abcd") {
		if (head == NULL)
			cout << "\nNo testing reports pending to approve!";
		else {
			for (pending_status = head; pending_status != NULL; pending_status = pending_status->next_person)
			{
				if (pending_status->report_status != 1) {
					if (pending_status->report_status != 0) {
						cout << "\nReports of ID  number " << pending_status->ID;
						cout << "\nEnter SARS-CoV2 Detection: \n1. Positive \n0. Negative \nEnter status: ";
						cin >> detection;
						switch (detection) {
						case 0: pending_status->report_status = 0;
							break;
						case 1: pending_status->report_status = 1;
							break;
						}
					}
					cout << "Do you want to continue:(y/n)? ";
					cin >> ch;
					if ("n")
						break;
					else 
						continue;
				}
			}
		}
	}
}

//--------------------------------------------MAIN-----------------------------------
int main() {
	People p;
	int n,choose, family_members, Patient_id;
	do {
		again:
		cout << "\n1. Patient \n2. Admin";
		cout << "\nEnter choice: ";
		cin >> choose;
		switch (choose) {

		case 1: do {
			cout << "\n__________________________________________________________________________________________________________";
			cout << "\n                                           COVID-19 TESTING PORTAL                                        ";
			cout << "\n1. Register for Covid-testing \n2. View your report \n3. Exit";
			cout << "\n_____________________________________________________________________";
			cout << "\n Choose action : ";
			cin >> n;
			switch (n) {
			case 1: cout << "How many members you want to test for Covid-19: ";
				cin >> family_members;
				cout << "\n__________________________________________________________________________________________________________";
				p.registration(family_members);
				break;
			
			case 2: cout << "Enter ID of patient to view report: ";
				cin >> Patient_id;
				p.view_report(Patient_id);
				break;
			case 3: goto again;
				break;
			}
		}while (n != 3);
		break;
		//------------------------------------------------------------------------------------------------------------------------------
		case 2: p.admin();
			break;
		}
		
	} while (choose != 3);
	return 0;
}