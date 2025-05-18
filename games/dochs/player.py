import engine # type: ignore

class Player:
    # movement variables
    slide_left = 1
    slide_right = 1
    slide_time = 0.0
    grounded = False
    coyote_time = 0.0
    jumping = False
    jump_time = 0.0
    knockback = (0.0,0.0)
    kb_time = 0.0
    kb_decay_rate = 0.5

    # attack variables
    attacking = False
    attack_time = 0.0
    attack_speed = 0.25
    attack_direction = (0,0)
    hitbox = None
    hitboxes = {"up": -1,"down":-1,"left":-1,"right":-1}
    boxes_hit = []

    # game variables
    hp = 10
    damage = 2
    face_direction = 1
    invincible = False
    invincible_time = 0.0

    def __init__(self, callback):
        self.rb = engine.create_rigid_body((125,50),(25,25))
        print(f"creating player rigid: {self.rb}" )
        engine.set_terminal_velo(self.rb, 0.0, 400.0)
        engine.set_rigid_body_static(self.rb, False)
        engine.set_rigid_body_gravity(self.rb, True)

        self.hit_callback = callback
        player_position = engine.get_rigid_body_position(self.rb)

        self.hitboxes["up"] = engine.create_box_collider(player_position,(35,45))
        self.hitboxes["down"] = engine.create_box_collider(player_position,(25,45))
        self.hitboxes["left"] = engine.create_box_collider(player_position,(45,35))
        self.hitboxes["right"] = engine.create_box_collider(player_position,(45,35))
        for key in self.hitboxes.keys():
            engine.set_box_trigger(self.hitboxes[key], False)
            engine.set_box_callback(self.hitboxes[key], self.hit_callback)

        self.speed = 200.0
        self.jump_speed = -480.0
    
    def draw(self) -> None:
        engine.draw_rigid_body_collider(self.rb)
        for key in self.hitboxes.keys():
            if engine.get_box_trigger(self.hitboxes[key]):
                engine.draw_box(self.hitboxes[key])

    def launch(self,lx,ly):
        self.knockback = (lx,ly)
        self.kb_time = engine.current_time()
        engine.set_rigid_body_velocity(self.rb, self.knockback)
        self.jumping = False

    def take_damage(self,amount, lx, ly):
        if self.invincible:
            return
        self.hp -= amount
        print(f"Player: took {amount} damage! Now at {self.hp} HP.")
        self.launch(lx,ly)

        self.invincible = True
        self.invincible_time = engine.current_time()

    def update(self):
        
        self.movement()
        self.attack()

        px, py = engine.get_rigid_body_position(self.rb)
        engine.set_box_position(self.hitboxes["up"], (px-5,py-45))
        engine.set_box_position(self.hitboxes["down"], (px,py+25))
        engine.set_box_position(self.hitboxes["left"], (px-45,py-5))
        engine.set_box_position(self.hitboxes["right"], (px+25,py-5))


    def attack(self):
        #print("checking attack")
        if not self.attacking:
            # or engine.mouse_button_is_pressed("Left")
            if engine.key_is_pressed("E") or engine.mouse_button_is_pressed("Left")!=-1:
                # checking direction
                vertical = 0
                horizontal = 0
                if engine.key_is_pressed("Up") or engine.key_is_pressed("W"):
                    vertical += -1
                if engine.key_is_pressed("Down") or engine.key_is_pressed("S"):
                    vertical += 1
                if engine.key_is_pressed("Left") or engine.key_is_pressed("A"):
                    horizontal += -1
                if engine.key_is_pressed("Right") or engine.key_is_pressed("D"):
                    horizontal += 1
                # spawing hit
                if vertical == -1:
                    self.hitbox = "up"
                    self.attack_direction = (0,0)
                    #print("attacking up")
                elif vertical == 1:
                    self.hitbox = "down"
                    self.attack_direction = (0,1)
                    #print("attacking down")
                elif horizontal == -1:
                    self.hitbox = "left"
                    self.attack_direction = (-1,0)
                    #print("attacking left")
                elif horizontal == 1:
                    self.hitbox = "right"
                    self.attack_direction = (1,0)
                    #print("attacking right")
                else:
                    if self.face_direction == -1:
                        self.hitbox = "left"
                        self.attack_direction = (-1,0)
                    else:
                        self.hitbox = "right"
                        self.attack_direction = (1,0)
                    #print("attacking default: ",self.hitbox)
                
                # setting attack cooldown
                engine.set_box_trigger(self.hitboxes[self.hitbox], True)
                self.attack_time = engine.current_time()
                self.attacking = True
        elif engine.current_time()-self.attack_time > self.attack_speed:
            self.attacking = False
            self.boxes_hit = []
        else:
            if self.hitbox != None:
                # update hitbox
                if engine.current_time()-self.attack_time > self.attack_speed-0.1:
                    # hitbox end
                    engine.set_box_trigger(self.hitboxes[self.hitbox], False)
                    self.hitbox = None

    def movement(self) -> None:
        # jumping logic
        #print(engine.delta_time())
        velocity = engine.get_rigid_body_velocity(self.rb)
        if self.jumping:
            if engine.current_time()-self.jump_time > 0.3:
                self.jumping = False
            elif engine.key_is_pressed(" "):
                engine.apply_force(self.rb, 0.0, self.jump_speed*engine.delta_time())
            else:

                engine.set_rigid_body_velocity(self.rb, (velocity[0],10.0))
                self.jumping = False

        if engine.key_is_pressed(" ") and not self.jumping and (self.grounded or engine.current_time()-self.coyote_time<0.15):
            engine.set_rigid_body_velocity(self.rb, (velocity[0], self.jump_speed))
            self.jumping = True
            self.grounded = False
            self.jump_time = engine.current_time()

        # decay knockback
        velocity = engine.get_rigid_body_velocity(self.rb)
        decay_mult = 1.0-((engine.current_time()-self.kb_time)/self.kb_decay_rate)
        if engine.current_time()-self.kb_time < self.kb_decay_rate:
            kbx = self.knockback[0]*decay_mult
            kby = velocity[1]
            engine.set_rigid_body_velocity(self.rb, (kbx, kby))

        # normal logic
        
        velocity = engine.get_rigid_body_velocity(self.rb)
        direction = 0
        if engine.key_is_pressed("Left") or engine.key_is_pressed("A"):
            direction += -1*self.slide_left
        if engine.key_is_pressed("Right") or engine.key_is_pressed("D"):
            direction += 1*self.slide_right
        #print(direction)
        if direction != 0:
            self.face_direction = direction

        if velocity[0] < self.speed + 10.0 and velocity[0] > -self.speed - 10.0:
            engine.set_rigid_body_velocity(self.rb, (self.speed*direction,velocity[1]))
        else:
            pass
            #engine.apply_force(self.rb, 10.0*direction,0.0)
            #print("Shouldn't be called")

        if self.grounded:
            self.coyote_time = engine.current_time()
            self.grounded = False
        
        if engine.current_time()-self.slide_time>0.30:
            self.slide_left = 1
            self.slide_right = 1
            self.slide_time = 0.0
        
        if engine.current_time()-self.invincible_time>1 and self.invincible:
            self.invincible_time = 0.0
            self.invincible = False
