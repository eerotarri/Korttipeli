#ifndef MOVEAGENTACTION_HH
#define MOVEAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

/**
 * @brief MoveAgentAction luokka määrittelee liikkumisen toteuttavan luokan
 */
class MoveAgentAction: public Interface::ActionInterface
{
public:
    /**
     * @brief MoveAgentAction rakentaja
     * @param agent siirtoon liittyvä agentti
     * @param mw osoitus pääikkunaan, jossa siirto tapahtuu
     */
    explicit MoveAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~MoveAgentAction();

    /**
     * @brief canPerform kertoo, onko siirto tehtävissä
     * @pre -
     * @return tosi, joss siirto on tehtävissä
     * @post Poikkeustakuu: nothrow
     */
    virtual bool canPerform() const;
    /**
     * @brief perform suorittaa siirron
     * @pre siirto on tehtävissä
     * @post Poikkeustakuu: nothrow
     */
    virtual void perform();

private:

    std::shared_ptr<Agent> agent_ = nullptr;
    MainWindow* mainwindow_ = nullptr;

};

#endif // MOVEAGENTACTION_HH
