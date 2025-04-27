import engine
import time
import math

class Ball:
    def __init__(self):
        self.circle = engine.create_circle(10.0)
        engine.set_circle_fill_color(self.circle,(0,255,0,255))
        self.x = 200
        self.y = 200

class Game:
    def __init__(self):
        self.ball = Ball()
        self.ball2 = Ball()
        self.background = engine.create_sprite("../games/testing/assets/vector.jpg")
        engine.set_sprite_position(self.background,(0,0))
        self.test_block = engine.create_rigid_body((125,0),(25,25))
        engine.set_rigid_body_gravity(self.test_block,True)
        self.platform = engine.create_rigid_body((0,300),(500,20))
        engine.set_rigid_body_static(self.platform,True)

        self.vec1 = engine.create_vector()
        self.vec2 = engine.create_vector(3, 5)
        #print(self.vec2, type(self.vec2), type(1))
        print(engine.length(self.vec2))
        self.vec3 = engine.normalize(self.vec2)
        print(engine.length(self.vec3))

        self.vec4 = engine.create_vector(4, 6.5)
        print(engine.dot(self.vec2, self.vec4))
        print(engine.cross(self.vec2, self.vec4))

        self.epic_music = engine.create_music("../games/testing/assets/epic_music.wav")
        engine.set_gravity(0.0, 1.0)
        engine.set_terminal_velo(self.test_block, 0.0, 60.0)

       #print(engine.get_rigid_body_size(self.platform))

game = None
first = True

# Key Functions for Game
def init():
    global game
    game = Game()
    #engine.free_sprite(game.background)

    engine.create_box_collider((1, 167.5), (100, 100))
    engine.play_music(game.epic_music)

def update():
    global game
    global first
    key = "NUM0"
    t = engine.current_time()
    delta = engine.delta_time()
    #print(delta)
    game.ball.x = math.cos(t) * 50 + 200
    game.ball.y = math.sin(t) * 59 + 200
    engine.set_circle_position(game.ball.circle,(game.ball.x,game.ball.y))

    game.ball2.x = math.cos(0) * 50 + 200
    game.ball2.y = math.sin(0) * 59 + 200
    engine.set_circle_position(game.ball2.circle,(game.ball2.x,game.ball2.y))
    
    #print(engine.get_rigid_body_position(game.platform))

    # engine.collides_with(game.ball.circle,game.ball2.circle)
    # if engine.collides_with(game.ball.circle,game.ball2.circle):
    #     print("Balls are colliding")

    if first and engine.key_is_pressed(key):
        first = False
        print(f"{key} has been pressed")
    # print(engine.collides_with(game.ball.circle,game.ball2.circle))

def draw():
    global game

    ball = game.ball

#    engine.draw_sprite(game.background)
    engine.draw_circle(ball.circle)
    engine.draw_circle(game.ball2.circle)
    engine.draw_rigid_body_collider(game.test_block)
    engine.draw_rigid_body_collider(game.platform)

