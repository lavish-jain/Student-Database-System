#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>

using namespace std;

int whatToDo(); // Inputs the choice of user
void addRecord(); // Add a Record
void displayRecord(); // Display a Record
void modifyRecord(); // Modify a record
void deleteRecord(); // Delete a Record

// main
int main() {
    int what_to_do, f = 0;
    while(f==0) {
        system("clear");
        what_to_do = whatToDo();
        switch(what_to_do) {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                modifyRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                cout<<"\nThank you for using the service!\nThe program will now exit\n\n";
                f=1;
                break;
        }
    }
}

// whatToDo:- Input the choice of user
int whatToDo() {
    int choice;
    system("clear");
    cout<<"\t\t====== STUDENT INFORMATION SYSTEM ======\n\n";
    cout<<"Enter your choice:-\n";
    cout<<"1. Add Record.\n";
    cout<<"2. Display Record\n";
    cout<<"3. Modify Record\n";
    cout<<"4. Delete Record\n";
    cout<<"5. Exit\n";
    cin>>choice;
    return choice;
}

// Add a Student Record into the database
void addRecord() {
    system("clear");
    ofstream file("users.txt", ios::app);
    long roll_no;
    string first_name;
    string last_name;
    double cgpa;
    char another = 'y';
    while(another=='y' || another=='Y') {
        system("clear");
        cout<<"Enter the Roll No.: ";
        cin>>roll_no;
        cout<<"Enter the First Name: ";
        cin>>first_name;
        cout<<"Enter the Last Name: ";
        cin>>last_name;
        cout<<"Enter the CGPA: ";
        cin>>cgpa;
        cgpa = floor(cgpa*100.0)/100;
        file<<roll_no<<"    "<<first_name<<"    "<<last_name<<"    "<<cgpa<<endl;
        cout<<"Do you want to add another entry? [Y/N]";
        cin>>another;
    }
    file.close();
}

// Display the current entries in the file
void displayRecord() {
    system("clear");
    ifstream file("users.txt");
    if(file.peek()==EOF) {
        cout<<"The file is empty!"<<endl;
    }
    else {
        const int name_width = 15;
        const int num_width = 15;
        const char seperator = ' ';
        long roll_no;
        string first_name;
        string last_name;
        double cgpa;
        // Displaying in Regular Table form
        // left- Left Aligned
        // setw- Fixed width of the entire column
        // setfill- Empty spaces filled with ' '
        cout<<left<<setw(num_width)<<setfill(seperator)<<"Roll No.";
        cout<<left<<setw(name_width)<<setfill(seperator)<<"First Name";
        cout<<left<<setw(name_width)<<setfill(seperator)<<"Last Name";
        cout<<left<<setw(num_width)<<setfill(seperator)<<"CGPA";
        cout<<"\n \n";
        while(file>>roll_no>>first_name>>last_name>>cgpa) {
            cout<<left<<setw(num_width)<<setfill(seperator)<<roll_no;
            cout<<left<<setw(name_width)<<setfill(seperator)<<first_name;
            cout<<left<<setw(name_width)<<setfill(seperator)<<last_name;
            cout<<left<<setw(num_width)<<setfill(seperator)<<cgpa;
            cout<<endl;
        }
    }
    cin.ignore(1024, '\n');
    cout<<"Enter any key to continue";
    getchar();
    file.close();
}

// Modify the record
void modifyRecord() {
    system("clear");
    ifstream in("users.txt");
    if(in.peek()==EOF) {
        cout<<"The file is empty!"<<endl;
        in.close();
    }
    else {
        ofstream out("temp.txt");
        int found = 0;
        long roll_no;
        cout<<"Enter the roll number of the student whose data needs to be modified ";
        cin>>roll_no;
        long r_no;
        string f_name, l_name;
        double cgpa;
        while(in>>r_no>>f_name>>l_name>>cgpa) {
            if(r_no==roll_no) {
                cout<<"Enter the new roll no. ";
                cin>>r_no;
                cout<<"Enter the new First Name ";
                cin>>f_name;
                cout<<"Enter the new Last Name ";
                cin>>l_name;
                cout<<"Enter the new CGPA ";
                cin>>cgpa;
                cgpa = floor(cgpa*100.0)/100;
                found = 1;
            }
            out<<r_no<<"    "<<f_name<<"    "<<l_name<<"    "<<cgpa<<"    "<<endl;
        }
        if(found==0)
            cout<<"The record was not found"<<endl;
        else
            cout<<"The record was successfully modified"<<endl;
        in.close();
        out.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
    }
    cin.ignore(1024, '\n');
    cout<<"Press enter to continue";
    getchar();
    displayRecord();
}


// Delete the record
void deleteRecord() {
    system("clear");
    ifstream in("users.txt");
    if(in.peek()==EOF) {
        cout<<"The file is empty!"<<endl;
        in.close();
    }
    else {
        ofstream out("temp.txt");
        long roll_no;
        cout<<"Enter the Roll no. of the student whose record needs to be deleted ";
        cin>>roll_no;
        int found = 0;
        long r_no;
        string f_name, l_name;
        double cgpa;
        while(in>>r_no>>f_name>>l_name>>cgpa) {
            if(r_no!=roll_no) {
                out<<r_no<<"    "<<f_name<<"    "<<l_name<<"    "<<cgpa<<endl;
            }
            if(r_no==roll_no)
                found = 1;
        }
        if(found==0)
            cout<<"Entry not found"<<endl;
        else
            cout<<"Entry successfully deleted"<<endl;
        in.close();
        remove("users.txt");
        rename("temp.txt","users.txt");
        out.close();
        }
        cin.ignore(1024,'\n');
        cout<<"Press enter to continue";
        getchar();
        displayRecord();
}
