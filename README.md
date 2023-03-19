# 2d-game-using-cpp
## Introduction
The objective of the project is to develop a 2D  game that illustrates the feature of
game architecture, computer graphics, and basic logic.
These are the three main criteria for this project:
- 2D Game System design. Characters are assigned to have a basic ability.
- 2D graphics representation. 2D graphics are a feature of this game. In addition, the technique used in the game industry is greatly demonstrated.
- Developing a 2D game using a library of C++. Provide some background information on OpenGL and why you chose to use it. Open Graphics Library (OpenGL) is a cross-platform, hardware-accelerated, language-independent, industrial standard API for producing 3D (including 2D) graphics. OpenGL is the software interface to graphics hardware. In other words, OpenGL graphic rendering commands issued by your applications could be directed to the graphic hardware and accelerated.

We have chosen to use OpenGL because: it's commonly used to make UI animations more responsive or handle embedded video or draw vector graphics 
It's straightforward to use. 
It is becoming increasingly clear that understanding how to leverage its incredible power is a must for developers.
Describe the overall structure of the game, including the graphics and gameplay.

When either agent is destroyed by an enemy, the battle is over. When an agent is struck by an enemy, it is destroyed. To defend themselves from the enemy, the agents can be moved up and down or left and right. 
The score is determined by the number of times the "animate" function is invoked. When the game is over, the tally will be displayed on the console.

## User Manual
The game will end when both agents will get destroyed by any enemy. Agents and enemies are remarked as green circles and red circles. An agent gets destroyed when it gets hit by an enemy. 
The movement path of the enemy is given in the diagram. The agents can be moved up and down or left and right to protect them from the enemy. 

The score is the number of times the “animate” function gets called. When the game finishes, the score will be shown on the console.
Agent movement: Agent A Moves up, down, left, and right on the corresponding key press u,d,l,r
Agent B Moves up, and down if we press the arrow key.

## Conclusion
The main point of the report is to give a clear idea of the whole project and its structure.
Challenges we had to face:
- Calculating the movements quadrant-wise.
- The custom movement of enemy 
- Logically calculating the distance between agent and enemy. 
After all, I've reached a point which gave some confidence that I can code some logical tasks for the GLUT project. I'm interested in this kind of development if I get an opportunity 

