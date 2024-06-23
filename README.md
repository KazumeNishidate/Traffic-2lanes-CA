Traffic flow CA with two lanes.

We can develop our own two lanes traffic flow CA based on the one-lane
traffic flow CA. In Japan, cars usually move in the left lane.

If a vehicle is ahead of it and has some spaces in the right lane, it
will change the lane to the right with a probability of p_l. If a
vehicle is ahead of it and has some spaces in the left lane, it will
change the lane to the left with a probability of p_r, which we put as
p_l < p_r.

When a vehicle in the left/right lane detects ample space ahead, it
showcases its remarkable adaptability by accelerating, a behavior that
is intricately influenced by the available space. When a vehicle in
the left/right lane identifies poor space ahead, it demonstrates its
adaptability by decelerating its speed.

We introduce randomness: vehicles slow down the speed with the
probability of ps.

All vehicles run forward by their speed value v in one update CA step.


kazume.nishidate@gmail.com