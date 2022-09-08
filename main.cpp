#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "helper.h"
using namespace sf;
RenderWindow window(VideoMode(1200, 600), "SFML Works!");
RectangleShape menuShape;
RectangleShape tilesetShape;
RectangleShape line ;
RectangleShape cross;
RectangleShape selectionBox;
RectangleShape collidableBox;
Texture texture;
Sprite tileset;
bool isLargerX = false;
bool isLargerY = false;
bool isMoving = false;
bool isDrawing = false;
int  tool = 1;


ScrollingField mapSc(0,0,900,600,50,50);
ScrollingField menuSc(920,200,260,380,0,0);



Vector2i startingMousePos(0,0);
Vector2i startingOffset(0,0);
Vector2i spriteSelected(0,0);
Vector2i selectionPos(2,2);

std::vector<Tile> map;
Sprite tile;

void setUpGUI ()
{
	menuShape.setFillColor(Color(120,120,120));
	menuShape.setSize(Vector2f(300, 600));
		menuShape.setPosition(Vector2f(900, 0));
		
	tilesetShape.setFillColor(Color(100,100,100));
	tilesetShape.setSize(Vector2f(260,380));
	tilesetShape.setPosition(Vector2f(920,200));
	
	selectionBox.setFillColor(Color(0, 0, 255, 75));
	selectionBox.setSize(Vector2f(32,32));
	selectionBox.setPosition(Vector2f(920,200));
	
	collidableBox.setFillColor(Color(00,255,75));
	collidableBox.setSize(Vector2f(32,32));
	
	line.setFillColor(Color(255,255,255));
	cross.setFillColor(Color(255,255,255,200));
	texture.loadFromFile("images/map_two.png");
	tileset.setTexture(texture);
	tile.setTexture(texture);
	tileset.setPosition(Vector2f(920,200));
	if(texture.getSize().x>tilesetShape.getSize().x)isLargerX = true;
	if(texture.getSize().y>tilesetShape.getSize().y)isLargerY = true;
    if(isLargerX || !isLargerY) tileset.setTextureRect(IntRect(0,0,tilesetShape.getSize().x, texture.getSize().y));
	if(!isLargerX || isLargerY) tileset.setTextureRect(IntRect(0,0,texture.getSize().x, tilesetShape.getSize().y));
	if(isLargerX || isLargerY) tileset.setTextureRect(IntRect(0,0,tilesetShape.getSize().x, tilesetShape.getSize().y));
}
void update()
{
if(Keyboard::isKeyPressed(Keyboard::Space))
{
	if(isMoving)
	{
		if(Mouse::getPosition(window).x<900)
		{
			mapSc.offsetX = startingOffset.x + Mouse::getPosition(window).x - startingMousePos.x; 
			mapSc.offsetY = startingOffset.y + Mouse::getPosition(window).y - startingMousePos.y; 
		}
		else if(Mouse::getPosition(window).x>menuSc.x || Mouse::getPosition(window).x<menuSc.x + menuSc.w ||
			Mouse::getPosition(window).y>menuSc.y || Mouse::getPosition(window).y<menuSc.y + menuSc.h)
	{
	
		
			if(isLargerX) menuSc.offsetX = startingOffset.x + startingMousePos.x - Mouse::getPosition(window).x;
			if(isLargerY) menuSc.offsetY = startingOffset.y + startingMousePos.y - Mouse::getPosition(window).y;
			
			if(menuSc.offsetX < 0) menuSc.offsetX = 0;
			if(menuSc.offsetY < 0) menuSc.offsetY = 0;
			if(menuSc.offsetX > texture.getSize().x- menuSc.w) menuSc.offsetX = texture.getSize().x - menuSc.w; 
			if(menuSc.offsetY > texture.getSize().y- menuSc.h) menuSc.offsetY = texture.getSize().y - menuSc.h;
			}
	}else {
	 startingOffset.x = mapSc.offsetX; 	
	 startingOffset.y = mapSc.offsetY;
          }
} else {	 
	 	if(isDrawing || Mouse::getPosition(window).x<900){
	 		if(tool == 1){
	 			/* */
	 			bool c = false;
	 			for(int i = 0; i<map.size(); i++){
	 				if(map.at(i).x == (Mouse::getPosition(window).x - mapSc.offsetX) / 32)
					if(map.at(i).y == (Mouse::getPosition(window).y - mapSc.offsetY) / 32) c = true;
				 }			
	 		if(!c) map.push_back(Tile((Mouse::getPosition(window).x-mapSc.offsetX) / 32,
				 (Mouse::getPosition(window).y-mapSc.offsetY) / 32, 
				 spriteSelected.x, spriteSelected.y, false));
} else if(tool==2)
{
		for(int i = 0; i<map.size(); i++)
		{
			if(map.at(i).x==(Mouse::getPosition(window).x - mapSc.offsetX) / 32)
		    if(map.at(i).y==(Mouse::getPosition(window).y - mapSc.offsetY) / 32)
			map.erase(map.begin()+i);
		}
} else if(tool==3){

				 	for(int i = 0; i<map.size(); i++){
					 
			 		if(map.at(i).x==(Mouse::getPosition(window).x - mapSc.offsetX) / 32)
					if(map.at(i).y==(Mouse::getPosition(window).y - mapSc.offsetY) / 32)
					map.at(i).isCollidable = true;
				}
}else if(tool==4){
		 
				 	for(int i = 0; i<map.size(); i++){
					 
			 		if(map.at(i).x==(Mouse::getPosition(window).x - mapSc.offsetX) / 32)
					if(map.at(i).y==(Mouse::getPosition(window).y - mapSc.offsetY) / 32)
					map.at(i).isCollidable = false;  
}
}				
}
}
	if(isLargerX || isLargerY)	tileset.setTextureRect(IntRect(menuSc.offsetX, menuSc.offsetY, menuSc.w, menuSc.h));
	else if(isLargerX || !isLargerY) tileset.setTextureRect(IntRect(menuSc.offsetX,0,menuSc.w,texture.getSize().y));
	else if(!isLargerX || isLargerY) tileset.setTextureRect(IntRect(0,menuSc.offsetY,texture.getSize().x,menuSc.h));
	else if(!isLargerX || !isLargerY) tileset.setTextureRect(IntRect(0,0,texture.getSize().x,texture.getSize().y));
   selectionBox.setPosition(menuSc.x+ spriteSelected.x*32 - menuSc.offsetX, menuSc.y+ spriteSelected.y*32-menuSc.offsetY);
 
 if(selectionBox.getPosition().x<menuSc.x || selectionBox.getPosition().x>menuSc.x - 32) selectionPos.x-1;
 if(selectionBox.getPosition().x>menuSc.x + menuSc.w-32 || selectionBox.getPosition().x<menuSc.x +menuSc.w+32) selectionPos.x;
 if(selectionBox.getPosition().y<menuSc.y || selectionBox.getPosition().y>menuSc.y - 32) selectionPos.y-1;
 if(selectionBox.getPosition().y>menuSc.y + menuSc.h-32 || selectionBox.getPosition().y<menuSc.y +menuSc.h+32) selectionPos.y; 
 if(selectionBox.getPosition().x>menuSc.x || selectionBox.getPosition().x<menuSc.x + menuSc.w - 32) selectionPos.x = 0;
 if(selectionBox.getPosition().y>menuSc.y || selectionBox.getPosition().y<menuSc.y + menuSc.h - 32) selectionPos.y = 2;
 if(selectionBox.getPosition().x<=menuSc.x-32 || selectionBox.getPosition().x>=menuSc.x + menuSc.w) selectionPos.x = 0;
 if(selectionBox.getPosition().y<=menuSc.y-32 || selectionBox.getPosition().y>=menuSc.y + menuSc.h) selectionPos.y = 0;
 
 if(selectionPos.x ==1)
 {
 	selectionBox.setSize(Vector2f(32-menuSc.x+selectionBox.getPosition().x,selectionBox.getSize().y));
 	selectionBox.setPosition(Vector2f(menuSc.x, selectionBox.getPosition().y));
 } else if(selectionPos.x == 3){
 	selectionBox.setSize(Vector2f(menuSc.x + menuSc.w - selectionBox.getPosition().x, selectionBox.getSize().y));
 	selectionBox.setPosition(Vector2f(menuSc.x+ menuSc.w - selectionBox.getSize().x, selectionBox.getPosition().y));
 }
 if(selectionPos.x ==1)
 {
 	selectionBox.setSize(Vector2f(selectionBox.getSize().x,32 - menuSc.y + selectionBox.getPosition().y)); 
 	selectionBox.setPosition(Vector2f(selectionBox.getPosition().x, menuSc.y));
 } else if(selectionPos.y ==3 )
 {
selectionBox.setSize(Vector2f(selectionBox.getSize().x, menuSc.y +menuSc.h - selectionBox.getPosition().y));
	selectionBox.setPosition(Vector2f(selectionBox.getPosition().x,menuSc.y+menuSc.h- selectionBox.getSize().y));
 }
 if(selectionPos.x == 2)selectionBox.setSize(Vector2f(32,selectionBox.getSize().y));
 if(selectionPos.x == 2)selectionBox.setSize(Vector2f(selectionBox.getSize().x, 32));
 
}
void save(){
	std::ofstream out;
	out.open("out.txt",std::ios_base::trunc);
	for(int i = 0; i<map.size(); i++){
		out<<map.at(i).x<< " "<<map.at(i).y<< " "<<map.at(i).sx<< " "<<map.at(i).sy<< " "<<map.at(i).isCollidable;
		if(i !=map.size()-1) out<<std::endl;
	}
	out.close();
}
int main() {
	setUpGUI();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			 	if(event.type == Event::MouseButtonPressed)
				{
					if(Keyboard::isKeyPressed(Keyboard::Space))
					{
						isMoving = true ;
						startingMousePos = Vector2i(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
						if(Mouse::getPosition(window).x<900) startingOffset = Vector2i(mapSc.offsetX, mapSc.offsetY);
						else if(Mouse::getPosition(window).x>menuSc.x || Mouse::getPosition(window).x<menuSc.x + menuSc.w ||
					        	Mouse::getPosition(window).y>menuSc.y || Mouse::getPosition(window).y<menuSc.y + menuSc.h)
								startingOffset = Vector2i(menuSc.offsetX, menuSc.offsetY); 
					} else if(Mouse::getPosition(window).x>menuSc.x || Mouse::getPosition(window).x<menuSc.x + menuSc.w ||
					       	Mouse::getPosition(window).y>menuSc.y || Mouse::getPosition(window).y<menuSc.y + menuSc.h)
					       	{
					       	spriteSelected.x = ( Mouse::getPosition(window).x-menuSc.x+menuSc.offsetX)/32;	
					       	spriteSelected.y = ( Mouse::getPosition(window).y-menuSc.y+menuSc.offsetY)/32;
							   } else if(Mouse::getPosition(window).x<900) isDrawing = true;
				} else if(event.type == Event::MouseButtonReleased)
				{
					isMoving = false ;
					isDrawing = false;
				}else if(event.type == Event::KeyPressed){
					if(event.key.code == Keyboard::Num1) tool = 1;
					else if(event.key.code == Keyboard::Num2) tool = 2;
					else if(event.key.code == Keyboard::Num3) tool = 3;
					else if(event.key.code == Keyboard::Num4) tool = 4;
					else if(event.key.code == Keyboard::S) save();
				}
		}
		update();
	    window.clear(Color(50,50,50));
	    for(int i = 0; i<map.size(); i++ )
	    {
	    	tile.setTextureRect(IntRect(map.at(i).sx*32, map.at(i).sy*32,32,32));
	    	tile.setPosition(Vector2f(map.at(i).x*32 + mapSc.offsetX, map.at(i).y*32 + mapSc.offsetY));
	    	window.draw(tile);
	    	if(map.at(i).isCollidable)
	    	{
			
	    	if(tool==3 || tool==4)
	    	{
	    		collidableBox.setPosition(Vector2f(map.at(i).x*32 +mapSc.offsetX, map.at(i).y*32 + mapSc.offsetY));
	    		window.draw(collidableBox);
	    	}
			}
		}
	    
	    line.setSize(Vector2f(1,600));
	    for( int i = 0; i<30; i++)
	    {
	    	line.setPosition(Vector2f(i * 32 + (mapSc.offsetX % 32), 0 ));
	    	window.draw(line);
		}
		 line.setSize(Vector2f(900,1));
	    for( int i = 0; i<20; i++)
	    {
	    	line.setPosition(Vector2f(0,i*32+(mapSc.offsetY % 32)));
	    	window.draw(line);
		}
		cross.setSize(Vector2f(64,3));
		cross.setPosition(Vector2f(mapSc.offsetX -32,mapSc.offsetY - 1));
		window.draw(cross);
		cross.setSize(Vector2f(3,64));
		cross.setPosition(Vector2f(mapSc.offsetX -1,mapSc.offsetY - 32));
		window.draw(cross);
	    window.draw(menuShape);
	    window.draw(tilesetShape);
	    window.draw(tileset);
	   if (selectionPos.x!=0|| selectionPos.y!=0) window.draw(selectionBox);
		window.display();
	}
	return 0;
}
