#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "canvas.h"


Canvas canvas;
bool initialized = false;


int quit(void) {
	SDL_Event event;
	SDL_PollEvent(&event);
	return event.type == SDL_EVENT_QUIT;
}


void initializationError(lua_State *luaState) {
	puts("`createCanvas` was not the first drawing function called. It must be the first function you call.");
	lua_error(luaState);
}
    

int createCanvas(lua_State *luaState) {
	if (!lua_isinteger(luaState, 1)) {
		printf("createCanvas: First argument must be a positive integer. It is the size of the canvas to create in virtual pixels.\n");
		lua_error(luaState);
		return 0;
	}
	int canvas_size = lua_tointeger(luaState, 1);
	if (!lua_isinteger(luaState, 2)) {
		printf("createCanvas: Second argument must be a positive integer greater than or equal to than the canvas size. It is the size of the window to create in pixels.\n");
		lua_error(luaState);
		return 0;
	}
	int window_size = lua_tointeger(luaState, 2);
	if (window_size <= 0) {
		printf("The window size you gave was %i. It must be greater than 0.\n");
		lua_error(luaState);
		return 0;
	}
	if (canvas_size <= 0) {
		printf("The canvas size you gave was %i. It must be greater than 0.\n");
		lua_error(luaState);
		return 0;
	}
	if (window_size < canvas_size) {
		printf("The canvas size is larger than the window size. It must be the same size or smaller.\n");
		lua_error(luaState);
		return 0;
	}
	canvas_init(&canvas, canvas_size, window_size);
	initialized = true;
	return 0;
}

int setColor(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	if (!lua_isinteger(luaState, 1)) {
		printf("setColor: Argument must be a 24-bit RGB color represented as an integer.\n");
		lua_error(luaState);
		return 0;
	}
	int color = lua_tointeger(luaState, 1);
	canvas_setColor(&canvas, color);
	return 0;
}

int setPosition(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	if (!lua_isinteger(luaState, 1)) {
		printf("setPosition: First argument must be an integer. It is the x-axis coordinate.\n");
		lua_error(luaState);
		return 0;
	}
	int x = lua_tointeger(luaState, 1);
	if (!lua_isinteger(luaState, 2)) {
		printf("setPosition: Second argument must be an integer. It is the y-axis coordinate.\n");
		lua_error(luaState);
		return 0;
	}
	int y = lua_tointeger(luaState, 2);
	canvas_setPosition(&canvas, x, y);
	return 0;
}

int plot(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	canvas_plot(&canvas);
	return 0;
}

int up(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	canvas_up(&canvas);
	return 0;
}

int down(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	canvas_down(&canvas);
	return 0;
}

int left(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	canvas_left(&canvas);
	return 0;
}

int right(lua_State *luaState) {
	if (!initialized) {
		initializationError(luaState);
		return 0;
	}
	canvas_right(&canvas);
	return 0;
}

int render(lua_State *luaState) {
	if (quit()) {
		lua_error(luaState);
		return 0;
	}
	(void) canvas_render(&canvas);
	return 0;
}


int main(int argc, char *argv[]) {
	int e = 0;

	if (argc < 2) {
		puts("usage:");
		printf("%s LUA_SCRIPT_FILE_NAME [ARGUMENTS...]\n", argv[0]);
		return 1;
	}

	const char *fileName = argv[1];

	lua_State *luaState = luaL_newstate();
	(void) luaL_openlibs(luaState);

	
	struct {
		char *name;
		lua_CFunction func;
	} cfuncs[] = {
		{"createCanvas", createCanvas},
		{"setColor", setColor},
		{"setPosition", setPosition},
		{"plot", plot},
		{"up", up},
		{"down", down},
		{"left", left},
		{"right", right},
		{"render", render},
		{NULL, NULL}
	};
	for (int i = 0; cfuncs[i].name != NULL; i++) {
		lua_pushcfunction(luaState, cfuncs[i].func);
		lua_setglobal(luaState, cfuncs[i].name);
	}

	e = luaL_dofile(luaState, fileName);
	if (e) {
		puts(lua_tolstring(luaState, -1, NULL));
		return 1;
	}

	while (1) {
		if (quit()) break;
		(void) canvas_render(&canvas);
	}

	(void) canvas_quit(&canvas);
}
