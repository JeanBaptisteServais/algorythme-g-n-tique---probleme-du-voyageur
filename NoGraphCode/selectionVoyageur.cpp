#include "selectionVoyageur.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

selectionVoyageur::selectionVoyageur(){}
selectionVoyageur::~selectionVoyageur(){}



/*----------------------------------------------------- REPLACEMENT -----------------------------------------------
                                         (Changin last best generation in current.)                              */

void selectionVoyageur::
putLastGeneration(int *travelWeight, vector<vector<int>> &cheminsTraveller,
                int *scoreMutate, vector<vector<int>> &cheminMutate, const int popSizeSave, 
                const int NUMBER_POINTS)
{
    //Replace last roads in new generation.
    int counter{0};
    for (auto element: cheminMutate)
    {
        cheminsTraveller.at(counter) = element;
        counter++;
    }

    //Replace last score in new score.
    for (int i{0}; i < (popSizeSave * NUMBER_POINTS); i++) {
        travelWeight[i] = scoreMutate[i];
    }
}




/*------------------------------------------------------- MUTATION 7 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */

void selectionVoyageur::
mutate7(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            aleatoireProba(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
aleatoireProba(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    int probabilite = rand() % 100 + 1;

    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    { for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]); };

    pushing(road, roadModifiate);


    int counter{0};
    for (int i: roadModifiate)
    {
        if (counter != 0 && counter != (roadModifiate.size() - 1)){
            int mutation = rand() % 100 + 1;

            if (mutation < probabilite)
            {
                int position = counter;
                while (position == counter) { position = rand() % (NUMBER_POINTS - 1) + 1; }

                int pair1 = roadModifiate[counter];
                int pair2 = roadModifiate[position];

                roadModifiate[counter]  = pair2;
                roadModifiate[position] = pair1;
            }
        }
        counter++;
    }
}   


/*------------------------------------------------------- MUTATION 6 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */

void selectionVoyageur::
mutate6(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            replaceThree(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
replaceThree(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    int randOne   = rand() % (NUMBER_POINTS - 1) + 1;
    int randTwo   = randOne;
    int randThree = randOne;

    while (randTwo == randOne)                           { randTwo   = rand() % (NUMBER_POINTS - 1) + 1; }
    while (randThree == randOne || randThree == randTwo) { randThree = rand() % (NUMBER_POINTS - 1) + 1; }
    
    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    { for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]); };


    pushing(road, roadModifiate);

    int one = roadModifiate[randOne];
    int two = roadModifiate[randTwo];

    roadModifiate[randOne] = two;
    roadModifiate[randTwo] = one;

    int oneBis = roadModifiate[randOne];
    int three  = roadModifiate[randThree];

    roadModifiate[randOne]   = three;
    roadModifiate[randThree] = oneBis;
}



/*------------------------------------------------------- MUTATION 5 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */

void selectionVoyageur::
mutate5(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            replaceOneTwo(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
replaceOneTwo(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    int randOne = rand() % (NUMBER_POINTS - 1) + 1;
    int randTwo = randOne;
    while (randTwo == randOne) { randTwo = rand() % (NUMBER_POINTS - 1) + 1; }

    vector<int> container;
    int pairOne = road[randOne];
    int pairTwo = road[randTwo];

    int counter{0};
    for (int i: road)
    {
        if      (counter == randOne)  container.push_back(pairTwo);
        else if (counter == randTwo)  container.push_back(pairOne);
        else                          container.push_back(i);
        counter++;
    }

    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    { for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]); };

    pushing(container, roadModifiate);
}


/*------------------------------------------------------- MUTATION 4 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */

void selectionVoyageur::
mutate4(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            reverseThree(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
reverseThree(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    int cutOne = rand() % (NUMBER_POINTS - 3) + 1;

    vector<int> before;
    vector<int> current;
    vector<int> after;

    int counter{0};
    for (int i: road)
    {
        if      (counter < cutOne)                           before.push_back(i);  
        else if (counter >= cutOne && counter <= cutOne + 2) current.push_back(i); 
        else if (counter > cutOne + 2)                       after.push_back(i);   

        counter++;
    }

    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    { for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]); };

    pushing(before, roadModifiate);

    //Function for reverse part of chrom.
    auto reverse = [](vector<int> sequence){
        vector<int> out; for (int i{int(sequence.size() - 1)}; i >= 0; i--) out.push_back(sequence[i]); return out;
    };

    auto modifiate1 = reverse(current);
    pushing(modifiate1, roadModifiate);

    pushing(after, roadModifiate);
}




/*------------------------------------------------------- MUTATION 3 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */

void selectionVoyageur::
mutate3(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            renverseChromosomeInRange(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
renverseChromosomeInRange(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    //Generate two random points.
    int randOne = rand() % (NUMBER_POINTS - 2) + 1;
    int randTwo = randOne;
    while (randTwo == randOne) { randTwo = rand() % (NUMBER_POINTS - 2) + 1; }

    //Make point one less higther point two.
    int cutOne;
    int cutTwo;
    if       (randOne > randTwo) { cutOne = randTwo; cutTwo = randOne; }
    else if  (randTwo > randOne) { cutOne = randOne; cutTwo = randTwo; }

    vector<int> before;
    vector<int> current;
    vector<int> after;

    //push in vector one less point one, in vector two points to reverse.
    int counter{0};
    for (int i: road)
    {
        if      (counter < cutOne) before.push_back(i);
        else if (counter >= cutOne && counter <= cutTwo) current.push_back(i);
        else if (counter > cutTwo) after.push_back(i);

        counter++;
    }

    // 0 1 2 3 4 5 6 0     -> pt1(2) & pt2(5)
    // 0 1 * 2 3 4 5 * 6 0 
    // 0 1 * 5 4 3 2 * 6 0
    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    { for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]); };

    pushing(before, roadModifiate);

    //Function for reverse part of chrom.
    auto reverse = [](vector<int> sequence){
        vector<int> out; for (int i{int(sequence.size() - 1)}; i >= 0; i--) out.push_back(sequence[i]); return out;
    };

    auto modifiate1 = reverse(current);
    pushing(modifiate1, roadModifiate);

    pushing(after, roadModifiate);
}



/*------------------------------------------------------- MUTATION 2 -----------------------------------------------
                                                  (Changin Randomly Pairs.)                                        */
void selectionVoyageur::
mutate2(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            cheminMutate.push_back(roads);
        }
        else
        {   
            vector<int> roadModifiate;
            renverseChromosome(roads, roadModifiate, NUMBER_POINTS);
            cheminMutate.push_back(roadModifiate);
        }
        counter++;
    }
}

void selectionVoyageur::
renverseChromosome(vector<int> roads, vector<int> &roadModifiate, const int NUMBER_POINTS)
{
    vector<int> firstSequence; vector<int> secondSequence;

    int cut = rand() % (NUMBER_POINTS - 2) + 1;
    //cout << "aleatoire: " << cut << endl;

    //Cut chromose in two parts.
    for (int i{1}; i < NUMBER_POINTS; i++)
    {
        if (i >= cut)  secondSequence.push_back(roads[i]);
        else  firstSequence.push_back(roads[i]);
    }

    //displaySequence(firstSequence, secondSequence);

    //Function for reverse part of chrom.
    auto reverse = [](vector<int> sequence){
        vector<int> out; for (int i{int(sequence.size() - 1)}; i >= 0; i--) out.push_back(sequence[i]); return out;
    };

    //Reverse part one and two.
    auto modifiate1 = reverse(firstSequence);
    auto modifiate2 = reverse(secondSequence);
 
    //displaySequenceReverse(modifiate1, modifiate2);

    //Function for pushing part into a new chromo.
    auto pushing = [](vector<int> container, vector<int> &recuperate) -> void
    {
        for (int i{0}; i < container.size(); i++)  recuperate.push_back(container[i]);
    };
 
    roadModifiate.push_back(0);
    pushing(modifiate1, roadModifiate);
    pushing(modifiate2, roadModifiate);
    roadModifiate.push_back(0);

    //displayFiniModifiate(roadModifiate);


}


void selectionVoyageur:: 
displayFiniModifiate(vector<int> roadModifiate)
{
    for (int i: roadModifiate) { cout << i; };
    cout << endl;
}

void selectionVoyageur:: 
displaySequence(vector<int> firstSequence, vector<int> secondSequence)
{
    cout << "first part: ";
    for (int i: firstSequence) { cout << i; };
    cout << endl;
    cout << "second part: ";
    for (int i: secondSequence) { cout << i; };
    cout << endl;
}


void selectionVoyageur::
displaySequenceReverse(vector<int> modifiate1, vector<int> modifiate2)
{
    cout << "first part reverse : ";
    for (int i: modifiate1) { cout << i; };
    cout << endl;
    cout << "second part reverse : ";
    for (int i: modifiate2) { cout << i; };
    cout << endl;
}








/*------------------------------------------------------- MUTATION 1  -----------------------------------------------
                                                 (Changin Randomly x Pairs.)                                        */




/*-----------------------Recuperate weights mutation -------------------- */
void selectionVoyageur::
recuperateWeightMutate(vector<vector<int>> &cheminMutate, int *scoreMutate, list<tuple<int, int, int>> weights,
                     const int popSizeSave, const int NUMBER_POINTS)
{ 
    int counter{0};
    for (auto element: cheminMutate)
    {
        for (int i{0}; i < NUMBER_POINTS; i++)
        {   
            int road1 = element[i];
            int road2 = element[i + 1];

            int score = recuperateWeight(road1, road2, weights);
            scoreMutate[counter] = score;
            counter++;
        }
    }
}

int selectionVoyageur::recuperateWeight(int road1, int road2, list<tuple<int, int, int>> weights)
{
    for (auto element: weights)
    {
        if  ((road1 == get<0>(element) && road2 == get<1>(element)) ||
             (road1 == get<1>(element) && road2 == get<0>(element)))
             { return get<2>(element); }
    }
    cout << "selectionVoyageur :: recuperate Weight no found" << endl; exit(1);
}



/*--------------------Generate mutate road from last best roads. ------------------ */
void selectionVoyageur::
mutate(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate, 
        const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    int counter{0};
    for (auto roads: cheminHighter)
    {
        if (counter == 0)
        {
            int noneTab[2]{-1};
            changePairs(roads, cheminMutate, noneTab, NUMBER_POINTS, NUMBER_SWITCH);
        }
        else
        {
            int randomPoints[NUMBER_SWITCH]{-1};
            choosePairToSwitch(randomPoints, NUMBER_POINTS, NUMBER_SWITCH);
            changePairs(roads, cheminMutate, randomPoints, NUMBER_POINTS, NUMBER_SWITCH);
        }
        counter++;
    }
}


/*-----------------------Switching pairs -------------------- */
void selectionVoyageur::
changePairs(vector<int> cheminHighter, vector<vector<int>> &cheminMutate, 
            int *randomPoint, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    //cheminHighter -> 0123456
    //cheminMutate  -> 0213456
    //randomPoint   -> point to change
    //NUMBER_SWITCH -> number  point to change

    if (randomPoint[0] == -1) 
        cheminMutate.push_back(cheminHighter);
    else
    {
        vector<int> container;
        for (int i{0}; i < NUMBER_POINTS; i++){ container.push_back(cheminHighter[i]); }

        for (int i{0}; i < NUMBER_SWITCH - 1; i++){ 

            int positionPair1 = randomPoint[i];    
            int positionPair2 = randomPoint[i + 1];

            int pair1A = container[positionPair1]; 
            int pair2A = container[positionPair1 + 1];
            int pair1B = container[positionPair2];
            int pair2B = container[positionPair2 + 1];

            container.at(positionPair2 + 1) = pair1A;
            container.at(positionPair2)     = pair2A;
            container.at(positionPair1 + 1) = pair1B;
            container.at(positionPair1)     = pair2B;
        }
        container.push_back(0);
        cheminMutate.push_back(container);
    }
}


/*-----------------------Searching random points to change. -------------------- */
void selectionVoyageur::
choosePairToSwitch(int *randomPoints, const int NUMBER_POINTS, const int NUMBER_SWITCH)
{
    for (int i{0}; i < NUMBER_SWITCH; i++)
    {
        bool oContinuer = true;
        while (oContinuer){

            int generateRandom = rand() % (NUMBER_POINTS - 2) + 1;

            bool nbImpair      = generateRandom % 2 != 0;

            bool verification = true;
            for (int element{0}; element < NUMBER_SWITCH; element++)
                if (randomPoints[element] == generateRandom) { verification = false; break; }

            if (verification && nbImpair) { randomPoints[i] = generateRandom; oContinuer = false; }
        }
    }
    //displayRandom(randomPoints, NUMBER_SWITCH);
}



/*-----------------------DISPLAY -------------------- */
void selectionVoyageur::
displayRandom(int *randomPoints, const int NUMBER_SWITCH)
{
    cout << "random to change: ";
    for (int i{0}; i < NUMBER_SWITCH; i++)
        cout << randomPoints[i] << " ";
 
    cout << endl;
}

 





/*--------------------------------------------- RECUPERATE BEST TRAVELLER --------------------------------------------
                                               (Recuperate best travaller.)                                         */


void selectionVoyageur::
recuperateMineurElement(int *listSumTravel,  vector<vector<int>> &cheminsTraveller, int *saveHighter, 
                        vector<vector<int>> &cheminHighter, const int popSizeSave, const int TRAVELLER)
{
    //1) sort individu.
    vector<int> copySumTraveller;

    for (int i{0} ; i < TRAVELLER ; i++) { copySumTraveller.push_back(listSumTravel[i]); }
    stable_sort (copySumTraveller.begin(), copySumTraveller.end());
    //displaySortSum(listSumTravel, copySumTraveller, TRAVELLER, popSizeSave);


    //2) Recuperate the minimum individu define by threshold.
    int threshold = copySumTraveller.at(popSizeSave);
    //displayTreshold(threshold);


    //3) Save them.
    for (int i{0} ; i < popSizeSave; i++)
    {
        // ----------- a) Recuperate score.
        int sumSave = copySumTraveller.at(i);
        saveHighter[i] = sumSave;

        // ----------- b) Recuperate road.
        int indexChemin  = searchRoad(sumSave, listSumTravel, cheminsTraveller, cheminHighter, TRAVELLER, i); 
        cheminHighter.push_back(cheminsTraveller[indexChemin]);
    }
}


/* Searching from the original list non sorted roads. */

int selectionVoyageur::
searchRoad(int score, int *listSumTravel, vector<vector<int>> &cheminsTraveller, 
            vector<vector<int>> &cheminHighter, const int TRAVELLER, int indexSize)
{
    for (int i{0} ; i < TRAVELLER; i++)
    {
        bool isMatching  = score == listSumTravel[i];

        auto recup = cheminsTraveller.at(i);

        //Verify we havnt got the current adress in case two road have the same score.
        bool noContains = true;
        for (auto saveElement: cheminsTraveller)
            for (auto highterElement: cheminHighter)
                if (saveElement == highterElement)  
                break; 

        if (isMatching && noContains) { return i; }
    }
    cout << "erreur: selectionVoyageur::searchRoad erreur no found chemin...." << endl;
    exit(1);

}


/*-----------------------DISPLAY -------------------- */


void selectionVoyageur::
displayTreshold(int threshold)
{
    cout << "threshold value: " << threshold << endl;
    cout << endl;
}

void selectionVoyageur::
displaySortSum(int *listSumTravel, vector<int> &copySumTraveller, const int TRAVELLER, const int popSizeSave)
{
    cout << "scores: ";
    for (int i{0}; i < TRAVELLER; i++)
        cout << listSumTravel[i] << " ";

    cout << endl;

    cout << "selections: ";
    for (int i{0}; i <= popSizeSave; i++)
        cout << copySumTraveller[i] << " ";

    cout << endl;
}




/*---------------------------------------------------- MAKE SUMMARY -----------------------------------------------
                                           (Recuperate total score travaller.)                                    */


void selectionVoyageur::
makeSum(int *travelWeight, int *listSumTravel, const int TRAVELLER, const int NUMBER_POINTS)
{
    int sum{0};      //increment sum.
    int counter{0}; //increment travellers.

    for (int i{0}; i < TRAVELLER * NUMBER_POINTS; i++)
    {
        if ( i % NUMBER_POINTS == 0 && i > 0 ) //number of country by one traveller.
        {
            listSumTravel[counter] = sum; //recuperate his sum(score).
            sum  = 0;                     //reinitialise sum
            counter += 1;                 //increment traveller.
        }
        sum += travelWeight[i];//increment sum
    }
    listSumTravel[counter] = sum; //last traveller
}