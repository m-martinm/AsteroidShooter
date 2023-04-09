# AsteroidShooter
## TODO
- make the enemy class
- make the bullet class

## Improve
- add animation to the ship (simple gif)
- change the input detetction
	- https://stackoverflow.com/questions/53403266/sfml-pollevent-is-making-pauses-when-i-continuesly-press-keys


## Physik
- pressing button -> giving it a force
	- only if a button is pressed or released
	- there is a breaking force
		- it takes away force every second, but if the force is null then nothing
- positon = v * t, v = a * t, a = f/m
	- we have to calculate it every second