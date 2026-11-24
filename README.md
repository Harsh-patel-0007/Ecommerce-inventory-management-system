# E-Commerce Inventory Management System

A menu-driven inventory management application developed in C as a Design and Analysis of Algorithms (DAA) project. The system manages products, handles inventory operations, processes orders, and demonstrates the practical implementation of various data structures and algorithms.

## Project Overview

The E-Commerce Inventory Management System is designed to simplify product and stock management. It allows users to add, search, update, sort and manage products while demonstrating the efficiency of different algorithms and data structures.

The project focuses on applying fundamental DAA concepts to a real-world inventory management scenario.

## Objectives

- Efficiently manage product records and inventory.
- Implement and compare multiple searching algorithms.
- Implement sorting algorithms for organizing products.
- Manage orders using appropriate data structures.
- Identify products with low stock levels.
- Analyse algorithm performance based on time complexity and execution time.

## ⚙️ Technologies Used

- Programming Language: C
- Compiler: GCC
- IDE: Visual Studio Code
- Concepts: Data Structures and Algorithms, File Handling, Algorithm Analysis

## 🧠 Data Structures & Algorithms Implemented

| Algorithm / Data Structure | Purpose | Average Time Complexity |
|---|---|---|
| Linear Search | Search for products sequentially | O(n) |
| Binary Search | Search in sorted product data | O(log n) |
| Hash Table | Efficient product lookup using IDs | O(1) |
| Binary Search Tree (BST) | Search and organize product records | O(log n)* |
| Merge Sort | Sort product records efficiently | O(n log n) |
| Bubble Sort | Demonstrate comparison-based sorting | O(n²) |
| Min Heap | Identify products with minimum stock | O(1) for minimum retrieval |
| Queue | Process orders in FIFO order | O(1) for enqueue/dequeue |

*BST complexity assumes a reasonably balanced tree. In the worst case, it can be O(n). Hash Table complexity is average-case and may also degrade to O(n) in the worst case.*

## Features

- Add new products to inventory.
- Display available product records.
- Search products using multiple searching algorithms.
- Sort products using different sorting techniques.
- Update product stock
