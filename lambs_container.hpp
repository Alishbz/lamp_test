/****************************************************************************************
* ALI SAHBAZ
*
*
* Date          : 20.02.2024
* By            : Ali Þahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#pragma once 
#include <map>
#include <stdexcept>

/** incomplete types  **/ 
class lamb_x_base;
class lamb_y_base;
class lamb_z_base;
 
class lamb_container  {

public:

	lamb_container( )  {}

	~lamb_container() = default;

	/**********/

	bool add(int _index , lamb_x_base& new_lamb) {
		 
		lambs.emplace(_index, new_lamb);
	 
		return true;
	}

	lamb_x_base& get(int _index) {
		auto it = lambs.find(_index);

		if (it == lambs.end()) {
			throw std::out_of_range("map err");
		}

		return it->second;
	}
	 

private:

	std::map<int, lamb_x_base> lambs;
};