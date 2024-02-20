/****************************************************************************************
* ALI SAHBAZ   
* 
*
* Date          : 20.02.2024
* By            : Ali Şahbaz
* e-mail        : ali_sahbaz@outlook.com 
*/  
#include <iostream>
#include <memory>
#include <vector>
#include "mini_tdd.hpp"

#ifdef _WIN32
  #include <windows.h>  
#else
  #warning "OS is not known"
#endif 

#include "lamb_x.hpp"
#include "lamb_y.hpp"
#include "lamb_z.hpp"
       
#include "lamb.hpp"
#include "lambs_container.hpp"

/** LOW_LOWEL API *********************************************************************************************/
  
static uint32_t Q_TIME = 0;
 
 
/** low level , hardware dep. func **/
static void _ll_hal_led_controller(int m_id , bool led_state, char red_val, char green_val, char blue_val, char brightness_val) 
{
    if (led_state) {
        std::cout << " led " << m_id << " ON ";
    }
    else {
        std::cout << " led " << m_id << " OFF ";
    }

    std::cout << " r: " << (int)red_val  << " g: " << (int)green_val << " b: " << (int)blue_val << " l: " << (int)brightness_val  ;

    std::cout << " \n";
}



/** TESTS *********************************************************************************************/

  
TEST_CASE(lamb_1_fail_test) 
{
    lamb1 L_1(6);
     
    L_1.bind(_ll_hal_led_controller);

    L_1.off();
    L_1.on(); 

    lamb1::state_e st = L_1.get();

    ASSERT(st == lamb1::state_e::OFF);
}


TEST_CASE(lamb_1_on_test) 
{
    lamb1 L_1(8);

    L_1.bind(_ll_hal_led_controller);

    L_1.on();

    lamb1::state_e st = L_1();

    ASSERT(st == lamb1::state_e::ON);
}

TEST_CASE(lamb_1_off_test)
{
    lamb1 L_1(9);

    L_1.bind(_ll_hal_led_controller);

    L_1.off();

    lamb1::state_e st = L_1();

    ASSERT(st == lamb1::state_e::OFF);
}


TEST_CASE(lamb_1_mix_test)
{
    lamb1 L_1(11);

    L_1.bind(_ll_hal_led_controller);

    L_1.off();
    L_1.on();
    L_1.off();
    L_1.on();
    L_1.on();

    lamb1::state_e st = L_1.get();

    ASSERT(st == lamb1::state_e::ON);  
}


TEST_CASE(lamb_2_mix_test)
{
    lamb2 LAMB(12);

    LAMB.bind(_ll_hal_led_controller);

    LAMB.off();
    LAMB.on();
    LAMB.off();

    /** Config clock **/
    LAMB.set_order(2, lamb_low_feature::state_e::ON);

    Q_TIME = 0;

    auto TimerCallback = [](HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
        Q_TIME++; 
        std::cerr << "timer on: " << Q_TIME <<std::endl;
       };
     
    UINT_PTR timerID = SetTimer(NULL, 0, 1000,  TimerCallback );

    if (timerID == 0) {
        std::cerr << "Timer error!" << std::endl;
        return ;
    }
     
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        LAMB.scheculer(Q_TIME);
        if (lamb_low_feature::state_e::ON == LAMB()) { break;  }
    }
     
    KillTimer(NULL, timerID);

    lamb_low_feature::state_e st = LAMB.get();

    ASSERT(st == lamb_low_feature::state_e::ON);
}


 

TEST_CASE(lamb_3_mix_test)
{
    lamb3 LAMB(14); 

    LAMB.bind(_ll_hal_led_controller);

    LAMB.set_features(0x15451215);

    LAMB.off();
    LAMB.on();
    LAMB.off();

    /** Config clock **/
    LAMB.set_order(3, lamb_low_feature::state_e::ON);

    Q_TIME = 0;

    auto TimerCallback = [](HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
        Q_TIME++;
        std::cerr << "timer on: " << Q_TIME << std::endl;
        };

    UINT_PTR timerID = SetTimer(NULL, 0, 1000, TimerCallback);

    if (timerID == 0) {
        std::cerr << "Timer error!" << std::endl;
        return;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        LAMB.scheculer(Q_TIME);
        if (lamb_low_feature::state_e::ON == LAMB()) { break; }
    }

    KillTimer(NULL, timerID);

    lamb_low_feature::state_e st = LAMB.get();

    ASSERT(st == lamb_low_feature::state_e::ON);
}


TEST_CASE(app_mocking_test)
{
    app_lamb<lamb3> LAMB(1);

    LAMB.bind(_ll_hal_led_controller);

    LAMB.set_features(0x33112299);

    LAMB.off();
    LAMB.on();
    LAMB.off();

    lamb_low_feature::state_e st = LAMB();

    ASSERT(st == lamb_low_feature::state_e::OFF);
}



TEST_CASE(container_test)
{
    lamb3 LAMB1(14);
    lamb2 LAMB2(13);
    lamb1 LAMB3(12);
     
    LAMB2.bind(_ll_hal_led_controller);

    lamb_container container{};

    container.add(1 , LAMB1);
    container.add(5 , LAMB2);
    container.add(8, LAMB3);
     
    try {
        auto x = container.get(5);
        x.on();
        x.off(); 
        lamb_low_feature::state_e st = x();
        ASSERT(st == lamb_low_feature::state_e::OFF);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "err: " << e.what() << std::endl;
    }  

    /*
    try {
        container.get(9);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }*/
}


  
int main() { 
       
    std::cout << "TEST 5 \n" ;
     
    /** SERVICE TEST *************/
 
    RUN_TEST(lamb_1_fail_test);
    RUN_TEST(lamb_1_on_test);
    RUN_TEST(lamb_1_off_test);
    RUN_TEST(lamb_1_mix_test);
    RUN_TEST(lamb_2_mix_test);
    RUN_TEST(lamb_3_mix_test);
    RUN_TEST(app_mocking_test);
    RUN_TEST(container_test);
    
    /**************/
     
    return 0;
}


 

