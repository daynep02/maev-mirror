import engine
import time
import math

AKEY = "A"
DKEY = "D"

class Game:
    def __init__(self):
        self.scene = "P"
        self.player = engine.create_rigid_body((10, 10), (10, 10))
        self.platforms = [engine.create_rigid_body((0,300), (100,20))]
        self.platforms.append(engine.create_rigid_body((150, 350), (500,10)))
        self.platforms.append(engine.create_rigid_body((660, 250), (200,10)))
        self.platforms.append(engine.create_rigid_body((850, 00), (10,250)))
        self.platforms.append(engine.create_rigid_body((-20, -10), (900, 10)))
        self.platforms.append(engine.create_rigid_body((570, 450), (500,10)))
        self.platforms.append(engine.create_rigid_body((950, 250), (500,10)))
        self.zone1 = engine.create_box_collider((1000, 0), (30,1000))
        self.zone1_enabled = True
        self.zone2 = engine.create_box_collider((1300, 0), (30, 1000))
        self.zone2_enabled = True

        engine.set_rigid_body_static(self.player, False)
        engine.set_rigid_body_gravity(self.player, True)

        engine.set_gravity(0.0, 100.0)
        engine.set_terminal_velo(self.player, 200.0, 200.0)

        for platform in self.platforms:
            engine.set_rigid_body_static(platform,True)

        self.font = engine.create_font("../games/platformer/assets/comic.ttf")
        self.text = engine.create_text(self.font)
        engine.set_text(self.text, "Game over")
        engine.set_text_position(self.text, (-110,0))
        engine.set_text_size(self.text, 50)
        engine.set_text_color(self.text, (255,0,0,255))

def init():
    global game
    game = Game()

def update():
    global game
    delta = engine.delta_time()

    if game.scene == "P":
        pos = engine.get_rigid_body_position(game.player)
        if pos[1] < 0 or pos[1] > 1000:
            game.scene = "E"
            engine.set_camera_position((0,0))
            # print("game over")
            return

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

        if game.zone1_enabled and engine.rigid_body_collides_with(game.player, game.zone1):
            print("Colliding")
            engine.set_gravity(0.0, -100.0)
            game.zone1_enabled = False
        if game.zone2_enabled and engine.rigid_body_collides_with(game.player, game.zone2):
            print("Colliding")
            game.zone1_enabled = False
            engine.set_text(game.text, "You win!")
            engine.set_camera_position((0,0))
            engine.set_text_color(game.text, (0,255,0,255))
            game.scene = "E"
            return
        # else:
            # print("Not colliding")

def draw():
    global game

    if game.scene == "P":
        engine.draw_rigid_body_collider(game.player)
        # engine.draw

        for platform in game.platforms:
            engine.draw_rigid_body_collider(platform)
        
        # engine.draw_rigid_body_collider(game.platforms[0])
        # engine.draw_rigid_body_collider(game.platforms[1])
    else:
        engine.draw_text(game.text)