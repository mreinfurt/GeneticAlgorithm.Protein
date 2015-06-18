GA
==

Genetic algorithm developed for the 2D-HP protein folding model. The application creates an initial population of conformaions (a protein folding) and then applies selection, mutation and crossover.

<p align="center">
  <img src="https://raw.githubusercontent.com/mreinfurt/GeneticAlgorithm/master/information/preview.png">
</p>

# General concept
- A conformation contains elements
- An element is either hydrophile or not
- An element has a position relative to the conformation
- An element has a direction pointing towards the successor's position (Left, Right, Straight)

# Selection
The following selection methods are supported: 
- Fitness-proportional
- Probability-based tournament
- Single Elimination tournament
- "Best wins" tournament
The tournament size can be specified.
