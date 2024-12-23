#include <stdio.h>
#include <iostream>

using namespace std;

//BouncyBalls - classes

#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include "SDL.h"
#include "SDL_image.h"
#include "BouncyBall.h"
#include "Plane.h"
#include "TextureManager.h"

using namespace std;

static TextureManager* textureManager = nullptr;
static const int nBalls = 10;
static SDL_Texture* ballTex = nullptr, *planeTex = nullptr;
list<GameObject*> gameObjects;
//BouncyBall balls[nBalls];
//Plane plane;

int processEvents(SDL_Window* window)
{
	SDL_Event event;
	int done = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		}
		break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}
	return done;
}

void doRender(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 240, 240, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//SDL_Rect rect = { 0,0,32,32 };
	//SDL_RenderCopy(renderer, ball, nullptr, &rect);

	for (auto gameObject : gameObjects)
	{
		gameObject->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

void doUpdates()
{
	list<list<GameObject*>::iterator> toDie;
	int numBalls = 0, numPlanes = 0;

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		auto gameObject = *it;

		gameObject->update();

		Plane* planePtr = dynamic_cast<Plane*>(gameObject);
		BouncyBall* ballPtr = dynamic_cast<BouncyBall*>(gameObject);
		if (ballPtr != nullptr)
		{
			//can safely use ball
			numBalls++;
		}
		else if (planePtr != nullptr)
		{
			if (planePtr->getX() < -32)
			{
				//non possiamo eliminare un elemento mentre lo stiamo iterando
				//quindi lo aggiungiamo a una lista di elementi da eliminare
				toDie.push_back(it);
			}
			numPlanes++;
		}
	}

	for (auto iit : toDie)
	{
		delete* iit;
		gameObjects.erase(iit);
	}

	if (numPlanes == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			Plane* plane = new Plane;
			plane->setTexture(planeTex);
			plane->setPos(640-rand() % 100, rand() % 480 - 40);
			gameObjects.push_back(plane);
		}
	}
}

int main(int argc, char* argv[])
{
	// Initialize random seed
	srand(time(nullptr));

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		"Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TextureManager::setRenderer(renderer);
	textureManager = new TextureManager;

	ballTex = textureManager->getTexture("ball.png");
	planeTex = textureManager->getTexture("plane.png");

	for (int i = 0; i < nBalls; i++)
	{
		BouncyBall *ball = new BouncyBall;
		ball->setPos(50 + i * 32, 100);
		ball->setTexture(ballTex);
		ball->setElasticity((float)i / nBalls);

		gameObjects.push_back(ball);
	}


	int done = 0;

	while (!done)
	{
		done = processEvents(window);

		doUpdates();

		doRender(renderer);

		SDL_Delay(10);
	}

	for (auto gameObject:gameObjects)
	{
		delete gameObject;
	}
	gameObjects.clear();

	SDL_DestroyTexture(ballTex);
	SDL_DestroyTexture(planeTex);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete textureManager;

	SDL_Quit();
	return 0;
}


//IntArray - operator override
/*#include "IntArray.h"

void func()
{
	IntArray a(100), b(200);

	for (int i = 0; i < 100; i++)
	{
		a.set(i, i*2);
	}
	for (int i = 0; i < 200; i++)
	{
		b.set(i, i * 4);
	}

	IntArray c = a + b;

	c[101] = 50;
	printf("%d\n", c[101]);

}

int main()
{
	func();

	return 0;
}
*/

//Encapsulated int - implicit conversion
/*#include <iostream>

using namespace std;

static int numberOfAdditions = 0;

class EncapsulatedInt
{
public:
	EncapsulatedInt()
	{ }

	EncapsulatedInt(int someInt)
	{
		i = someInt;
	}

	//operators
	EncapsulatedInt operator+(const EncapsulatedInt& rhs)
	{
		numberOfAdditions++;
		return EncapsulatedInt(i + rhs.i);
	}

	//implicit conversion
	operator int()
	{
		return i;
	}

private:
	int i = 0;
};

void func(int i)
{
	cout << "func gets " << i << endl;
}

int main()
{
	EncapsulatedInt a, b(10);
	auto c = a + b;

	int i = c;
	func(c);

	cout << numberOfAdditions << endl;

	return 0;
}*/

//new and delete
/*using namespace std;

class Example
{
public:
	~Example()
	{
		cout << "destructor of example\n";
	}
};

int main()
{
	Example* e = new Example[100];

	delete []e; //if you call new with [] you have to call delete with [] or it wont
				//call all the destructors
	return 0;
}*/

//templates
/*using namespace std;

//instead of writing a function for each type i can use templates, so the compiler will do that
template <typename NumberType>
NumberType powerOf2(NumberType i)
{
	return i * i;
}

int main()
{
	cout << powerOf2(0.5) << endl;
	cout << powerOf2(0.5f) << endl;

	return 0;
}
*/

//data structures
/*when to use:
	maps when searching by key (indexes)
	sets when searching by value (also when uniqness needed)
	lists when doing many insertions/deletions in middle
	vectors for everything else
*/
/*#include <vector>

int main()
{
	vector<int> v;

	v.push_back(0);
	v.push_back(1);
	v.push_back(2);

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	//or you can use the human syntax (foreach)
	for (int& i : v)
	{
		cout << i << endl;
	}
	//or better
	for(auto i : v)
	{
		cout << i << endl;
	}
}
*/
