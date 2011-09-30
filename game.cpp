
#include "game.h"


game * activGame;


		void game::spawnHoleRow(){
			int rowHole;
			rowHole=rand()%16;
			cout << "rowHole";
			for (int i=1;i<21;i++){
				if (i <=rowHole || i >= rowHole+4 )
				otherObjects.push_back( new block (i*5, 80, 5,rand()%4));
			}

		}

		GLuint game::loadTexture(Image *image) {
			GLuint textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGB,
					image->width, image->height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					image->pixels);
			return textureId;
		}



		void game::timerCallback()
		{
		if (firstResize) {
			glutReshapeWindow(640,480);
			firstResize=0;
			printf("First Reshape");
		}
			object::activGame->gameTime += 1;
			if (noBlockGeneration <= 0){
				if (rand() % 100000 > (99990-score)){
					spawnHoleRow();	
					noBlockGeneration = 600;
				}
				
				else if (rand() % 1000 > 995-(score/10))
					otherObjects.push_back( new block ((rand() % 18+1)*5, 80, 5,rand()%4));
			}
			else
				noBlockGeneration--;



			if (score == 20) {
				otherObjects.push_back(new addon (rand() % 100, 80, 1, 1));
				score++;

			}
			list<object *>::iterator it;
			//          thePlayer-> timerCallback(0.5);
			for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
				if  (!(*it)->timerCallback(0.1)){
						delete *it;
					it = otherObjects.erase (it);
					//score++;
				}

			handleCollisions();


		}


		void game::plot()
		{
			glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer


			list<object *>::iterator it;
			for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
				(*it)->plot();

			glColor3f(0.0f, 0.0f, 1.0f);
			glRasterPos2i(30, 110);
			glColor3f(0.0f, 0.0f, 1.0f);
			const char* textToRender = "your points:";
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned const char*)textToRender );
			char buffer[12];
			sprintf(buffer, "%d", score);
			glColor3f(0.0f, 0.0f, 1.0f);
			glRasterPos2i(30, 105);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned const char*)buffer );


		}


		void game::spawnObject(object *p) {
			otherObjects.push_back (p);
		}

game::game () : score (0), gameTime (0)
		{

			srand (time(NULL));
			otherObjects.push_back(new bamster( 20, 50));
			otherObjects.push_back(new hwall (50,0,100));
			otherObjects.push_back(new hwall (50,100,100));

			otherObjects.push_back(new vwall (0,50,100));
			otherObjects.push_back(new vwall (100,50,100));
			noBlockGeneration = 0;
			score = 0;
		firstResize=1;
		}

void game::handleCollisions()
{
	//object-object

	list<object*>::iterator it, jt, next;

	unsigned int counteri, counterj;
	char fromWhere;


	for (it = otherObjects.begin() ; it != otherObjects.end(); it++)
	{
		jt = it;
		for (jt++; jt != otherObjects.end(); jt++)
		{
			if ((fromWhere = ((* it)->collidesWith (**jt))))
			{
				(*it)-> collision(*jt, fromWhere);
				(*jt)-> collision(*it, otherSide(fromWhere));


			}
		}

	}

}




