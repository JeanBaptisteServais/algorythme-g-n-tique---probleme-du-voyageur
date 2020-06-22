#ifndef COORDS_H
#define COORDS_H

#include <tuple>
#include <list>

using namespace std;


struct points{
    list<tuple<int, int, int>> weights;
    list<tuple<int, int>> coord;
};

class coords
{
    public:
        coords();

        void generateCoord(list<tuple<int, int>> &coordinates, int NUMBER_POINTS, int SQUAREX, int SQUAREY);
 
        void generateWeightsPoint(list<tuple<int, int, int>> &weghts, list<tuple<int, int>> &coordinates,
                             int WEIGHT_SCORE, int NUMBER_POINTS);
        void generateWeightsEuclidean(list<tuple<int, int, int>> &weghts, list<tuple<int, int>> &coordinates,
                             int NUMBER_POINTS);

        bool verifyIsContains(list<tuple<int, int, int>> weights, int i, int j);


        virtual ~coords();


    protected:

    private:
};

#endif // COORDS_H