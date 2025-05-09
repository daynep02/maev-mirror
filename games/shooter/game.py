import engine
import math
import random

ORIG_SCREEN_SIZE = (1024, 600)
NEW_SCREEN_SIZE = (1080, 720)

class Ball:
    def __init__(self):
        body_size = 15.0
        self.body = engine.create_circle(body_size)
       
        ratio_w = NEW_SCREEN_SIZE[0] / ORIG_SCREEN_SIZE[0]
        ratio_h = NEW_SCREEN_SIZE[1] / ORIG_SCREEN_SIZE[1]

		# ball centering not consistent due to how screen gets resized
        self.x = ((ORIG_SCREEN_SIZE[0] / 2) - (0.5 * body_size) * (ratio_w))
        self.y = ((ORIG_SCREEN_SIZE[1] / 2) - (0.5 * body_size) * (ratio_h))
        engine.set_circle_position(self.body, (self.x, self.y))

# game handler object
class Game:
	def __init__(self):
		self.player = Ball()

		# creates n enemies
		n = 5
		self.enemies = []
		for i in range(n):
			a, b = random.randint(0, 600), random.randint(0, 600)
			self.enemies.append(engine.create_rigid_body((a, b), (20,20)))


def init():
	engine.set_screen_size(NEW_SCREEN_SIZE[0], NEW_SCREEN_SIZE[1])
	global game
	game = Game()

def update():
	# TODO: how to move everything given camera?
	# how to keep player centered if player is thing moving?
	global game
	...

def draw():
	global game
	engine.draw_circle(game.player.body)
	for i in game.enemies:
		engine.draw_rigid_body_collider(i)
