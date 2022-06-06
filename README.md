# BetterTextDraw
A simple console graphics command line utility for linux, mac and windows.


How to use it:

Syntax:
btd {width of canvass} {height of canvass} < commmand_input_file

Sample:
btd 130 30 < sample.txt

Commands:

{#} Means number
{$} Means a charater

x{#}
Positions the invisible X pointer on the canvass.

y{#}
Positions the invisible Y pointer on the canvass.

ch{$}
Change the default character to write. Default is space.

col{#}
Change the default fore color of the canvass. Default is 7.
{#} Ranges from 0 - 7.

l{#} r{#} u{#} d{#} ul{#} ur{#} ll{#} lr{#}
Corresponds to draw default character with default color to the left, right, up, down, upper left, upper right, lower left, and lower right by {#} times. Also moves the invisible X, Y pointer {#} + 1 times.

ml{#} mr{#} mu{#} md{#} mul{#} mur{#} mll{#} mlr{#}
Corresponds to move direction of the pointer {#} + 1 times.

circ{#}
Draws a circle with radius{#}.

fil{#} (Not yet available as of this writing)
Fill all ' ' with the default ch and color.


