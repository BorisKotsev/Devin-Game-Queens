#include "InputManager.h"


InputManager::InputManager()
{
    m_scroll = 0;
}

InputManager::~InputManager()
{
    delete m_keyboardState;
}

void InputManager::setMouseMultiply(float2 multiplier)
{
    m_mouseMultiply.x = multiplier.x;
    m_mouseMultiply.y = multiplier.y;
}

void startDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;

    inputManager->m_drag = true;
    inputManager->m_mouseOnRelease = false;
}

void stopDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;

    inputManager->m_drag = false;
    inputManager->m_mouseOnRelease = true;
}

void InputManager::init(string path)
{
    path = CONFIG_FOLDER + path;

    fstream stream;
    string tmp;
}

void InputManager::handleInput()
{
    m_mouseIsPressed = false;
    m_mouseIsDoubleClicked = false;
    m_mouseIsRightPressed = false;

    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));

            m_mouseCoor.x *= m_mouseMultiply.x;
            m_mouseCoor.y *= m_mouseMultiply.y;

            break;
        case SDL_MOUSEBUTTONDOWN:
            startDrag(this);

            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_mouseIsPressed = true;
            }

            if (m_event.button.button == SDL_BUTTON_RIGHT)
            {
                m_mouseIsRightPressed = true;
            }

            break;
        case SDL_MOUSEBUTTONUP:
			stopDrag(this);

			break;
        case SDL_TEXTINPUT:
            
            if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_BACKSPACE && m_textInput.length() > 0)
            {
                m_textInput = m_textInput.substr(0, m_textInput.length() - 1);
            }
            if (m_event.type == SDL_TEXTINPUT)
            {
                if (isNumber(m_event.text.text))
                {
                    m_textInput += m_event.text.text;
                }
            }
            break;
        case SDL_KEYDOWN:
            if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_BACKSPACE && m_textInput.length() > 0)
            {
                m_textInput = m_textInput.substr(0, m_textInput.length() - 1);
            }
            if (m_event.type == SDL_TEXTINPUT)
            {
                if(isNumber(m_event.text.text))
                {
                    m_textInput += m_event.text.text;
                }
            }
            break;
        }
    }

    SDL_StartTextInput();

    m_keyboardState = SDL_GetKeyboardState(NULL);

    m_scroll = 0;

    switch (m_event.wheel.type)
    {
    case SDL_MOUSEWHEEL:
        m_scroll = m_event.wheel.y;
        break;

    default:
        break;
    }

    m_event.wheel = SDL_MouseWheelEvent();

    //if (m_textInputIsActive)
    //{

    //}
    //else
    //{
    //    if (m_keyboardState != NULL) //DELAY MUST BE ADDED
    //    {
    //        
    //    }
    //}

    if (m_mouseIsPressed)
    {
        if (!m_mouseIsPressedPrevFrame)
        {
            m_mouseOnClick = true;
        }
        else
        {
            m_mouseOnClick = false;
        }

        m_mouseIsHolded = true;
    }
    else
    {
        m_mouseIsPressedPrevFrame = false;
        m_mouseOnClick = false;
    }

    if (m_drag)
    {

    }
}

bool InputManager::isSpacePressed()
{
    /*if (m_event.type == SDL_KEYDOWN)*/
    return m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_SPACE;

    /*if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_SPACE)
    {
        return true;
    }
    return false;*/
}

bool InputManager::isSpaceReleased()
{
    return m_event.type == SDL_KEYUP && m_event.key.keysym.sym == SDLK_SPACE;
}

string InputManager::getInputData()
{
    if (m_inputData != "")
    {
        string returnValue = m_inputData;
        m_inputData.clear();

        return returnValue;
    }

    return m_inputData;
}


void InputManager::startTextInput()
{
    SDL_StartTextInput();

    m_textInput = "";

    m_textInputIsActive = true;
}

void InputManager::stopTextInput()
{
    SDL_StopTextInput();

    m_textInputIsActive = false;
}

string InputManager::getTextInput()
{
    return m_textInput;
}

void InputManager::resetText(string reset)
{
    if (reset == "0")
    {
        reset = "";
    }
    m_textInput = reset;
}

bool InputManager::anyKeyIsPressed()
{
    int numOfKeys = 322;
	
    for (int i = 0; i < numOfKeys; i++)
    {
        if (m_keyboardState[i])
        {
            return true;
        }
    }
    return false;
}

void InputManager::setPlayerScreenPos(int2* playerScreenPos)
{
    m_playerScreenPos = playerScreenPos;
}