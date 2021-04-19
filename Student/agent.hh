#ifndef AGENT_HH
#define AGENT_HH

#include "agentinterface.h"
#include "QPushButton"
#include "location.h"
#include "QGraphicsScene"

/**
 * @brief Yksittäisen agentin kuvaava luokka
 *
 * Agent on periytetty AgentInterface luokasta eli sisältää sen ja CardInterface luokan.
 *
 * Luokka kuvaa agentin osana peliä, eli tallentaa ns. kortin instanssin ja
 * toimii erityisesti korttia (nappia) tallentavana tahona.
 */
class Agent: public Interface::AgentInterface
{
public:

    /**
      * @brief Agent luokan rakentaja.
      * @post Agentilla on alustetut tiedot ja se kuuluu jollekkin pelaajalle ja on pelaajan kädessä.
      */
    explicit Agent(QPushButton* button = nullptr,
                   std::weak_ptr<Interface::Player> ownr = {}, std::weak_ptr<Interface::Location> lctn = {},
                   unsigned short pts = 0, QString name = "", QString typeName = "", QString title = "", QGraphicsScene* scene = nullptr);
    virtual ~Agent();

    /*!
     * @brief name palauttaa kortin nimen
     * @pre -
     * @return Kortin nimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString name() const;
    /**
     * @brief typeName palauttaa kortin tyypin
     * @pre -
     * @return Kortin tyyppi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString typeName() const;
    /*!
     * @brief title palauttaa kortin arvonimen
     * @pre -
     * @return Kortin arvonimi merkkijonona
     * @post Poikkeustakuu: nothrow
     */
    virtual QString title() const;
    /**
     * @brief location kertoo, mihin pelialueeseen kortti liittyy
     * @pre -
     * @return heikko osoitin pelialueeseen johon kortti liittyy, tai tyhjä osoitin jos se ei liity mihinkään
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Interface::Location> location() const;
    /**
     * @brief owner kertoo pelaajan, joka omistaa kortin
     * @pre -
     * @return heikko osoitin kortin omistavaan pelaajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Interface::Player> owner() const;
    /**
     * @brief setOwner asettaa kortille omistajan
     * @pre -
     * @param owner heikko osoitin kortin omistajaan, tai tyhjä osoitin jos sitä ei omista kukaan
     * @post Kortilla on uusi omistaja
     * @post Poikkeustakuu: nothrow
     */
    virtual void setOwner(std::weak_ptr<Interface::Player> owner);
    /*!
     * @brief isCommon kertoo, onko kyseessä "geneerinen" agentti, joka ei liity mihinkään pelilaudan alueeseen
     * @pre -
     * @return tosi, joss agentti ei liity mihinkään pelilaudan alueeseen
     * @post Poikkeustakuu: nothrow
     */
    virtual bool isCommon() const;
    /**
     * @brief placement palauttaa tiedon agentin sijainnista
     * @pre -
     * @return heikko osoitin pelilaudan alueelle jossa agentti sijaitsee, tai tyhjä osoitin jos se ei ole laudalla
     * @post Poikkeustakuu: nothrow
     */
    virtual std::weak_ptr<Interface::Location> placement() const;
    virtual void setButton(QPushButton* button);
    virtual QPushButton* getButton();
    /**
     * @brief setPlacement kertoo agentille millä pelialueella se on
     * @pre -
     * @param placement pelialue, tai tyhjä osoitin jos agentti ei ole laudalla
     * @post agentti tietää olevansa alueella
     * @post Poikkeustakuu: nothrow
     */
    virtual void setPlacement(std::weak_ptr<Interface::Location> placement);
    /**
     * @brief connections kertoo suhteiden tason
     * @pre -
     * @return palauttaa suhteiden senhetkisen tilanteen
     * @post Poikkeustakuu: nothrow
     */
    virtual unsigned short connections() const;
    /**
     * @brief setConnections asettaa agentille suhteiden tason
     * @pre -
     * @param connections uusi suhteiden taso
     * @post suhteet ovat parametrin mukaiset
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void setConnections(unsigned short connections);
    /**
     * @brief setConnections muuttaa agentin suhteiden tasoa
     * @pre -
     * @param change suhteiden muutos
     * @post suhteita on muutettu parametrin mukaisesti
     * @post Poikkeustakuu: vahva
     * @exception StateException jos rikkoisi invariantin
     */
    virtual void modifyConnections(short change);

    /**
     * @brief scene palauttaa scenen, jossa agentti on
     * @return QGraphicsScene* osoitin sceneen johon agentti kuuluu
     */
    QGraphicsScene *scene();
    /**
     * @brief setScene asettaa scenen agentille
     * @param scene johon agentti on asetettu
     */
    virtual void setScene(QGraphicsScene* scene);


private:

    QString name_;

    QString title_;

    QString typeName_;

    std::weak_ptr<Interface::Location> location_;

    std::weak_ptr<Interface::Player> owner_;

    unsigned short connections_;

    bool isCommon_ = true;

    QPushButton* button_;

    QGraphicsScene* scene_;
};

#endif // AGENT_HH
