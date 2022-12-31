#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// master class
class MasterClass{
   
    protected:
    string line; // critical
    int ID;
    string name;
    string college;
   
    public:
   
    MasterClass() {
        ID = 0;
        name = "";
        college = "";
    } 

    virtual void pack(){  //override
        line = to_string(ID)+"#"+name+"#"+college+"#";
    }

    virtual void write() = 0;  // override

    virtual void readLine() = 0;  // overrides

    virtual void get_data(){  // override
        string temp_coll;
        bool state = false;
        cout << "Enter ID: ";
        cin >> ID;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter college: ";
        cin >> temp_coll;
        fstream file;
        file.open("collage.txt", ios::in);
        while(getline(file, line)) {
            int del_position = line.find("#");
            string data_college = line.substr(0, del_position);
            line = line.substr(del_position+1);
            if(data_college == temp_coll){
                state = true;
                break;
            }
        }
        if(state){
            college = temp_coll;
        }
        else {
            college =  "wrong_entered_college";
            cout << "college has been assigned to wrong entered college" << endl;
        }
    }   

    virtual void printData(){  // override
        //unpack();
        cout << "ID: " << ID << endl
             << "name: " << name << endl
             << "college: " << college << endl;
    }

    virtual void unpack(){  // override
        // ID unpack
        int del_position = line.find("#");
        ID = stoi(line.substr(0, del_position));
        line = line.substr(del_position+1);
        // name unpack
        del_position = line.find("#");
        name = line.substr(0, del_position);
        line = line.substr(del_position+1);
        // college unpack
        del_position = line.find("#");
        college = line.substr(0, del_position);
        line = line.substr(del_position+1);
    }

    virtual void search(int sid) = 0;  //override

    virtual void deleteUser(int sid) = 0; //override

    virtual void update(int sid) = 0;  // override



};

// student
class Student: public MasterClass{
    string level;
    string GPA;

    public:
    Student(): MasterClass() {
        level =  "";
        GPA = "" ;
    }

    void pack() {      //pack
        MasterClass::pack();
        line += level + '#' + GPA + "\n";
    }

    void get_data() {  //get data
        MasterClass::get_data();
        cout << "Enter Level: ";
        cin >> level;
        cout << "Enter GPA: ";
        cin >> GPA;
    }

    void write(){  //write
        get_data();
        pack();
        fstream file;
        file.open("Student.txt", ios::app);
        file << line;
    }

    void readLine(){
        fstream file;
        file.open("Student.txt", ios::in);
        getline(file, line);
    }

    void unpack(){
        readLine();
        MasterClass::unpack();
        // level unpack
        int del_position = line.find("#");
        level = line.substr(0, del_position);
        line = line.substr(del_position+1);
        // gpd unpack
        del_position = line.find("#");
        GPA = line.substr(0, del_position);
        line = line.substr(del_position+1);

    }

    void printData(){
        //unpack();
        MasterClass::printData();
        cout << "ID: " << ID << endl
             << "name: " << name << endl;
    }

    void search(int sid) {
        fstream file;
        file.open("Student.txt", ios::in);
        while(getline(file, line)) {
            unpack();
            if(ID == sid){
                printData();
                return;
            }
        }
        cout << "not found" << endl;
            
    };   //search

    void deleteUser(int sid) {
        fstream file;
        file.open("Student.txt", ios::in);
        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(ID == sid)
                continue;
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Student.txt");
        rename("emp2.txt", "Student.txt");
    };  //delete

    void update(int sid) {
        fstream file;
        file.open("Student.txt", ios::in);

        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(ID == sid)
                get_data();
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Student.txt");
        rename("emp2.txt", "Student.txt");
    };   //update
};

// Professor

class Professor: public MasterClass{    
    string salary;

    public:
    Professor(): MasterClass() {
        salary = "";
    }

    void pack() {      //pack
        MasterClass::pack();
        line += salary + "\n";
    }

    void get_data() {  //get data
        MasterClass::get_data();
        cout << "Enter salary: ";
        cin >> salary;
    }

    void write(){  //write
        get_data();
        pack();
        fstream file;
        file.open("Professor.txt", ios::app);
        file << line;
    }

    void readLine(){
        fstream file;
        file.open("Professor.txt", ios::in);
        getline(file, line);
    }

    void unpack(){
        readLine();
        MasterClass::unpack();
        // level unpack
        int del_position = line.find("#");
        salary = line.substr(0, del_position);
        line = line.substr(del_position+1);
    }

    void printData(){
        //unpack();
        MasterClass::printData();
        cout << "salary: " << salary << endl;
    }

    void search(int sid) {
        fstream file;
        file.open("Professor.txt", ios::in);
        while(getline(file, line)) {
            unpack();
            if(ID == sid){
                printData();
                return;
            }
        }
        cout << "not found" << endl;
            
    };   //search

    void deleteUser(int sid) {
        fstream file;
        file.open("Professor.txt", ios::in);
        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(ID == sid)
                continue;
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Professor.txt");
        rename("emp2.txt", "Professor.txt");
    };  //delete

    void update(int sid) {
        fstream file;
        file.open("Professor.txt", ios::in);

        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(ID == sid)
                get_data();
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Professor.txt");
        rename("emp2.txt", "Professor.txt");
    };   //update
};

// file classes:
// deparment:
class Department: public MasterClass{
    private:
    int dep_id;
    string dep_name;
    int members_count;
    
    public:

    Department(): MasterClass(), dep_id(0), dep_name("room"), members_count(0){}

    void get_data(){
        //MasterClass::get_data();
        cout << "Enter department id: ";
        cin >> dep_id;
        cout << "Enter department name: ";
        cin >> dep_name;
        cout << "Enter members number: ";
        cin >> members_count; 
    }

    void pack(){
        //MasterClass::pack();
        line = to_string(dep_id) + "#" + dep_name + "#" + to_string(members_count)+"\n";
    }

    void write(){
        get_data();
        pack();
        fstream file;
        file.open("Department.txt", ios::app);
        file << line;
    }

    void readLine(){
        fstream file;
        file.open("Department.txt", ios::in);
        getline(file, line);
    }

    void unpack(){
        readLine();
        //MasterClass::unpack();
        // dep_id unpack
        int del_position = line.find("#");
        dep_id = stoi(line.substr(0, del_position));
        line = line.substr(del_position+1);
        // dep_name unpack
        del_position = line.find("#");
        dep_name = line.substr(0, del_position);
        line = line.substr(del_position+1);
        // members number unpack
        del_position = line.find("#");
        members_count = stoi(line.substr(0, del_position));
        line = line.substr(del_position+1);
    }

    void printData(){
        //unpack();
        //MasterClass::printData();
        cout << "Deparment ID: " << dep_id << endl
             << "department name: " << dep_name << endl
             << "members count: " << members_count << endl;

    }

    void search(int sid) {
        fstream file;
        file.open("Department.txt", ios::in);
        while(getline(file, line)) {
            unpack();
            if(dep_id == sid){
                printData();
                return;
            }
        }
        cout << "not found" << endl;
            
    };

    void deleteUser(int sid) {
        fstream file;
        file.open("Department.txt", ios::in);
        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(dep_id == sid)
                continue;
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Department.txt");
        rename("emp2.txt", "Department.txt");
    };

    void update(int sid) {
        fstream file;
        file.open("Department.txt", ios::in);

        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(dep_id == sid)
                get_data();
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("Department.txt");
        rename("emp2.txt", "Department.txt");
    };   //update
};



// admin class  --> main class
class Admin {
    private:
    string username = "admin";
    string password = "7" ;

    // critical private function
    
    void adminPanal(){

        while (true) {
            int type, option;

            cout << "\nWelcome to the admin panal..." << endl;
            cout << "\nChoose an operation from the following..." << endl << endl;
            cout << "[ 1 ] : Searching for a user." << endl;
            cout << "[ 2 ] : Adding new user." << endl;
            cout << "[ 3 ] : Updating current user." << endl;
            cout << "[ 4 ] : Deleting user." << endl;
            cout << "[ 5 ] : Logout." << endl;

            cout << "Choose the action you would like to do: ";
            cin >> option;

            if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {  // not valid option
                cout << '\a' << "Please enter a valid option!" << endl;
            }

            else {      // valid option
                int input;
                switch(option){
                    case 1:
                        cout << "\nChoose the user type..." << endl;
                        cout << "[ 1 ] : Student." << endl;
                        cout << "[ 2 ] : Professor." << endl;
                        cout << "[ 3 ] : Department." << endl;
                        cout << "\nEnter a number : ";
                        cin >> input;
                        if (input == 1) {       // student search
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Student object;
                            object.search(id);
                            // Including the searching method from the Student Class.
                        }
                        else if (input == 2) {  // prof search
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Professor object;
                            object.search(id);
                            // Including the searching method from the Professor Class.
                        }
                        else if (input == 3){   // dep search
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Department object;
                            object.search(id);
                            // Including the searching method from the Professor Class.
                        }

                        break;
                    
                    case 2:
                        cout << "\nChoose the user type..." << endl;
                        cout << "[ 1 ] : Student." << endl;
                        cout << "[ 2 ] : Professor." << endl;
                        cout << "[ 3 ] : Department." << endl;
                        cout << "\nEnter a number : ";
                        cin >> input;

                        if (input == 1) {     // student add
                            Student object;
                            object.write();
                        }
                        else if (input == 2) {  // prof add
                            Professor object;
                            object.write();
                            // Including the add method from the Professor Class.
                        }
                        else if(input == 3){    // dep add
                            Department object;
                            object.write();
                        }
                        
                        break;

                    case 3:
                        cout << "\nChoose the user type..." << endl;
                        cout << "[ 1 ] : Student." << endl;
                        cout << "[ 2 ] : Professor." << endl;
                        cout << "[ 3 ] : Department." << endl;
                        cout << "\nEnter a number : ";
                        cin >> input;

                        if (input == 1) {   // student update
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Student object;
                            object.update(id);
                        }
                        else if (input == 2) {  // prof update
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Professor object;
                            object.update(id);
                            // Including the update method from the Professor Class.
                        }
                        else if (input == 3) {  // dep update
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Department object;
                            object.update(id);
                            // Including the update method from the Professor Class.
                        }
                        
                        break;
                    
                    case 4:
                        cout << "\nChoose the user type..." << endl;
                        cout << "[ 1 ] : Student." << endl;
                        cout << "[ 2 ] : Professor." << endl;
                        cout << "[ 3 ] : Department." << endl;
                        cout << "\nEnter a number : ";
                        cin >> input;

                        if (input == 1) {   // student delete
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Student object;
                            object.deleteUser(id);
                        }
                        else if (input == 2) {  // prof delete
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Professor object;
                            object.deleteUser(id);
                            // Including the delete method from the Professor Class.
                        }
                        else if (input == 3) {  // dep deletes
                            int id;
                            cout << "Enter search ID: ";
                            cin >> id;
                            Department object;
                            object.deleteUser(id);
                            // Including the delete method from the Professor Class.
                        }
                        
                        break;

                    case 5:     // logout
                        cout << "\nLogging out..." << endl;
                        cout << "Closing System..." << endl;
                        return;
                    
                    default:       // not valid input
                        cout << "Neither student nor professor has been chosen :(" << endl;
                }
            }
        }

    }

    void login() { // Login page 

        string username_input;
        string password_input;

        while (true) {
            cout << "Login to the admin panal..." << endl;
            cout << "Enter your username : ";
            cin >> username_input;

            cout << "Enter your password : ";
            cin >> password_input;

            // reading from admin login file and store in username and passwor attributes


            if (username_input == username && password_input == password) {

                adminPanal();
                return;
            }
            else
            {
                cout << "Invalid username or password.\a" << endl;
                cout << "\nPlese, Try again..." << endl << endl;
            }
        }
	}

    public:
    void runSystem(){
        while(true){
            int choise;
            cout << endl << "---------- Welcome to Sinia Uniersity Admin Portal ----------" << endl << endl;
            cout << "[1] Admin Login" << endl
                    << "[2] How to use out System" << endl
                    << "[3] About Development Team" << endl
                    << "[4] Exit" << endl << "Choose a number : ";
            cin >> choise;
            switch(choise){
                case 1:
                    login();
                    break;
                case 2:
                    cout << endl << "Admin portal manual" << endl
                         << "After you have successfully login" << endl
                         << "Available operations:" << endl
                         << "1. searching   2. adding   3. update" << endl
                         << "4. deleting" << endl
                         << "All operations are availe for Students, Professors, and Department" << endl
                         << "Or you can logout" << endl;
                         break;
                case 3:
                    cout << endl << "Meet our Development Team 💪️"<< endl
                         << "Eng: Mostafa specialist at CS and python expert ما شاء الله" << endl
                         << "Eng: Nooreldin expert at Web applications and AI ما شاء الله" << endl
                         << "Eng: Yousef Expert software Engineer and CEO ما شاء الله" << endl
                         << "Eng: Mohmed Hisham: Expert Embeded Systems engineer ما شاء الله" << endl
                         << "Eng: Mohmed ALi: Expert at BI and ML ما شاء الله" << endl
                         << "Eng: Ahmed: Expert at DS and Big data ما شاء الله" << endl
                         << "Eng: Mahmoud على الله حكايته ما شاء الله" << endl;
                         break;
                case 4:
                    return;
            }

        }

    }    
};

/*class College_file: public MasterClass{

    public:
    void pack() {
        line = college + "#" + "\n";
    }

    void get_data() {
        cout << "Enter new College name: ";
        cin >> college;
    }

    void write(){  //write
        get_data();
        pack();
        fstream file;
        file.open("collage.txt", ios::app);
        file << line;
    }

    void readLine(){
        fstream file;
        file.open("Student.txt", ios::in);
        getline(file, line);
    }

    void unpack(){
        readLine();
        // college unpack
        int del_position = line.find("#");
        college = line.substr(0, del_position);
        line = line.substr(del_position+1);

    }

    void printData(){}

    void search(int sid) {
        fstream file;
        file.open("collage.txt", ios::in);
        while(getline(file, line)) {
            unpack();
            if(ID == sid){
                printData();
                return;
            }
        }
        cout << "not found" << endl;
            
    };   //search

    bool search(string s_coll) {
        fstream file;
        file.open("collage.txt", ios::in);
        while(getline(file, line)) {
            unpack();
            if(college == s_coll){
                return true;
            }
        }
        return false;
            
    };   //search

    void deleteUser(int sid) {};  //delete
     
    void deleteUser(string d_coll) {
        fstream file;
        file.open("colleg.txt", ios::in);
        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(college == d_coll)
                continue;
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("collage.txt");
        rename("emp2.txt", "collage.txt");
    };

    void update(int sid) {};   //update
    void update(string s_coll) {
        fstream file;
        file.open("collage.txt", ios::in);

        fstream file2;
        file2.open("emp2.txt", ios::app);
        while(getline(file, line)) {
            unpack();
            if(college == s_coll)
                get_data();
            pack();
            file2 << line;

        }

        file.close();
        file2.close();

        remove("collage.txt");
        rename("emp2.txt", "collage.txt");
    };   //update
};*/


int main(){
    Admin admin;
    admin.runSystem();
}