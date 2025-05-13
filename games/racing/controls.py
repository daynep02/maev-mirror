import engine #type: ignore

class Controls:
    def __init__(self):
        self.font = engine.create_font("../games/racing/assets/MesloLGS_NF_Regular.ttf")

        w = engine.get_screen_width()
        h = engine.get_screen_height()
        engine.set_camera_size((w,h))

        self.title_text = engine.create_text(self.font)
        engine.set_text_size(self.title_text, 50)
        tx, ty = engine.get_text_position(self.title_text)
        engine.set_camera_position((tx, ty+200))

        self.options = []
        modi = 0
        for name in ["^ up", "< left", "> right"]:
            opt = engine.create_text(self.font)
            self.options.append(opt)
            engine.set_text(opt, name)
            engine.set_text_size(opt, 30)
            engine.set_text_color(opt, (255, 255, 255, 255))
            engine.set_text_position(opt, (tx/2,100+modi))
            modi+=50
        
    def update(self):
        
        if engine.key_is_pressed("ESCAPE"):
            return 2
        return 0
    
    def draw(self):
        engine.draw_text(self.title_text)
        for opt in self.options:
            engine.draw_text(opt)
