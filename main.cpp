#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

void loadProducts(std::vector<Product> &products, int &count, const char *file);
void loadCategories(std::vector<std::string> &categories);

void userMenu(std::vector<Product> &products, int &count, const char *file, int role, ShopData &data, std::vector<std::string> &categories);
void addProduct(std::vector<Product> &products, int &count, const char *file, std::vector<std::string> &categories);
void editProduct(std::vector<Product> &products, int count, const char *file);
void deleteProduct(std::vector<Product> &products, int &count, const char *file);
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
        std::cout << "Choose role: ";
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

void loadProducts(std::vector<Product> &products, int &count, const char *file)
{
    std::ifstream fin(file);

    fin >> count;

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
    std::cout << "\nEnter product Id: ";
    std::getline(std::cin, p.id);
    std::cout << "\nEnter product Name: ";
    std::getline(std::cin, p.name);
    std::cout << "\nEnter product Category: ";
    std::getline(std::cin, p.category);
    std::cout << "\nEnter product Price: ";
    std::cin >> p.price;
    std::cout << "\nEnter product Quantity: ";
    std::cin >> p.quantity;
    p.status = (p.quantity > 0) ? AVAILABLE : OUT_OF_STOCK;

    products.push_back(p);
    count++;
}

void editProduct(std::vector<Product> &products, int count, const char *file)
{
    std::string tempId;
    std::cout << "\nEnter the Id of the product to edit: ";
    std::getline(std::cin, tempId);
    int index;

    for (int i = 0; i < count; i++)
    {
        if (products[i].id == tempId)
        {
            index = i;
        }
        else
        {
            std::cout << "\nProduct not found!\n";
            return;
        }
    }
    std::cout << "Product: " << products[index].name << "\nCategory: " << products[index].category
              << "\nPrice: " << products[index].price << " ETB\nAvailable Quantity: " << products[index].quantity << std::endl;
    std::cout << "Property to edit.\n";
    std::cout << "1.Name   2.Id   3.Price   4.Quantity  5.all\n";
    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "\nNew name: ";
        std::getline(std::cin, products[index].name);
        break;
    case 2:
        std::cout << "\nNew Id: ";
        std::getline(std::cin, products[index].id);
        break;
    case 3:
        std::cout << "\nNew price: ";
        std::cin >> products[index].price;
        break;
    case 4:
        std::cout << "\nNew quantity: ";
        std::cin >> products[index].quantity;
        break;
    case 5:
        std::cout << "\nNew Id: ";
        std::getline(std::cin, products[index].id);
        std::cout << "\nNew name: ";
        std::getline(std::cin, products[index].name);
        std::cout << "\nNew price: ";
        std::cin >> products[index].price;
        std::cout << "\nNew quantity: ";
        std::cin >> products[index].quantity;
    default:
        std::cout << "\nInvalid input\n";
    }
}

void deleteProduct(std::vector<Product> &products, int &count, const char *file) {}
void userMenu(std::vector<Product> &products, int &count, const char *file, int role, ShopData &data, std::vector<std::string> &categories)
{
    int choice;
    do
    {

        if (role == 1)
        {
            std::cout << "\n--- SELLER MENU ---\n";
            std::cout << "1. Add Product\n2. Edit Product\n3. Delete Product\n4. View Products\n5. Sort Products\n6. Search Products\n7. View Summary\n8. Change Password\n0. Back\n";
            std::cout << "Choice: ";
            std::cin >> choice;

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
                std::cout << "\nView products\n";
                break;
            case 5:
                std::cout << "\nSort products\n";
                break;
            case 6:
                std::cout << "\nSearch products\n";
                break;
            case 7:
                std::cout << "\nView summary\n";
                break;
            case 8:
                std::cout << "\nChange password\n";
                break;
            default:
            }
        }
        else
        {
        }
    } while (choice != 0);
}