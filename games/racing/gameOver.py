
import engine #type: ignore
from state import *

class GameOver:

    def __init__(self, camera):
        self.camera = camera

        self.font = engine.create_font("../games/racing/assets/MesloLGS_NF_Regular.ttf")
        self.select_color = (255,255,255,255)
        self.deselect_color = (255,255,255,128)
        self.state_cooldown = 0
        self.state = 0

    def start(self):
        w = engine.get_screen_width()
        h = engine.get_screen_height()

        engine.set_camera_size((w,h))

        self.title_text = engine.create_text(self.font)
        engine.set_text(self.title_text, "Game Over!")

        engine.set_text_size(self.title_text, 50)
        engine.set_text_color(self.title_text, (255,0,0,255))


        tx, ty = engine.get_text_position(self.title_text)

        self.make_play_again(tx, ty)

        self.camera.set_position((tx, ty+200))

        self.options = []

        modi = 0

        for name in ["Yes", "No"]:

            opt = engine.create_text(self.font)
            self.options.append(opt)
            engine.set_text(opt, name)
            engine.set_text_size(opt, 30)
            engine.set_text_color(opt, self.deselect_color)
            engine.set_text_position(opt, (tx/2,150+modi))
            modi+=50

        self.state = 0
        self.state_cooldown = 0

        pass

    def make_play_again(self, tx, ty):
        self.play_again = engine.create_text(self.font)
        engine.set_text(self.play_again, "Play Again?")
        engine.set_text_position(self.play_again, (tx / 2, ty + 50))
        engine.set_text_size(self.title_text, 50)
        engine.set_text_color(self.title_text, (255,0,0,255))

    def move_states(self):
        if engine.current_time()-self.state_cooldown < 0.20:
            return NO_CHANGE

        if engine.key_is_pressed("Up"):
            self.state-=1
            self.state_cooldown = engine.current_time()

        elif engine.key_is_pressed("Down"):
            self.state+=1
            self.state_cooldown = engine.current_time()
        
        if self.state >= len(self.options):
            self.state = 0

        if self.state < 0:
            self.state = len(self.options)-1

        if self.state == 0 and engine.key_is_pressed("ENTER"):
            return TITLE

        if self.state == 1 and engine.key_is_pressed("ENTER"):
            return QUIT

        return NO_CHANGE


    def update(self):
        val = self.move_states()
        for i in range(0,len(self.options)):
            if i == self.state:
                engine.set_text_color(self.options[i],self.select_color)
            else:
                engine.set_text_color(self.options[i],self.deselect_color)

        return val
    
    def draw(self):
        engine.draw_text(self.title_text)
        engine.draw_text(self.play_again)
        for opt in self.options:
            engine.draw_text(opt)

