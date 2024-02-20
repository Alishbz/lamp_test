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

#include "lamb_y.hpp"


class lamb_z_base : public lamb_y_base {

public:
  
	virtual ~lamb_z_base() {}

	lamb_z_base(int _id):lamb_y_base(_id), m_r(0), m_g(0), m_b(0), m_l(0) {}

	void set_features(uint32_t _rgbl) {
		m_r = static_cast<char>(_rgbl >> 24);
		m_g = static_cast<char>(_rgbl >> 16);
		m_b = static_cast<char>(_rgbl >> 8);
		m_l = static_cast<char>(_rgbl >> 0);
	}
	 
	uint32_t get_features(  ) {
		return static_cast<uint32_t>((m_r << 24) | (m_g << 16) | (m_b << 8) | (m_l << 0)); 
	}

	error on() final
	{
		if (!m_order_avtive) { 
			return direct_on(m_r, m_g , m_b , m_l); 
		}
		return error::DATE_ACTIVE_ERR;
	}
	 
	error off() final
	{
		if (!m_order_avtive) { 
			return direct_off(m_r, m_g, m_b, m_l);
		}
		return error::DATE_ACTIVE_ERR;
	}

private:
	 
	char m_r;
	char m_g;
	char m_b;
	char m_l;

};

using lamb3 = lamb_z_base;
using lamb_high_feature = lamb_z_base;