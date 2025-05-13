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
        # actual physical positioning
        self.x, self.y = random.randint(-295, 1280), random.randint(-595, -20)
        self.body = engine.create_rigid_body((self.x, self.y), (15,15))

        # friction and velocity
        self.dx = 0
        self.dy = 0
        #engine.set_terminal_velo(self.body, 1.0, 1.0)
        engine.set_rigid_body_static(self.body, False)
        engine.set_rigid_body_gravity(self.body, False)

        # other traits
        self.health = 1000
        self.seek_player = False

    def move(self):
        # between player and enemy
        dist_from_player = engine.create_vector(self.x - game.player.x, self.y - game.player.y)

        # pursue player directly: change velocity based on dist from player
        # all numbers fairly arbitrary: base attraction speed * random aggression * magnet to player
        if self.seek_player:
            aggro = random.randint(1, 100)
            if self.x > game.player.x:
                self.dx -= 0.001 * (5 / aggro) * (20 / engine.length(dist_from_player))
            elif self.x < game.player.x:
                self.dx += 0.001 * (5 / aggro) * (20 / engine.length(dist_from_player))
            if self.y > game.player.y:
                self.dy -= 0.001 * (5 / aggro) * (20 / engine.length(dist_from_player))
            elif self.y < game.player.y:
                self.dy += 0.001 * (5 / aggro) * (20 / engine.length(dist_from_player))
            engine.set_rigid_body_velocity(self.body, (self.dx, self.dy))
        
        # like an idle animation: slightly tweak absolute position
        else:
            self.dx = 0
            self.dy = 0
            i = random.randint(0, 100)
            if i == 1:
                self.x -= 0.05
            elif i == 2:
                self.x += 0.05
            if i == 3:
                self.y -= 0.05
            elif i == 4:
                self.y += 0.05

        # change enemy's absolute position considering velocity (so works for either mode)
        self.x += self.dx
        self.y += self.dy
        engine.set_rigid_body_position(self.body, (self.x, self.y))


# game handler object
class Game:
    def __init__(self):
        self.player = Player()

        n = 15
        self.enemies = []
        for i in range(n):
            self.enemies.append(Enemy())

        self.walls = []
        self.walls.append(engine.create_rigid_body((300, 0), (2, 500)))
        self.walls.append(engine.create_rigid_body((300, 500), (400, 2)))
        self.walls.append(engine.create_rigid_body((700, 0), (2, 500)))

        self.walls.append(engine.create_rigid_body((-300, 0), (600,2)))
        self.walls.append(engine.create_rigid_body((700, 0), (600,2)))
        self.walls.append(engine.create_rigid_body((-300, -600), (2, 600)))
        self.walls.append(engine.create_rigid_body((1300, -600), (2, 600)))
        self.walls.append(engine.create_rigid_body((-300, -600), (1600, 2)))



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
        crit_dist_x = (NEW_SCREEN_SIZE[0] / 5)
        crit_dist_y = (NEW_SCREEN_SIZE[1] / 5)

        if ((game.player.x - crit_dist_x) <= i.x <= (game.player.x + crit_dist_x)) and \
        ((game.player.y - crit_dist_y) <= i.y <= (game.player.y + crit_dist_y)):
            i.seek_player = True
        else:
            i.seek_player = False
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

    for i in game.walls:
        engine.draw_rigid_body_collider(i)
