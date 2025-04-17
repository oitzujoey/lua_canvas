# lua_canvas

## Dependencies

Lua 5.4  
SDL3

## API

### `createCanvas(canvas_size::PositiveInteger, window_size::PositiveInteger)`

This should be the first drawing function called. `canvas_size` is how many virtual pixels wide and tall to make the screen. Make it big to make the virtual pixels small, and make it small to make the virtual pixels big. `window_size` is the number of pixels wide and tall the window will be that contains the canvas.

### `setColor(rgbColor::PositiveInteger)`

This function sets the color of the cursor. `rgbColor` is a 24-bit number. Bits 31-16 are an 8-bit number that sets the red brightness. Bits 15-8 are an 8-bit number that sets the green brightness. Bits 7-0 are an 8-bit number that sets the blue brightness.

### `setPosition(x::PositiveInteger, y::PositiveInteger)`

This function sets the position of the cursor. The origin (0, 0) is the top-left of the screen. A large value of `x` will place the cursor on the right of the canvas. A large value of `y` will place the cursor near the bottom of the canvas. If `x` is 9 and the size of the canvas is 10, then the cursor will be on the right edge of the canvas.

### `plot()`

Paints the pixel at the position the cursor is at. It will have the color the cursor was previously set to.

### `up()`

Move the cursor up.

### `down()`

Move the cursor down.

### `left()`

Move the cursor left.

### `right()`

Move the cursor right.

### `render()`

This might be useful for long drawing routines. It draws the contents of the canvas on the screen and also checks to see if the window has been closed.
