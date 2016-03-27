#include "map.h"
#include <string>

int main()
{
	int i;
	my::map<std::string, int> m;
	m.print();
	m["Moscow"] = 666;
	m["St Pi"] = 7;
	m["London"] = 8;
	m["Dubai"] = 33;
	m["Alexandria"] = 101;

	my::map<std::string, int> m2(m);
	m2.print();
	m2["New York"] = 1133;

	my::map<std::string, int>::iterator it;
	my::map<std::string, int>::iterator it_end;
	it = m.begin();
	it_end = m.end();

	std::cout << std::endl << "testing ++ and --" << std::endl;

	++it;
	std::cout <<"it->first=" << it->first << " it->second= " << it->second << std::endl;
	++it;
	std::cout <<"it->first=" << it->first << " it->second= " << it->second << std::endl;
	--it;
	std::cout <<"it->first=" << it->first << " it->second= " << it->second << std::endl;
	--it;
	std::cout <<"it->first=" << it->first << " it->second= " << it->second << std::endl;

	it = m.find("Moscow");
	std::cout <<"it->first= " << it->first << " it->second= " << it->second << std::endl;

	m.print();

	my::map<std::string, int> m3;

	std::pair<std::string, int> Ipair("Bejing", 55);
	m.insert2(Ipair);
	std::pair<std::string, int> Ipair2("Colombo", 321);
	m.insert2(Ipair2);
	std::pair<std::string, int> Ipair3("Colombo", 123);
	std::pair<bool, my::map<std::string, int>::iterator> pr1;
	pr1 = m.insert2(Ipair3);
	std::cout << "pr1 = " << pr1.first << std::endl;	// Colombo exists!
	
	std::cout << std::endl << "TESTING MIN" << std::endl;

	my::map<std::string, int>::iterator it1;
	it1 = m.min();
	std::cout << "min = " << it1->first;
	std::cout << " " << it1->second << std::endl;

	std::cout << std::endl << "TESTING MAX" << std::endl;

	my::map<std::string, int>::iterator it2;
	it2 = m.max();
	std::cout << "max = " << it2->first;
	std::cout << " " << it2->second << std::endl;

	std::cout << std::endl << " SIZE ="  << m.wsize() << std::endl;
	
	std::cout << std::endl << "TESTING ERASE" << std::endl;
	m.print();
	it = m.find("London");
	m.erase(it);
	it = m.find("St Pi");
	m.erase(it);
	it = m.find("Alexandria");
	m.erase(it);
	it = m.find("Bejing");
	m.erase(it);
	m.print();

	std::cout << std::endl << " SIZE ="  << m.wsize() << std::endl;

	int x;
	std::cin >> x;
	return 0;
}