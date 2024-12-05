
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
void RoundOneFight();

int main()
{
    playerName = SetPlayerName();
    player = new Creature(playerName, 20, 4, 10, false, std::make_unique<HealingPotion>());
    CombactManager::Get().SetPlayer(player);

    //introduzione e tutorial
    Introduction(playerName);
    TutorialIntro();
    //primo combatimento/atto
    RoundOneFight();
    


    //chiudere l'eseguibile solo quando l'utente lo desidera 
    std::cout << " digita 1 per uscire" << std::endl;
    char input;
    do {
        std::cin >> input;
    } while (input != '1');
    return 0;
}

bool isNumber(std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) return false; // Controlla se ogni carattere è un numero
    }
    return !str.empty(); // Controlla che la stringa non sia vuota
}

//restituisce TRUE(equivalente a un si) o FALSE (equivalente a un no)
bool GetUserDecision() 
{
    std::string userChoice;

    do {
        std::cout << "Inserisci 1 o 0  per selezionare una delle due opzioni : ";
        std::cin >> userChoice;

        if (!isNumber(userChoice) || (userChoice != "1" && userChoice != "0")) {
            std::cout << "Input non valido. Riprova.";
            std::cout << std::endl;
        }
    } while (userChoice != "1" && userChoice != "0");

    return userChoice == "1"; // Restituisce true per "1", false per "0"
}

std::string SetPlayerName()
{
    std::cout << "lo sapevi che questo gioco ti permette di scegliere un nome ? dovresti approfitarne" << std::endl;
    std::string playerName;
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

        std::cout << "sicuro della scelta ?" << std::endl;
        std::cout << std::endl;
        
        std::cout << "(1) : si"<<std::endl;
        std::cout << "(0) : no" << std::endl;

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

    std::cout << "consapevole del rischio e pronto al peggio, hai riposto il pacco nella tua borsa e iniziato il tuo viaggio verso la destinazione." << std::endl
        << "dopo quasi due ore di viaggio alle spalle e il sole di mezzogiorno che irradiava forte sulla tua testa, hai deciso di concederti una pausa sotto l'ombra di un albero" << std::endl;

    GoForwardOnConsole();
}

void TutorialIntro()
{
    std::cout << "sdraiato sul tronco dell albero,stavi provando a immaginare  cosa avresti fatto con tutti quei soldi una volta finita la consegna," << std::endl
        <<"'" << playerName << "' disse un uomo sulla quarantina che sembrava essere apparso dal nulla" << std::endl
        << "'cosa !?' avevi risposto tu, completamente colto alla sprovvista dell' arrivo di quel uomo di cui non sapevi niente" << std::endl
        << "'il tuo nome', disse l'uomo misterioso indicando la tua targetta identificativa" << std::endl
        << "'comunque mi chiamo Dutch, non sono cosi vecchio , ma lo sono abbastanza per sapere che  viaggiare da queste parti e pericoloso , soppratutto per chi non sa difendersi'" << std::endl
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
    std::cout << "Dutch : bene , allora partiamo dalle basi : " << std::endl;
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
    std::cout << "Dutch : ci sono altre cose che potrei dirti, ma forse e meglio se provi a buttarti nella pratica" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "inserisci il numero corrispodente su console" << std::endl;
    std::cout << std::endl;
    std::cout << "(1) : si, facciamoo!(continua il tutorial, sfida Dutch a una battaglia di prova) " << std::endl;
    std::cout << "(0) : no, penso sia sufficiente (termina il tutorial) " << std::endl;
    std::cout << std::endl;

    bool playerChoice = GetUserDecision();
    //inizia la battalia di prova
    if (playerChoice)
    {
        std::cout << "Dutch : bene allora iniziamo " << std::endl;
        std::cout << std::endl;
        std::cout << "Dutch ti porge un ampolla , 'cura' c'era scritto sull eticheta. \ndutch si sistemo accanto ad un manichino, un manichino che aveva qualcosa di diverso dagli altri" << std::endl;
        
        std::unique_ptr<Creature> dutch = std::make_unique<Creature>("Dutch", 15, 3, 3, false, std::make_unique<HealingPotion>());
        std::unique_ptr<Creature> manichino = std::make_unique<Creature>("Manichino", 20, 8, 1, true, nullptr);

        std::vector<std::unique_ptr<Creature>> tutorialEnemies;
        tutorialEnemies.push_back(std::move(dutch));
        tutorialEnemies.push_back(std::move(manichino));

        CombactManager::Get().SetEnemies(std::move(tutorialEnemies));
        CombactManager::Get().StartAndManageFight();

        //combattimento finito -> dutch pone al giocatore un consumabile
         
        GoForwardOnConsole();

        std::cout << "Dutch : bene, vedo che impari in fretta, prendi una di queste , te la sei meritata. " << std::endl;
        std::cout << std::endl;
        std::cout << "Dutch ha tirato fuori due oggetti e te li ha porsi davanti a te, dandotti la possibilita di prenderne uno dei due " << std::endl;
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
        std::cout << "senza pensarci due volte, hai preso la "<< messagge<< " e te la sei messa nella borsa, ringraziando Dutch per tutto quello che ha fatto per te" << std::endl;
        std::cout << std::endl;
    }
    //salta la battaglia di prova
    else
    {
        std::cout << "come preferisci " << std::endl;
        return;
    }

    GoForwardOnConsole();
    
    std::cout << "\n  scrolatta la polvere di dosso , ti sei rimesso in cammino, ignaro di quello che sarebbe arrivato dopo" << std::endl;
    std::cout << std::endl;
    GoForwardOnConsole();
}

void RoundOneFight()
{
    std::cout << std::endl;
    std::cout <<"dopo 90 minuti di viaggio sei arrivato a nella citta di  destinazione :  'Blackwater', una citta sulla costa di medie dimensioni, con una triste notorieta per i suoi fuorilegge " << std::endl;

    GoForwardOnConsole();

    std::cout <<"reduce dal lungo viaggio che hai dovuto seguire e vicino al luogo di consegna, hai deciso di concederti una bevuta in un pub nelle vicinanze prima di raggiungere il luogo della consegna," << std::endl;
    std::cout <<"tuttavia, non hai fatto in tempo ad entrare che un trio di teppisti ha iniziato a sbararti la strada" << std::endl;

    GoForwardOnConsole();

    std::cout <<"Colosso :cosa abbiamo qui, ragazzi?" << std::endl;
    std::cout << "\n Sgherro : qualcuno che sta trasportando qualcosa di molto importante" << std::endl;
    std::cout << "\n l'altro Sgherro : qualcosa che fara meglio a lasciarci se ci tiene alla vita" << std::endl;

    std::cout << "\n al suono di  quelle parole  minacciose , ti sei deciso a tirare su le maniche e prepararti al peggio " << std::endl;

    GoForwardOnConsole();

    //puntatori smart unici -> gestione automatica della memoria
    std::unique_ptr<Creature> colosso = std::make_unique<Creature>("Colosso", 25, 9, 3, true, std::make_unique<HealingPotion>());
    std::unique_ptr<Creature> sgherro = std::make_unique<Creature>("Sgherro", 15, 2, 6, true, std::make_unique<IncendiaryBomb>());
    std::unique_ptr<Creature> sgherro1 = std::make_unique<Creature>("Sgherro", 15, 2, 6, true, nullptr);
    //array dinamico ci puntatori unici
    std::vector<std::unique_ptr<Creature>> roundOneEnemies;
    
    //trasferire i puntatori dei nemici in una nuova posizione
    roundOneEnemies.push_back(std::move(colosso));
    roundOneEnemies.push_back(std::move(sgherro));
    roundOneEnemies.push_back(std::move(sgherro1));


    //passare la lista di nemici per questo round
    CombactManager::Get().SetEnemies(std::move(roundOneEnemies));
 
    CombactManager::Get().StartAndManageFight();

    GoForwardOnConsole();
}
