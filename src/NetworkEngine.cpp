#include "NetworkEngine.h"

NetworkEngine::NetworkEngine()
{
    Engine();
}

NetworkEngine::~NetworkEngine()
{

}
void NetworkEngine::update(sf::RenderWindow& window){
    getMousePosition(window);
    if(! clicked || turn->getMovePremission() == true)
        last_turn_board_state = board.update(clicked,turn,mouse);
    if(clicked)
        if(state != Winner)
            if(turn->getMovePremission() == true)
            {
                if(last_turn_board_state == Board::NextTurn)
                {
                    turn = players[(++current_player_number)%=2].get();
                    DEBUG_MSG("NEXT TURN : " << turn->toStr() << std::endl);
                }
                clicked = false;
                if(last_turn_board_state == Board::Winner)
                {
                    DEBUG_MSG("Winner is: " << turn->toStr() << std::endl);
                    state = Winner;
                }
            }else
                clicked = false;
    if(state == PlayingGame)
        window.draw(board);
    else if(state == Winner)
    {
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
        text.setPosition(window.getSize().x/2.0 - text.getLocalBounds().width/2.0, window.getSize().y/2.0 - text.getLocalBounds().height/2.0);
        window.draw(text);
    }
}
