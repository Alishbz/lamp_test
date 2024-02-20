/****************************************************************************************
* ALI SAHBAZ
*
*
* Date          : 20.02.2024
* By            : Ali Þahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#pragma once 
 
/** application mocking ***/

template <typename T>
class app_lamb : public T{

public:
	 
	app_lamb(int _id):T(_id) {}

	~app_lamb() = default;

	void my_led_on() { this->on(); }

	void my_led_off() { this->off(); }

	/*** do your state machine here ***/
};