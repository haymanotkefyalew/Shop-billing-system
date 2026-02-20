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

struct ShopeData
{
    unsigned int receiptCount = 0;
    unsigned int totalItemsSold = 0;
    double totalSales = 0;
    double totalTax = 0;
    std::vector<ProductSales> productSummary;
};

int main()
{

    return 0;
}