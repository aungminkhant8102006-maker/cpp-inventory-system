#include <iostream>  
#include <string>
#include <algorithm> 
#include <iomanip>
#include<windows.h>
#include<fstream>
#include<sstream>
#include<conio.h>


using namespace std;

// ========================================================
// DATABASE & STRUCTURES
// ========================================================
struct Product
{
  int id;
  string name;
  double price;
  int quantity;
};

Product products[100];
int productCount = 0; 

// ========================================================
// FUNCTION PROTOTYPES
// ========================================================
bool login();
void mainMenu();
void addProduct();
void viewProducts();   
void searchProduct();  
void updateProduct();
void deleteProduct();
string toLowerCase(string str); 
void stockInOut();
void reports();
void allProductsReport();
void lowStockReport();
void outOfStockReport();
void totalInventoryValue();
bool logout();
void setColor(int color);
void saveProducts();
void loadProducts();
string getPassword();

// ---------------- SAVE PRODUCTS ----------------
void saveProducts()
{
    ofstream file("products.txt");

    if (!file)
    {
        cout << "Cannot open file!" << endl;
        return;
    }

    file << productCount << endl;

    for (int i = 0; i < productCount; i++)
    {
        file << products[i].id << endl;
        file << products[i].name << endl;
        file << products[i].price << endl;
        file << products[i].quantity << endl;
    }

    file.close();
}

// ---------------- LOAD PRODUCTS ----------------
void loadProducts()
{
    ifstream file("products.txt");

    if (!file)
    {
        productCount = 0;
        return;
    }

    file >> productCount;
    file.ignore();

    for (int i = 0; i < productCount; i++)
    {
        file >> products[i].id;
        file.ignore();

        getline(file, products[i].name);

        file >> products[i].price;
        file >> products[i].quantity;
        file.ignore();
    }

    file.close();
}
int main()
{
	setColor(11);
    cout << "======================================" << endl;
    cout << "   INVENTORY MANAGEMENT SYSTEM" << endl;
    cout << "======================================" << endl <<endl;
    setColor(7);
    
    loadProducts();

    if (login())
    {
        mainMenu();
    }

    cout << "\nSystem Closed..." << endl;

    return 0;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ---------------- LOWERCASE HELPER ----------------
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// ---------------- HIDDEN PASSWORD ----------------
string getPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13) // Enter key
        {
            break;
        }
        else if (ch == 8) // Backspace
{
    if (password.length() > 0)
    {
        password.erase(password.length() - 1);
        cout << "\b \b";
    }
}
        else
        {
            password += ch;
            cout << "*";
        }
    }

    return password;
}
// ---------------- LOGIN ----------------
bool login()
{
    string username, password;

    const string USER = "admin";
    const string PASS = "1234";

    int attempts = 0;
    const int MAX_ATTEMPTS = 3;


    while (attempts < MAX_ATTEMPTS)
    {
        setColor(11);
    	

        cout << "               LOGIN                " << endl;
        cout  <<"------------------------------------"<<endl<<endl;
        setColor(7);


        cout << "Login Attempt : "
             << attempts + 1 << "/" << MAX_ATTEMPTS << endl;


        cout << "Username      : ";
        cin >> username;


        cout << "Password      : ";
        password= getPassword();
		cout<<endl;


        if (username == USER && password == PASS)
        {
            setColor(10);
            cout << "\nLogin Successful!" << endl;
            setColor(7);

            return true;
        }
        else
        {
            attempts++;

            setColor(12);
            cout << "\nInvalid Username or Password!" << endl<<endl;
            setColor(7);


            if (attempts < MAX_ATTEMPTS)
            {
                cout << "Remaining Attempts : "
                     << MAX_ATTEMPTS - attempts << endl<<endl;
            }
        }
    }


    setColor(12);
    cout << "\n==================================" << endl;
    cout << "Too Many Failed Login Attempts!" << endl;
    cout << "System Closed for Security Reasons." << endl;
    cout << "==================================" << endl;
    setColor(7);


    return false;
}
// ---------------- MAIN MENU ----------------
void mainMenu()
{
    int choice;
    
    bool logout=false;
    do
    {
    
    	setColor(11);
        cout << "\n==================================" << endl;
        cout << "          MAIN MENU" << endl;
        cout << "==================================" << endl;
        setColor(7);
        cout << "[1]  Add Product" << endl;
        cout << "[2]  View Products" << endl;
        cout << "[3]  Search Product" << endl;
        cout << "[4]  Update Product" << endl;
        cout << "[5]  Delete Product" << endl;
        cout << "[6]  Stock In / Out" << endl;
        cout << "[7]  Reports" << endl;
        cout << "[8]  Logout" << endl<<endl;
        
        cout<<"---------------------------------------"<<endl;
		setColor(14);
        cout << "\nEnter Choice : ";
        
        
        cin >> choice;
        setColor(7);

        switch (choice)
        {
        case 1: addProduct(); break;
        case 2: viewProducts(); break;
        case 3: searchProduct(); break;
        case 4: updateProduct(); break;
        case 5: deleteProduct(); break;
        case 6: stockInOut() ; break;
        case 7: reports(); break;
        case 8:
{
    string confirm;
	setColor(14);
    cout << "\nAre you sure you want to logout? (Yes/No): ";
    cin >> confirm;
    setColor(7);

    confirm = toLowerCase(confirm);

    if (confirm == "yes")
    {
        setColor(10);
        cout << "\nLogging Out..." << endl;
        cout << "Thank you for using Inventory Management System!" << endl;
        setColor(7);

        logout = true;
    }
    else if (confirm == "no")
    {
        setColor(12);
        cout << "\nLogout Cancelled! Returning to Main Menu..." << endl;
        setColor(7);
    }
    else
    {
        setColor(12);
        cout << "\nInvalid Input! Returning to Main Menu..." << endl;
        setColor(7);
    }

    break;
}
default:
    cout << "\nInvalid Choice! Please Try Again.\n";
}

} while (!logout);

}


// ---------------- ADD PRODUCT ----------------

// ---------------- CHECK DUPLICATE PRODUCT ID ----------------
bool isDuplicateID(int id)
{
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            return true;   // ID already exists
        }
    }
    return false;          // ID not found
}
void addProduct()
{
  string choice;
  do
  {
      if (productCount >= 100) {
          cout << "\nInventory is Full! Cannot add more products.\n";
          return;
      }
    setColor(11);
    cout<<"\n========== ADD PRODUCT ==========\n" <<endl;
    setColor(7);
      
     
      int newID;

while (true)
{
    cout << "Enter Product ID        : ";
    cin >> newID;

    if (isDuplicateID(newID))
    {
        setColor(12);
        cout << "Product ID already exists! Please enter a different ID.\n";
        setColor(7);
    }
    else
    {
        products[productCount].id = newID;
        break;
    }
}
      cin.ignore();   
      
      cout<<"Enter Product Name      : ";
      getline(cin, products[productCount].name);
      
      cout<<"Enter Product Price     : ";
      cin>> products[productCount].price;
      
      cout<<"Enter Product Quantity  : ";
      cin>> products[productCount].quantity;
            productCount++;
            
            saveProducts();
      setColor(10);
      cout << "\nProduct Added Successfully!\n";
       setColor(7);
      setColor(14);
      cout<<"\nDo you want to add another product? (Yes or No)  : ";
      cin>>choice;
      setColor(7);
  }
  while (choice == "Yes" || choice == "yes"); 
}

 
    // ---------------- VIEW PRODUCTS ----------------
void viewProducts()
{   
	setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                    ALL PRODUCTS LIST                      " << endl;
    cout << "===========================================================" << endl;
    setColor(7);

    if (productCount == 0) {
    	setColor(12);
        cout << "No products available in the inventory.\n";
        cout << "===========================================================" << endl;
        setColor(7);
        return;
    }

        cout << left << setw(6)  << "ID" 
         << "| " << setw(20) << "Name" 
         << "| " << setw(18) << "Price" 
         << "| " << setw(8)  << "Qty" << endl;
    cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < productCount; i++) {
        
        cout << left << setw(6)  << products[i].id << "| "
             << setw(20) << products[i].name << "| "
             << left << setw(12) << (int)products[i].price << setw(6) << "kyat" << "| "
             << setw(8)  << products[i].quantity << endl;
    }
    cout << "===========================================================" << endl;
}

// ---------------- SEARCH PRODUCT ----------------
void searchProduct()
{
    if (productCount == 0)
    {
        cout << "\nInventory is empty. Nothing to search.\n";
        return;
    }

    int choice;
	
	setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                   SEARCH PRODUCT                          " << endl;
    cout << "===========================================================" << endl;
    setColor(7);
	setColor(14);
    cout << "1. Search by ID" << endl;
    cout << "2. Search by Name" << endl;
    cout << "3. Back" << endl;
    

    cout << "\nEnter Choice : ";
    cin >> choice;
    setColor(7);

    switch (choice)
    {
    case 1:
    {
        int searchID;
        bool found = false;
		setColor(14);
        cout << "\nEnter Product ID to Search : ";
        cin >> searchID;
        setColor(7);

        cout << "\n-----------------------------------------------------------\n";
        cout << left << setw(6) << "ID"
             << "| " << setw(20) << "Name"
             << "| " << setw(15) << "Price"
             << "| " << setw(8) << "Qty" << endl;
        cout << "-----------------------------------------------------------\n";

        for (int i = 0; i < productCount; i++)
        {
            if (products[i].id == searchID)
            {
                cout << left << setw(6) << products[i].id
                     << "| " << setw(20) << products[i].name
                     << "| " << setw(10) << products[i].price << "Kyat"
                     << "| " << setw(8) << products[i].quantity << endl;

                found = true;
                break;
            }
        }

        if (!found)
        {
        	setColor(12);
            cout << "\nProduct ID not found!\n";
            setColor(7);
        }

        break;
    }

    case 2:
    {
        string query;
        bool found = false;

        cin.ignore();
		setColor(14);
        cout << "\nEnter Product Name to Search : ";
        
        getline(cin, query);
        setColor(7);

        string lowerQuery = toLowerCase(query);
        
    cout << "\n-----------------------------------------------------------\n";
        cout << left << setw(6) << "ID"
             << "| " << setw(20) << "Name"
             << "| " << setw(15) << "Price"
             << "| " << setw(8) << "Qty" << endl;
        cout << "-----------------------------------------------------------\n";

        for (int i = 0; i < productCount; i++)
        {
            if (toLowerCase(products[i].name).find(lowerQuery) != string::npos)
            {
                cout << left << setw(6) << products[i].id
                     << "| " << setw(20) << products[i].name
                     << "| " << setw(10) << products[i].price << "Kyat"
                     << "| " << setw(8) << products[i].quantity << endl;

                found = true;
            }
        }

        if (!found)
        {
        	setColor(12);
            cout << "\nProduct Name not found!\n";
            setColor(7);
        }

        break;
    }

    case 3:
        return;

    default:
        cout << "\nInvalid Choice!\n";
    }

    cout << "===========================================================\n";
}

// ---------------- UPDATE PRODUCT ----------------
void updateProduct()
{
    if (productCount == 0)
    {
        cout << "\nNo Products Available!\n";
        return;
    }

    int choice;

	setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                   UPDATE PRODUCT                          " << endl;
    cout << "===========================================================" << endl;
    setColor(7);
	setColor(14);
    cout << "1. Update by ID" << endl;
    cout << "2. Update by Name" << endl;
    cout << "3. Back" << endl;

    cout << "\nEnter Choice : ";
    cin >> choice;
    setColor(7);

    switch (choice)
    {
    case 1:
    {
        int searchID;
        bool found = false;
		setColor(14);
        cout << "\nEnter Product ID to Update : ";
        cin >> searchID;
        setColor(7);

        for (int i = 0; i < productCount; i++)
        {
            if (products[i].id == searchID)
            {
                found = true;
				setColor(11);
                cout << "\nCurrent Product Information\n";
                cout << "ID       : " << products[i].id << endl;
                cout << "Name     : " << products[i].name << endl;
                cout << "Price    : " << products[i].price << endl;
                cout << "Quantity : " << products[i].quantity << endl;
                setColor(7);
                
                cout<<"--------------------------"<<endl;

                cin.ignore();

                cout << "\nEnter New Product Name   : ";
                getline(cin, products[i].name);

                cout << "Enter New Product Price    : ";
                cin >> products[i].price;

                cout << "Enter New Product Quantity : ";
                cin >> products[i].quantity;
                
                saveProducts();
				setColor(10);
                cout << "\nProduct Updated Successfully!\n";
                setColor(7);
                break;
            }
        }

        if (!found)
        {
        	setColor(12);
            cout << "\nProduct ID not found!\n";
            setColor(7);
        }

        break;
    }

    case 2:
{
    string searchName;
    bool found = false;

    cin.ignore();
	setColor(14);
    cout << "\nEnter Product Name to Search : ";
    getline(cin, searchName);
    setColor(7);

    string lowerName = toLowerCase(searchName);

    // Show all matching products
    cout << "\nMatching Products\n";
    cout << "=========================================================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Qty" << endl;
    cout << "=========================================================\n";

    for (int i = 0; i < productCount; i++)
    {
        if (toLowerCase(products[i].name).find(lowerName) != string::npos)
        {
            found = true;

            cout << left
                 << setw(10) << products[i].id
                 << setw(25) << products[i].name
                 << setw(12) << products[i].price
                 << setw(10) << products[i].quantity
                 << endl;
        }
    }

    if (!found)
    {
        setColor(12);
        cout << "\nProduct Name not found!\n";
        setColor(7);
        break;
    }
	setColor(14);
    int updateID;
    cout << "\nEnter Product ID to Update : ";
    cin >> updateID;
    setColor(7);

    bool idFound = false;
    cin.ignore();

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == updateID)
        {
            idFound = true;
			setColor(11);
            cout << "\nCurrent Product Information\n";
            cout << "ID       : " << products[i].id << endl;
            cout << "Name     : " << products[i].name << endl;
            cout << "Price    : " << products[i].price << endl;
            cout << "Quantity : " << products[i].quantity << endl;
            setColor(7);

            cout << "\nEnter New Product Name   : ";
            getline(cin, products[i].name);

            cout << "Enter New Product Price    : ";
            cin >> products[i].price;

            cout << "Enter New Product Quantity : ";
            cin >> products[i].quantity;

            saveProducts();
			setColor(10);
            cout << "\nProduct Updated Successfully!\n";
            setColor(7);
            break;
        }
    }

    if (!idFound)
    {
        setColor(12);
        cout << "\nInvalid Product ID!\n";
        setColor(7);
    }

    break;
}
    case 3:
        return;

    default:
        cout << "\nInvalid Choice!\n";
    }

    cout << "===========================================================\n";
}

// ---------------- DELETE PRODUCT ----------------
void deleteProduct()
{
    if (productCount == 0)
    {
        cout << "\nNo Products Available!\n";
        return;
    }

    int choice;
	setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                   DELETE PRODUCT                          " << endl;
    cout << "===========================================================" << endl;
    setColor(7);
	setColor(14);
    cout << "1. Delete by ID" << endl;
    cout << "2. Delete by Name" << endl;
    cout << "3. Back" << endl;

    cout << "\nEnter Choice : ";
    cin >> choice;
    setColor(7);

    switch (choice)
    {
    case 1:
    {
        int searchID;
        bool found = false;
        string confirm;
		setColor(14);
        cout << "\nEnter Product ID to Delete : ";
        cin >> searchID;
        setColor(7);

        for (int i = 0; i < productCount; i++)
        {
            if (products[i].id == searchID)
            {
                found = true;
				setColor(10);
                cout << "\nProduct Found!\n";
                setColor(7);
                cout << "ID       : " << products[i].id << endl;
                cout << "Name     : " << products[i].name << endl;
                cout << "Price    : " << products[i].price << endl;
                cout << "Quantity : " << products[i].quantity << endl;
				setColor(14);
                cout << "\nAre you sure you want to delete this product? (Yes/No): ";
                cin >> confirm;
                setColor(7);

                if (toLowerCase(confirm) == "yes")
                {
                    for (int j = i; j < productCount - 1; j++)
                    {
                        products[j] = products[j + 1];
                    }

                    productCount--;
                    saveProducts();
                    setColor(10);
                    cout << "\nProduct Deleted Successfully!\n";
                    setColor(7);
                }
                else
                {
                	setColor(12);
                    cout << "\nDelete Cancelled.\n";
                    setColor(7);
                }

                break;
            }
        }

        if (!found)
        {
        	setColor(12);
            cout << "\nProduct ID not found!\n";
            setColor(7);
        }

        break;
    }

    case 2:
{
    string searchName;
    bool found = false;
    string confirm;

    cin.ignore();
	setColor(14);
    cout << "\nEnter Product Name to Search : ";
    
    getline(cin, searchName);
    setColor(7);

    string lowerName = toLowerCase(searchName);

    // Show matching products
    cout << "\nMatching Products\n";
    cout << "=========================================================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Qty" << endl;
    cout << "=========================================================\n";

    for (int i = 0; i < productCount; i++)
    {
        if (toLowerCase(products[i].name).find(lowerName) != string::npos)
        {
            found = true;

            cout << left
                 << setw(10) << products[i].id
                 << setw(25) << products[i].name
                 << setw(12) << products[i].price
                 << setw(10) << products[i].quantity
                 << endl;
        }
    }

    if (!found)
    {
        setColor(12);
        cout << "\nProduct Name not found!\n";
        setColor(7);
        break;
    }

    int deleteID;
    setColor(14);
    cout << "\nEnter Product ID to Delete : ";
    
    cin >> deleteID;
    setColor(7);

    bool idFound = false;

    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == deleteID)
        {
            idFound = true;

            cout << "\nProduct Found!\n";
            cout << "ID       : " << products[i].id << endl;
            cout << "Name     : " << products[i].name << endl;
            cout << "Price    : " << products[i].price << endl;
            cout << "Quantity : " << products[i].quantity << endl;
			setColor(14);
            cout << "\nAre you sure you want to delete this product? (Yes/No): ";
            cin >> confirm;
            setColor(7);

            if (toLowerCase(confirm) == "yes")
            {
                for (int j = i; j < productCount - 1; j++)
                {
                    products[j] = products[j + 1];
                }

                productCount--;
                saveProducts();
				setColor(10);
                cout << "\nProduct Deleted Successfully!\n";
                setColor(7);
            }
            else
            {
            	setColor(12);
                cout << "\nDelete Cancelled.\n";
                setColor(7);
            }

            break;
        }
    }

    if (!idFound)
    {
        setColor(12);
        cout << "\nInvalid Product ID!\n";
        setColor(7);
    }

    break;
}
    case 3:
        return;

    default:
        cout << "\nInvalid Choice!\n";
    }

    cout << "===========================================================\n";
}

// ---------------- STOCK IN / STOCK OUT ----------------
void stockInOut()
{
    if (productCount == 0)
    {
        cout << "\nNo Products Available!\n";
        return;
    }

    int choice;
	setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                 STOCK IN / STOCK OUT" << endl;
    cout << "===========================================================" << endl;
    setColor(7);
    setColor(14);
    cout << "1. Search by ID" << endl;
    cout << "2. Search by Name" << endl;
    cout << "3. Back" << endl;

    cout << "\nEnter Choice : ";
    cin >> choice;
    setColor(7);

    switch (choice)
    {
    // ================= SEARCH BY ID =================
    case 1:
    {
        int searchID;
        bool found = false;
		setColor(14);
        cout << "\nEnter Product ID : ";
        cin >> searchID;
        setColor(7);

        for (int i = 0; i < productCount; i++)
        {
            if (products[i].id == searchID)
            {
                found = true;
				setColor(10);
                cout << "\nProduct Found!\n";
                setColor(7);
                
                cout << "ID       : " << products[i].id << endl;
                cout << "Name     : " << products[i].name << endl;
                cout << "Price    : " << products[i].price << " Kyat" << endl;
                cout << "Quantity : " << products[i].quantity << endl;
				setColor(14);
                int action;
                cout << "\n1. Stock In" << endl;
                cout << "2. Stock Out" << endl;
                cout << "Enter Choice : ";
                cin >> action;
                setColor(7);

                int qty;
                string confirm;

                if (action == 1)
                {
                	setColor(14);
                    cout << "\nEnter Quantity to Add : ";
                    cin >> qty;
                    setColor(7);

                    if (qty <= 0)
                    {
                    	setColor(12);
                        cout << "\nInvalid Quantity! Quantity must be greater than 0.\n";
                        return;
                        setColor(7);
                    }
					setColor(14);
                    cout << "Confirm Stock In? (Yes/No) : ";
                    cin >> confirm;
                    setColor(7);

                    if (toLowerCase(confirm) == "yes")
                    {
                        int oldStock = products[i].quantity;
                        products[i].quantity += qty;
                        
                        saveProducts();
						setColor(10);
                        cout << "\nStock Added Successfully!\n";
                        setColor(7);
                        cout << "Previous Stock : " << oldStock << endl;
                        cout << "New Stock      : " << products[i].quantity << endl;
                    }
                    else
                    {
                    	setColor(12);
                        cout << "\nOperation Cancelled.\n";
                        setColor(7);
                    }
                }
                else if (action == 2)
                {
                	setColor(14);
                    cout << "\nEnter Quantity to Remove : ";
                    cin >> qty;
                    setColor(7);

                    if (qty <= 0)
                    {
                    	setColor(12);
                        cout << "\nInvalid Quantity! Quantity must be greater than 0.\n";
                        setColor(7);
                        return;
                    }

                    if (qty > products[i].quantity)
                    {
                    	setColor(12);
                        cout << "\nNot Enough Stock Available!\n";
                        setColor(7);
                        return;
                    }
					setColor(14);
                    cout << "Confirm Stock Out? (Yes/No) : ";
                    cin >> confirm;
                    setColor(7);

                    if (toLowerCase(confirm) == "yes")
                    {
                        int oldStock = products[i].quantity;
                        products[i].quantity -= qty;
						setColor(10);
                        cout << "\nStock Removed Successfully!\n";
                        setColor(7);
                        cout << "Previous Stock : " << oldStock << endl;
                        cout << "New Stock      : " << products[i].quantity << endl;
                    }
                    else
                    {
                    	setColor(12);
                        cout << "\nOperation Cancelled.\n";
                        setColor(7);
                    }
                }
                else
                {
                    cout << "\nInvalid Choice!\n";
                }

                break;
            }
        }

        if (!found)
        { 
        	setColor(12);
            cout << "\nProduct ID not found!\n";
            setColor(7);
        }

        break;
    }
    
    // ================= SEARCH BY NAME =================
    case 2:
{
    string searchName;
    bool found = false;

    cin.ignore();
	setColor(14);
    cout << "\nEnter Product Name to Search : ";
    getline(cin, searchName);
    setColor(10);

    string lowerName = toLowerCase(searchName);

	setColor(10);
    cout << "\nMatching Products\n";
    cout << "=========================================================\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Qty" << endl;
    cout << "=========================================================\n";
    setColor(7);

    for (int i = 0; i < productCount; i++)
    {
        if (toLowerCase(products[i].name).find(lowerName) != string::npos)
        {
            found = true;

            cout << left
                 << setw(10) << products[i].id
                 << setw(25) << products[i].name
                 << setw(12) << products[i].price
                 << setw(10) << products[i].quantity
                 << endl;
        }
    }


    if (!found)
    {
        setColor(12);
        cout << "\nProduct Name not found!\n";
        setColor(7);
        break;
    }


    int stockID;
	setColor(14);
    cout << "\nEnter Product ID : ";
    cin >> stockID;
    setColor(7);


    bool idFound = false;


    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == stockID)
        {
            idFound = true;

			setColor(10);
            cout << "\nProduct Found!\n";
            setColor(7);
            cout << "ID       : " << products[i].id << endl;
            cout << "Name     : " << products[i].name << endl;
            cout << "Price    : " << products[i].price << " Kyat" << endl;
            cout << "Quantity : " << products[i].quantity << endl;


            int action;
            setColor(14);
            cout << "\n1. Stock In" << endl;
            cout << "2. Stock Out" << endl;
            cout << "Enter Choice : ";
            setColor(7);
            cin >> action;


            int qty;
            string confirm;


            if (action == 1)
            {
            	setColor(14);
                cout << "\nEnter Quantity to Add : ";
                cin >> qty;


                if (qty <= 0)
                {
                	setColor(12);
                    cout << "\nInvalid Quantity!\n";
                    break;
                    
                }

				setColor(14);
                cout << "Confirm Stock In? (Yes/No) : ";
                cin >> confirm;
                setColor(7);


                if (toLowerCase(confirm) == "yes")
                {
                    int oldStock = products[i].quantity;

                    products[i].quantity += qty;

                    saveProducts();


                    setColor(10);
                    cout << "\nStock Added Successfully!\n";
                    setColor(7);


                    cout << "Previous Stock : " << oldStock << endl;
                    cout << "New Stock      : " << products[i].quantity << endl;
                }
                else
                {
                    setColor(12);
                    cout << "\nOperation Cancelled.\n";
                    setColor(7);
                }
            }


            else if (action == 2)
            {
            	setColor(14);
                cout << "\nEnter Quantity to Remove : ";
                cin >> qty;


                if (qty <= 0)
                {
                	setColor(12);
                    cout << "\nInvalid Quantity!\n";
                    break;
                }


                if (qty > products[i].quantity)
                {
                    cout << "\nNot Enough Stock Available!\n";
                    break;
                }

				setColor(14);
                cout << "Confirm Stock Out? (Yes/No) : ";
                cin >> confirm;
                setColor(7);


                if (toLowerCase(confirm) == "yes")
                {
                    int oldStock = products[i].quantity;

                    products[i].quantity -= qty;

                    saveProducts();


                    setColor(10);
                    cout << "\nStock Removed Successfully!\n";
                    setColor(7);


                    cout << "Previous Stock : " << oldStock << endl;
                    cout << "New Stock      : " << products[i].quantity << endl;
                }
                else
                {
                    setColor(12);
                    cout << "\nOperation Cancelled.\n";
                    setColor(7);
                }
            }

            else
            {
                cout << "\nInvalid Choice!\n";
            }


            break;
        }
    }


    if (!idFound)
    {
        setColor(12);
        cout << "\nInvalid Product ID!\n";
        setColor(7);
    }


    break;
}

    case 3:
        return;

    default:
        cout << "\nInvalid Choice!\n";
    }

    cout << "===========================================================\n";
}

void reports()
{
    int choice;

    do
    {
    	setColor(11);
        cout << "\n===========================================================" << endl;
        cout << "                      REPORTS" << endl;
        cout << "===========================================================" << endl;
        setColor(7);
        cout << "1. All Products Report" << endl;
        cout << "2. Low Stock Report" << endl;
        cout << "3. Out of Stock Report" << endl;
        cout << "4. Total Inventory Value" << endl;
        cout << "5. Back" << endl;
		setColor(14);
        cout << "\nEnter Choice : ";
        cin >> choice;
        setColor(7);

        switch(choice)
        {
            case 1:
                allProductsReport();
                break;

            case 2:
                lowStockReport();
                break;

            case 3:
                outOfStockReport();
                break;

            case 4:
                totalInventoryValue();
                break;

            case 5:
                return;

            default:
                cout << "\nInvalid Choice!\n";
        }

    }while(choice != 5);
}

void allProductsReport()
{
	setColor(11);
    cout << "\n================ ALL PRODUCTS REPORT ================\n";
    setColor(7);

    cout << left
         << setw(5) << "ID"
         << setw(22) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Qty"
         << endl;

    cout << "-----------------------------------------------------\n";

    for(int i=0;i<productCount;i++)
    {
        cout << left
             << setw(5) << products[i].id
             << setw(22) << products[i].name
             << setw(12) << products[i].price
             << setw(10) << products[i].quantity
             << endl;
    }
}

void lowStockReport()
{
    bool found=false;
	setColor(11);
    cout << "\n================ LOW STOCK REPORT ================\n";
    setColor(7);

    cout << left
         << setw(5) << "ID"
         << setw(22) << "Name"
         << setw(10) << "Qty"
         << endl;

    cout << "-----------------------------------------------\n";

    for(int i=0;i<productCount;i++)
    {
        if(products[i].quantity < 10)
        {
            found=true;

            cout << left
                 << setw(5) << products[i].id
                 << setw(22) << products[i].name
                 << setw(10) << products[i].quantity
                 << endl;
        }
    }

    if(!found)
    	setColor(12);
        cout << "No Low Stock Products.\n";
        setColor(7);
}

void outOfStockReport()
{
    bool found=false;
	setColor(11);
    cout << "\n=============== OUT OF STOCK REPORT ===============\n";
    setColor(7);

    cout << left
         << setw(5) << "ID"
         << setw(22) << "Name"
         << endl;

    cout << "-----------------------------------------\n";

    for(int i=0;i<productCount;i++)
    {
        if(products[i].quantity==0)
        {
            found=true;

            cout << left
                 << setw(5) << products[i].id
                 << setw(22) << products[i].name
                 << endl;
        }
    }

    if(!found)
    	setColor(12);
        cout << "No Out of Stock Products.\n";
        setColor(7);
}

void totalInventoryValue()
{
    double total=0;

    for(int i=0;i<productCount;i++)
    {
        total += products[i].price * products[i].quantity;
    }
	setColor(11);
    cout << "\n=====================================\n";
    cout << "     TOTAL INVENTORY VALUE\n";
    cout << "=====================================\n";
    setColor(7);

    cout << fixed << setprecision(0);
    cout << "Total Value : " << total << " Kyats\n";
}

// ---------------- LOGOUT ----------------
bool logout()
{
    string confirm;

    setColor(11);
    cout << "\n===========================================================" << endl;
    cout << "                         LOGOUT" << endl;
    cout << "===========================================================" << endl;
    setColor(7);
	setColor(14);
    cout << "Are you sure you want to logout? (Yes/No): ";
    cin >> confirm;
    setColor(7);

    confirm = toLowerCase(confirm);

    if (confirm == "yes")
    {
        setColor(10);
        cout << "\nLogging Out..." << endl;
        cout << "Thank you for using Inventory Management System!" << endl;
        setColor(7);

        return true;   // Logout successful
    }
    else if (confirm == "no")
    {
        setColor(12);
        cout << "\nLogout Cancelled!" << endl;
        setColor(7);

        return false;  // Stay in main menu
    }
    else
    {
        setColor(12);
        cout << "\nInvalid Choice! Returning to Main Menu..." << endl;
        setColor(7);

        return false;
    }
}
