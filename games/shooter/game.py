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

        self.health = 1000

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


class Enemy:
    def __init__(self):
        self.x, self.y = random.randint(0, 2000), random.randint(0, 2000)
        self.body = engine.create_rigid_body((self.x, self.y), (15,15))
        self.health = 1000
        self.seek_player = False

    def move(self):
        # pursue player directly
        if self.seek_player:
            if self.x > game.player.x:
                self.x -= 0.05
            elif self.x < game.player.x:
                self.x += 0.05
            if self.y > game.player.y:
                self.y -= 0.05
            elif self.y < game.player.y:
                self.y += 0.05
        
        # like an idle animation
        else:
            i = random.randint(0, 100)
            if i == 1:
                self.x -= 0.05
            elif i == 2:
                self.x += 0.05
            if i == 3:
                self.y -= 0.05
            elif i == 4:
                self.y += 0.05
        engine.set_rigid_body_position(self.body, (self.x, self.y))


# game handler object
class Game:
    def __init__(self):
        self.player = Player()

        n = 15
        self.enemies = []
        for i in range(n):
            self.enemies.append(Enemy())


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

    for i in game.enemies:
        # how close enemies need to be to pursue
        crit_dist_x = (NEW_SCREEN_SIZE[0] / 10)
        crit_dist_y = (NEW_SCREEN_SIZE[1] / 10)

        if ((game.player.x - crit_dist_x) <= i.x <= (game.player.x + crit_dist_x)) and \
        ((game.player.y - crit_dist_y) <= i.y <= (game.player.y + crit_dist_y)):
            i.seek_player = True
        i.move()

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
		engine.draw_rigid_body_collider(i.body)
