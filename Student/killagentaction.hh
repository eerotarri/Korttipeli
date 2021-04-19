#ifndef KILLAGENTACTION_HH
#define KILLAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

/**
 * @brief KillAgentAction luokka määrittelee tappamisen toteuttavan luokan
 */
class KillAgentAction: public Interface::ActionInterface
{
public:
    /**
     * @brief KillAgentAction rakentaja
     * @param agent siirtoon liittyvä agentti
     * @param mw osoitus pääikkunaan, jossa siirto tapahtuu
     */
    explicit KillAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~KillAgentAction();
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

#endif // KILLAGENTACTION_HH
