#include "travelling.hpp"


#include <iostream>
#include <list>
#include <tuple>
#include <vector>

using namespace std;



traveling::traveling(){}
traveling::~traveling(){}


void traveling::
recuperateScore(list<tuple<int, int, int>> weights, int* travelWeight, vector<vector<int>> &cheminsTraveller,
                int TRAVELLER, int NUMBER_POINTS)
{
    for (int person = 0; person < TRAVELLER; person++)
    {
        //-------------------------------------------- Recuperate random roads.
        int roadVisited[NUMBER_POINTS + 1]{0};
        searchingARoad(roadVisited, NUMBER_POINTS);
        //displayRandomRoads(roadVisited, NUMBER_POINTS);

        //  ------------------------------------------ Container score and roads.
        int tableauScore[NUMBER_POINTS]{0};
        vector<int> saveRoad;


        //  ------------------------------------------ Sauvegarde score and roads.
        for (int i{0} ; i < NUMBER_POINTS; i++) {

            //  -------------- Sauvegarde score.
            int score = recuperateWeight(roadVisited[i], roadVisited[i + 1], weights);
            travelWeight[(person * NUMBER_POINTS) + i] = score;

            //  -------------- Sauvegarde roads.
            saveRoad.push_back(roadVisited[i]);
        }
        saveRoad.push_back(0);
        cheminsTraveller.push_back(saveRoad);
    }
}




/* Verify traveller hasnt got visited point. */
bool traveling::
searching(int foudPoint, int* roadVisited, int NUMBER_POINTS)
{
    for (int i{0} ; i <= NUMBER_POINTS; i++){ if (roadVisited[i] == foudPoint) { return true; } }
    return false;
}


/* Searching random road. For that run point: 0 - NUMBER_POINTS, stock it and verify traveller isn't pass from it. */
void traveling::
searchingARoad(int* roadVisited, int NUMBER_POINTS)
{
    int randomRoad{0};
    for (int road{1} ; road < NUMBER_POINTS; road++){

        bool oContinuer{true};
        while (oContinuer)
        {
            randomRoad = rand() % (NUMBER_POINTS - 1) + 1;
            oContinuer = searching(randomRoad, roadVisited, NUMBER_POINTS);
        }
        roadVisited[road] = randomRoad;
    }
}


//Recyoerate weight beetween 2 points.
int traveling::
recuperateWeight(int road1, int road2, list<tuple<int, int, int>> weights)
{
    for (auto element: weights)
    {
        int passage1 = get<0>(element); //pos Index1.
        int passage2 = get<1>(element); //pos Index2.
        int score    = get<2>(element); //Score road.

        //Verify.
        bool isMatching = (road1 == passage1 && road2 == passage2) ||
                          (road1 == passage2 && road2 == passage1);
        if (isMatching) { return score; }
    }
    cout << "traveling::recuperateWeight ERROR score, retourne pas de score"; exit(1);
}








void traveling::
displayRandomRoads(int *roadVisited, int NUMBER_POINTS)
{
    cout << "road generated: ";
    for (int i{0} ; i < NUMBER_POINTS; i++)
        cout << roadVisited[i] << "-";

    cout << endl;
    cout << endl;
}