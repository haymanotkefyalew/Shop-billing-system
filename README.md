# 🧾 Shop Billing System (C++)

A **console-based shop inventory and billing system** built using **C++ and file handling**.
The application allows **sellers to manage inventory** and **customers to browse and purchase products**, while automatically generating receipts and tracking sales.

This project demonstrates practical use of **data structures, file I/O, searching, sorting, and modular programming**.

---

## 🚀 Features

### 👨‍💼 Seller (Admin)

- Add new products
- Edit product details
- Delete products
- View products
- Filter products by category
- Sort products
- Search products by ID or name
- View shop sales summary
- Change admin password

### 🛒 Customer

- View available products
- Filter products by category
- Sort products by name or price
- Search products
- Purchase products
- Automatically generate receipt

---

## 🧠 System Concepts Used

This project demonstrates several important C++ programming concepts:

- Structs
- Enums
- Templates
- Vectors (STL)
- File handling
- Searching algorithms
- Sorting algorithms
- Input validation
- Modular function design
- Console UI formatting

---

## 📂 Project Structure

```
Shop-Billing-System/
│
├── main.cpp
├── products.txt
├── categories.txt
├── receipts.txt
└── README.md
```

### File Description

| File             | Description                                  |
| ---------------- | -------------------------------------------- |
| `main.cpp`       | Main source code containing all system logic |
| `products.txt`   | Stores product inventory                     |
| `categories.txt` | Stores product categories                    |
| `receipts.txt`   | Stores generated receipts                    |
| `README.md`      | Project documentation                        |

---

## 🗃️ Data Storage

### Products File (`products.txt`)

The system stores product data in the following format:

```
number_of_products
product_id
product_name
category
price
quantity
status
```

Example:

```
2
P001
Soap
HYGIENE
15
10
0
P002
Bread
FOOD
8
20
0
```

Status values:

| Value | Meaning      |
| ----- | ------------ |
| 0     | Available    |
| 1     | Out of Stock |

---

## 🧾 Receipt Generation

When a customer buys a product the system:

1. Calculates **subtotal**
2. Applies **15% tax**
3. Calculates **total price**
4. Prints receipt to console
5. Saves receipt to `receipts.txt`

Example receipt:

```
=== RECEIPT ===
Receipt ID: R000001
Time: Wed Mar 11 00:16:43 2026
Product: Bread
Quantity: 2
Price per unit: 8.00 ETB
Subtotal: 16.00 ETB
Tax: 2.40 ETB
Total: 18.40 ETB
```

---

## 📊 Seller Summary

The seller can view:

- Total items sold
- Total sales amount
- Total tax collected
- Sales per product

Example output:

```
=== SELLER SUMMARY PER PRODUCT ===
ID   Name       Units Sold   Sales(ETB)   Tax(ETB)

P001 Soap       10           150          22.5
P002 Bread      5            40           6
```

---

## 🔐 Seller Authentication

Default password:

```
1234
```

The seller can **change the password from the menu**.

---

## 📌 Program Workflow

```
Start Program
     │
Choose Role
     │
 ┌─────────────┬─────────────┐
 │             │             │
Seller      Customer        Exit
 │             │
Manage        Browse
Products      Products
 │             │
View Summary   Buy Product
```

---

## 🛠 Possible Improvements

Future enhancements could include:

- Multi-product cart system
- Persistent sales statistics
- Database integration (MySQL / SQLite)
- Graphical user interface (GUI)
- Barcode scanning
- Login system with multiple sellers
- Advanced sorting algorithms

---

## 📚 Learning Purpose

This project is ideal for learning:

- Intermediate **C++ programming**
- **File handling systems**
- **Inventory management logic**
- **Billing system design**

---

## 👨‍💻 Author

### Haymanot Kefyalew

---

⭐ If you find this project useful, consider giving it a **star** on GitHub.

---
