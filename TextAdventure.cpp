
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"

//variabili
std::string playerName;
Creature* player = nullptr;
//setup
void GoForwardOnConsole();
bool GetUserDecision();
std::string SetPlayerName();
//intro/tutorial
void Introduction(std::string playerName);
void TutorialIntro();
void TutorialInfo();
void TutorialFight();
//journey
int main()
{
    playerName = SetPlayerName();
    player = new Creature(playerName, 15, 4, 10, false, std::make_unique<HealingPotion>());
    CombactManager::Get().SetPlayer(player);

    Introduction(playerName);
    TutorialIntro();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    //puntatori smart unici -> gestione automatica della memoria
    //nemici Round One
    std::unique_ptr<Creature> endersuit = std::make_unique<Creature>("Colosso", 25, 9, 3, true, std::make_unique<HealingPotion>());
    std::unique_ptr<Creature> enderman = std::make_unique<Creature>("Sgherro", 15, 2, 6, true, std::make_unique<IncendiaryBomb>());
    std::unique_ptr<Creature> endermite = std::make_unique<Creature>("sgherro", 15, 2, 6, true, nullptr);
    //array dinamico ci puntatori unici
    std::vector<std::unique_ptr<Creature>> roundOneEnemies;
    //trasferire i puntatori dei nemici in una nuova posizione
    roundOneEnemies.push_back(std::move(endersuit));
    roundOneEnemies.push_back(std::move(enderman));
    roundOneEnemies.push_back(std::move(endermite));
    

    //passare la lista di nemici per questo round
    CombactManager::Get().SetEnemies(std::move(roundOneEnemies));


    //DEBUG 
    CombactManager::Get().StartAndManageFight();
    
    //chiudere l'eseguibile solo quando l'utente lo desidera 
    std::cout << " digita 1 per uscire" << std::endl;
    char input;
    do {
        std::cin >> input;
    } while (input != '1');
    return 0;
}

//restituisce TRUE(equivalente a un si) o FALSE (equivalente a un no)
bool GetUserDecision()
{
    int userChoice = -1;
    while (userChoice < 0 || userChoice > 1)
    {
        std::cin >> userChoice;
    }
    return (userChoice == 1) ? true : false;
}

std::string SetPlayerName()
{
    std::cout << "lo sapevi che questo gioco ti permette di scegliere un nome ? dovresti approfitarne" << std::endl;
    std::string playerName = "nothing";
    bool nameChosen = false;

    while (nameChosen == false)
    {
        std::cout << "digita un nome proprio qui , non premere invio senza aver inserito almeno un nome : ";
        std::cin >> playerName; //getline prende l'intera linea , inclusa la linea vuota
        std::cout << std::endl;

        if (playerName._Equal("Endersuit") || (playerName._Equal("endersuit"))) //piccolo easter egg
        {
            std::cout << playerName << "? strano, mi  sembra familiare, ";
        }
        else
            if (playerName.empty())
            {
                std::cout << "non puoi usare un nome vuoto" << std::endl;
            }
        std::cout << "sicuro della scelta(1 : si, 0 : no) ? " << std::endl;
        std::cout << std::endl;
        nameChosen = GetUserDecision();
    }
    return playerName;
}

void GoForwardOnConsole()
{
    bool canContinue = false;
    while (!canContinue)
    {
        std::string input;
        std::cout << std::endl;
        std::cout << "premi 1 per continuare : ";
        std::cin >> input;
        if (input._Equal("1"))
            canContinue = true;
    }
    std::cout << std::endl;
}

void Introduction(std::string playerName)
{
    std::cout << std::endl;
    std::cout << "il tuo nome e' " << playerName << "' ,sei un semplice corriere che un giorno ha deciso di accettare "
        << "una richiesta di consegna parrechio proficua per conto di terzi,che sborsavano una marea di soldi per consegnare " << std::endl
        << "un pacco a una distanza relativamente corta rispetto alla media." << std::endl
        << "quando hai accetato  l'incarico avevi la sensazione che sotto c'era una fregatura, e in realta non ti sbagliavi : " << std::endl
        << "il viaggio era rischioso per via di una zona pericolosa che avresti dovuto attraversare,popolata da gente pericolosa," << std::endl
        << "e per quanto l'idea di attravesarla non ti rendeva felice, hai deciso di correre e accettare l'incarico. " << std::endl;

    GoForwardOnConsole();

    std::cout << "consapevole del rischio e pronto al peggio, hai riposto il pacco nella tua borsa e iniziato il tuo viaggio verso la destinaizone." << std::endl
        << "dopo quasi due ore di viaggio alle spalle e il sole di mezzogiorno che irradiava forte sulla tua testa, hai deciso di concederti una pausa sotto l'ombra di un albero" << std::endl;

    GoForwardOnConsole();
}

void TutorialIntro()
{
    std::cout << "sdraiato sul tronco dell albero,stavi provando a imaginare  cosa avresti fatto con tutti quei soldi una volta finila la consegna," << std::endl
        <<"'" << playerName << "' disse un uomo sulla quarantina che sembrava essere apparso dal nulla" << std::endl
        << "'cosa !?' avevi risposto tu, completamente colto alla sprovista dell arrivo di quel uomo di cui non sapevi niente" << std::endl
        << "'il tuo nome', disse l'uomo misterioso indicando la tua targetta identificativa" << std::endl
        << "'comunque mi chiamo dutch, non sono cosi vecchio, ma lo sono abbastanza per sapere che  viaggiare da queste parti e pericoloso , soppratutto per chi non sa difendersi'" << std::endl
        << "'tuttavia, potrei insegnarti a darle e prenderle, se me lo permetessi.....(tutorial)'" << std::endl;

    std::cout << std::endl;
    std::cout << "inserisci il numero corrispodente su console" << std::endl;
    std::cout << std::endl;
    std::cout <<"(1) : d'accordo allora, insegnami (inizia il tutorial) " << std::endl;
    std::cout << "(0) : apprezzo l'interesse, ma non e la prima volta che lo faccio (salta il tutorial il tutorial) " << std::endl;
    std::cout << std::endl;

    bool playerChoice = GetUserDecision();
    //inizia il tutorial
    if (playerChoice)
    {
        TutorialInfo();
        TutorialFight();
    }
    //salta il tutorial
    else
    {
        return;
    }
}

void TutorialInfo()
{
    std::cout << std::endl;
    std::cout << "dutch : bene , allora partiamo dalle basi : " << std::endl;
    std::cout << std::endl;

    std::cout << "<<STATISTICHE>> " << std::endl;
    std::cout << std::endl;
    std::cout<< "ogni creatura esistente in questo mondo , incluso tu stesso, avete delle statistiche :  " << std::endl;
    std::cout << std::endl;
    
    std::cout << "- SALUTE ATTUALE : ogni creatura muore se raggiunge lo zero  " << std::endl;
    std::cout << std::endl;
    
    std::cout << "- ATTACCO : la quantita di danni che la creatura puo infliggere  " << std::endl;
    std::cout << "una creatura non puo attacare mentre la sua difesa e alzata" << std::endl;
    std::cout << std::endl;
    
    std::cout << "- DIFESA : rappresenta la capacita della creatura di bloccare i danni in arrivo quando la sua difesa e' \033[1m" << "alzata" << "\033[0m  " << std::endl;
    std::cout << "se alzata, la difesa riduce di 0.5 i danni in arrivo  ogni 1 punti difesa" << std::endl;
    std::cout << std::endl;
    
    std::cout << "-PUNTI AZIONE : ogni creatura ha a disposizione due punti azione per turno. attacarre, alzare/abbasare la difesa o usare un conumabile consuma punti azione" << std::endl;
    std::cout << std::endl;

    std::cout << "<<CONSUMABILI>> " << std::endl;
    std::cout << std::endl;
    
    std::cout << "- ogni creatura in questo gioco  puo  usare dei consumabili " << std::endl;
    std::cout << std::endl;
    
    std::cout << "-  attulamente esistono soli due tipi di consumabile :"<< std::endl<<  
        "pozione di cura(cura un po della tua salute)"<<std::endl 
        <<"bomba incediaria(danneggia un nemico scelto, puo essesre usata anche mentre sei in difesa" << std::endl;
    
    std::cout << "- il tuo consumabile e sempre stampato nella tua scheda su console, ma non puoi vedere quello dei nemici" << std::endl;
    std::cout << std::endl;
}

void TutorialFight()
{
    std::cout << "dutch : ci sono altre cose che potrei dirti, ma forse e meglio se provi a buttarti nella pratica" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "inserisci il numero corrispodente su console" << std::endl;
    std::cout << std::endl;
    std::cout << "(1) : si, facciamoo!(continua il tutorial, sfida dutch a una battaglia di prova) " << std::endl;
    std::cout << "(0) : no, penso sia sufficiente (termina il tutorial) " << std::endl;
    std::cout << std::endl;

    bool playerChoice = GetUserDecision();
    //inizia la battalia di prova
    if (playerChoice)
    {
        std::cout << "dutch : bene allora iniziamo " << std::endl;
        std::cout << std::endl;
        std::cout << "dutch ti porge un ampolla , 'cura' c'era scritto sull eticheta. \ndutch si sistemo accanto ad un manichino, un manichino che aveva qualcosa di diverso dagli altri" << std::endl;
        
        std::unique_ptr<Creature> dutch = std::make_unique<Creature>("Dutch", 15, 3, 3, false, std::make_unique<HealingPotion>());
        std::unique_ptr<Creature> manichino = std::make_unique<Creature>("Manichino", 20, 8, 1, true, nullptr);

        std::vector<std::unique_ptr<Creature>> tutorialEnemies;
        tutorialEnemies.push_back(std::move(dutch));
        tutorialEnemies.push_back(std::move(manichino));

        CombactManager::Get().SetEnemies(std::move(tutorialEnemies));
        CombactManager::Get().StartAndManageFight();

        //combattimento finito -> dutch pone al giocatore un consumabile
         
        std::cout << "dutch : bene, vedo che impari in fretta, prendi una di queste , te la sei meritata. " << std::endl;
        std::cout << std::endl;
        std::cout << "dutch ha tirato fuori due oggetti e te li ha porsi davanti a te, dandotti la possibilita di prenderne uno die due " << std::endl;
        std::cout << std::endl;

        std::cout << "(1) : pozione di cura (ripristina una parte della tua salute) " << std::endl;
        std::cout << "(0) : pozione incendiaria (puo essere lanciata su un nemico, anche mentre sei in difesa) " << std::endl;
        std::cout << std::endl;

        int consumabeChosen = (int)GetUserDecision();

        if (consumabeChosen == 1)
        {
            player->SetNewConsumable(1);
        }
        else
        {
            player->SetNewConsumable(2);
        }
        std::string messagge = (consumabeChosen == 1) ? "pozione di cura" : "bomba incendiaria";
        std::cout << "senza pensarci due volte, hai preso la "<< messagge<< " e te la sei messa nella borsa" << std::endl;
        std::cout << std::endl;
    }
    //salta la battaglia di prova
    else
    {
        std::cout << "come preferisci " << std::endl;
        return;
    }
}
