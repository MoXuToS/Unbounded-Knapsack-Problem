//===========================================================
// A tourist, going on a hike, buys products in indivisible
// packages of known weight Cj and caloric content aj, j = 1..n.
// The number of products of each type can be bought no more than dj
// packages, j = 1..n.
// Define a plan so that the calorie content is not lower than
// To kilocalories, and the total weight was minimal
//===========================================================
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<time.h>
#include<algorithm>
#include <ctime>
#include<fstream>
#include<stdio.h>

using namespace std;
//===========================================================
// class of products chosen by the tourist
class Product
{
private:
    int Weight_; // Weight of product
    int Calories_; // Calories of product
    int Avaliable_; // Avalieble counts of product
    string Name_of_Product;
public:
    // constructor
    Product(int Cj, int Aj, int Dj, string Name)
    {
        Weight_ = Cj;
        Calories_ = Aj;
        Avaliable_ = Dj;
        Name_of_Product = Name;
    };
    void Show_Products(vector<Product>& Products);
    int Max_Weight_of_Products(vector<Product>&);
    int Solution(vector<vector<int> >&,
                 vector<Product>&, int, int, int);
    // Sort by Calories
    void Sort(vector<Product>&, vector<int>&);
    // search best combination
    void findAns(int k, int s, vector<vector<int> >&,
                 vector<Product>, vector<int>&, int);
    void As_Taken_Products(vector<int>&, vector<int>&,
                           vector<int>&, vector<Product>);
    void Save_Input_Information(vector<Product>&);
};
//===========================================================
// Fill result table
void Fill_Products(vector<Product>&,
                   vector<int>, vector<int>&);
//===========================================================
int randomize_Callorias()
{
    return rand() % 400 + 100;
}

int randomize()
{
    return rand() % 10 + 1;
}
int minimal(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}
int maximum(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
void fill_by_input_format(int& choise, vector<int>& choises,
                          vector<int>& Aj, vector<Product>& Products)
{
    // 0 - random generation
    // 1 - handle generaion
    // 2 - from file
    cin >> choise;
    choises.push_back(choise);
    // from keyboard yes or no
    switch (choise)
    {
    case 0:
        // Fill information
        Fill_Products(Products, choises, Aj);
        break;
    case 1:
        cout << "\nDo your products contain unique"
             << " name ? \n"
             << "1 - The name is unique. For example: Banana \n"
             << "0 - The name is not unique.\n" << endl;
        cin >> choise;
        choises.push_back(choise);
        // Fill information
        Fill_Products(Products, choises, Aj);
        break;
    case 2:
        choise = 1;
        choises.push_back(choise);
        // Fill information
        Fill_Products(Products, choises, Aj);
        break;
    default:
        cout << "Wrong entry, please try again\n";
        break;
    }
}
// Fill information
void Fill_Products(vector<Product>& Products, vector<int> Choise,
                   vector<int>& Aj_)
{
    int Cj{}, Aj{}, Dj{}; // weight, calories, count
    switch (Choise[1])
    {
    case 0: // without keyboard
        for (size_t i = 1; i <= Choise[0]; i++)
        {
            // Remembering calories
            Aj_.push_back(randomize_Callorias());
            Products.push_back(Product(randomize(),
                                       Aj_[i - 1], randomize(),
                                       to_string(i)));
        }
        break;
    case 1: // from keyboard
        switch (Choise[2])
        {
        case 0: // non-Unique name
            cout << "Enter in turn: \n"
                 << "Weight, Calories, Count\n";
            for (size_t i = 1; i <= Choise[0]; i++)
            {
                cin >> Cj >> Aj >> Dj;
                Products.push_back(Product(Cj, Aj, Dj,
                                           to_string(i)));
                Aj_.push_back(Aj);
            }
            break;
        case 1: // Unique name
            string name = ""; // Name of product
            cout << "Enter in turn: \n"
                 << "Weight, Calories, Count, "
                 << "Name \n";
            for (size_t i = 1; i <= Choise[0]; i++)
            {
                cin >> Cj >> Aj >> Dj >> name;
                Products.push_back(Product(Cj, Aj, Dj, name));
                Aj_.push_back(Aj);
            }
            break;
        }
        break;
    case 2: // from file
        ifstream out;
        out.open("out.txt");
        string name = ""; // product name
        getline(out, name);
        if (stoi(name) < Choise[0])
        {
            Choise[1] = 0;
            cout << "\nRANDOM GENERATION IS USED,"
                 << "BECAUSE THERE ARE NOT ENOUGH PRODUCTS IN THE FILE.\n";
            Fill_Products(Products, Choise, Aj_);
            break;
        }
        for (size_t i = 0; i < Choise[0]; i++)
        {
            getline(out, name, ' ');
            Cj = stoi(name);
            getline(out, name, ' ');
            Aj = stoi(name);
            getline(out, name, ' ');
            Dj = stoi(name);
            getline(out, name);
            Products.push_back(Product(Cj, Aj, Dj, name));
            Aj_.push_back(Aj); // helping with sorting
        }
    }
}
// watching list of products
void watch_products(int& choise, vector<Product> Products,
                    Product Initializator)
{
    // 0 - no
    // 1 - yes
    cin >> choise;
    // watching
    switch (choise)
    {
    case 0:
        break;
    case 1:
        // watching products list
        Initializator.Show_Products(Products);
    }
}
// dialog with user
void dialogue(int& choise, int& Required_calories,
              vector<int>& choises, vector<Product>& Products,
              vector<int>& Aj, Product Initializator)
{
    cout << "\nEnter the required number of kilocalories" << endl;
    cin >> Required_calories;
    Required_calories *= 1000;
    cout << "\nChoose a data entry method: \n"
         << "0 - Machine random input \n"
         << "1 - Keyboard input \n"
         << "2 - Restoration of previously entered data \n\n";
    fill_by_input_format(choise, choises, Aj, Products);
    cout << "\nDo you want to see the created product table? \n"
         << "1 - Yes \n"
         << "0 - No \n\n";
    watch_products(choise, Products, Initializator);
    cout << "\n\nDo you want to save the entered data?\n"
         << "1 - yes, save\n"
         << "0 - no, don't\n\n";
    cin >> choise;
    if (choise == 1)
        Initializator.Save_Input_Information(Products);
}

//===========================================================
// Show table of products
void Product::Show_Products(vector<Product>& Products)
{
    cout << setw(40) << "PRODUCT INFORMATION" << endl;
    for (size_t i = 0; i < 59; i++)
        cout << "-";
    cout << endl;
    cout << "|" << setw(10) << "Name"
         << setw(4) << "|" << setw(5) << "Weight"
         << setw(4) << "|" << setw(15) << "Calories"
         << setw(4) << "|" << setw(12) << "Count"
         << setw(4) << "|" << endl;
    for (size_t i = 0; i < 59; i++)
        cout << "-";
    cout << endl;
    for (size_t i = 0; i < Products.size(); i++)
    {
        cout << "|" << setw(10) << internal
             << Products[i].Name_of_Product
             << setw(4) << "|" << setw(5)
             << Products[i].Weight_
             << setw(4) << "|" << setw(15)
             << Products[i].Calories_
             << setw(4) << "|" << setw(12)
             << Products[i].Avaliable_
             << setw(4) << "|" << endl;
        for (size_t i = 0; i < 59; i++)
            cout << "-";
        cout << endl;
    }
}
// Finding max weight
int Product::Max_Weight_of_Products(vector<Product>& Products)
{
    int max_weight = 0; // maximum
    int max_calories = 0;
    for (size_t i = 0; i < Products.size(); i++)
        // take all products
        max_weight += Products[i].Weight_ * Products[i].Avaliable_;
    return max_weight;
}
// Sort by increasing calories
void Product::Sort(vector<Product>& Products, vector<int>& Product_Calories)
{
    int temp;
    string temp_string;
    for (size_t i = 0; i < Product_Calories.size(); i++)
    {
        auto min = min_element(Product_Calories.begin() + i, Product_Calories.end());
        int index_min_element = min - Product_Calories.begin();
        // rearrange calories
        temp = Product_Calories[i];
        Product_Calories[i] = Product_Calories[index_min_element];
        Product_Calories[index_min_element] = temp;
        // rearrange weight
        temp = Products[i].Weight_;
        Products[i].Weight_ = Products[index_min_element].Weight_;
        Products[index_min_element].Weight_ = temp;
        // rearrange calories
        temp = Products[i].Calories_;
        Products[i].Calories_ = Products[index_min_element].Calories_;
        Products[index_min_element].Calories_ = temp;
        // rearrange Products count
        temp = Products[i].Avaliable_;
        Products[i].Avaliable_ = Products[index_min_element].Avaliable_;
        Products[index_min_element].Avaliable_ = temp;
        // rearrange postion
        temp_string = Products[i].Name_of_Product;
        Products[i].Name_of_Product = Products[index_min_element].Name_of_Product;
        Products[index_min_element].Name_of_Product = temp_string;
    }
}

// Solution of task
int Product::Solution(vector<vector<int>>& table_w_c,
                      vector<Product>& Products, int n, int required, int max_weight)
{
    int min_weight{ INT32_MAX }; // minimal Weight
    int required_min = 0; // minimum number of calories 
    // achieved by us
    for (size_t i = 0; i <= max_weight; i++)
        table_w_c[0].push_back(0); // fill the first line with zeros
    for (size_t i = 1; i <= Products.size(); i++)
    {
        table_w_c[i].push_back(0); // first column matching
         // 0 kg of weight, fill with zeros
         // since the object weighs something
         // count from weight to unit
        for (size_t k = 1; k <= max_weight; k++)
        {
            // throw in the previous value
            table_w_c[i].push_back(table_w_c[i][k - 1]);
            // up to the possible number of items taken
            for (size_t l = minimal(Products[i - 1].Avaliable_,
                                    k / Products[i - 1].Weight_); l != 0; l--)
                // maximum between previous and previous
                // subject to weight available weight - weight possible
                // taken items +
                // same calorie content
                table_w_c[i][k] = maximum(table_w_c[i][k],
                                          table_w_c[i - 1][k - l * Products[i - 1].Weight_] + Products[i - 1].Calories_ * l);
            // is the condition true
            if (table_w_c[i][k] >= required)
            {
                if (required_min == 0)
                    required_min = table_w_c[i][k];
                max_weight = k;
                break;
            }
        }
    }
    // checking whether we have found the minimum possible weight
    if (required_min == 0)
        return 0;
    else
        return max_weight;
}
// looking for the composition of the taken items
void Product::findAns(int k, int s, vector<vector<int>>& Table,
                      vector<Product> Products, vector<int>& number_of_product,
                      int requiremed)
{
    // k - number of product
    // s - minimal weight
    for (k; k != 0; k--)
    {
        for (size_t l = minimal(Products[k - 1].Avaliable_, s / Products[k - 1].Weight_); l != 0; l--)
        {
            number_of_product.push_back(k);
            s -= Products[k - 1].Weight_;
        }
        if (s == 0)
            break;
    }
}
// counts how many took this or that item
void Product::As_Taken_Products(vector<int>& number_of_Products,
                                vector<int>& Taken, vector<int>& Product_Number,
                                vector<Product> Products)
{
    for (size_t i = 0; i < number_of_Products.size(); i++)
    {
        Product_Number.push_back(number_of_Products[i]);
        Taken.push_back(1);
        if (i + 1 >= number_of_Products.size())
            break;
        while (number_of_Products[i] == number_of_Products[i + 1])
        {
            Taken[Taken.size() - 1] += 1;
            ++i;
            if (i + 1 >= number_of_Products.size())
                break;
        }
    }
    cout << "\n";
    cout << "\n";
    for (size_t i = 0; i < 59; i++)
        cout << "-";
    cout << "\n|" <<
         setw(40) << "The following items were taken"
         << setw(19) << "|\n";
    for (size_t i = 0; i < 59; i++)
        cout << "-";
    cout << "\n|" <<
         setw(20) << "Item name"
         << setw(10) << "|" << setw(19)
         << "Quantity" << setw(10) << "|\n";
    for (size_t i = 0; i < 59; i++)
        cout << "-";
    for (size_t i = 0; i < Product_Number.size(); ++i)
    {
        cout << "\n|" << setw(15)
             << Products[Product_Number[i] - 1].Name_of_Product
             << setw(15) << "|" << setw(15) << Taken[i] << setw(14)
             << "|\n";
        for (size_t i = 0; i < 59; i++)
            cout << "-";
    }
}

// saving entered data
void Product::Save_Input_Information(vector<Product>& Products)
{
    ofstream out("out.txt");
    out << Products.size() << endl;
    for (size_t i = 0; i < Products.size(); i++)
    {
        out << Products[i].Weight_ << " " << Products[i].Calories_
            << " " << Products[i].Avaliable_
            << " " << Products[i].Name_of_Product;
        out << endl;
    }
}
//===========================================================

int main()
{
    system("color F0");
    system("chcp 1251"); // Russian language in the console
    srand(time(0));
    int Required_calories{}; // required calories
    int min_weight{ 0 }; // minimum weight that satisfies
    // conditions
    vector<int> choises; // all user choices
    int choise{ 0 }; // user choice
    int max_weight{ 0 }; // maximum weight of one product
    vector<Product> Products; // vector containing
    // product information
    Product Initializator(0, 0, 0, "0"); // Launches
    // class functions
    vector<int> Aj;
    int n{ 0 }; // number of products
    cout << "Enter the number of products: \n";
    cin >> choise;
    choises.push_back(choise);
    n = choise; // fixed the number of products
    vector<vector<int>> Table(n + 1); // table of weight values
    // and calories
    dialogue(choise, Required_calories, choises, Products, Aj, Initializator);
    clock_t start = clock(); // main processing started, started
    // measure running time
    // find the maximum weight of one item taken by the maximum
    // number of times
    max_weight = Initializator.Max_Weight_of_Products(Products);
    // sort the array by increasing number of calories
    Initializator.Sort(Products, Aj);
    //find the answer for the task
    min_weight = Initializator.Solution(Table, Products, n,
                                        Required_calories, max_weight);
    if (min_weight == 0)
    {
        cout << "\nIt is impossible to collect such a combination of items,"
             << "to reach the desired number of calories.\n";
        return 0;
    }
    cout << "\nThe minimum weight of products will be: " << min_weight;
    // We are looking for the number of the item under which the condition is met
    for (n; n != 0; n--)
        if (Table[n][min_weight] >= Required_calories)
            // condition met
            break;
    vector<int> number_of_product;
    vector<int> taken;
    vector<int> product_Number;
    Initializator.findAns(n, min_weight, Table, Products,
                          number_of_product, Required_calories);
    Initializator.As_Taken_Products(number_of_product, taken,
                                    product_Number, Products);
    clock_t end = clock(); // end of program
    cout << "\n\nProgram running time:"
         << (double)(end - start) / CLOCKS_PER_SEC << endl;
    return 0;
}
