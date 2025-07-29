#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree db;
    int choice;
    while (true) {
        std::cout << "\n--- Jewelry DB System ---\n";
        std::cout << "1. Insert\n2. Delete\n3. Search\n4. Display All\n5. Range Query\n6. Count\n0. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 0) break;

        int id, low, high;
        std::string name;
        double price;
        Record* rec;

        switch (choice) {
            case 1:
                std::cout << "Enter ID: "; std::cin >> id;
                std::cout << "Enter Name: "; std::cin >> name;
                std::cout << "Enter Price: "; std::cin >> price;
                db.insert({id, name, price});
                break;

            case 2:
                std::cout << "Enter ID to delete: "; std::cin >> id;
                db.remove(id);
                break;

            case 3:
                std::cout << "Enter ID to search: "; std::cin >> id;
                rec = db.search(id);
                if (rec)
                    std::cout << "Found -> Name: " << rec->name << ", Price: $" << rec->price << "\n";
                else
                    std::cout << "Record not found.\n";
                break;

            case 4:
                db.displayInOrder();
                break;

            case 5:
                std::cout << "Enter low and high ID range: ";
                std::cin >> low >> high;
                db.rangeQuery(low, high);
                break;

            case 6:
                std::cout << "Total records: " << db.count() << "\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
