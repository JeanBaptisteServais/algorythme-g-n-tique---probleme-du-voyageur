#include "display.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <tuple>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>


using namespace std;


struct displaying{
    TTF_Font* font = TTF_OpenFont("times-new-roman.ttf", 18);
};


/* ---------------------------------------------------------------------------------------------------- */
display::display(){}
display::~display(){}








//Displaying all lines on window. weights[0] & weight[1] == pair & weights[2] = score;
void display::drawRoad(list<tuple<int, int>> coord, vector<vector<int>> &cheminHighter, SDL_Renderer *renderer)
{

    int counter{0};

    for (vector<int> element: cheminHighter)
    {
        //for (int i{element.size() - 1}; i > 0; i--)
        for (int i{0}; i < element.size(); i++)
        {
            tuple<int, int> coordinate1 = recuperateIndexFromList(element[i], coord);
            tuple<int, int> coordinate2 = recuperateIndexFromList(element[i + 1], coord);

            //cout << element[i] << " " << element[i + 1];

            if      (counter == 0)  {modifyColorElement(255, 0, 0, renderer);}
            else if (counter == 1)  {modifyColorElement(255, 255, 0, renderer);}
            else if (counter == 2)  {modifyColorElement(0, 255, 0, renderer);}
            else if (counter == 3)  {modifyColorElement(0, 0, 255, renderer);}

            auto verify{SDL_RenderDrawLine(renderer,
                get<0>(coordinate1), get<1>(coordinate1),
                get<0>(coordinate2), get<1>(coordinate2))};
            if (verify != 0)testingSdlElement("Erreur coordinate line");
        }
        counter++;
        //if (counter == 2) { break; }
        break;
    }
}








/* ---------------------------------------------------------------------------------------------------- */
//Drawing score in midle of liaison of points.
void display::drawScores(list<tuple<int, int>> coord, list<tuple<int, int, int>> weights,
                         SDL_Renderer *renderer, TTF_Font* font)
{
    //-----------------------------------------------------Index Score
    for (auto w: weights)
    {
        int index1{get<0>(w)}; //index coord1.
        int index2{get<1>(w)}; //index coord2.
        int score{get<2>(w)};  //score beetween coords.
        for (int i{0} ; i < 10 ; i++)
        {
            tuple<int, int> a{recuperateIndexFromList(index1, coord)}; //Recuperate coord1.
            tuple<int, int> b{recuperateIndexFromList(index2, coord)}; //Recuperate coord2.
            string msg = to_string(score);  //Recuperate score.

            //Middle of vectors.
            int X = (get<0>(a) + get<0>(b))/2;
            int Y = (get<1>(a) + get<1>(b))/2;

            //Display scores.
            putScore(font, msg.c_str(), make_tuple(X, Y), renderer, 255, 255, 255);


            //--------------------------------------------------------Index Point

            string msgIndex1 = to_string(index1);  //Recuperate index1.
            putScore(font, msgIndex1.c_str(), a, renderer, 0, 255, 0);

            string msgIndex2 = to_string(index2);  //Recuperate index2.
            putScore(font, msgIndex2.c_str(), b, renderer, 0, 255, 0);
        }
    }
}

void display::putScore(TTF_Font* font, const char *msg, tuple<int, int> coords, SDL_Renderer *renderer, int r, int g, int b)
{
    // Crée un surface qui contient le texte
    SDL_Surface* text = TTF_RenderText_Blended(font, msg, { r, g, b, 255 });

    if (text == NULL)
        testingSdlElement("Erreur text");

    // Crée la texture qu'on va afficher a partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    if (texture == NULL)
        testingSdlElement("Erreur texture");

    SDL_Rect position{get<0>(coords), get<1>(coords), 20, 20};


    // Récupere la dimension de la texture
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, texture, nullptr, &position);
    SDL_RenderPresent(renderer);
}








/* ---------------------------------------------------------------------------------------------------- */
//Displaying all lines on window. weights[0] & weight[1] == pair & weights[2] = score;
void display::drawLine(list<tuple<int, int>> coord, list<tuple<int, int, int>> weights, SDL_Renderer *renderer)
{
    //weights -> [(0, 1, 10), (0, 20, 20)]
    //coord   -> [(10, 10), (0, 20), (15, 10)]
    for (auto w: weights)
    {
        int index1{get<0>(w)}; //index coord1
        int index2{get<1>(w)}; //index coord2
        int score{get<2>(w)};  //score beetween coords.

        tuple<int, int> coordinate1{recuperateIndexFromList(index1, coord)};
        tuple<int, int> coordinate2{recuperateIndexFromList(index2, coord)};

        modifyColorElement(182, 182, 182, renderer);
        auto verify{SDL_RenderDrawLine(renderer,
            get<0>(coordinate1), get<1>(coordinate1),
            get<0>(coordinate2), get<1>(coordinate2))};
        if (verify != 0)testingSdlElement("Erreur coordinate line");

    }
}
//Recuperate element in list from index.
tuple<int, int> display::recuperateIndexFromList(int index, list<tuple<int, int>> coord)
{
    auto returning{make_tuple(0, 0)};
    int counter{0};

    for (auto i: coord)
    {
        bool isIndex = counter == index;
        if (isIndex) { return i; }
        counter++;
    }
    return returning;
}





/* ---------------------------------------------------------------------------------------------------- */
//Displaying all points on window.
void display::drawPoints(list<tuple<int, int>> &coordinates, SDL_Renderer *renderer)
{
    //Displaying all points.
    int counter{0};
    for (tuple<int, int> coord: coordinates){
        bool isDeparture{counter == 0};

        if (isDeparture) { //Put red point.
            modifyColorElement(255, 0, 0, renderer);
            createPoints(coord, renderer);
        }
        else{   //Put blue points.
            modifyColorElement(0, 0, 255, renderer);
            createPoints(coord, renderer);
        }
        counter++;
    }
}


/* ---------------------------------------------------------------------------------------------------- */
/* Make coordinates display like croix */
void display::createPoints(tuple<int, int> coods, SDL_Renderer *renderer)
{
    //Recuperate (x, y)
    auto coordX{get<0>(coods)};
    auto coordY{get<1>(coods)};

    //Make croix X coord
    auto functionX = [](int coordX, int coordY, int coordA, int coordB, SDL_Renderer *renderer)
        {
            SDL_RenderDrawPoint(renderer, coordX,  coordA);
            SDL_RenderDrawPoint(renderer, coordX,  coordB);
            return SDL_RenderDrawPoint(renderer, coordX,  coordY);
        };
    //Make croix Y coord
    auto functionY = [](int coordX, int coordY, int coordA, int coordB, SDL_Renderer *renderer)
        {
            SDL_RenderDrawPoint(renderer, coordA,  coordY);
            SDL_RenderDrawPoint(renderer, coordB,  coordY);
            return SDL_RenderDrawPoint(renderer, coordX,  coordY);
        };

    //Make length of croix
    for (int i{0} ; i <= 6 ; i++)
    {

        auto verify0{functionX(coordX + i, coordY, coordY - 1, coordY + 1, renderer)};
            if (verify0 != 0)  testingSdlElement("Erreur coordinate 1");

        auto verify1{functionX(coordX - i, coordY, coordY - 1, coordY + 1, renderer)};
            if (verify1 != 0)  testingSdlElement("Erreur coordinate 2");

        auto verify2{functionY(coordX,  coordY + i, coordX - 1, coordX + 1, renderer)};
            if (verify2 != 0)  testingSdlElement("Erreur coordinate 3");

        auto verify3{functionY(coordX,  coordY - i, coordX - 1, coordX + 1, renderer)};
            if (verify3 != 0)  testingSdlElement("Erreur coordinate 4");
    }
}


/* ---------------------------------------------------------------------------------------------------- */
/* Modify color of objects */
void display::modifyColorElement(int r, int g, int b , SDL_Renderer *renderer)
{
    if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0)
        testingSdlElement("Erreur background");
}






/* ---------------------------------------------------------------------------------------------------- */
/* Testing function od SDL if return 0 */
void display::testingSdlElement(const char *message)
{
    SDL_Log("Erreur background modification");
    exit(EXIT_FAILURE);
}


