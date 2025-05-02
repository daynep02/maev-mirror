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
        self.platforms.append(engine.create_rigid_body((570, 450), (500,10)))
        self.zone1 = engine.create_box_collider((660, 250), (200,10))

        engine.set_rigid_body_static(self.player, False)
        engine.set_rigid_body_gravity(self.player, True)

        engine.set_gravity(0.0, 1.0)
        engine.set_terminal_velo(self.player, 200.0, 200.0)

        for platform in self.platforms:
            engine.set_rigid_body_static(platform,True)

def init():
    global game
    game = Game()

def update():
    global game
    delta = engine.delta_time()

    # engine.set_rigid_body_velocity(game.player, (0.0, 0.0))
    # if engine.key_is_pressed(AKEY):
    #     engine.set_rigid_body_velocity(game.player, (-50.0, 0.0))
    #     # print("A pressed")
    # if engine.key_is_pressed(DKEY):
    #     engine.set_rigid_body_velocity(game.player, (50.0, 0.0))
    #     # print("D pressed")
    if engine.key_is_pressed("Up"):
        engine.apply_force(game.player, 0.0, -2.0)
    if engine.key_is_pressed( "Down"):
        engine.apply_force(game.player, 0.0, 2.0)
    if engine.key_is_pressed("Left"):
        engine.apply_force(game.player,-2.0, 0.0)
    if engine.key_is_pressed("Right"):
        engine.apply_force(game.player, 1.0, 0.0)

    tup = engine.get_rigid_body_position(game.player)
    engine.set_camera_position(tup)

    engine.rigid_body_collides_with(game.player, game.zone1)

def draw():
    global game

    engine.draw_rigid_body_collider(game.player)
    # engine.draw

    for platform in game.platforms:
        engine.draw_rigid_body_collider(platform)
    
    # engine.draw_rigid_body_collider(game.platforms[0])
    # engine.draw_rigid_body_collider(game.platforms[1])