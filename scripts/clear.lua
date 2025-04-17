createCanvas(10, 600)

setColor(0x00000000)
for y = 1,10 do
	for x = 1,10 do
		plot()
		right()
	end
	for x = 1,10 do
		left()
	end
	down()
	render()
end
setPosition(5, 5)
setColor(0xFF0000)
plot()
