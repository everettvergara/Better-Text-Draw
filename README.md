# BetterTextDraw
A simple console graphics command line utility for linux, mac and windows.

How to use it:

```c++
/*

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

fi{#}
Fill all ' ' with the default ch and color.

t "Your text here"
Writes a text at the current position. Texts must be enclosed by "".

tcx "Your text here centered horizontally"
Writes a text at the current position of y but centered horizontally within the canvass.

tcy "Your text here centered vertically"
Writes a text at the current position of x but centered vertically within the canvass.

tcxy "Your text here centered horizontally vertically"
Writes a text at centered horizontally and vertically within the canvass.

q
quit the program.

Sample Commands:

mlr10
ch h col1 r1ur5u3ul1l1ll1d13r2ul3u2ur3r3lr2d4
ch e col2 lr1ur2r5ur2u1ul2l2ll2d4lr1r3
ch l col3 r3ur5u6ul1l1ll1d10lr1
ch ! col4 r3ur5u6ul1l1ll1d10lr1r3
ch o col5 r5ur1r1ur2u1u2ul2l3ll2d4lr2r2
ch . col0 r5ur2
ch w col6 u4d4lr2r1ur2u4d4lr2r1ur2u4d4lr2
ch o col7 r5ur1r1ur2u1u2ul2l3ll2d4lr2r2
ch r col3 r3ur5u3ul1l1ll1d1lr1r10ur1u1ul1l1ll1d7lr1
ch l col2 r3ur5u6ul1l1ll1d10lr1     
ch d col4 r7ur1r1ur2u1u2ul2l3ll2d4lr2r5u13
q

*/

```
![alt text](https://github.com/everettvergara/BetterTextDraw/blob/main/assets/btd.png)
