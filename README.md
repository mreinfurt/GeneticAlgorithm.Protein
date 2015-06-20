Genetic Algorithm (2D-HP Protein Folding)
==

Genetic algorithm developed for the 2D-HP protein folding model. The application creates an initial population of conformations (a protein folding) and then applies selection, mutation and crossover.

<p align="center">
  <img src="https://raw.githubusercontent.com/mreinfurt/GeneticAlgorithm/master/information/preview.png">
</p>

# Installation
The repository contains a Visual Studio 2013 project which includes all dependencies and can be run straight away. 

# General concept
- A conformation contains elements
- An element is either hydrophile or not
- An element has a position relative to the conformation
- An element has a direction pointing towards the successor's position (Left, Right, Straight)

## Selection
The following selection methods are supported: 
- Fitness-proportional
- Probability-based tournament
- Single Elimination tournament
- "Best wins" tournament

Tournament sizes (number of conformations) can be specified.

## Logging
The algorithm automatically logs a runthrough to the ```average.txt``` file which contains the average energy of one population for each generation. This can be used to generate graphs like this (average energy vertical, generation number horizontal):
<p align="center">
  <img src="https://raw.githubusercontent.com/mreinfurt/GeneticAlgorithm/master/information/seq50.png">
</p>

Additionally, the functions ```testTournaments``` and ```testRates``` are available, both of which use a set of parameters, do one runthrough of the algorithm. Then they change the parameters by a little bit and do another runthrough. This can be done for as many runthroughs as wanted. This way it's easy to analyze how the parameters affect the results.

## Example
The easiest way to adjust the algorithm is by playing around with the parameters from the ```Algorithm::setUp``` method:
```setUp(int maxGeneration, int populationSize, std::string &chain, float mutationRate, float crossoverRate, Selection *selection, std::string& file = (std::string)"average.txt");```

- *maxGeneration:* How many generations to iterate through
- *populationSize:* How many individuals a generation has
- *chain:* What benchmark sequence to use (SEQ20, SEQ36…)
- *mutationRate:* How many individuals are being mutated every generation (in %)
- *crossoverRate:* How many individuals are being crossovered every generation (in %)
- *selection:* What selection method to use
- *file:* Logfile for saving the values of each generation

An example call would be ```setUp(250, 5000, SEQ20, 0.08, 0.30f, new TournamentSelection(2.0, 80.0f));```
