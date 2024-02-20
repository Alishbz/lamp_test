/****************************************************************************************
* ALI SAHBAZ
*
*
* Date          : 20.02.2024
* By            : Ali Þahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#pragma once 

#include <cstdint> 

#include "lamb_x.hpp"
 

class lamb_y_base : public lamb_x_base {

public:

	using state = lamb_x_base::state_e;
	using error = lamb_x_base::error_e;

	virtual ~lamb_y_base() {}
	   
	lamb_y_base(int _id) : lamb_x_base(_id), m_order_avtive(false) , m_set_date(0) , m_q_time(0), m_order_state(state::OFF){}
	   
	error on() override 
	{  
		if (!m_order_avtive) { return direct_on(); }
		return error::DATE_ACTIVE_ERR;
	}
	 
	error off() override 
	{
		if (!m_order_avtive) { return direct_off(); }
		return error::DATE_ACTIVE_ERR;
	}

	void set_order(uint32_t _date , state _state) {
		m_order_avtive = true;
		m_set_date = _date;
		m_order_state = _state;
	}

	void scheculer(uint32_t _q_time) {    /** could be 1sc / 1ms...  **/
		
		m_q_time = _q_time;

		/** time control **/
		if (m_order_avtive && m_q_time > m_set_date) {
		 
			m_order_avtive = false;
			if (m_order_state == state::ON) {
				direct_on();
			}
			else { 
				direct_off(); 
			}
		}
	}

	void cancel_order() {
		m_order_avtive = false;
	}

protected:
	bool m_order_avtive;

private:

	uint32_t m_set_date;
	uint32_t m_q_time;
	state m_order_state;

};

using lamb2 = lamb_y_base;
using lamb_mid_feature = lamb_y_base;