#include "sfmltest.h"

sfmltest::sfmltest()
{
}

void sfmltest::run()
{
    sf::Joystick::update();

    // Check if a joystick (gamepad) is connected
    if (sf::Joystick::isConnected(0)) {
        std::cout << "PS5 Gamepad connected!" << std::endl;

        // Main loop
        while (true) {
            sf::Joystick::update();

            auto gamepadinfo = sf::Joystick::getIdentification(0);
            std::cout << "name : " << gamepadinfo.name.toAnsiString() << std::endl;
            std::cout << "productId : " << gamepadinfo.productId << std::endl;
            std::cout << "vendorId : " << gamepadinfo.vendorId << std::endl;

//            pdidi->dwVendorId == 0x045E //xbox
            //0x054c //ps5

            int buttoncount = sf::Joystick::getButtonCount(0);
            std::cout << buttoncount << std::endl;

            // Check if button 0 (circle) is pressed
//            for (int i = 0; i < 32 ; i++)
//            {
//                if (sf::Joystick::isButtonPressed(0, i)) {
//                    std::cout << "Button "<<i<<" pressed!" << std::endl;
//                }
//            }
            if (sf::Joystick::isButtonPressed(0, 0)) {
                std::cout << "Button 0 (Rect) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 1)) {
                std::cout << "Button 1 (cross) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 2)) {
                std::cout << "Button 2 (circle) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 3)) {
                std::cout << "Button 3 (Triangle) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 4)) {
                std::cout << "Button 4 (L1) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 5)) {
                std::cout << "Button 5 (R1) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 6)) {
                std::cout << "Button 6 (L2) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 7)) {
                std::cout << "Button 7 (R2) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 8)) {
                std::cout << "Button 8 (share) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 9)) {
                std::cout << "Button 9 (menu) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 10)) {
                std::cout << "Button 10 (lsb) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 11)) {
                std::cout << "Button 11 (rsb) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 12)) {
                std::cout << "Button 12 (PS) pressed!" << std::endl;
            }
            if (sf::Joystick::isButtonPressed(0, 13)) {
                std::cout << "Button 13 (touchpad btn) pressed!" << std::endl;
            }

            // Check other buttons or axes as needed

            // You can also get the position of analog axes
            float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);  // ls-x
            float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);  // ls-y

            std::cout << "X Axis: " << xAxis << ", Y Axis: " << yAxis << "" << std::endl;

            float zAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Z); // rs-x
            float rAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::R); // rs-y
            float uAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::U); // lt
            float vAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::V); // rt
            int pxAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX); // dirc-x
            int pyAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY); // dirc-y

            std::cout << "zAxis : " << zAxis << ", rAxis: " << rAxis << "" << std::endl;
            std::cout << "uAxis : " << uAxis << ", vAxis: " << vAxis << "" << std::endl;
            std::cout << "pxAxis : " << pxAxis << ", pyAxis: " << pyAxis << "" << std::endl;


            // Adjust the loop rate (you may need to experiment with this)
            sf::sleep(sf::milliseconds(100));
        }
    } else {
        std::cout << "PS5 Gamepad not connected!" << std::endl;
    }
}
