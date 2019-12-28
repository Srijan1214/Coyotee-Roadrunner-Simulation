# Coyotee-Roadrunner-Simulation

A two-dimensional predator-prey simulation.

For the simulation, I have the prey be some number (r) of roadrunners and the
predators are some number of coyotes (c). The agents (both prey and predator) exist in a
bound n x m uniformly space grid environment. Only one agent may occupy a cell of the
grid at any given time. The environment is bounded, thus agents cannot move outside of
the grid area.
For every time step in the simulation, every agent will make an action based on its current
state, and the states of various cells near the agent.

Roadrunners
● Move If no coyote is in an adjacent cell, move in a random direction by 1 cell. If
there is at least one adjacent coyote, move in a direction (1 to 2 cells) that will
minimize the number of coyotes adjacent to the agent in the next time step.
● Breed If at the end of a 3rd consecutive time step, there is a free adjacent cell, a new
roadrunner is created.
● Die If at any time a coyote occupies the same cell as a roadrunner, the roadrunner
dies.

Coyotees
● Move Every time step, if there is an adjacent roadrunner, then move to that cell. If
that cell is still occupied after the move, then eat the roadrunner. If no roadrunner is
in an adjacent cell, move in a random direction by 1 cell.
● Breed After the 8th time step, spawn a new coyote as we do roadrunners.
● Die If a coyote goes 4 steps without eating a roadrunner, it dies before the start of
the next step.

This project demonstrates the use of Object-oriented Design principles and the UML diagram are in the files.
