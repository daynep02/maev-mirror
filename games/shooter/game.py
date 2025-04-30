import engine
import math
import random

class Ball:
    def __init__(self):
        self.body = engine.create_circle(15.0)
        self.x = 200	# should be center of screen
        self.y = 200	# should be center of screen

# game handler object
class Game:
	def __init__(self):
		# TODO: no global sizes (screen height, width, etc.)
		self.player = Ball()

		# creates n enemies
		n = 5
		self.enemies = []
		for i in range(n):
			a, b = random.randint(0, 600), random.randint(0, 600)
			self.enemies.append(engine.create_rigid_body((a, b), (20,20)))


def init():
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
