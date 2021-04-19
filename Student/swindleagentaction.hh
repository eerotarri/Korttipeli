#ifndef SWINDLEAGENTACTION_HH
#define SWINDLEAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

/**
 * @brief MoveAgentAction luokka määrittelee huijaamisen toteuttavan luokan
 */
class SwindleAgentAction: public Interface::ActionInterface
{
public:
    /**
     * @brief SwindleAgentAction rakentaja
     * @param agent siirtoon liittyvä agentti
     * @param mw osoitus pääikkunaan, jossa siirto tapahtuu
     */
    explicit SwindleAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~SwindleAgentAction();
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

#endif // SWINDLEAGENTACTION_HH
