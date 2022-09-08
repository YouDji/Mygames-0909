class Tile
{
 public:
 int x,y;
 int sx,sy;
 bool isCollidable;
 Tile(int x,int y, int sx ,int sy, bool isCollidable );	
};
class ScrollingField{
	public:
		int x,y;
		int w,h;
		int offsetX, offsetY;
		ScrollingField(int x, int y , int w, int h, int offsetX,int offsetY);
};
/*		
				
				  else if(tool==3){
				 	for(int i = 0; i<map.size(); i++){
			 		if(map.at(i).x==(Mouse::getPosition(window).x - mapSc.offsetX) / 32 ||
					   map.at(i).y==(Mouse::getPosition(window).y - mapSc.offsetY) / 32){
					map.at(i).isCollidable = true;
			}
			}	 else if(tool==4){		 
				 	for(int i = 0; i<map.size(); i++){
			 		if(map.at(i).x==(Mouse::getPosition(window).x - mapSc.offsetX) / 32 ||
					   map.at(i).y==(Mouse::getPosition(window).y - mapSc.offsetY) / 32){
					map.at(i).isCollidable = false;
			

*/
