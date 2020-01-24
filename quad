//gcc -o quadtree -Iinclude/SDL2 quadtree.c -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#define window_width 512
#define window_height 512

#define qt_max_points 3
#define max_points 100

SDL_Renderer *renderer;
SDL_Window *window;

typedef struct{
	int x, y;
} point;

typedef struct quadtree_node {
	int x, y;
	int w, h;
	
	point **points;
	int pcount; //how many points
	
	struct quadtree_node *sub;
} quadtree_node;

point *points[max_points] = {NULL};

int point_add(int x, int y)
{
	for (int i = 0; i < max_points; i++){
		if (points[i] == NULL){
			point *pt = malloc(sizeof(point));

			if (pt == NULL){
				break;
			}
			
			pt->x = x; pt->y = y;
			points[i] = pt;
			
			return 1;
		}
	}
	return 0;
}

int quadtree_init(quadtree_node *nd, int x, int y, int w, int h)
{
	if (nd == NULL){
		return 0;
	}
	nd->x = x; nd->y = y; nd->w = w; nd->h = h;
	nd->pcount = 0, nd->sub = NULL; nd->points = NULL;
	return 1;
}

int quadtree_destroy(quadtree_node *nd)
{
	if (nd->sub != NULL){
		for (int i = 0; i < 4; i++){
			quadtree_destroy(&nd->sub[i]);
		}
	}
	free(nd);
	return 1;
}

int quadtree_insert(quadtree_node *nd, point *pt)
{
	//check if node has no children
	if (nd->sub == NULL){
		//should node split?
		if (nd->pcount == qt_max_points){
			//split
			nd->sub = malloc(4 * sizeof(quadtree_node));
			
			if (nd->sub == NULL){
				//BAD ERROR
				
				return 0;
			}
			
			int halfwidth = nd->w >> 1;
			int halfheight = nd->h >> 1;
			
			int x = nd->x + halfwidth;
			int y = nd->y + halfheight;
			
			quadtree_init(&nd->sub[0], nd->x, nd->y, halfwidth, halfheight);
			quadtree_init(&nd->sub[1], x, nd->y, halfwidth, halfheight);
			quadtree_init(&nd->sub[2], y, nd->x, halfwidth, halfheight);
			quadtree_init(&nd->sub[3], x, y, halfwidth, halfheight);
			
			//push points into children
			
			for (int i = 0; i < qt_max_points; i++){
				if (quadtree_insert(&nd->sub[0], &nd->points[i])){
					continue;
				}
				if (quadtree_insert(&nd->sub[1], &nd->points[i])){
					continue;
				}
				if (quadtree_insert(&nd->sub[2], &nd->points[i])){
					continue;
				}
				if (quadtree_insert(&nd->sub[3], &nd->points[i])){
					continue;
				}
			}
			
			free(nd->points);
			
			goto jmp;
			//return 1;
		}
		
		//aabb check
		if (!(pt->x > nd->x && pt->x < (nd->x + nd->w) && pt->y > nd->y && pt->y < (nd->y + nd->h))){
			return 0;
		}
		
		nd->points = realloc(nd->points, nd->pcount += 1);
		nd->points[nd->pcount - 1] = pt;
		
		return 1;
	}
	
	jmp:
	//push point to children
	for (int i = 0; i < 4; i++){
		if (quadtree_insert(&nd->sub[i], pt)){
			break;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	quadtree_node root;
	
	if (quadtree_init(&root, 0, 0, 512, 512) == NULL){
		
		return 0;
	}
	
	for (int i = 0; i < max_points; i++){
		if (points[i] != NULL){
			quadtree_insert(&root, points[i]);
		}
	}
	
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("quadtree",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,window_width,window_height,SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
