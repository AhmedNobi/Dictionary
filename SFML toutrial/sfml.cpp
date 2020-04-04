#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;
#define maze_y 23
#define maze_x 28
int x, score = 0, x_pink = 0, y_pink = 0;
RenderWindow window(VideoMode(512, 600), "Pacman!", Style::Default);
RectangleShape wall1(Vector2f(485.f, 8.f)), wall2(Vector2f(8.f, 550.f)), wall3(Vector2f(488.f, 8.f)), wall4(Vector2f(8.f, 550.f)), squ(Vector2f(10.f,10.f));
RectangleShape red(Vector2f(14.f, 20.f)), pink(Vector2f(14.f, 20.f)), blue(Vector2f(14.f, 20.f)), brown(Vector2f(14.f, 20.f)), virtual_ghost(Vector2f(14.f, 20.f));
CircleShape point(3), hero(9);
Texture heroTexture, red_texture, pink_texture, blue_texture, brown_texture;
vector < RectangleShape > wall;
vector < CircleShape > points;
int hero_speed = 10, red_speed = 5, pink_speed = 5, blue_speed = 5, brown_speed = 3;
Vector2f pos((float) 0.2, (float) 0.0), pink_target, blue_target, dest[4], vaild;
char maze[maze_y][maze_x]=
{

    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},		//1
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},		//2
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},		//3
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},		//4
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//5
    {1,0,1,1,1,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,0,1},		//6
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},		//7
    {1,1,1,1,1,1,0,1,0,1,1,1,2,1,1,2,1,1,0,1,1,0,0,0,1,1,0,1},		//8
    {2,2,2,2,2,1,0,1,0,1,1,1,2,1,1,2,1,1,0,1,1,0,1,0,0,0,0,0},		//9
    {2,2,2,2,2,1,0,1,0,2,2,2,2,'R',2,2,2,2,2,0,0,0,0,2,0,0,2,2},	//10
    {1,1,1,1,1,1,0,1,1,2,1,1,1,4,4,1,1,1,2,1,1,0,0,1,0,0,0,1},		//11
    {'T',2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,'T'},	//12
    {1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1},		//13
    {2,2,2,2,2,1,0,1,1,2,2,2,2,3,2,2,2,2,0,1,1,0,0,2,2,2,0,1},		//14
    {1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},		//15
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},		//16
    {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},		//17
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//18
    {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},		//19
    {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},		//20
    {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},		//21
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//22
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},		//23

};

void load_texture();
void set_position();
void set_color();
void draw();
void maze_draw();
bool check_hero_move(CircleShape);
bool check_ghost_move(RectangleShape);
void move_hero(int);
Vector2f destination(RectangleShape &, Vector2f, int );
void move_ghost(RectangleShape &, Vector2f, int);

int main()
{
	/// calling the function
	set_color();
	load_texture();
	set_position();
	// array of points
	for(int i = 0; i < 300; i++)
		points.push_back(point);
	// array of walls
	for(int i = 0; i < 255; i++)
		wall.push_back(squ);	

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// if pressed on 'X' sign close the window
			if(event.type == event.Closed)
				window.close();
		}
		move_hero(hero_speed);
		move_ghost(red, hero.getPosition(), red_speed);
		move_ghost(pink,pink_target, pink_speed);
		//move_ghost(blue,blue_target, 4);
		move_ghost(brown,hero.getPosition(), brown_speed);
		window.clear();
		maze_draw();
		draw();
		window.display();// display the window
	}

    return 0;
}
/*int main ()
{
	RectangleShape rect(Vector2f(10, 10));
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == event.Closed)
				window.close();
		}
		FloatRect Prect = rect.getLocalBounds();
		window.draw(rect);
		window.display();
	}
	return 0;
}*/
void load_texture()
{
	//hero
	heroTexture.loadFromFile("pacman1.png");

	hero.setTexture(&heroTexture);
	//ghosts
	red_texture.loadFromFile("red.png");
	pink_texture.loadFromFile("pink.png");
	blue_texture.loadFromFile("blue.png");
	brown_texture.loadFromFile("brown.png");

	red.setTexture(&red_texture);
	pink.setTexture(&pink_texture);
	blue.setTexture(&blue_texture);
	brown.setTexture(&brown_texture);

}

void set_position()
{
	//hero
	hero.setOrigin(9, 9);
	
	hero.setPosition(240, 260);
	
	//ghosts
	red.setOrigin(7, 10);
	pink.setOrigin(7, 10);
	blue.setOrigin(7, 10);
	brown.setOrigin(7, 10);
	
	red.setPosition(240, 240);
	pink.setPosition(200, 260);
	blue.setPosition(240, 220);
	brown.setPosition(280, 240);
	
	//objects
	squ.setOrigin(5, 5);
	wall1.setOrigin(242.5, 4);
	wall2.setOrigin(4, 275);
	wall3.setOrigin(244, 4);
	wall4.setOrigin(4, 275);
	wall1.setPosition(242.5, 4);
	wall2.setPosition(4, 275);
	wall3.setPosition(244, 554);
	wall4.setPosition(484, 275);
	
}

void set_color()
{
	//objects
	squ.setFillColor(Color::Blue);
	wall1.setFillColor(Color::Blue);
	wall2.setFillColor(Color::Blue);
	wall3.setFillColor(Color::Blue);
	wall4.setFillColor(Color::Blue);
	point.setFillColor(Color::White);

	
	//hero
	hero.setFillColor(Color::Yellow);

}

void draw()
{
	//ghosts
	window.draw(red);
	window.draw(pink);
	window.draw(blue);
	window.draw(brown);
	
	//walls
	window.draw(wall1);
	window.draw(wall2);
	window.draw(wall3);
	window.draw(wall4);

	//hero
	window.draw(hero);

}
// drawing the maze on the window
void maze_draw()
{
	int points_counter = 0, wall_counter = 0, width = 22, length = 20;
	for(int i=0; i<23; i++)
        for(int j=0; j<28; j++)
        {
            if(maze[i][j] == 0) // if maze = 0 draw a point
			{
				points[points_counter].setPosition((float) i * width,(float) j * length); // setting where to draw the point
				window.draw(points[points_counter]); // draw a point 
				points_counter ++; // increase points counter
			}
			else if(maze[i][j] == 1 && i != 0 && j !=0 && i != maze_y - 1 && j != maze_x - 1) // if maze = 1 draw a wall and ignore the wall on the boarder 
			{
				wall[wall_counter].setPosition((float) i * width,(float) j * length); // setting where to draw the wall
				window.draw(wall[wall_counter]); // draw a wall
				wall_counter ++; //increase wall counter
			}
		}
}

bool check_hero_move(CircleShape object)
{
	// if the object (hero) over main walls (map's boarders) return false
	if (object.getGlobalBounds().intersects(wall1.getGlobalBounds()) || object.getGlobalBounds().intersects(wall2.getGlobalBounds()) || object.getGlobalBounds().intersects(wall3.getGlobalBounds()) || object.getGlobalBounds().intersects(wall4.getGlobalBounds()))
        return false;
	// if the object (hero) over any wall inside the map return false
	for(int i = 0; i < (int)wall.size(); i++)
		if(object.getGlobalBounds().intersects(wall[i].getGlobalBounds()))
			return false;
	// else return true
    return true;
}

bool check_ghost_move(RectangleShape object)
{
	// if the object (ghost) over main walls (map's borders) return false
	/*if (object.getGlobalBounds().intersects(wall1.getGlobalBounds()) || object.getGlobalBounds().intersects(wall2.getGlobalBounds()) || object.getGlobalBounds().intersects(wall3.getGlobalBounds()) || object.getGlobalBounds().intersects(wall4.getGlobalBounds()))
        return false;
	// if the object (ghost) over any wall inside the map return false*/
	for(int i = 0; i < (int)wall.size(); i++)
		if(object.getGlobalBounds().intersects(wall[i].getGlobalBounds()))
			return false;
	// else return true
    return true;
}

// moving the hero and getting the targets of pink and blue ghosts
void move_hero(int speed)
{
	// getting the position of the hero
	Vector2f hero_position = hero.getPosition() ;
	if(check_hero_move(hero))
		vaild = hero_position;
	for(int i = 0; i < (int)points.size(); i++) // if the hero over any point and it's color is white increase the score by 1
		if(hero.getGlobalBounds().intersects(points[i].getGlobalBounds()) && points[i].getFillColor() == Color::White)
		{
			points[i].setFillColor(Color::Black); // set the color of the current point to black (color of window's background)
			score++; // increase the score by 1
			system("cls");
			cout << "Score : " << score << endl;
		}
	// if the player pressed (up) key and the hero isn't over any wall 
	if (Keyboard::isKeyPressed(Keyboard::Up) && check_hero_move(hero)) 
	{
		y_pink = -1; //setting pink target
		pos.x = (float) 0; 
		pos.y = (float) -0.1;
		hero.setRotation(0); // set hero angel to 0
		hero.rotate(270); // rotate by 270
	}
	// if the player pressed (down) key and the hero isn't over any wall 
	else if (Keyboard::isKeyPressed(Keyboard::Down) && check_hero_move(hero))
	{
		y_pink = 1; //setting pink target
		pos.x = (float) 0;
		pos.y = (float) 0.1;
		hero.setRotation(0); // set hero angel to 0
		hero.rotate(90); // rotate by 90
	}
	// if the player pressed (right) key and the hero isn't over any wall
	else if (Keyboard::isKeyPressed(Keyboard::Right) && check_hero_move(hero))
	{
		x_pink = 1; //setting pink target
		pos.x = (float) 0.1;
		pos.y = (float) 0;
		hero.setRotation(0); // set hero angel to 0
		hero.rotate(0); // rotate by 0 (no need but to be in the safe zone :D)
	}
	// if the player pressed (left) key and the hero isn't over any wall
	else if (Keyboard::isKeyPressed(Keyboard::Left) && check_hero_move(hero))
	{
		x_pink = -1; //setting pink target
		pos.x = (float)-0.1;
		pos.y = (float)0;
		hero.setRotation(0); // set hero angel to 0
		hero.rotate(180);  // rotate by 180
	}
	// if the hero over any wall backtrack :D
	else if (!check_hero_move(hero))
	{
	//  cout << "vaild : " << vaild.x << " " << vaild.y << endl;
		Vector2f h_p = hero.getPosition();
		h_p.x = vaild.x - h_p.x;
		h_p.y = vaild.y - h_p.y;
	//	cout << "h_p : " << h_p.x << " " << h_p.y << endl;
		hero.move(h_p);
		pos.x *= -1;
		pos.y *= -1;
	}
	pink_target.x = hero_position.x + x_pink; // setting pink target
	pink_target.y = hero_position.y + y_pink; // setting pink target
	blue_target = pink.getPosition(); // setting blue target
	swap(blue_target.x, blue_target.y);
	blue_target.x = 480 - blue_target.x;
	blue_target.y = 550 - blue_target.y;
	hero.move(pos.x * speed, pos.y * speed); // move the hero
}

//getting which direction should the ghost move
Vector2f destination(RectangleShape &ghost, Vector2f target, int speed)
{
	Vector2f ghost_position = ghost.getPosition(); // getting current ghost position
	Vector2f distance;
	long double dist_1, dist_2;

	// tring all possible destinations
	dest[0].x = (float) 0.1 * speed, dest[0].y = (float) 0.0 * speed; 
	dest[1].x = (float) -0.1 * speed, dest[1].y = (float) 0.0 * speed;
	dest[2].x = (float) 0.0 * speed, dest[2].y = (float) -0.1 * speed;
	dest[3].x = (float) 0.0 * speed, dest[3].y = (float) 0.1 * speed;
	// getting distance between the ghost and it's target
	distance.x = ghost_position.x - target.x;
	distance.y = ghost_position.y - target.y;
	dist_1 = sqrt((distance.x * distance.x) + (distance.y * distance.y));

	for(int i = 0; i < 4; i++)
	{
		//tring all destinations
		dist_2 = sqrt(((distance.x + dest[i].x) * (distance.x + dest[i].x)) + ((distance.y + dest[i].y) * (distance.y + dest[i].y)));
		if(dist_2 < dist_1) // if a destination is a vaild move it
			return dest[i];
	}
	// if there is no destination return (0,0) (no need as there is one vaild destination at least but to be in the safe zone againe :P)
	return Vector2f(0, 0);
}

// moving the ghost 
void ghost_stuck(RectangleShape &ghost , Vector2f destina, int speed)
{
	float x = destina.x * speed, y = destina.y * speed;
	swap(x, y);
	if (check_ghost_move(ghost))
	{
		ghost.move(x, y);
		ghost.move(destina);
		if(check_ghost_move(ghost))
			return;
		ghost.move(-1 * destina.x, -1 * destina.y);
		move_hero(hero_speed);
	}
	if(!check_ghost_move(ghost))
		{
			ghost.move(-1 * x, -1 * y);
			move_hero(hero_speed);
		}
	else
		return;
	if (check_ghost_move(ghost))
	{
		ghost.move(-1 * x, -1 * y);
		ghost.move(destina);
		if(check_ghost_move(ghost))
			return;
		ghost.move(-1 * destina.x, -1 * destina.y);
		move_hero(hero_speed);
	}
}
void move_ghost(RectangleShape &ghost, Vector2f target, int speed)
{
	Vector2f destina = destination(ghost, target, speed); // getting which direction should the ghost move
	Vector2f ghost_origin = ghost.getPosition();
	ghost.move(destina);
	if(!check_ghost_move(ghost)) // if the ghost over any wall
	{
		Vector2f current_position = ghost.getPosition();
		ghost_origin.x -= current_position.x;
		ghost_origin.y -= current_position.y;
		ghost.move(ghost_origin); // backtrack
		// then try all other distinations 
		/// need to be updated ( sfml -_- )
		ghost_stuck(ghost, destina, speed);
	}
}