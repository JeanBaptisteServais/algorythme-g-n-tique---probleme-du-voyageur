#ifndef SELECTIONVOYAGEUR_H
#define SELECTIONVOYAGEUR_H

#include <string>
#include <list>
#include <vector>

using namespace std;


class selectionVoyageur
{
    public:
        selectionVoyageur();
        virtual ~selectionVoyageur();

        /* ----------------------------------------------SUM------------------------------------------------- */
        void makeSum(int *travelWeight, int *listSumTravel, const int TRAVELLER, const int NUMBER_POINTS);


        /* ------------------------------------------RECUP MINEUR------------------------------------------------ */
        void recuperateMineurElement(int *listSumTravel, vector<vector<int>> &cheminsTraveller, int *saveHighter,
                                    vector<vector<int>> &cheminHighter, const int popSizeSave, const int TRAVELLER);


        /* ------------------------------------------SEARCH ROAD---------------------------------------------- */
        int searchRoad(int score, int *listSumTravel, vector<vector<int>> &cheminsTraveller,
                        vector<vector<int>> &cheminHighter, const int TRAVELLER, int indexSize);


        /* ---------------------------------------------MUTATE 1------------------------------------------------ */
        void mutate(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void choosePairToSwitch(int *randomPoints, const int NUMBER_POINTS, const int NUMBER_SWITCH);
        void changePairs(vector<int> cheminHighter, vector<vector<int>> &cheminMutate,
                        int *randomPoint, const int NUMBER_POINTS, const int NUMBER_SWITCH);
        void displayRandom(int *randomPoints, const int NUMBER_SWITCH);

        void recuperateWeightMutate(vector<vector<int>> &cheminMutate, int *scoreMutate, list<tuple<int, int, int>> weights,
                                    const int popSizeSave, const int NUMBER_POINTS);

        int recuperateWeight(int road1, int road2, list<tuple<int, int, int>> weights);


        /* ---------------------------------------------MUTATE 2------------------------------------------------- */

        void mutate2(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);
        void renverseChromosome(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);


        void displaySequence(vector<int> firstSequence, vector<int> secondSequence);
        void displaySequenceReverse(vector<int> modifiate1, vector<int> modifiate2);
        void displayFiniModifiate(vector<int> roadModifiate);

        /* ---------------------------------------------MUTATE 3------------------------------------------------- */
        void mutate3(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void renverseChromosomeInRange(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);


        /* ---------------------------------------------MUTATE 4------------------------------------------------- */
        void mutate4(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void reverseThree(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);

        /* ---------------------------------------------MUTATE 5------------------------------------------------- */
        void mutate5(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void replaceOneTwo(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);


        /* ---------------------------------------------MUTATE 6------------------------------------------------- */
        void mutate6(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void replaceThree(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);


        /* ---------------------------------------------MUTATE 7------------------------------------------------- */
        void mutate7(vector<vector<int>> &cheminHighter, vector<vector<int>> &cheminMutate,
                    const int popSizeSave, const int NUMBER_POINTS, const int NUMBER_SWITCH);

        void aleatoireProba(vector<int> road, vector<int> &roadModifiate, const int NUMBER_POINTS);


        /* --------------------------------------------REPLACE-------------------------------------------------- */

        void putLastGeneration(int *travelWeight, vector<vector<int>> &cheminsTraveller,
                                int *scoreMutate, vector<vector<int>> &cheminMutate, const int popSizeSave,
                                const int NUMBER_POINTS);

        /* --------------------------------------------DISPLAY-------------------------------------------------- */
        void displaySortSum(int *listSumTravel, vector<int> &copySumTraveller, const int TRAVELLER, const int popSizeSave);
        void displayTreshold(int threshold);



    protected:

    private:
};

#endif // SELECTIONVOYAGEUR_H
