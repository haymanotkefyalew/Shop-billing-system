#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

enum Status
{
    AVAILABLE,
    OUT_OF_STOCK
};

enum SortType
{
    NAME_A,
    NAME_D,
    PRICE_A,
    PRICE_D
};

struct Product
{
    std::string id;
    std::string name;
    std::string category;
    double price;
    unsigned int quantity;
    Status status;
};

struct ProductSales
{
    std::string id;
    std::string name;
    unsigned int unitsSold = 0;
    double sales = 0;
    double tax = 0;
};

struct ShopData
{
    unsigned int receiptCount = 0;
    unsigned int totalItemsSold = 0;
    double totalSales = 0;
    double totalTax = 0;
    std::vector<ProductSales> productSummary;
};

std::string normalizer(const std::string txt);
std::string inputString(const std::string msg);
template <typename T>
T inputNumber(const std::string msg, T min);
void loadProducts(std::vector<Product> &products, int &count, const char *file);
void loadCategories(std::vector<std::string> &categories);

void userMenu(std::vector<Product> &products, int &count, const char *file, int role, ShopData &data, std::vector<std::string> &categories);
void addProduct(std::vector<Product> &products, int &count, const char *file, std::vector<std::string> &categories);
void editProduct(std::vector<Product> &products, int count, const char *file);
void deleteProduct(std::vector<Product> &products, int &count, const char *file);
void viewProducts(std::vector<Product> &products, int count, bool hideOut, const std::vector<std::string> &categories, const std::string &filterCategory = "all");
void sortProducts(std::vector<Product> &products, int count);
void searchProducts(std::vector<Product> &products, int count, int role);

template <typename T>
int searchById(std::vector<T> &items, int count, const std::string &id);

void buyProduct(std::vector<Product> &products, int count, const char *file, ShopData &data, const std::vector<std::string> &categories);

void generateReceipt(const Product &products, int quantity, ShopData &data, const int count);

void saveProducts(std::vector<Product> &products, int count, const char *file);

int main()
{
    int productCount = 0;
    const char *fileName = "products.txt";

    std::vector<Product> products;
    ShopData shopdata;
    std::vector<std::string> categories;

    loadProducts(products, productCount, fileName);
    loadCategories(categories);
    int choice;
    do
    {
        std::cout << "\n=== SHOP BILLING SYSTEM ===\n";
        std::cout << "1. Seller\n2. Customer\n0. Exit\n";
        choice = inputNumber("Choose role: ", 0);
        switch (choice)
        {

        case 1:
            userMenu(products, productCount, fileName, 1, shopdata, categories);
            break;
        case 2:
            userMenu(products, productCount, fileName, 2, shopdata, categories);
            break;
        case 0:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid Input\n";
        }
    } while (choice != 0);
    return 0;
}

std::string normalizer(const std::string text)
{
    std::string normalizedTxt;
    for (char ch : text)
    {
        normalizedTxt += toupper(ch);
    }
    return normalizedTxt;
}
template <typename T>
T inputNumber(const std::string msg, T min)
{
    T x;
    while (true)
    {

        std::cout << msg;
        std::cin >> x;
        if (std::cin.fail() || x < min)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Try again.\n";
        }
        else
        {
            std::cin.ignore(1000, '\n');
            return x;
        }
    }
}
std::string inputString(const std::string msg)
{
    std::string s;
    std::cout << msg;
    std::getline(std::cin >> std::ws, s);
    return s;
}
void loadProducts(std::vector<Product> &products, int &count, const char *file)
{
    std::ifstream fin(file);
    static bool opened = false;
    if (!fin && opened)
    {
        std::cerr << "Failed to open product file.\n";
    }
    else if (!fin)
    {
        opened = true;
        return;
    }
    fin >> count;
    fin.ignore();
    products.clear();

    for (int i = 0; i < count; i++)
    {
        Product p;

        getline(fin, p.id);
        getline(fin, p.name);
        getline(fin, p.category);
        fin >> p.price;
        fin >> p.quantity;
        int st;
        fin >> st;
        p.status = static_cast<Status>(st);
        fin.ignore();

        products.push_back(p);
    }
    fin.close();
}
void loadCategories(std::vector<std::string> &categories)
{
    std::ifstream fin("categories.txt");
    static bool opened = false;
    if (!fin && opened)
    {
        std::cerr << "Failed to open categories file.\n";
        return;
    }
    else if (!fin)
    {
        opened = true;
        return;
    }
    std::string cat;

    while (getline(fin, cat))
    {
        categories.push_back(cat);
    }
    fin.close();
}

void addProduct(std::vector<Product> &products, int &count, const char *file, std::vector<std::string> &categories)
{
    Product p;
    std::string tempId;
    do
    {
        tempId = inputString("Enter product ID: ");
        if (searchById<Product>(products, count, tempId) == -1)
        {
            p.id = tempId;
            break;
        }
        std::cout << "NOTICE!! Product with the same ID exists.\n";
    } while (true);
    p.name = inputString("\nEnter product Name: ");

    std::cout << "Available categories:\n";
    int idx = 1;
    std::vector<std::string> catList(categories.begin(), categories.end());
    for (const auto &c : catList)
        std::cout << idx++ << ". " << c << std::endl;
    std::cout << idx << ". Add new category\n";
    int catChoice = inputNumber<int>("Choose category: ", 1);
    if (catChoice == idx)
    {
        p.category = inputString("Enter new category: ");
        p.category = normalizer(p.category);
        categories.push_back(p.category);
        std::ofstream fout("categories.txt", std::ios::app);
        if (!fout)
        {
            std::cerr << "Failed to open categories file.\n";
        }
        else
            fout << p.category << std::endl;
        fout.close();
    }
    else
    {
        p.category = catList[catChoice - 1];
    }
    p.price = inputNumber("\nEnter product Price: ", 0);
    p.quantity = inputNumber("\nEnter product Quantity: ", 0);
    p.status = (p.quantity > 0) ? AVAILABLE : OUT_OF_STOCK;

    products.push_back(p);
    count++;

    saveProducts(products, count, file);
}

void editProduct(std::vector<Product> &products, int count, const char *file)
{
    std::string tempId;
    tempId = inputString("\nEnter the Id of the product to edit: ");
    int index = searchById<Product>(products, count, tempId);
    if (index == -1)
    {
        std::cout << "Product not found.\n";
        return;
    }

    std::cout << "Product: " << products[index].name << "\nCategory: " << products[index].category
              << "\nPrice: " << products[index].price << " ETB\nAvailable Quantity: " << products[index].quantity << std::endl;
    std::cout << "Property to edit.\n";
    std::cout << "1.Name   2.Id   3.Price   4.Quantity  5.all\n";
    int choice;
    choice = inputNumber("Enter your choice:", 0);

    switch (choice)
    {
    case 1:
        products[index].name = inputString("\nNew name: ");
        break;
    case 2:

        products[index].id = inputString("\nNew Id: ");
        break;
    case 3:
        products[index].price = inputNumber("\nNew price: ", 0);
        break;
    case 4:
        products[index].quantity = inputNumber("\nNew quantity: ", 0);
        break;
    case 5:
        products[index].id = inputString("\nNew Id: ");
        products[index].name = inputString("\nNew name: ");
        products[index].price = inputNumber("\nNew price: ", 0);
        products[index].quantity = inputNumber("\nNew quantity: ", 0);
    default:
        std::cout << "\nInvalid input\n";
    }

    saveProducts(products, count, file);
}

void deleteProduct(std::vector<Product> &products, int &count, const char *file)
{
    std::string tempId;
    tempId = inputString("\nEnter the Id of the product to edit: ");
    int index = searchById<Product>(products, count, tempId);
    if (index == -1)
    {
        std::cout << "Product not found.\n";
        return;
    }

    char confirm;
    std::cout << "Are you sure you want to delete this product? (Y/N): ";
    std::cin >> confirm;
    std::cin.ignore();
    if (confirm != 'Y' && confirm != 'y')
    {
        std::cout << "Action canceled.\n";
        return;
    }
    products.erase(products.begin() + index);
    count--;

    saveProducts(products, count, file);
}

void viewProducts(std::vector<Product> &products, int count, bool hideOut, const std::vector<std::string> &categories, const std::string &filterCategory)
{
    bool hasProduct = false;
    for (int i = 0; i < count; i++)
    {
        if ((!hideOut || products[i].status == AVAILABLE) &&
            (filterCategory == "all" || normalizer(products[i].category) == normalizer(filterCategory)))
        {
            hasProduct = true;
            break;
        }
    }
    if (!hasProduct)
    {
        std::cout << "\nNo products available.\n";
        return;
    }
    std::cout << "\nID     Name            Category        Price(ETB)  Qty\n";
    std::cout << "-----------------------------------------------------\n";
    for (int i = 0; i < count; i++)
    {
        if ((hideOut && products[i].status == OUT_OF_STOCK))
            continue;
        if (filterCategory != "all" && normalizer(products[i].category) != normalizer(filterCategory))
            continue;
        std::cout << products[i].id << " "
                  << products[i].name << " "
                  << products[i].category << " "
                  << products[i].price << " "
                  << products[i].quantity << std::endl;
    }
}

void sortProducts(std::vector<Product> &products, int count)
{

    SortType type;
    std::cout
        << "Sort by: \n"
        << "1. Name(A-Z) 2. Name(Z-A) 3. Price(cheap-expensive) 4. Price(expensive-cheap) 0. Back\n";
    int s;
    s = inputNumber("Choose role: ", 0);
    if (s == 1)
        type = NAME_A;
    else if (s == 2)
        type = NAME_D;
    else if (s == 3)
        type = PRICE_A;
    else if (s == 4)
        type = PRICE_D;
    else
        return;

    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
        {
            if ((type == NAME_A && products[i].name > products[j].name) ||
                (type == PRICE_A && products[i].price > products[j].price))
            {
                std::swap(products[i], products[j]);
            }
            else if ((type == NAME_D && products[i].name < products[j].name) ||
                     (type == PRICE_D && products[i].price < products[j].price))
            {
                std::swap(products[i], products[j]);
            }
        }
}
void searchProducts(std::vector<Product> &products, int count, int role)
{
    bool found = false;
    std::string key = inputString("Enter product name or ID to search: ");
    std::cout << "\nID   Name            Category        Price(ETB)  Qty\n";
    std::cout << "-----------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        if (normalizer(products[i].id).find(normalizer(key)) != std::string::npos ||
            normalizer(products[i].name).find(normalizer(key)) != std::string::npos)
        {
            std::cout << products[i].id << " "
                      << products[i].name << " "
                      << products[i].category << " "
                      << products[i].price << " "
                      << products[i].quantity << std::endl;
            found = true;
        }
    }
    if (!found)
        std::cout << "No products found.\n";
}
template <typename T>
int searchById(std::vector<T> &items, int count, const std::string &id)
{
    for (int i = 0; i < count; i++)
        if (normalizer(items[i].id) == normalizer(id))
            return i;
    return -1;
}

void buyProduct(std::vector<Product> &products, int count, const char *file, ShopData &data, const std::vector<std::string> &categories)
{
    std::cout << "Available categories:\n";
    int idx = 1;
    std::vector<std::string> catList(categories.begin(), categories.end());
    for (const auto &c : catList)
        std::cout << idx++ << ". " << c << std::endl;
    std::cout << idx << ". All\n";
    while (true)
    {
        int catChoice = inputNumber<int>("Choose category to view products: ", 1);
        if (catChoice > idx)
        {
            std::cout << "Invalid Input!\n";
            continue;
        }
        else
        {
            std::string selectedCat = (catChoice == idx) ? "all" : catList[catChoice - 1];
            viewProducts(products, count, true, categories, selectedCat);
            break;
        }
    }
    std::string id = inputString("Enter product ID to buy: ");
    int i = searchById(products, count, id);
    if (i == -1 || products[i].status == OUT_OF_STOCK)
    {
        std::cout << "Product unavailable.\n";
        return;
    }
    std::cout << "Product: " << products[i].name << "\nCategory: " << products[i].category
              << "\nPrice: " << products[i].price << " ETB\nAvailable Quantity: " << products[i].quantity << std::endl;
    int qty = inputNumber<int>("Enter quantity: ", 1);
    if (qty > products[i].quantity)
    {
        std::cout << "Not enough stock.\n";
        return;
    }

    char confirm;
    std::cout << "Confirm purchase? (Y/N): ";
    std::cin >> confirm;
    std::cin.ignore();
    if (confirm != 'Y' && confirm != 'y')
    {
        std::cout << "Order canceled.\n";
        return;
    }

    products[i].quantity -= qty;
    if (products[i].quantity == 0)
        products[i].status = OUT_OF_STOCK;

    saveProducts(products, count, file);
}

void saveProducts(std::vector<Product> &products, int count, const char *file)
{
    std::ofstream fout(file);
    if (!fout)
    {
        std::cerr << "Failed to open product file.\n";
        return;
    }
    fout << count << "\n";
    for (int i = 0; i < count; i++)
    {
        fout << products[i].id << "\n"
             << products[i].name << "\n"
             << products[i].category << "\n"
             << products[i].price << "\n"
             << products[i].quantity << "\n"
             << products[i].status << "\n";
    }
    fout.close();
}

void generateReceipt(const Product &products, int quantity, ShopData &data, const int count)
{
}

void userMenu(std::vector<Product> &products, int &count, const char *file, int role, ShopData &data, std::vector<std::string> &categories)
{
    static int pass = 1234;
    static bool flag = true;
    int choice;
    do
    {

        if (role == 1)
        {
            while (flag)
            {
                int password = inputNumber<int>("Enter Password to continue: ", 0);
                if (password == pass)
                {
                    flag = false;
                    break;
                }
                else
                    std::cout << "Wrong password!\n";
            }
            std::cout << "\n--- SELLER MENU ---\n";
            std::cout << "1. Add Product\n2. Edit Product\n3. Delete Product\n4. View Products\n5. Sort Products\n6. Search Products\n7. View Summary\n8. Change Password\n0. Back\n";
            choice = inputNumber("Choose role: ", 0);

            switch (choice)
            {
            case 1:
                std::cout << "\nAdd product\n";
                addProduct(products, count, file, categories);
                break;

            case 2:
                std::cout << "\nEdit product\n";
                editProduct(products, count, file);
                break;
            case 3:
                std::cout << "\nDelete product\n";
                deleteProduct(products, count, file);
                break;
            case 4:
            {
                std::cout << "\nView products\n";
                std::cout << "Filter by category:\n"
                          << "1. All\n";
                int idx = 2;
                std::vector<std::string> catList(categories.begin(), categories.end());
                for (const auto &c : catList)
                    std::cout << idx++ << ". " << c << std::endl;
                while (true)
                {
                    int cChoice = inputNumber<int>("Choose: ", 1);
                    if (cChoice >= idx)
                    {
                        std::cout << "Invalid Input!\n";
                        continue;
                    }
                    else
                    {
                        std::string selCat = (cChoice == 1) ? "all" : catList[cChoice - 2];
                        viewProducts(products, count, false, categories, selCat);
                        break;
                    }
                }
                break;
            }
            case 5:
                std::cout << "\nSort products\n";
                sortProducts(products, count);
                break;
            case 6:
                std::cout << "\nSearch products\n";
                searchProducts(products, count, role);
                break;
            case 7:
                std::cout << "\nView summary\n";
                break;
            case 8:
            {
                std::cout << "\nChange password\n";

                int password = inputNumber<int>("Enter Old Password: ", 1000);
                if (password == pass)
                {
                    pass = inputNumber<int>("Enter New Password(at least 4 digit number): ", 1000);
                    std::cout << "Password changed successfully.\n";
                    break;
                }
                else
                    std::cout << "Wrong password!\n";
            }
            break;
            case 0:
                flag = true;
                break;
            default:
                std::cout << "Invalid Input!\n";
            }
        }
        else
        {

            std::cout << "\n--- CUSTOMER MENU ---\n";
            std::cout << "1. View Products\n2. Sort Products\n3. Buy Product\n4. Search Products\n0. Back\n";
            choice = inputNumber<int>("Choice: ", 0);

            switch (choice)
            {
            case 1:
            {
                std::cout << "Filter by category:\n"
                          << "1. All\n";
                int idx = 2;
                std::vector<std::string> catList(categories.begin(), categories.end());
                for (const auto &c : catList)
                {
                    std::cout << idx++ << ". " << c << std::endl;
                }
                while (true)
                {
                    int cChoice = inputNumber<int>("Choose: ", 1);
                    if (cChoice >= idx)
                    {
                        std::cout << "Invalid Input!\n";
                        continue;
                    }
                    else
                    {
                        std::string selCat = (cChoice == 1) ? "all" : catList[cChoice - 2];
                        viewProducts(products, count, true, categories, selCat);
                        break;
                    }
                }
            }
            break;
            case 2:
                sortProducts(products, count);
                break;
            case 3:
                buyProduct(products, count, file, data, categories);
                break;
            case 4:
                searchProducts(products, count, role);
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid Input!\n";
            }
        }
    } while (choice != 0);
}