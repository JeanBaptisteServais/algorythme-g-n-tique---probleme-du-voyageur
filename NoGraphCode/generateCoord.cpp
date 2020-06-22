#include "generateCoord.hpp"

#include <tuple>
#include <list>
#include <iostream>
#include <math.h>
#include <vector>

coords::coords(){}
coords::~coords(){}




/* ---------------------------------------------------------------------------------------------------- */
/* Generate randomly weights from pair of coordinates */
void coords::
generateWeightsPoint(list<tuple<int, int, int>> &weights, list<tuple<int, int>> &coordinates,
                    int WEIGHT_SCORE, int NUMBER_POINTS)
{
    //Generate random score beetween 0 - 9.
    for (int i{0} ; i < NUMBER_POINTS ; i++)
    {
        for (int j{0} ; j < NUMBER_POINTS ; j++)
        {
            bool isI = i == j;
            if (!isI) {
                bool isIncrement{verifyIsContains(weights, i, j)};
                if (!isIncrement){
                    auto random = rand()% 9 + 1;
                    weights.push_back(make_tuple(i, j, random));
                }
            }
        }
    }
}

void coords::
generateWeightsEuclidean(list<tuple<int, int, int>> &weights, list<tuple<int, int>> &coordinates,
                        int NUMBER_POINTS)
{
    //Generate euclidean distance score.
    vector <int> coordX; vector <int> coordY;
    for (auto coord: coordinates)
    {
        coordX.push_back(get<0>(coord));
        coordY.push_back(get<1>(coord));
    }

    for (int i{0} ; i < NUMBER_POINTS ; i++)
    {
        for (int j{0} ; j < NUMBER_POINTS ; j++)
        {
            if (!(i == j))
            {
                //Verify if our weight container doesn't contains already
                //the coordinates.
                if (!( verifyIsContains(weights, i, j) )){

                    int elementX = (coordX.at(i) - coordX.at(j)) * (coordX.at(i) - coordX.at(j));
                    int elementY = (coordY.at(i) - coordY.at(j)) * (coordY.at(i) - coordY.at(j));
                    int dist = sqrt( elementX + elementY  );
                    weights.push_back(make_tuple(i, j, dist));
                }
            }
        }
    } 
}


/* Verify there are not doublon scoring */
bool coords::verifyIsContains(list<tuple<int, int, int>> weights, int coordA, int coordB)
{
    for (auto w: weights)
    {
        int index1{get<0>(w)}; //index coord1
        int index2{get<1>(w)}; //index coord2

        //Verify coord arent contains.
        if ( (index1 == coordA && index2 == coordB) ||
             (index1 == coordB && index2 == coordA)
           ) { return true; };
    }
    return false;
}







/* -------------------------------------------------------------------------------------------- */
void coords::
generateCoord(list<tuple<int, int>> &coordinates, int NUMBER_POINTS, int SQUAREX, int SQUAREY)
{
    for (int i{0} ; i < NUMBER_POINTS ; i++)
    {
        auto pointX{rand() % SQUAREX + 1};
        auto pointY{rand() % SQUAREY + 1};

        //cout << "coord found: (" << pointX << " ," << pointY << ")" << endl;
        coordinates.push_back(make_tuple(pointX, pointY));
    }
}