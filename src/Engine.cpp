#include "Engine.h"
#include <iostream>
#include <AiPlayer.h>

#define HEIGHT 20
#define WIDTH 30

#include "HumanPlayer.h"

Engine::Engine()
        :
        turn(nullptr),
        current_player_number(0),
        clicked(0) {
    DEBUG_MSG("Engine creating" << std::endl);
}

Engine::~Engine() {
    DEBUG_MSG("Engine removing" << std::endl);
}

void Engine::init(sf::RenderWindow &window) {
    view = window.getDefaultView();
    state = PlayingGame;
    board.init(HEIGHT, WIDTH);
    window.draw(board);
    players[0].reset(new AiPlayer);
    players[1].reset(new AiPlayer);
    players[1]->move_premission = false;
    turn = players[0].get();
    players[0]->setTexture("textures/square_marked_circle.png");
    players[1]->setTexture("textures/square_marked_cross.png");
    {
        const std::string player1Name("Player1");
        const std::string player2Name("Player2");
        players[0]->setName(player1Name);
        players[1]->setName(player2Name);
    }
    goodfoot.loadFromFile("fonts/goodfoot.ttf"); // font is a sf::Font
}

void Engine::getMousePosition(sf::RenderWindow &window) {
    mouse = static_cast<sf::Vector2i> (window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void Engine::update(sf::RenderWindow &window) {
    getMousePosition(window);
    if (state != Winner) {
        last_turn_board_state = board.update(clicked, turn, mouse);
        if (last_turn_board_state == Board::NextTurn) {
            turn = players[(++current_player_number) %= 2].get(); ///unfortunately changes when there were player turn failed
            DEBUG_MSG("NEXT TURN : " << turn->toStr() << std::endl);
        }
    }
    if (clicked)
        clicked = false;
    if (last_turn_board_state == Board::Winner) {
        DEBUG_MSG("Winner is: " << turn->toStr() << std::endl);
        state = Winner;
    }

    if (state == PlayingGame)
        window.draw(board);
    else if (state == Winner) {
        window.setView(window.getDefaultView());
        std::string winning_msg = "Winner is: ";
        std::string tmp = "\n\nPress esc to return to menu.";
        winning_msg += turn->toStr();
        winning_msg += tmp;
        sf::Text text;
        text.setFont(goodfoot);

        text.setString(winning_msg);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x / 2.0 - text.getLocalBounds().width / 2.0,
                         window.getSize().y / 2.0 - text.getLocalBounds().height / 2.0);
        window.draw(text);
    }
}

void Engine::events(sf::RenderWindow &window,
                    sf::Event &event) { //TODO(foto): make camera events moving zooming ectr. in different function
    static sf::Vector2i old_position;
    static bool screen_moving;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                std::cout << "wheel type: vertical" << std::endl;
                DEBUG_MSG("scroll delta :" << event.mouseWheelScroll.delta << std::endl);
                view.zoom(1.00f - 0.1f * event.mouseWheelScroll.delta);
                window.setView(view);
            }
        }


        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            keyboardEvents(window, event);
        }
        if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
            clicked = true;
            DEBUG_MSG(" lmouse button=" << clicked << std::endl);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right) {
            old_position = sf::Mouse::getPosition();
            if (!screen_moving)
                screen_moving = true;
            DEBUG_MSG(" right button - screen moving" << std::endl);
        } else if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Right) {
            screen_moving = false;
        }
    }
    if (screen_moving) {
        sf::Vector2i new_position = sf::Mouse::getPosition();
        view.setCenter(view.getCenter().x - new_position.x + old_position.x,
                       view.getCenter().y - new_position.y + old_position.y);
        old_position = new_position;
        window.setView(view);
    }
}

Engine::EngineState Engine::currentState() const {
    return state;
}

void Engine::keyboardEvents(sf::RenderWindow &window, sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape :
            DEBUG_MSG("the escape key was pressed" << std::endl);
            DEBUG_MSG("control:" << event.key.control << std::endl);
            DEBUG_MSG("alt:" << event.key.alt << std::endl);
            DEBUG_MSG("shift:" << event.key.shift << std::endl);
            DEBUG_MSG("system:" << event.key.system << std::endl);
            state = EndOfGame;
            break;

        case sf::Keyboard::Add :
            view.zoom(0.9f);
            window.setView(view);
            DEBUG_MSG("zoomed" << zoom << std::endl);
            break;

        case sf::Keyboard::Subtract :
            view.zoom(1.1f);
            window.setView(view);
            DEBUG_MSG("out zoomed" << zoom << std::endl);
            break;

        case sf::Keyboard::Up :
            view.setCenter((view.getCenter().x), view.getCenter().y - 10.0f);
            window.setView(view);
            DEBUG_MSG("mooving up" << std::endl);
            break;

        case sf::Keyboard::Down :
            view.setCenter((view.getCenter().x), view.getCenter().y + 10.0f);
            window.setView(view);
            DEBUG_MSG("mooving down" << std::endl);
            break;

        case sf::Keyboard::Right :
            view.setCenter((view.getCenter().x + 10.0f), view.getCenter().y);
            window.setView(view);
            DEBUG_MSG("mooving right" << std::endl);
            break;
        case sf::Keyboard::Left :
            view.setCenter((view.getCenter().x - 10.0f), view.getCenter().y);
            window.setView(view);
            DEBUG_MSG("mooving left" << std::endl);
            break;

    }

}
