#ifndef DISPLAY_H
#define DISPLAY_H

#include "generateCoord.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <tuple>
#include <string>
#include <list>
#include <vector>

using namespace std;


class display
{
    public:
        display();


        void drawPoints(list<tuple<int, int>> &coordinates, SDL_Renderer *renderer);
        void drawLine(list<tuple<int, int>> coord, list<tuple<int, int, int>> weights, SDL_Renderer *renderer);
        tuple<int, int> recuperateIndexFromList(int index, list<tuple<int, int>> coord);

        void drawScores(list<tuple<int, int>> coord, list<tuple<int, int, int>> weights,
                        SDL_Renderer *renderer, TTF_Font* font);
        void putScore(TTF_Font* font, const char *msg, tuple<int, int> coords, SDL_Renderer *renderer, int r, int g, int b);

        void drawRoad(list<tuple<int, int>> coord, vector<vector<int>> &cheminHighter, SDL_Renderer *renderer);

        void createPoints(tuple<int, int> coods, SDL_Renderer *renderer);
        void modifyColorElement(int r, int g, int b , SDL_Renderer *renderer);


        void testingSdlElement(const char *message);



        virtual ~display();



    protected:

    private:
};

#endif // DISPLAY_H
