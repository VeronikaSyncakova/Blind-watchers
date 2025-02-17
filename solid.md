 - Single Responsibility Principle:<br>
Although some of the classes in our game contain a lot of variables and such which were put in for the sake of time, Our game still follows the singles responsibility principle in many ways
One good example for instance is the "RenderObject" class, which is used to do all of the drawing in the game, it simply stores a pointer to the shapes that are needed to be drawn, itterates over them and draws them.
This is great for single responsibility because not only is the potential for changing the rendering code very easy, as it is in one simple class
but it also only handles the direct rendering of the objects, and nothing else.
Another good example is state / command machine contained in the pawn
This is a good example as it doesnt use much information and all it does is move the pawns sprite, even better than that it also uses DIP which i will explore in the DIP part.
Another one of the examples, of which we have many, is the vision cone.
The vision cone is a class solely comprised of its body, and some functions for moving it around.
this class follows many of the SOLID principles such as DIP and of course single responsibility, as all it knows about, is itself


```mermaid
---
Title: Two examples of SRP in vision cone and walking stick
---
classDiagram
    blindNpc *-- visionCone
    blindNpc *-- WalkingStick

    class WalkingStick{
	WalkingStick()
	~WalkingStick()

	void initialise(sf::Vector2f t_pos, float t_startAngle = 0.f)
	void rotate(float t_newRotation)
	void setPos(sf::Vector2f t_newPos)
	void update()

	std::shared_ptr<sf::RectangleShape> m_stick
	float m_rotateSpeed
	bool m_positive
	float m_setAngle
	float m_targetAngle
    }

    class blindNpc{
	blindNpc(npcData& t_characterData)
	~blindNpc()

	virtual void update()override

	void expire()override

	virtual void moveBody(sf::Vector2f const& t_moveVector)override

	virtual sf::FloatRect getBounds()override

	npcData getData()
	bool checkFoundPlayer(sf::FloatRect t_playerBounds)
	void rotate(float t_angle)override
	int getCurrentRoom()override

	void position(sf::Vector2f& t_position) override

	void writeYAML(YAML::Emitter& t_out) override

	void huntPlayer()

	void setPatrolPoints(npcData& t_characterData)

	std::shared_ptr<body> m_body
	float m_maxSpeed

	visionCone m_visionCone
	float m_cantFindPlayer

	WalkingStick m_stick
}

    class visionCone{

	visionCone(sf::Vector2f t_spawnPos, float t_len, float t_angle)
	void moveCone(sf::Vector2f t_newPosition)
	void setRotation(float t_angle)
	bool checkCollision(sf::FloatRect t_playerBounds)
	float getRotation()

	std::shared_ptr<sf::ConvexShape> m_cone 
}
```

 - Open/Closed Principle: <br>
Some of the main classes created in our game follows the open closed principle very well.
For instance the states class that the npcs and the player uses
This is easily extentible as you can easily add more states and more behaviours on how the enmy will move, but it must use the move function from the player, which just takes a displacement,
where then the pawn decides how to actually move and at what speed
Alot of the classes use the open closed principle when loading in from the yaml file
for instance the player uses the character selection screen, which is open for extension, by just adding the new type name to a switch, enum, and adding one to the amount variable, and adding the info into the yaml file, there is then a new player available for selection, without changing any complicated internal code for speed, size, sprint duration, sprint time and such.

```mermaid
---
Title: Example of open/closed principle for states
---
classDiagram
    Pawn *-- AbstractState
    NoneState <|-- AbstractState
    playerInputState <|-- AbstractState
    WanderState <|-- AbstractState
    PatrolState <|-- AbstractState
    SeekPlayer <|-- AbstractState

    class Pawn{
	Pawn()
	~Pawn()

	virtual void update() = 0
	virtual void moveBody(sf::Vector2f const& t_moveVector) = 0
	virtual void expire() = 0
    virtual sf::FloatRect getBounds() = 0
    virtual void position(sf::Vector2f& t_position)=0
	virtual void writeYAML(YAML::Emitter& t_out) = 0
	virtual int getCurrentRoom() = 0
    virtual void rotate(float t_angle) = 0


	bool getActive() 
	sf::Vector2f getPosition()
	std::vector<sf::Vector2f> getPatrolPoints() 
	State getState() 
	std::shared_ptr<AbstractState> getAbstractState()
	void applyDamage(int t_damageAmt)



    State m_currentState
	std::shared_ptr<AbstractState> m_state
	sf::Vector2f m_position
	float m_moveSpeed
	bool m_active
	std::vector<sf::Vector2f> m_patrolPoints
	int m_roomNumber
	int m_health
	int m_maxHealth
	sf::Texture m_bodyTexture
	std::shared_ptr<AnimatedSprite> m_bodySprite
    }

    class AbstractState{
	virtual void enter(std::shared_ptr<Pawn> t_pawn) = 0
	virtual void update(std::shared_ptr<Pawn> t_pawn) = 0
	virtual void exit(std::shared_ptr<Pawn> t_pawn) = 0
    }
    class NoneState{
	virtual void enter(std::shared_ptr<Pawn> t_pawn)
	virtual void update(std::shared_ptr<Pawn> t_pawn)
	virtual void exit(std::shared_ptr<Pawn> t_pawn)
    }

    class playerInputState{
	virtual void enter(std::shared_ptr<Pawn> t_pawn)
	virtual void update(std::shared_ptr<Pawn> t_pawn)
	virtual void exit(std::shared_ptr<Pawn> t_pawn)
    }

    class WanderState {
	virtual void enter(std::shared_ptr<Pawn> t_pawn)
	virtual void update(std::shared_ptr<Pawn> t_pawn)
	virtual void exit(std::shared_ptr<Pawn> t_pawn)

	void resetWanderPoint(std::shared_ptr<Pawn> t_pawn)

	float m_wanderRadius
	sf::Vector2f m_startPosition
	float m_wanderTimeLeft
	float m_wanderWait
	sf::Vector2f m_chosenDirection
    }

    class PatrolState{
	virtual void enter(std::shared_ptr<Pawn> t_pawn)
	virtual void update(std::shared_ptr<Pawn> t_pawn)
	virtual void exit(std::shared_ptr<Pawn> t_pawn)

	void skipPoint(std::shared_ptr<Pawn> t_pawn)

	int m_nextPoint
    }

    class SeekPlayer{
	virtual void enter(std::shared_ptr<Pawn> t_pawn)
	virtual void update(std::shared_ptr<Pawn> t_pawn)
	virtual void exit(std::shared_ptr<Pawn> t_pawn)

	void SetPlayer(sf::Vector2f t_playerPos)

	sf::Vector2f m_playerPos
    }

   
```

 - Dependency inversion Principle<br>
Alot of the classes in our game use this principle, but the best examples are the structs such as med body, 
this class uses a function called "uninitialise" to move it off screen(to hide the sprite), set active to false, and to move the collision bounds, so that instead of the gameplay class relying on the types and functions of the specific, rectangle shape, and the sprite.

```mermaid
---
Title: Dependency inversion in med body struct
---
classDiagram
    Medication *-- medBody
    GamePlay --|> Medication

    class GamePlay{

	GamePlay()
	~GamePlay()

	void resetLevel()override
	void events(sf::Event& t_event)override
	void update()override

	void processKeys(sf::Event& t_event)override
	void processMouse(sf::Event& t_event)override
	void initialiseRandom()

	std::vector<std::shared_ptr<Pawn>> m_pawns
	levelData m_level
	Medication m_meds

	std::shared_ptr<bar> m_medProgress
	std::shared_ptr<bar> m_stressMeter
	GameType m_currentGameMode

	BulletHolder m_bulletManager
	bool m_shooting
}

    class Medication{
	Medication()
	~Medication()

	void initialise(std::vector<MedData>& t_medData)
	void update()
	void updatePlayerPosition(sf::FloatRect t_playerBounds)
	bool checkInteract()
	void addMedication(MedData& t_data)
	void writeYAML(YAML::Emitter& t_out)
	bool erase(sf::Vector2f& t_mousePos)

	std::vector<medBody> m_meds
	sf::Texture m_medTexture

	sf::Texture m_pressButtonT
	std::shared_ptr<AnimatedSprite> m_pressButton
}

    class medBody{
	sf::Vector2f pos()
	sf::FloatRect bounds() 
	void uninitialise()

	std::shared_ptr<sf::Sprite> sprite

	std::shared_ptr<sf::RectangleShape> interactionBounds
	bool m_inBounds
}

```