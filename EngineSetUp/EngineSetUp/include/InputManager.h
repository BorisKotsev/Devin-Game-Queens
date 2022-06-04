#pragma once

#include <utility>

#include <SDL.h>
#include <fstream>
#include <string>

#include "defines.h"
#include "Engine.h"
#include "Validator.h"

/*
* \brief input handler
* In order to use this class first you must init it from the World
* if you need any variable you can pass it by reference
* don't call SDL_PollEvent or SDL_GetKeyboardState anywhere else
*/

class InputManager
{
public:
    InputManager();
    ~InputManager();

    bool m_mouseIsPressed;
    bool m_mouseIsDoubleClicked;
    // mouse is being pressed for first time
    bool m_mouseOnClick;
    bool m_mouseOnRelease;
    bool m_drag;
    bool m_mouseIsPressedPrevFrame;
    bool m_mouseIsHolded;
    bool m_mouseIsRightPressed;

    int2 m_inputDirection;

    int2 m_mouseCoor;

    const Uint8* m_keyboardState;

    int m_scroll;

    string getInputData();

    bool isSpacePressed(); //< returns if space is pressed xd
    bool isSpaceReleased(); //< returns if space is released xd                                enjoy
    void handleInput(); //< call the SDL_PollEvent fnc and update all variables
    void setMouseMultiply(float2 multiplier); //< multiply the mouseCoor corespondingly to the screen resolution
    void setPlayerScreenPos(int2* playerScreenPos);

    void init(string path); //< read the pre-set controlls in a configFile 
    void startTextInput();
    void stopTextInput();
    void resetText(string reset);

    bool anyKeyIsPressed();

    string getTextInput();
private:
    SDL_Event m_event;

    float2 m_mouseMultiply;

    int2* m_playerScreenPos;

    int2 m_screenCenter;
    int2 m_direction;

    string m_inputData;
    string m_textInput;

    bool m_textInputIsActive;
};