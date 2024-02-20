/****************************************************************************************
* ALI SAHBAZ
*
*
* Date          : 20.02.2024
* By            : Ali Þahbaz
* e-mail        : ali_sahbaz@outlook.com
*/  
#pragma once 

#include <functional>

class lamb_x_base {

public:
	enum class error_e : char {
	   HARDWARE_ERR,
	   SOFTWARE_ERR, 
	   CURRENT_ERR,
	   LOGIC_ERR,
	   NO_ERR,
	   DATE_ACTIVE_ERR,
	};

	enum class state_e : char {
		ON,
		OFF
	};

	virtual ~lamb_x_base() {}

    lamb_x_base() :m_id(0), m_state(state_e::OFF) , last_error(error_e::NO_ERR){}

	lamb_x_base(int _id) :m_id(_id), m_state(state_e::OFF), last_error(error_e::NO_ERR) {}
	   
	virtual error_e on() 
	{ 
		return direct_on();
	}

	virtual error_e off() 
	{
		return direct_off();
	}

	int id() {
		return (m_id); 
	}

	state_e get() {
		if(m_id)
			return m_state;
	}

	state_e operator()() {
		if (m_id)
			return m_state;
	}

	template <typename Function, typename Class>
	void bind(Function&& function, Class* handler) {
		m_on_off = std::bind(std::forward<Function>(function),
			handler,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4,
			std::placeholders::_5,
			std::placeholders::_6);
	}

	template <typename Function>
	void bind(Function&& function) {
		m_on_off = std::bind(std::forward<Function>(function),
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4,
			std::placeholders::_5,
			std::placeholders::_6);
	}
	
protected:

    error_e direct_on(char red = 0, char green = 0, char blue = 0, char brightness = 0)
	{
		if (!m_id) {
			last_error = error_e::SOFTWARE_ERR;
			return last_error;
		}

		if (m_state == state_e::ON) {
			last_error = error_e::LOGIC_ERR;
			return last_error;
		}

		m_state = state_e::ON;
		last_error = error_e::NO_ERR;

		if (m_on_off)
			m_on_off(m_id, true, red, green, blue, brightness);

		return last_error;
	}

	virtual error_e direct_off(char red = 0 , char green = 0 , char blue = 0 , char brightness = 0)
	{
		if (!m_id) {
			last_error = error_e::SOFTWARE_ERR;
			return last_error;
		}

		if (m_state == state_e::OFF) {
			last_error = error_e::LOGIC_ERR;
			return last_error;
		}

		m_state = state_e::OFF;
		last_error = error_e::NO_ERR;

		if (m_on_off)
			m_on_off(m_id, false , red, green, blue, brightness);

		return last_error;
	}
	 
private:
	int m_id;
	state_e m_state;
	error_e last_error;
	std::function<void(int, bool,char,char,char,char)> m_on_off; 

};

using lamb1 = lamb_x_base;
using lamb_low_feature = lamb_x_base;