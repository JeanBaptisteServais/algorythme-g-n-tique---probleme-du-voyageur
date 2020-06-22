#include "generateCoord.h"
#include "travelling.h"
#include "selectionVoyageur.h"
#include "display.h"



#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <cstdlib>
#include <list>
#include <tuple>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define WEIGHT 1000
#define HEIGHT 600
#define WINDOW_WAIT 20000000
#define NUMBER_POINTS 8 //Number of coordinates.
#define WEIGHT_SCORE 9   //Length of square.
#define TRAVELLER 10
#define SAVE_GENERATION 2.5 //50% pop
#define SQUAREY 500        //coords aleatoire
#define SQUAREX 1000
#define NUMBER_SWITCH 2
#define STABILISATION 5000

using namespace std;

//Generation of points ---
void generatingCoords(coords *coords, points *pointsCoords);
void displayCoord(list<tuple<int, int>> coord);
void displayWeight(list<tuple<int, int, int>> weight);


//First ---
void Algorythm(points *pointsCoords, int *firstElement, int *counterStab, int *generation,
                int *first, vector<int> &road, int noMutation);
void displayResult(int firstElement, int counterStab, int generation, int first, vector<int> road, string message);

void displayingGraphe(points *pointsCoords, vector<vector<int>> &cheminHighter, SDL_Renderer *renderer, display *display,
                    Uint32 *frameStart, int *frameTime, const int frameDelay);


//a)
void verification();

//b)
void travellingPointAndScore(traveling *traveling, points *pointsCoords, int *travelWeight, vector<vector<int>> &cheminsTraveller);
void displayWeightRoad(int *travelWeight, vector<vector<int>> &cheminsTraveller);
void displayChemin(vector<vector<int>> &cheminsTraveller);

//c)
void recuperateSummaryWeight(selectionVoyageur *selection, int *travelWeight, int *listSumTravel);
void displaySummaryTrav(int *travelWeight, int *listSumTravel);

//d)
void selectionOfTheBestTraveller(selectionVoyageur *selection, int *listSumTravel,  vector<vector<int>> &cheminsTraveller,
                                int *recuperateHighter, vector<vector<int>> &cheminHighter, const int popSizeSave);
void displayBestTravellersScore(int popSizeSave, int *recuperateHighter);
void displayBestTravellersRoad(vector<vector<int>> &cheminHighter, int *recuperateHighter);


//e)
//--------------------------------------------------------------------------------------------------------------- 1)
void makeMutation(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);

//--------------------------------------------------------------------------------------------------------------- 2)
void makeMutation2(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);
//--------------------------------------------------------------------------------------------------------------- 3)
void makeMutation3(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);

//--------------------------------------------------------------------------------------------------------------- 4)
void makeMutation4(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);

//--------------------------------------------------------------------------------------------------------------- 5)
void makeMutation5(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);

//--------------------------------------------------------------------------------------------------------------- 6)
void makeMutation6(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);
//--------------------------------------------------------------------------------------------------------------- 7)
void makeMutation7(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
                  vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);


void beforeMutation(vector<vector<int>> &cheminHighter);
void afterMutation(vector<vector<int>> &cheminMutate);
void displayScoreMutation(vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave);


//f)
void repalceCurrentByLastGen(selectionVoyageur *selection, int *travelWeight, vector<vector<int>> &cheminsTraveller, int *scoreMutate,
                            vector<vector<int>> &cheminMutate, int const popSizeSave);
void displayReplacement(int *travelWeight, vector<vector<int>> &cheminsTraveller, string message);
void displayScoreReplacement(int *travelWeight, string message);

//g)
void stopGeneration(int *listSumTravel, int *firstElement, int *oContiuer, int *counterStab, int *first,
                    vector<vector<int>> &cheminHighter, vector<int> &road, int loop);




int main(int argc, char **args)
{
    cout << "loading" << endl;

    /* -----------------------------------------------SDL----------------------------------------------- */
    SDL_Window   *window{NULL};     //window
    SDL_Renderer *renderer{NULL};   //background

    display displaying;             //class for displaying our points

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;


    //Charge display system SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        displaying.testingSdlElement("Erreur initialisation SDL");

    //Create window
    if (SDL_CreateWindowAndRenderer(WEIGHT, HEIGHT, 0, &window, &renderer) != 0)
        displaying.testingSdlElement("Erreur creation window");//Create window

    //modify color window background.
    if (SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
        displaying.testingSdlElement("Erreur background");

    //Can writting in window.
    if (TTF_Init() != 0)
        displaying.testingSdlElement("Erreur ttf");

    TTF_Font* font = TTF_OpenFont("times-new-roman.ttf", 15);
    if (font == NULL)
        displaying.testingSdlElement("Erreur font");

    /* --------------------------------------------FIN SDL--------------------------------------------------- */







    verification();

    srand (time(NULL));


    coords coords; //Classe pour générer les points et scores.
    points pointsCoords; //Structure des coordonées et des scores.

    //Génération des coordonées et des scores de route.
    generatingCoords(&coords, &pointsCoords);




    /* ------------------------------------------------SDL---------------------------------------------- */

    displaying.drawLine(pointsCoords.coord, pointsCoords.weights, renderer);
    //Displaying all points on window.
    displaying.drawPoints(pointsCoords.coord, renderer);
    //Displaying score on window.
    displaying.drawScores(pointsCoords.coord, pointsCoords.weights, renderer, font);

    SDL_RenderPresent(renderer);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
    else
        SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window); //Destroy window.

    /* --------------------------------------------FIN SDL--------------------------------------------------- */






    /* ------------------------------------------------- Mutation from pairs ------------------------------------------------- */


    vector<int> road;
    int firstElement = 0;
    int counterStab  = 0;
    int generation   = 0;
    int first        = 0;

    Algorythm(&pointsCoords, &firstElement, &counterStab, &generation, &first, road, 1);
    displayResult(firstElement, counterStab, generation, first, road, "\nPAR X PAIR de 2");


    vector<int> road1;
    int firstElement1 = 0;
    int counterStab1  = 0;
    int generation1   = 0;
    int first1        = 0;

    Algorythm(&pointsCoords, &firstElement1, &counterStab1, &generation1, &first1, road1, 2);
    displayResult(firstElement1, counterStab1, generation1, first1, road1, "\nPAR REVERSE 2 PARTS");



    vector<int> road2;
    int firstElement2 = 0;
    int counterStab2  = 0;
    int generation2   = 0;
    int first2        = 0;

    Algorythm(&pointsCoords, &firstElement2, &counterStab2, &generation2, &first2, road2, 3);
    displayResult(firstElement2, counterStab2, generation2, first2, road2, "\nPAR REVERSE ENTRE 2 PARTS");



    vector<int> road3;
    int firstElement3 = 0;
    int counterStab3  = 0;
    int generation3   = 0;
    int first3        = 0;

    Algorythm(&pointsCoords, &firstElement3, &counterStab3, &generation3, &first3, road3, 4);
    displayResult(firstElement3, counterStab3, generation3, first3, road3, "\nPAR REVERSE FROM 1");



    vector<int> road4;
    int firstElement4 = 0;
    int counterStab4  = 0;
    int generation4   = 0;
    int first4        = 0;

    Algorythm(&pointsCoords, &firstElement4, &counterStab4, &generation4, &first4, road4, 5);
    displayResult(firstElement4, counterStab4, generation4, first4, road4, "\nPAR PAIR (1-1)");



    vector<int> road5;
    int firstElement5 = 0;
    int counterStab5  = 0;
    int generation5   = 0;
    int first5        = 0;

    Algorythm(&pointsCoords, &firstElement5, &counterStab5, &generation5, &first5, road5, 6);
    displayResult(firstElement5, counterStab5, generation5, first5, road5, "\nPAR 3");


    vector<int> road6;
    int firstElement6 = 0;
    int counterStab6  = 0;
    int generation6   = 0;
    int first6        = 0;

    Algorythm(&pointsCoords, &firstElement6, &counterStab6, &generation6, &first6, road6, 7);
    displayResult(firstElement6, counterStab6, generation6, first6, road6, "\nPAR mutation partiel");






   /* ------------------------------------------------SDL---------------------------------------------- */
    TTF_Quit ();
    SDL_Quit();                //Liberation memory.
    /* --------------------------------------------FIN SDL--------------------------------------------------- */

}







/* -----------------------------------------------------   ALGORYTHME   ---------------------------------------------------- */
/*                                                (JinJo Algorythme Génétique)                                               */


void Algorythm(points *pointsCoords, int *firstElement, int *counterStab, int *generation, int *first, vector<int> &road, int noMutation)
{
    traveling traveling;         //classe pour faire voyager les points.
    selectionVoyageur selection; //Classe pour selectionner les voyageurs.

    const int popSizeSave = (int)(TRAVELLER / SAVE_GENERATION); //cout << popSizeSave << endl;
    int travelWeight[TRAVELLER * NUMBER_POINTS]{0};
    int listSumTravel[TRAVELLER]{0};
    int recuperateHighter[popSizeSave]{0};
    int scoreMutate[popSizeSave * NUMBER_POINTS]{0};

    vector<vector<int>> cheminsTraveller;
    vector<vector<int>> cheminHighter;
    vector<vector<int>> cheminMutate;

    int oContiuer    = 0;
    int loop         = 0;


    /* ---------------------------------------------------------------------- */
    display display;

    SDL_Window   *window{NULL};     //window
    SDL_Renderer *renderer{NULL};   //background



    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        display.testingSdlElement("Erreur initialisation SDL");

    if (SDL_CreateWindowAndRenderer(1000, 600, 0, &window, &renderer) != 0)
        display.testingSdlElement("Erreur creation window");//Create window


    if (SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
        display.testingSdlElement("Erreur background");

    if (TTF_Init() != 0)
        display.testingSdlElement("Erreur ttf");


    TTF_Font* font = TTF_OpenFont("times-new-roman.ttf", 15);
    if (font == NULL)
        display.testingSdlElement("Erreur font");



    const int fps = 60;
    const int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime;
    /* ---------------------------------------------------------------------- */



    while (oContiuer == 0){
    //for (loop; loop < 2; loop++){


        travellingPointAndScore(&traveling, pointsCoords, travelWeight, cheminsTraveller);

        if (loop > 0){
            repalceCurrentByLastGen(&selection, travelWeight, cheminsTraveller, scoreMutate, cheminMutate, popSizeSave);
            cheminMutate.clear();
            fill(begin(scoreMutate), end(scoreMutate), 0);
        }

        recuperateSummaryWeight(&selection, travelWeight, listSumTravel);

        selectionOfTheBestTraveller(&selection, listSumTravel, cheminsTraveller, recuperateHighter, cheminHighter, popSizeSave);

        displayingGraphe(pointsCoords, cheminHighter, renderer, &display,  &frameStart, &frameTime, frameDelay);


        if (noMutation == 1)
            makeMutation(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 2)
            makeMutation2(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 3)
            makeMutation3(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 4)
            makeMutation4(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 5)
            makeMutation5(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 6)
            makeMutation6(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);

        if (noMutation == 7)
            makeMutation7(&selection, pointsCoords, cheminHighter, cheminMutate, scoreMutate, popSizeSave);


        stopGeneration(listSumTravel, firstElement, &oContiuer, counterStab, first, cheminHighter, road, loop);



        cheminHighter.clear();
        cheminsTraveller.clear();
        fill(begin(travelWeight), end(travelWeight), 0);
        fill(begin(listSumTravel), end(listSumTravel), 0);
        fill(begin(recuperateHighter), end(recuperateHighter), 0);

        loop++;
        *generation = loop;
    }
}

void displayResult(int firstElement, int counterStab, int generation, int first, vector<int> road, string message){

    cout << message << endl;

    cout << "nombre génération : " << first << endl;
    cout << "best road: ";
    for (int i : road){ cout << i; }
    cout << "\nbest score: " << firstElement <<endl;
}


void displayingGraphe(points *pointsCoords, vector<vector<int>> &cheminHighter,
                      SDL_Renderer *renderer, display *display, Uint32 *frameStart, int *frameTime, const int frameDelay)
{
    display->drawRoad(pointsCoords->coord, cheminHighter, renderer);

    //Displaying all points on window.
    display->drawPoints(pointsCoords->coord, renderer);

    *frameStart = SDL_GetTicks();
    *frameTime = SDL_GetTicks()  - *frameStart;

    SDL_RenderPresent(renderer);

    if (frameDelay > *frameTime)
        SDL_Delay(frameDelay - *frameTime);

    display->drawLine(pointsCoords->coord, pointsCoords->weights, renderer);
}


/* -----------------------------------SIXTY ------------------------------------
                         (Stop if we got a stablisation)                       */

void stopGeneration(int *listSumTravel, int *firstElement, int *oContiuer, int *counterStab, int *first,
                    vector<vector<int>> &cheminHighter, vector<int> &road, int loop)
{
    if (listSumTravel[0] == *firstElement) {
        *counterStab += 1;
    }

    else {
        *counterStab = 0;
        *firstElement = listSumTravel[0];
        *first = loop;
    }

    if (*counterStab >= STABILISATION) {
        *oContiuer = 1;
        for (int i : cheminHighter[0]){ road.push_back(i); }
    }

}




/* -----------------------------------FIFTY ------------------------------------
                (Replace last best generation into current generation)        */

void
repalceCurrentByLastGen(selectionVoyageur *selection, int *travelWeight, vector<vector<int>> &cheminsTraveller, int *scoreMutate,
                        vector<vector<int>> &cheminMutate, int const popSizeSave)
{
    //displayReplacement(travelWeight, cheminsTraveller, "Before replacement");
    //displayScoreReplacement(travelWeight, "Before replacement");
    selection->putLastGeneration(travelWeight, cheminsTraveller, scoreMutate, cheminMutate, popSizeSave, NUMBER_POINTS);
    //displayReplacement(travelWeight, cheminsTraveller, "After replacement");
    //displayScoreReplacement(travelWeight, "After replacement");
}



void displayScoreReplacement(int *travelWeight, string message)
{
    cout << message << endl;;
    int counter{0};
    cout << "chemin " << counter << " : ";
    for (int i{0}; i < (TRAVELLER * NUMBER_POINTS); i++)
    {
        if (i % NUMBER_POINTS == 0 && i > 0){ cout << endl; counter++; cout << "chemin " << counter << " : "; }
        cout << travelWeight[i] << " ";
    }
    cout << endl; cout << endl;
}


void displayReplacement(int *travelWeight, vector<vector<int>> &cheminsTraveller, string message)
{
    cout << message << endl;
    int counter{0};
    for (auto element: cheminsTraveller){
        cout << "chemin " << counter << ": ";
        for (int i{0} ; i < NUMBER_POINTS; i++){
            cout << element[i];
        }
        cout << endl;
        counter++;
    }
    cout << endl; cout << endl;
}


/* ----------------------------------FOURTH -----------------------------------
                                 (Make mutation)                              */




/* -------  MUTATION 7 --------
         (Make mutation)       */

void
makeMutation7(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate7(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}



/* -------  MUTATION 6 --------
         (Make mutation)       */

void
makeMutation6(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate6(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}


/* -------  MUTATION 5 --------
         (Make mutation)       */

void
makeMutation5(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate5(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}


/* -------  MUTATION 4 --------
         (Make mutation)       */

void
makeMutation4(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate4(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}


/* -------  MUTATION 3 --------
         (Make mutation)       */

void
makeMutation3(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate3(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}



/* -------  MUTATION 2 --------
         (Make mutation)       */
void
makeMutation2(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    selection->mutate2(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
}

/* -------  MUTATION 1 --------
         (Make mutation)       */
void
makeMutation(selectionVoyageur *selection, points *pointsCoords, vector<vector<int>> &cheminHighter,
            vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    //beforeMutation(cheminHighter);
    selection->mutate(cheminHighter, cheminMutate, popSizeSave, NUMBER_POINTS, NUMBER_SWITCH);
    //afterMutation(cheminMutate);

    selection->recuperateWeightMutate(cheminMutate, scoreMutate, pointsCoords->weights, popSizeSave, NUMBER_POINTS);
    //displayScoreMutation(cheminMutate, scoreMutate, popSizeSave);
}

void
displayScoreMutation(vector<vector<int>> &cheminMutate, int *scoreMutate, const int popSizeSave)
{
    int counter{0};
    for (auto element: cheminMutate)
    {
        cout << "element " << counter << " : ";
        for (int j{0}; j <= NUMBER_POINTS; j++)
            cout << element[j];
        cout << endl;
        counter++;
    }

    cout << endl;

    counter = 0;
    cout << "element " << counter << " : ";
    for (int i{0}; i < (popSizeSave * NUMBER_POINTS); i++)
    {
        if (i % NUMBER_POINTS == 0 && i > 0) { cout << endl; counter++; cout << "element " << counter << " : "; }
        cout << scoreMutate[i] << " ";
    }
    cout << endl;
    cout << endl;
}


void
beforeMutation(vector<vector<int>> &cheminHighter)
{
    cout << "Before Mutation" << endl;
    int counter{0};
    for (auto element: cheminHighter)
    {
        cout << "chemin " << counter << ": ";
        for (int i{0}; i <= NUMBER_POINTS; i++)
        {
            cout << element[i] << " ";
        }
        counter++;
        cout << endl;
    }

    cout << endl;
}

void
afterMutation(vector<vector<int>> &cheminMutate)
{
    cout << "\nAfter Mutation" << endl;
    int counter{0};
    for (auto element: cheminMutate)
    {
        cout << "chemin " << counter << ": ";
        for (int i{0}; i <= NUMBER_POINTS; i++)
        {
            cout << element[i] << " ";
        }
        counter++;
        cout << endl;
    }
    cout << endl;
}




/* ----------------------------------THIRD -----------------------------------
                            (Select mineurs roads.)                         */

void
selectionOfTheBestTraveller(selectionVoyageur *selection, int *listSumTravel,  vector<vector<int>> &cheminsTraveller,
                            int *recuperateHighter, vector<vector<int>> &cheminHighter, const int popSizeSave)
{
    selection->recuperateMineurElement(listSumTravel, cheminsTraveller, recuperateHighter, cheminHighter, popSizeSave, TRAVELLER);
    //displayBestTravellersScore(popSizeSave, recuperateHighter);
    //displayBestTravellersRoad(cheminHighter, recuperateHighter);
}

void
displayBestTravellersRoad(vector<vector<int>> &cheminHighter, int *recuperateHighter)
{
    int counter{0};
    for (auto element: cheminHighter)
    {
        cout << "best road " << counter << " : ";
        for (int i{0}; i <= NUMBER_POINTS; i++)
            cout << element[i] << " ";
        cout << " score : " << recuperateHighter[counter];

        cout << endl;
        counter++;
    }
    cout << endl;
}

void
displayBestTravellersScore(const int popSizeSave, int *recuperateHighter)
{
    for (int i{0}; i <= popSizeSave; i++)
        cout << "higter score " << i << ": " << recuperateHighter[i] << endl;

    cout << endl;
}





/* ---------------------------------- SECOND --------------------------------
                               (Select travellers.)                         */


void
recuperateSummaryWeight(selectionVoyageur *selection, int *travelWeight, int *listSumTravel)
{
    selection->makeSum(travelWeight, listSumTravel, TRAVELLER, NUMBER_POINTS);
    //displaySummaryTrav(travelWeight, listSumTravel);
}


void
displaySummaryTrav(int *travelWeight, int *listSumTravel)
{
    /*
    for (int i{0}; i < TRAVELLER; i++)
        cout << "chemin score " << i << " : " << listSumTravel[i] << endl;
    */
    for (int i{0}; i <= (int)(TRAVELLER / SAVE_GENERATION); i++)
        cout << listSumTravel[i] << " ";

    cout << endl;
}




/* -----------------------------------FIRST ----------------------------------
                   (Recuperate score and generate random travel.)           */

void
travellingPointAndScore(traveling *traveling, points *pointsCoords,
                        int *travelWeight, vector<vector<int>> &cheminsTraveller)
{
    traveling->recuperateScore(pointsCoords->weights, travelWeight,
                                cheminsTraveller, TRAVELLER, NUMBER_POINTS);
    //displayWeightRoad(travelWeight, cheminsTraveller);
    //displayChemin(cheminsTraveller);
}


void
displayWeightRoad(int *travelWeight, vector<vector<int>> &cheminsTraveller)
{
    int counter{1};
    cout << "weights road 0 : ";
    for (int i{0}; i < (TRAVELLER * NUMBER_POINTS); i++)
    {
        if (i % NUMBER_POINTS == 0 & i > 0)
        {
            cout << endl; cout << "weights road " << counter << " : "; counter++;
        }
        cout << travelWeight[i] << "-";
    }
    cout << endl;
    cout << endl;
}


void
displayChemin(vector<vector<int>> &cheminsTraveller)
{
    int counter{0};
    for (auto chemins: cheminsTraveller)
    {
        cout << "chemins " << counter << " : ";
        for (int i{0}; i <= NUMBER_POINTS; i++)
        {
             cout << chemins[i] << " ";
        }
        cout << endl;
        counter++;
    }
    cout << endl;
    cout << endl;
}



/* ------------------------------------------------------ FIN ALGORYTHME 1  -------------------------------------------------- */












/* ---------------------------------------------- VERIFICATIONS DEFINES VARIABLES  ------------------------------------------------ */

void verification()
{

    bool saveGenerationMoreZero = TRAVELLER / SAVE_GENERATION > 0;
    if (saveGenerationMoreZero == false) {cout << "(ligne 304) verification:: generation = 0" << endl; exit(1);}

    bool pairToSwitchNoAllBestPopulation = (TRAVELLER / SAVE_GENERATION) > NUMBER_SWITCH;
    if (pairToSwitchNoAllBestPopulation == false){cout << "ligne (307) iverification:: pair depasse save generation" << endl; exit(1);}

}








/* ------------------------------------ GENERATION DE COORDONNEES ET DE SCORE DE WEIGHTS  ----------------------------- */
void generatingCoords(coords *coords, points *pointsCoords)
{
    coords->generateCoord(pointsCoords->coord, NUMBER_POINTS, SQUAREX, SQUAREY);
    //displayCoord(pointsCoords->coord);

    //coords->generateWeightsPoint(pointsCoords->weights, pointsCoords->coord, WEIGHT_SCORE, NUMBER_POINTS);
    //displayWeight(pointsCoords->weights);

    coords->generateWeightsEuclidean(pointsCoords->weights, pointsCoords->coord, NUMBER_POINTS);
    //displayWeight(pointsCoords->weights);
}

void displayWeight(list<tuple<int, int, int>> weight)
{
    int counter{0};
    for (auto element: weight)
    {
        int pts1  = get<0>(element);
        int pts2  = get<1>(element);
        int score = get<2>(element);
        cout << "coordonnées générées " << counter << ": " << pts1 << " " << pts2 << " score: " << score << endl;
        counter++;
    }
    cout << endl;
}
void displayCoord(list<tuple<int, int>> coord)
{
    int counter{0};
    for (auto element: coord)
    {
        int pts1 = get<0>(element);
        int pts2 = get<1>(element);
        cout << "coordonnées générées " << counter << ": " << pts1 << " " << pts2 << endl;
        counter++;
    }
    cout << endl;
}


