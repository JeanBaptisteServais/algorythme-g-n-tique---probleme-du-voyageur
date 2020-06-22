# algorythme-g-n-tique---probleme-du-voyageur
traveller problem, algorythme génétic and mutation technicsss

Can for example we can propose the minus road for navigate into a store and search quickly toilet, or with the preferance of the person propose him minimum road with store feeling on a A point to a B point

  - 2 choices of points (euclidean or number 0 - x)
  - choice to stop (stabilisation of the better road of 2000 générations)
  - choice of number of road


<h1>Selection 1</h1>

by competition or selection havnt understood, recuperate the x of the population (we can choose it)

![a](https://user-images.githubusercontent.com/54853371/85343886-6a7cc780-b4ee-11ea-820a-54a54a138981.png)

<h3>Mutation 1</h3> 
by changing pairs: 0 1 2 3 4 5 6 -> 12/34 -> 0 4 3 2 1 5 6 

<h3>Mutation 2</h3>
by changing one pair: 0 1 2 3 4 5 6 -> 1/3 -> 0 3 2 1 4 5 6 

<h3>Mutation 3</h3>
by seq reverse:  0 1 2 3 4 5 6 -> 3 -> 0 3 2 1 6 5 4 

<h3>Mutation 4</h3>
by reverse from one points:  0 1 2 3 4 5 6 -> 3 -> 0 1 2 6 5 4 3

<h3>Mutation 5</h3>
by probaility -> define P / generation p -> if p < P - generate other point to change


<h3>Mutation 6</h3> 
replace three points randomly -> i -> j -> i -> j ->  0 1 2 3 4 5 6 -> 1 3 5 -> 0 3 2 1 4 5 6 -> 0 5 2 1 4 3 6

<h3>Mutation 7</h3>
reverse three -> 0 1 2 3 4 5 6 -> 2 -> 0 1 4 3 2 5 6

<br><br>



![road](https://user-images.githubusercontent.com/54853371/85343888-6b155e00-b4ee-11ea-9e69-23b541b142de.gif)<br>
(take long but it moves)
<br><br><br><br>

![all](https://user-images.githubusercontent.com/54853371/85343854-589b2480-b4ee-11ea-8fd2-05ccb7e25c9f.gif)
red - highter, blue, green and yellow are the 2.5 save of the 10 individu
<br><br>

![c](https://user-images.githubusercontent.com/54853371/85343849-56d16100-b4ee-11ea-89d1-47d543a21ede.png)
![b](https://user-images.githubusercontent.com/54853371/85343851-58028e00-b4ee-11ea-911b-79b221d2e3f2.png)






Download SDL2 / SDL_ttf (for graph code)
