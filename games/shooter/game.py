import engine
import math
import random

ORIG_SCREEN_SIZE = (1024, 600)
NEW_SCREEN_SIZE = (1920, 1080)

# TODO: enemies
# TODO: levels
# TODO: title screen
# TODO: player health, weapon types, etc.

class Player:
    def __init__(self):
        body_size = 10.0
        self.body = engine.create_circle(body_size)
       
        ratio_w = NEW_SCREEN_SIZE[0] / ORIG_SCREEN_SIZE[0]
        ratio_h = NEW_SCREEN_SIZE[1] / ORIG_SCREEN_SIZE[1]

		# ball centering not consistent due to how screen gets resized
        self.x = ((ORIG_SCREEN_SIZE[0] / 2) - (0.5 * body_size) * (ratio_w))
        self.y = ((ORIG_SCREEN_SIZE[1] / 2) - (0.5 * body_size) * (ratio_h))
        engine.set_circle_position(self.body, (self.x, self.y))

    def move(self, direction):
        if direction == "up":
            self.y -= 0.1
        elif direction == "down":
            self.y += 0.1
        if direction == "left":
            self.x -= 0.1
        elif direction == "right":
            self.x += 0.1
        engine.set_circle_position(self.body, (self.x, self.y))

    def fire(self, mouse):
        ...


# game handler object
class Game:
	def __init__(self):
		self.player = Player()

		# creates n enemies
		n = 15
		self.enemies = []
		for i in range(n):
			a, b = random.randint(0, 2000), random.randint(0, 2000)
			self.enemies.append(engine.create_rigid_body((a, b), (15,15)))


def init():
	engine.set_screen_size(NEW_SCREEN_SIZE[0], NEW_SCREEN_SIZE[1])
	global game
	game = Game()


def update():
    # TODO: fire vectors
    global game
     
    # player movement
    if engine.key_is_pressed("W"):
        game.player.move("up")
    elif engine.key_is_pressed("S"):
        game.player.move("down")
    if engine.key_is_pressed("A"):
        game.player.move("left")
    elif engine.key_is_pressed("D"):
        game.player.move("right")

    # keep camera centered on player
    engine.set_camera_position((game.player.x, game.player.y))

    # player firing vectors
    l = engine.mouse_button_is_pressed("Left")
    if l > 0:
        # ensure mouse click is within screen bounds
        if 0 <= engine.x(l) <= NEW_SCREEN_SIZE[0] and 0 <= engine.y(l) <= NEW_SCREEN_SIZE[1]:
            bullet = engine.create_vector(engine.x(l), engine.y(l))
            
            # bullet calculations here
            
            engine.destroy_vector(bullet)
            # TODO: how to draw vector as line?


def draw():
	global game
	engine.draw_circle(game.player.body)
     
	for i in game.enemies:
		engine.draw_rigid_body_collider(i)
