#include <bits/stdc++.h>
using namespace std;

class SmsStruct
{
    public:
        string from;
        string to;
        string message_details;
        string date;
        int id;
        SmsStruct()
        {

        }
};

class SmsProtal
{
    int idx = 0;
    stack<SmsStruct*> s;

public:
    void addSmsFromFile(string filename)
    {
        ifstream file(filename);
        if(!file.is_open())
        {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while(getline(file, line))
        {
            istringstream iss(line);
            SmsStruct *sms = new SmsStruct();

            if(getline(iss, sms -> from, ',') && getline(iss, sms -> to, ',') && getline(iss, sms -> message_details, ',') && (iss >> sms -> date))
            {
                sms -> id = idx;
                idx++;
                s.push(sms);
            }
        }

        file.close();
    }

    void addSms()
    {
        SmsStruct *spush = new SmsStruct();

        cout << "Enter Sender Detail:" << endl;
        cin >> spush -> from;

        cout << "Enter Recipient Detail:" << endl;
        cin >> spush -> to;

        cin.ignore();

        cout << "Enter Message Details:" << endl;
        getline(cin, spush -> message_details);

        cout << "Enter Date:" << endl;
        cin >> spush -> date;

        cin.ignore();
        
        spush -> id = idx;
        idx++;
        s.push(spush);
        cout << "Message Added Succesfully" << endl;
    }

    void displayAllMessages()
    {
        stack<SmsStruct*> s1 = s;
        while(!s1.empty())
        {
            SmsStruct *front = s1.top();
            cout << "------------------------------------------------------------------------" << endl;
            cout << "From: " << front -> from << endl;
            cout << "To: " << front -> to << endl;
            cout << "Message: " << front ->message_details << endl;
            cout << "Date: " << front -> date << endl;
            cout << "Id: " << front -> id << endl;
            cout << "------------------------------------------------------------------------" << endl;
            s1.pop();
        }
    }

    void displayUserWise()
    {
        map<string, stack<SmsStruct*>> m;
        stack<SmsStruct *> s1 = s;
        while(!s1.empty())
        {
            SmsStruct *front = s1.top();
            m[front -> from].push(front);
            s1.pop();
        }

        for(auto pair : m)
        {
            string user = pair.first;
            stack<SmsStruct*> userStackCopy = pair.second;
            cout << user << ":" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            
            while (!userStackCopy.empty())
            {
                SmsStruct *sms = userStackCopy.top();
                userStackCopy.pop();
                cout << "From: " << sms -> from << endl;
                cout << "To: " << sms -> to << endl;
                cout << "Message: " << sms -> message_details << endl;
                cout << "Date: " << sms -> date << "\n\n";
                cout << "Id: " << sms -> id << "\n\n";
            }

            cout << "------------------------------------------------------------------------" << endl;
        }
    }

    void displayDateWise()
    {
        map<string, stack<SmsStruct*>, greater<string>> m;
        stack<SmsStruct*> s1 = s;
        
        while(!s1.empty())
        {
            SmsStruct *front = s1.top();
            m[front -> date].push(front);
            s1.pop();
        }

        for(auto pair : m)
        {
            string user = pair.first;
            stack<SmsStruct*> userStackCopy = pair.second;
            cout << user << ":" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            while(!userStackCopy.empty())
            {
                SmsStruct *sms = userStackCopy.top();
                userStackCopy.pop();
                cout << "From: " << sms -> from << endl;
                cout << "To: " << sms -> to << endl;
                cout << "Message: " << sms -> message_details << endl;
                cout << "Date: " << sms -> date << "\n\n";
                cout << "Id: " << sms -> id << "\n\n";
            }

            cout << "------------------------------------------------------------------------" << endl;
        }
    }

    void searchUser()
    {
        string user;
        cout << "Enter the Name of User:" << endl;
        cin >> user;
        stack<SmsStruct*> s1 = s;
        int count = 0;
        while(!s1.empty())
        {
            SmsStruct *front = s1.top();
            if(user == front -> to || user == front -> from)
            {
                cout << "------------------------------------------------------------------------" << endl;
                cout << "From: " << front -> from << endl;
                cout << "To: " << front -> to << endl;
                cout << "Message: " << front -> message_details << endl;
                cout << "Date: " << front -> date << endl;
                cout << "Id: " << front -> id << endl;
                cout << "------------------------------------------------------------------------" << endl;
                count++;
            }

            s1.pop();
        }

        if(count == 0)
            cout << "No User Exists" << endl;
    }

    void searchDate()
    {
        string date;
        cout << "Enter the date of Message:" << endl;
        cin >> date;
        stack<SmsStruct*> s1 = s;
        int count = 0;
        while(!s1.empty())
        {
            SmsStruct *front = s1.top();
            if(date == front->date)
            {
                cout << "------------------------------------------------------------------------" << endl;
                cout << "From: " << front -> from << endl;
                cout << "To: " << front -> to << endl;
                cout << "Message: " << front -> message_details << endl;
                cout << "Id: " << front -> id << endl;
                cout << "------------------------------------------------------------------------" << endl;
                count++;
            }

            s1.pop();
        }

        if(count == 0)
            cout << "No User Exists" << endl;
    }

    void deleteSmsByDate(int id)
    {
        stack<SmsStruct*> tempStack;
        stack<SmsStruct*> s1 = s;
        
        while(!s.empty())
        {
            SmsStruct *front = s.top();
            
            if(id != front -> id)
                tempStack.push(front);
            
            else
            {
                ofstream deletedSmsFile("deleted_sms.txt", ios::app);
                
                if(deletedSmsFile.is_open())
                {
                    deletedSmsFile << front -> from << ',' << front -> to << ',' << front -> id << ',' << front -> message_details << ',' << front -> date << endl;
                    deletedSmsFile.close();
                }

                else
                    cerr << "Failed to open file for deleted SMS." << endl;
                
                delete front;
            }

            s.pop();
        }

        while(!tempStack.empty())
        {
            s.push(tempStack.top());
            tempStack.pop();
        }
    }
};

int main()
{
    SmsProtal portal;
    int choice;
    portal.addSmsFromFile("assignmenttxt.txt");
    while(1)
    {
        cout << "SMS Portal Menu:" << endl;
        cout << "1. Add SMS" << endl;
        cout << "2. Display Messages by User" << endl;
        cout << "3. Display Messages by Date" << endl;
        cout << "4. Search Messages By User" << endl;
        cout << "5. Search Messages By Date" << endl;
        cout << "6. Display All Messages" << endl;
        cout << "7. Delete SMS by Id" << endl;
        cout << "8. Restore all Deleted SMS" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();
        if(choice == 1)
            portal.addSms();
        
        else if(choice == 2)
            portal.displayUserWise();
        
        else if(choice == 3)
            portal.displayDateWise();
        
        else if(choice == 4)
            portal.searchUser();
        
        else if(choice == 5)
            portal.searchDate();
        
        else if(choice == 6)
            portal.displayAllMessages();
        
        else if(choice == 7)
        {
            cout << "Enter the id of the SMS you want to delete: ";
            int id;
            cin >> id;
            portal.deleteSmsByDate(id);
            cout << "SMS deleted successfully!" << endl;
        }

        else if(choice == 8)
            portal.addSmsFromFile("deleted_sms.txt");
        
        else if(choice == 9)
            return 0;
        
        else
            cout << "Invalid choice. Please try again." << endl;
    }
}