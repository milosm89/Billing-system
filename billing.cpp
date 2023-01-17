#include <iostream>
#include <fstream>
using namespace std;

class Shopping {

    private:
        int productCode;
        float price;
        float discount;
        string productName;
    public:
        void menu();
        void administrator();
        void bayer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void Shopping::menu() {

    m:
    int choice;
    string email;
    string password;

    cout << "\t__________________________________\n";
    cout << "\t                                  \n";
    cout << "\t           Main Menu              \n";
    cout << "\t                                  \n";
    cout << "\t__________________________________\n";
    cout << "\t                                  \n";
    cout << "\t|  1) Administrator    \n";
    cout << "\t|                      \n";
    cout << "\t|  2) Bayer            \n";
    cout << "\t|                      \n";
    cout << "\t|  3) Exit             \n";
    cout << "\t|                      \n";
    cout << "\t   Please select!: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
        cout << "\tPlease login!  \n";
        cout << "\tEnter Email    \n";
        cin >> email;
        cout << "\tEnter Password \n";
        cin >> password;

        if (email == "admin@admin.com" && password == "admin123")
        {
            administrator();
        }else
        {
            cout <<"Invalid username or password";
        }
        break;
    case 2:
        bayer();
        break;

    case 3:
        exit(0);
        break;
    default:
        cout <<"Please select given options!";
        break;
    }
    goto m;
}

void Shopping::add() {

    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string name;

    cout <<"\n\n\t Add new product \n";
    cout <<"\n\n\t Product code of the product  \n";
    cin >> productCode;
    cout <<"\n\n\t Name of the product  \n";
    cin >> productName;
    cout <<"\n\n\t Price of the product  \n";
    cin >> price;
    cout <<"\n\n\t Discount on product  \n";
    cin >> discount;

    data.open("database.txt", ios::in);
    if (!data)
    {   
        data.open("database.txt", ios::app|ios::out);
        data << productCode << " " << productName << " " << price << " " << discount << "\n";
        data.close();
    }else
    {
        data >>c >> name >> p >> d;

        while (!data.eof())
        {
            if (c == productCode)
            {
                token++;
            }
            data >>c >> name >> p >> d;
        }
        data.close();

        if (token == 1)
        {
            cout << "Product code alreday exist. Try again!" << endl;
            goto m;

        }else
        {
            data.open("database.txt", ios::app|ios::out);
            data<< productCode << " " << productName << " " << price << " " << discount << "\n";
            data.close();
        }
    }
    cout <<"\n\n\t Record inserted!";
}

void Shopping::edit() {

    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string name;

    cout <<"\n\tEdit the record";
    cout <<"\n\tProduct code: \t";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data)
    {
        cout <<"\n\nFile dosen't exist!";
    }else
    {
        data1.open("database1.txt", ios::app|ios::out);
        data>>productCode>>productName>>price>>discount;

        while (!data.eof())
        {
            if (pkey == productCode)
            {
                cout <<"\n\tProduct new code: \t";
                cin >> c;
                cout <<"\n\tName of the product: \t";
                cin >> name;
                cout <<"\n\tPrice of the product: \t";
                cin >> p;
                cout <<"\n\tDiscount of the product: ";
                cin >> d;

                data1<<c << " " << name << " " << p << " " << d << "\n";
                cout <<"\n\n\tRecord edited";
                token++;
            }else
            {
                data1 << productCode << " " << productName << " " << price << " " << discount << "\n"; 
            }
            data>>productCode>>productName>>price>>discount;  
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0)
        {
            cout <<"\n\n Record not found1";
        }  
    }
}

void Shopping::rem() {

    fstream data, data1;
    int pkey;
    int token = 0;
    
    cout <<"\n\tDelete the product";
    cout <<"\n\tProduct code ";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data)
    {
        cout <<"\n\nFile dosen't exist!";
    }else
    {
        data1.open("database1.txt", ios::app|ios::out);
        data>>productCode>>productName>>price>>discount;

        while (!data.eof())
        {
            if (pkey == productCode)
            {
                cout <<"Product deleted succesfylly!";
                token++;
            }else
            {
                data1 << " " << productCode << " " << productName << " " << price << " " << discount << "\n"; 
            }
            data>> productCode >> productName >> price >> discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout <<"\n\n Record not found1";
        }      
    } 
}

void Shopping::bayer() {
    m:
    int choice;
    cout <<"\tBayer \n";
    cout <<"\t__________________________________\n";
    cout <<"\t1) Buy Product          \n";
    cout <<"\t                        \n";
    cout <<"\t2) Go back              \n";

    cout <<"\tEnter your choice:      \t";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
        break;

    default:
        cout <<"Please select given options!";
        break;
    }
    goto m;
}

void Shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout <<"\n\n____________________________________________________________\n";
    cout <<"ProductNo\tName\t\tPrice\n";
    cout <<"____________________________________________________________\n";
    data >> productCode >> productName >> price >> discount;

    while (!data.eof())
    {
        cout << productCode << "\t\t" << productName << "\t\t" << price << "\n";
        data >> productCode >> productName >> price >> discount;
    }
    data.close();
    
}

void Shopping::receipt() {
    
    fstream data;
    int array_code[100];
    int array_quantity[100];
    char choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

     cout <<"\n\n\n\t\t\t RECEIPT ";
    data.open("database.txt", ios::in);
    
    if (!data)
    {
        cout <<"\n\n Empty database";
    }else
    {
        data.close();
        list();
        cout <<"\n____________________________________________________________\n";
        cout <<"\nPlease place the order         \n";
        cout <<"____________________________________________________________\n\n";

        do
        {
            m:
            cout <<"Enter the product code:";
            cin >> array_code[c];
            cout <<"Enter the product quantity:";
            cin >> array_quantity[c];
            for (int i = 0; i < c; i++)
            {

                if (array_code[c] == array_code[i])
                {
                    cout <<"\n\n Duplicate product code. Please try again!" << endl;
                    goto m;
                }
            }
            
            c++;
            cout <<"\n\n Do you want to buy another product? If yes press y else no:";
            cin >> choice;
        } while (choice == 'y');

        cout <<"\n_________________________________RECEIPT____________________________________________________\n\n";
        cout <<"Product No \tProduct Name\tProduct Quantity\tPrice\tAmount\tAmount with discount\n";

        for (int i = 0; i < c; i++)
        {
            
            data.open("database.txt", ios::in);
            data>> productCode >> productName >> price >> discount;

            while (!data.eof())
            {
                
                if (productCode == array_code[i])
                {
                    amount = price * array_quantity[i];
                    discount = amount - (amount * discount / 100);
                    total = total + discount;
                    cout << "\n" << productCode << "\t\t" << productName << "\t\t" << array_quantity[i] << "\t\t\t" << price << "\t" << amount << "\t" <<discount << endl;
                }
                data >> productCode >> productName >> price >> discount;
                i++;
            }
        }
            data.close();
    }
    
    cout <<"\n\n____________________________________________________________________________________________";
    cout <<"\n Total Amount: " << total <<endl;
    cout << endl;

}

void Shopping::administrator() {
    m:
    int choice;
    cout <<"\n\n\n\tAdministrator Menu";
    cout << "\n\t|_____1)   Add the product________|";
    cout << "\n\t|                                 |";
    cout << "\n\t|_____2)   Edit the product_______|";
    cout << "\n\t|                                 |";
    cout << "\n\t|_____3)   Delete the product_____|";
    cout << "\n\t|                                 |";
    cout << "\n\t|_____4)   Back to main menu______|";

    cout <<"\n\n\t Please enter yoir choice \n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;
    case 2:
        edit();
        break;

    case 3:
        rem();
        break;
    case 4:
        menu();
        break;
    default:
        cout <<"Please select given options!";
        break;
    }
    goto m;

}

int main() {

    Shopping shopping;
    shopping.menu();
    return 0;
}

