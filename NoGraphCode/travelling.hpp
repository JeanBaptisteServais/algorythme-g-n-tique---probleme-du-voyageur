#ifndef TRAVELING_H
#define TRAVELING_H



#include <list>
#include <tuple>
#include <vector>


using namespace std;


class traveling
{
    public:
        traveling();

        void recuperateScore(list<tuple<int, int, int>> weights, int* travelWeight, vector<vector<int>> &cheminsTraveller,
                            int TRAVELLER, int NUMBER_POINTS);

        void searchingARoad(int* roadVisited, int NUMBER_POINTS);

        bool searching(int foudPoint, int* roadVisited,  int NUMBER_POINTS);

        int  recuperateWeight(int road1, int road2, list<tuple<int, int, int>> weights);

        virtual ~traveling();





        void displayRandomRoads(int* roadVisited, int NUMBER_POINTS);



    protected:

    private:
};

#endif // TRAVELING_H
