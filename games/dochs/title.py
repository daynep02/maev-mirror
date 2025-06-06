import engine #type: ignore

class Title:
    def __init__(self,version):
        self.version = version
        match(self.version):
            case 0:
                title = "Shape Arena"
                names = ["Play", "Controls", "Quit"]
            case 1:
                title = "Game Over :("
                names = ["Try Again", "Back to Menu"]
            case 2:
                title = "You Won!"
                names = ["Back to Menu"]

        self.font = engine.create_font("../games/dochs/assets/comic.ttf")
        self.select_color = (255,255,255,255)
        self.deselect_color = (255,255,255,128)

        w = engine.get_screen_width()
        h = engine.get_screen_height()
        engine.set_camera_size((w,h))

        self.title_text = engine.create_text(self.font)
        engine.set_text(self.title_text, title)
        engine.set_text_size(self.title_text, 50)
        engine.set_text_color(self.title_text, (255,0,0,255))
        tx, ty = engine.get_text_position(self.title_text)
        engine.set_camera_position((tx, ty+200))

        self.options = []
        modi = 0
        for name in names:
            opt = engine.create_text(self.font)
            self.options.append(opt)
            engine.set_text(opt, name)
            engine.set_text_size(opt, 30)
            engine.set_text_color(opt, self.deselect_color)
            engine.set_text_position(opt, (tx/2,100+modi))
            modi+=50
        
        self.state = 0
        self.state_cooldown = 0

    def move_states(self):
        if engine.current_time()-self.state_cooldown < 0.20:
            return

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

    def update_title(self):
        w = engine.get_screen_width()
        h = engine.get_screen_height()
        engine.set_camera_size((w,h))
        tx, ty = engine.get_text_position(self.title_text)
        engine.set_camera_position((tx, ty+200))

        self.move_states()

        for i in range(0,len(self.options)):
            if i == self.state:
                engine.set_text_color(self.options[i],self.select_color)
            else:
                engine.set_text_color(self.options[i],self.deselect_color)
    
    def draw_title(self):
        engine.draw_text(self.title_text)
        for opt in self.options:
            engine.draw_text(opt)
