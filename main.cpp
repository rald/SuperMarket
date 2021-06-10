#include <iomanip>
#include <iostream>
#include <vector>
#include <locale> 

template<class T>
std::string numberFormatWithCommas(T value){
    struct Numpunct: public std::numpunct<char>{
    protected:
        virtual char do_thousands_sep() const{return ',';}
        virtual std::string do_grouping() const{return "\03";}
    };
    std::stringstream ss;
    ss.imbue({std::locale(), new Numpunct});
    ss << std::setprecision(2) << std::fixed << value;
    return ss.str();
}

struct Product {
    int m_id;
    std::string m_name;
    double m_price;
    int m_qty;

		Product() {};

    Product(const int id,const std::string name,const double price,const int qty) : m_id(id), m_name(name), m_price(price), m_qty(qty){};
};

class SuperMarket {
public:
	void addProduct(Product product);
	void delProduct(int id);
	void removeProduct(int id);
	void listProducts();
	std::vector <Product> products {};
};


void SuperMarket::addProduct(Product product) {
	this->products.emplace_back(product);
};

void SuperMarket::delProduct(int id) {
	bool found=false;
	auto it=this->products.begin();
	while(it!=this->products.end()) {
		if(id==it->m_id) {
			this->products.erase(it);
			found=true;
			break;
		}
		it++;
	}
	if(found) {
		std::cout << "Product "	<< std::right << std::setfill('0') << std::setw(5) << id << " deleted" << std::endl;	
	} else {
		std::cout << "Product " << std::right << std::setfill('0') << std::setw(5) << id << " not found" << std::endl;
	}
};

void SuperMarket::listProducts() {
	if(this->products.size()==0) {
		std::cout << "No Products Found" << std::endl;
		return;
	}
	std::cout 
			<< std::left << std::setfill(' ')
			<< std::setw(5) << "ID" << ' '
			<< std::setw(16) << "Name" << ' '
			<< std::setw(12) << "Price" << ' '
			<< std::setw(12) << "Quantity"
			<< std::endl;
	for(const auto& i:this->products) {
	  std::cout 
			  << std::right << std::setfill('0') << std::setw(5) << i.m_id << ' '
			  << std::left << std::setfill(' ') << std::setw(16) << i.m_name << ' '
			  << std::right << std::setw(12) << std::fixed << std::showpoint << std::setprecision(2) << numberFormatWithCommas(i.m_price) << ' '
			  << std::right << std::setw(12) << std::fixed << std::showpoint << std::setprecision(2) << numberFormatWithCommas(i.m_qty)
			  << std::endl;
	}
}

SuperMarket sm;
std::string prompt="{=^.^=} enter command or type 'help' > ";
std::string cmd;
bool quit=false;

void doAdd() {
	Product product;
	bool found;
	
	std::cout << "*** Add Product ***" << std::endl;
	
	do {
	
		std::cout << "ID: "; std::cin >> product.m_id;

		found=false;
		auto it=sm.products.begin();
		while(it!=sm.products.end()) {
			if(product.m_id==it->m_id) {
				found=true;
				break;
			}
			it++;
		}
		if(found) {
			std::cout << "Product "	<< std::right << std::setfill('0') << std::setw(5) << product.m_id << " exists" << std::endl;	
		} 
		
	} while(found);
	
	std::cout << "Name: "; std::cin >> product.m_name;
	std::cout << "Price: "; std::cin >> product.m_price;
	std::cout << "Quantity: "; std::cin >> product.m_qty;
	
	sm.addProduct(product);
	
}

void doDel() {
	int id;
	std::cout << "*** Delete Product ***" << std::endl;
	std::cout << "ID: "; std::cin >> id;
	
	sm.delProduct(id);
}

void doList() {
	std::cout << "*** List Products ***" << std::endl;
	sm.listProducts();
}

void doHelp() {
	std::cout 
			<< "*** Help ***" << std::endl
			<< "help -> this help" << std::endl
			<< "add  -> add a product" << std::endl
			<< "del  -> delete a product by id" << std::endl
			<< "list -> list all products" << std::endl
			<< "quit -> quit program" << std::endl;
}

int main(void) {
	
	while(!quit) {
		std::cout << prompt;
		std::cin >> cmd;
		if(cmd=="quit") {
			quit=true;
		} else if(cmd=="help") {
			doHelp();
		} else if(cmd=="add") {
			doAdd();
		} else if(cmd=="del") {
			doDel();
		} else if(cmd=="list") {
			doList();
		}
	}

	std::cout << "Bye!" << std::endl;

	return 0;
}
