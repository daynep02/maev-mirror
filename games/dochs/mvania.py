import engine # type: ignore
import time
import math

class Player:
    def __init__(self):
        self.rb = engine.create_rigid_body((125,0),(25,25))
        print(f"creating player rigid: {self.rb}" )
        self.set_terminal_velo(0.0, 200.0)
        self.set_static(False)
        self.set_gravity(True)
    
    def set_gravity(self, x: bool) -> None:
        engine.set_rigid_body_gravity(self.rb, x)

    def set_static(self, x: bool) -> None:
        engine.set_rigid_body_static(self.rb, x)
    
    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.rb)

    def set_terminal_velo(self, x: float, y: float) -> None:
        engine.set_terminal_velo(self.rb, x, y)

    def movement(self) -> None:
        if engine.key_is_pressed("Up"):
            engine.apply_force(self.rb, 0.0, -2.0)
        if engine.key_is_pressed( "Down"):
            engine.apply_force(self.rb, 0.0, 1.0)
        if engine.key_is_pressed("Left"):
            engine.apply_force(self.rb,-1.0, 0.0)
        if engine.key_is_pressed("Right"):
            engine.apply_force(self.rb, 1.0, 0.0)
        
class Game:
    def __init__(self):

        self.player = Player()

        self.set_camera_size(600,400)

        #The platform to collide with
        self.platform = engine.create_rigid_body((0,300),(500,20))
        engine.set_rigid_body_static(self.platform,True)

        engine.set_gravity(0.0, 1.0)
    
    def set_camera_size(self, width, height):
        engine.set_camera_size((width,height))

def on_close():
    print("\"Window closed\", said the Python!")

game = None
first = True

def fun(lists, index=0, path=[], res=[]):  # function defination
    if index == len(lists): # base case 
        res.append(path[:])  
        return res
        
    for item in lists[index]: # recursive case 
        path.append(item)
        fun(lists, index + 1, path, res)
        path.pop()
    return res

a = [1, 3, 4]
b = [6, 7, 9]
c = [8, 10, 5]

d = [a, b, c]
result = fun(d) # function calling 
print(result)

# Key Functions for Game
def init():
    global game
    game = Game()
    engine.set_on_close(on_close)

def update():
    global game
    
    engine.set_camera_position(engine.get_rigid_body_position(game.player.rb))

    game.player.movement()


def draw():
    global game

    game.player.draw()
    engine.draw_rigid_body_collider(game.platform)

