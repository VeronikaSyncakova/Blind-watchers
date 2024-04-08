User Stories:
 - As a player, I want to see the NPCs vision cone, so I know the area to avoid. (David)
 - As a Player, I want the NPCs to path around the level so that the gameplay can be more difficult.(David)
 - As a Designer, I want to be able to edit the level, so I can tweak gameplay easily.(David)
 - As a Designer, I want to edit the NPC movement, so the gameplay is more engaging.(David)

 - As a player, I want to collect medication so I can give it to the patients. (Veronika)
 - As a player, I want to control the movement of my character to avoid patients when I don’t have any medication on me. (Veronika)
 - As a player, I want to see my patience meter so I can avoid losing the game. (Veronika)
 - As a player,  I want to clearly see the door so I know where I can exit the room and enter a new one. (Veronika)
 - As a player, I want to see if the medication has been spawned so I know which ones to collect at first. (Veronika) 

 ![image](./Misc%20Images/CRC%20cards.jpg)

 classDiagram
    class Player{
    }
    class Movement{
      +Vector2f PlayerPosition
      +getInput()
      +movePlayer()
    }
    class Inventory{
      +Pill currentPill
      +handlePickup()
    }
    class PatienceMeter{
        +currentPatience
        +decreasePatience()
        +increasePatience()
    }
    class VisionCone{
        +cone
        +collideWithPlayer()
        +sweepCone()
    }
    class NPC{
        +Pill requestedPill
        +takePill()
    }
    class NPCpathing{
        +pathingType
        +choosePath()
        +moveNpcOnPath()
        +FollowPlayer()
    }
    class PillArrow{
        +PillPosition
        +updateArrowTowardsPill()
    }
    class Game{
        +update()
        +render()
        +Events()
    }
    class Room {
        +roomShape
        +checkWallCollision()
    }
    class Pill{
        +pillType
        +Position
    }
    class door{
        +Position
        +Size
        +MoveToNextRoom()
    }
    class LevelEditor{
        +userInput()
        +saveArrangement()
    }
    class Wall{
        +Position
        +Size
    }