import engine
import time
import math

AKEY = "A"
DKEY = "D"

class Game:
    def __init__(self):
        self.player = engine.create_rigid_body((10, 10), (10, 10))
        self.platforms = [engine.create_rigid_body((0,300), (100,20))]
        self.platforms.append(engine.create_rigid_body((150, 350), (500,10)))
        self.platforms.append(engine.create_rigid_body((660, 250), (200,10)))

        for platform in self.platforms:
            engine.set_rigid_body_static(platform,True)

def init():
    global game
    game = Game()
    print(game.platforms)

def update():
    global game
    delta = engine.delta_time()

    if engine.key_is_pressed(AKEY):
        engine.set

def draw():
    global game

    engine.draw_rigid_body_collider(game.player)

    for platform in game.platforms:
        engine.draw_rigid_body_collider(platform)
    
    # engine.draw_rigid_body_collider(game.platforms[0])
    # engine.draw_rigid_body_collider(game.platforms[1])