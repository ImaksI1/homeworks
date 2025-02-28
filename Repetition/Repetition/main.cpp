#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
class Order {
private:
	string orderID;
	string customerName;
	vector<string> items;
	double totalAmount;
public:
	Order(string orderID, string customerName, vector<string> items, double totalAmount) {
		this->orderID = orderID;
		this->customerName = customerName;
		this->items = items;
		this->totalAmount = totalAmount;
	}

	string getOrderID() { return orderID; }
	string getCustomerName() { return customerName; }
	vector<string> getItems() { return items; }
	double getTotalAmount() { return totalAmount; }

	void setCustomerName(const string& customerName) { this->customerName = customerName; }
	void setItems(const vector<string>& items) { this->items = items; }
	void setTotalAmount(double totalAmount) { this->totalAmount = totalAmount; }
};

void printOrder(Order* order) {
	if (order == nullptr) {
		cout << "Order not found!" << endl;
		return;
	}
	cout << "Order ID: " << order->getOrderID() << endl;
	cout << "Customer name: " << order->getCustomerName() << endl;
	cout << "Items: " << endl;
	for (string item : order->getItems()) {
		cout << item << endl;
	}
	cout << order->getTotalAmount() << endl << endl;
}
void printAllOrders(vector<Order*> orders) {
	for (Order* order : orders) {
		printOrder(order);
	}
}

Order* findByID(vector<Order*> orders, const string& orderID) {
	auto it = find_if(orders.begin(), orders.end(), [orderID](Order* order) {
		return order->getOrderID() == orderID;
		});
	if (it != orders.end()) {
		return *it;
	}
	else {
		return nullptr;
	}
}

void addOrder(vector<Order*>& orders, const string& orderID, const string& customerName, const vector<string>& items, double totalAmount) {
	if (findByID(orders, orderID) != nullptr) {
		cout << "Order with ID " << orderID << " already exists!" << endl;
		return;
	}
	Order* order = new Order(orderID, customerName, items, totalAmount);
	orders.push_back(order);
	cout << "Order added!" << endl;
}

void deleteOrder(vector<Order*>& orders, const string& orderID) {
	auto it = find_if(orders.begin(), orders.end(), [orderID](Order* order) {
		return order->getOrderID() == orderID;
		}); // ще раз написав find_if бо findByID повертає вказівник на об'єкт Order, а у erase потрібен ітератор
	if (it != orders.end()) {
		orders.erase(it);
		cout << "Order deleted!" << endl;
		return;
	}
	cout << "Order not found!" << endl;
}

void filterByName(vector<Order*> orders, const string& customerName) {
	bool isFound = false;
	for_each(orders.begin(), orders.end(), [customerName, &isFound](Order* order) {
		if (order->getCustomerName() == customerName) {
			cout << "Orders by " << customerName << ": " << endl;
			printOrder(order);
			isFound = true;
		}
		});
	if (!isFound) {
		cout << "Orders by " << customerName << " not found!" << endl;
	}
}

void sortByTotalAmount(vector<Order*>& orders) {
	sort(orders.begin(), orders.end(), [](Order* a, Order* b) {
		return a->getTotalAmount() < b->getTotalAmount();
		});
}

void editOrder(vector<Order*>& orders, const string& orderID, const string& customerName, const vector<string>& items, double totalAmount) {
	Order* order = findByID(orders, orderID);
	if (order != nullptr) {
		order->setCustomerName(customerName);
		order->setItems(items);
		order->setTotalAmount(totalAmount);
		cout << "Order edited!" << endl;
		return;
	}
	cout << "Order not found!" << endl;
}

void loadOrders(vector<Order*>& orders, const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "File not found!" << endl;
		return;
	}
	string orderID, customerName, item;
	double totalAmount;
	vector<string> items;
	while (file >> orderID >> customerName >> totalAmount) {
		items.clear();
		while (file >> item && item != "end") {
			items.push_back(item);
		}
		addOrder(orders, orderID, customerName, items, totalAmount);
	}
	file.close();
}

void saveOrders(vector<Order*> orders, const string& filename) {
	ofstream file(filename);
	for (Order* order : orders) {
		file << order->getOrderID() << " " << order->getCustomerName() << " " << order->getTotalAmount() << endl;
		for (string item : order->getItems()) {
			file << item << " ";
		}
		file << "end" << endl;
	}
	file.close();
}

int main() {
	vector<Order*> orders;
	loadOrders(orders, "orders.txt");
	addOrder(orders, "ORD001", "Bob", { "phone", "laptop" }, 1000);
	addOrder(orders, "ORD002", "Patrik", { "PC", "monitor" }, 600);
	addOrder(orders, "ORD003", "Bob", { "TV", "airpods" }, 300);
	printAllOrders(orders);
	cout << "Find by ID: " << endl;
	printOrder(findByID(orders, "ORD003"));
	deleteOrder(orders, "ORD003");
	printAllOrders(orders);
	filterByName(orders, "Bob");
	sortByTotalAmount(orders);
	cout << "after sorting: " << endl;
	printAllOrders(orders);
	editOrder(orders, "ORD001", "Alice", { "phone", "laptop" }, 1000);
	printAllOrders(orders);
	saveOrders(orders, "orders.txt");
}